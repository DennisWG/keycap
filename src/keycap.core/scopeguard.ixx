module;

#include <deque>
#include <exception>
#include <functional>

export module keycap.core : scopeguard;

namespace keycap
{
    /// <summary>
    /// Copied from https://stackoverflow.com/a/28413370/13692001
    /// </summary>
    export class scope_guard
    {
      public:
        enum execution
        {
            always,
            no_exception,
            exception
        };

        scope_guard(scope_guard&&) = default;
        explicit scope_guard(execution policy = always)
          : policy_(policy)
        {
        }

        template <class Callable>
        scope_guard(Callable&& func, execution policy = always)
          : policy_(policy)
        {
            this->operator+=<Callable>(std::forward<Callable>(func));
        }

        template <class Callable>
        scope_guard& operator+=(Callable&& func)
        try
        {
            handlers_.emplace_front(std::forward<Callable>(func));
            return *this;
        }
        catch (...)
        {
            if (policy_ != no_exception)
                func();
            throw;
        }

        ~scope_guard()
        {
            int has_exceptions = std::uncaught_exceptions() > 0;
            if (policy_ == always || (has_exceptions == (policy_ == exception)))
            {
                for (auto&& f : handlers_)
                {
                    try
                    {
                        f(); // must not throw
                    }
                    catch (...)
                    {
                        // std::terminate(); ?
                    }
                }
            }
        }

        void dismiss() noexcept
        {
            handlers_.clear();
        }

      private:
        scope_guard(const scope_guard&) = delete;
        void operator=(const scope_guard&) = delete;

        std::deque<std::function<void()>> handlers_;
        execution policy_ = always;
    };
}
