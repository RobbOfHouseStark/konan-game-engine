#ifndef KGE_ECS_COMPONENT_ITERABLE_HPP
#define KGE_ECS_COMPONENT_ITERABLE_HPP

#include <coroutine>
#include <optional>

namespace konan::ecs {
    template <typename T>
    struct ComponentGenerator {
        struct promise_type;
        using handle_type = std::coroutine_handle<promise_type>;
        struct promise_type {
            T* value_;

            ComponentGenerator<T> get_return_object() {
                return ComponentGenerator<T>(handle_type::from_promise(*this));
            }

            std::suspend_always yield_value(T& from) {
                value_ = &from;
                return {};
            }

            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            void unhandled_exception() {}
            void return_void() {}
        };

        ComponentGenerator(handle_type handle)
            : handle_ { handle } {}

        ComponentGenerator(ComponentGenerator<T> const& rhs)
            : handle_ { rhs.handle_ } {
            rhs.should_be_destroyed_ = false;
        }

        ~ComponentGenerator() {
            if (should_be_destroyed_)
                handle_.destroy();
        }

        bool try_yield_value() {
            fill();
            return !handle_.done();
        }

        T& yielded_value() {
            fill();
            full_ = false;
            return *handle_.promise().value_;
        }

    private:
        void fill() {
            if (!full_) {
                handle_.resume();
                full_ = true;
            }
        }

    private:
        handle_type handle_;
        mutable bool should_be_destroyed_ { true };
        bool full_ {};
    };

    template <typename T>
    struct ComponentIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = value_type*;
        using reference = value_type&;

    public:
        ComponentIterator() = default;

        explicit ComponentIterator(ComponentGenerator<T> const& coroutine)
            : coroutine_ { coroutine } {}

        reference operator*() {
            return coroutine_.value().yielded_value();
        };

        ComponentIterator<T>& operator++() { return *this; }
        ComponentIterator<T> operator++(int) { return *this; }

        friend bool operator==(ComponentIterator<T>& lhs,
                               ComponentIterator<T>&)
        { return !(lhs.coroutine_.value().try_yield_value()); }
        friend bool operator!=(ComponentIterator<T>& lhs,
                               ComponentIterator<T>&)
        { return lhs.coroutine_.value().try_yield_value(); }

    private:
        std::optional<ComponentGenerator<T>> coroutine_ {};
    };

    template <typename T>
    struct ComponentIterable {
        explicit ComponentIterable(ComponentGenerator<T> const& coroutine)
            : coroutine_ { coroutine } {}

        auto begin() {
            return ComponentIterator<T>(coroutine_);
        }

        auto end() {
            return ComponentIterator<T>();
        }

    private:
        ComponentGenerator<T> coroutine_;
    };
}

#endif  // KGE_ECS_COMPONENT_ITERABLE_HPP
