module;

#ifdef _WIN32
#pragma warning(push, 1)
#endif
#include <backward.hpp>
#ifdef _WIN32
#pragma warning(pop)
#endif

#include <fmt/format.h>

#include <fstream>
#include <string>

export module keycap.core : error;

import : types;

namespace impl
{
    std::string generate_stack_trace();
}

namespace keycap
{
    /// <summary>
    /// A list of all possible error codes that may happen in an application
    /// </summary>
    export enum class error_code : u64 //
    {
        /// <summary>
        /// Some external api issued an error
        /// </summary>
        external_api_error,

        /// <summary>
        /// File could not be found
        /// </summary>
        bad_file_path,

        /// <summary>
        /// File content is bad (corrupt, not recognizable, etc.)
        /// </summary>
        bad_file_content,

        /// <summary>
        /// Not yet implemented
        /// </summary>
        not_implemented,

        /// <summary>
        /// The given argument was invalid
        /// </summary>
        invalid_argument,

        /// <summary>
        /// Some error in the programming logic
        /// </summary>
        logic_error,

        /// <summary>
        /// Buffer access caused an overflow (read too much!)
        /// </summary>
        buffer_overflow,
    };

    /// <summary>
    /// A list of modules. This maps to the C++ Modules
    /// </summary>
    export enum class module : u64 //
    {
        /// <summary>
        /// keycap.core
        /// </summary>
        core,

        /// <summary>
        /// keycap.window
        /// </summary>
        window,
    };

    /// <summary>
    /// An extensive exception providing ample information for error-reporting and debugging
    /// </summary>
    export struct exception
    {
        error_code error;
        keycap::module module;
        u64 fragment;
        u32 line_number;
        std::string error_message;
        std::string stack_trace;

        exception(error_code error, keycap::module module, u64 fragment, u32 line_number, std::string error_message)
          : error{error}
          , module{module}
          , fragment{fragment}
          , line_number{line_number}
          , error_message{std::move(error_message)}
          , stack_trace(impl::generate_stack_trace())
        {
        }

        std::string to_string(bool include_stacktrace = false) const
        {
            if (include_stacktrace)
            {
                return fmt::format("Error [{}-{}-{}-{}] \"{}\":\n{}", static_cast<u64>(error), static_cast<u64>(module),
                                   fragment, line_number, error_message, stack_trace);
            }
            else
            {
                return fmt::format("Error [{}-{}-{}-{}] \"{}\"", static_cast<u64>(error), static_cast<u64>(module),
                                   fragment, line_number, error_message);
            }
        }
    };
}

namespace impl
{
    std::string generate_lines(int num_lines, std::string_view filename, u32 line)
    {
        std::ifstream file(filename.data());
        if (!file)
            return "";

        std::string buffer;

        u32 i = 0;
        u32 begin_at_line = line - num_lines - 1;
        u32 end_at_line = line + num_lines + 2;

        for (std::string line_str; std::getline(file, line_str);)
        {
            ++i;
            if (i <= begin_at_line || i >= end_at_line)
                continue;

            char c = ' ';
            if (i == line)
            {
                c = '>';
            }
            buffer += fmt::format("   {} {}:    {}\n", c, i, line_str);
        }

        return buffer;
    }

    std::string generate_stack_trace()
    {
        backward::StackTrace st;
        backward::TraceResolver resolver;
        st.load_here();
        resolver.load_stacktrace(st);

        bool skip = true;

        std::string stack_trace_buffer;
        stack_trace_buffer.reserve(512);

        for (size_t i = st.size() - 1; i > 2; --i)
        {
            auto const trace = resolver.resolve(st[i]);

            if (trace.object_function == "main")
            {
                skip = false;
            }

            if (skip)
            {
                continue;
            }

            stack_trace_buffer += fmt::format("#{} at {} ({}:{})\n", i - 3, trace.object_function,
                                              trace.source.filename, trace.source.line);

            int lines_to_print = 0;
            if (i >= 4 && i <= 5)
                lines_to_print = 2;
            if (i == 3)
                lines_to_print = 5;

            if (lines_to_print > 0)
                stack_trace_buffer += generate_lines(lines_to_print, trace.source.filename, trace.source.line);
        }

        return stack_trace_buffer;
    }
}