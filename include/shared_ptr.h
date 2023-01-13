#ifndef MP_CPP_HW1_SHARED_PTR
#define MP_CPP_HW1_SHARED_PTR

#include <cstddef>  // std::size_t

namespace smart_pointer {
    template<typename, typename = void>
    constexpr bool is_type_complete_v = false;

    template<typename T>
    constexpr bool is_type_complete_v
            <T, std::void_t<decltype(sizeof(T))>> = true;

    template<typename T>
    class shared_ptr {
        using element_type = std::remove_reference_t<std::remove_extent_t<T>>;
    public:
        // Constructs an empty shared_ptr
        constexpr shared_ptr() noexcept;

        // Constructs another empty shared_ptr
        constexpr explicit shared_ptr(std::nullptr_t) noexcept;

        // Construct a shared_ptr that manages the given object or array
        template<typename Y>
            requires (std::is_array_v<T> && (std::is_convertible_v<Y(*)[], T *> ||
                                            std::is_convertible_v<Y(*)[sizeof(T) /
                                                                        sizeof(std::remove_extent_t<T>)], T *>) ||
                     !std::is_array_v<T> && std::is_convertible_v<Y *, T *>)
        explicit shared_ptr(Y *obj);

        // Copy constructor
        shared_ptr(const shared_ptr &other);

        // Move constructor
        shared_ptr(shared_ptr &&other) noexcept;

        // Destructor
        ~shared_ptr();

        // Copy assignment operator
        shared_ptr &operator=(const shared_ptr &other);

        // Move assignment operator
        shared_ptr &operator=(shared_ptr &&other) noexcept;

        // Dereference operator
        element_type &operator*() const;

        // Boolean conversion operator
        explicit operator bool() const noexcept {
            return obj_ != nullptr;
        };

        // Member access operator
        T *operator->() const requires (!std::is_array_v<T>) {
            return obj_;
        }

        // Index operator for array types
        element_type &operator[](std::size_t idx) const requires std::is_array_v<T> {
            return obj_[idx];
        }

        // Get the number of owners of the managed object
        [[nodiscard]] std::size_t use_count() const;

        // Release ownership of the managed object
        void reset() requires (!std::is_array_v<T>);

        // Release ownership of the managed array
        void reset() requires std::is_array_v<T>;

        // Release ownership of the managed object and take ownership of the given object
        void reset(std::remove_extent_t<T> *obj);

        // Get a raw pointer to the managed object
        element_type *get() const;

    private:
        element_type *obj_;
        std::size_t *ref_count_;

        void release() noexcept requires std::is_array_v<T>;

        void release() noexcept requires (!std::is_array_v<T>);
    };

    template<typename T>
    void shared_ptr<T>::reset(std::remove_extent_t<T> *obj) {
        if (obj_ == obj) {
            return;
        }
        release();
        obj_ = obj;
        ref_count_ = new std::size_t(1);
    }

    template<typename T>
    void shared_ptr<T>::release() noexcept requires (!std::is_array_v<T>) {
        if (!ref_count_) {
            return;
        }
        if (*ref_count_ > 0) {
            --*ref_count_;
        }
        if (*ref_count_ == 0) {
            delete obj_;
            obj_ = nullptr;
            delete ref_count_;
            ref_count_ = nullptr;
        }
    }

    template<typename T>
    void shared_ptr<T>::release() noexcept requires std::is_array_v<T> {
        if (!ref_count_) {
            return;
        }
        if (*ref_count_ > 0) {
            --*ref_count_;
        }
        if (*ref_count_ == 0) {
            delete[] obj_;
            obj_ = nullptr;
            delete ref_count_;
            ref_count_ = nullptr;
        }
    }

    template<typename T>
    constexpr shared_ptr<T>::shared_ptr(std::nullptr_t) noexcept : obj_(nullptr), ref_count_(new std::size_t(0)) {}

    template<typename T>
    constexpr shared_ptr<T>::shared_ptr() noexcept : obj_(nullptr), ref_count_(new std::size_t(0)) {}

    template<typename T>
    template<typename Y>
        requires (std::is_array_v<T> && (std::is_convertible_v<Y(*)[], T *> ||
                                        std::is_convertible_v<Y(*)[sizeof(T) /
                                                                    sizeof(std::remove_extent_t<T>)], T *>) ||
                 !std::is_array_v<T> && std::is_convertible_v<Y *, T *>)
    shared_ptr<T>::shared_ptr(Y *obj) : obj_(obj), ref_count_(new std::size_t(1)) {}

    template<typename T>
    shared_ptr<T>::shared_ptr(const shared_ptr &other) : obj_(other.obj_) {
        if (obj_) {
            ref_count_ = other.ref_count_;
            ++*ref_count_;
        } else {
            ref_count_ = new std::size_t(0);
        }
    }

    template<typename T>
    shared_ptr<T>::shared_ptr(shared_ptr &&other) noexcept : obj_(other.obj_), ref_count_(other.ref_count_) {
        other.obj_ = nullptr;
        other.ref_count_ = nullptr;
    }

    template<typename T>
    shared_ptr<T>::~shared_ptr() {
        release();
        if (ref_count_ && *ref_count_ == 0) {
            delete ref_count_;
        }
    }

    template<typename T>
    shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &other) {
        if (this != &other) {
            release();
            obj_ = other.obj_;
            if (obj_) {
                ref_count_ = other.ref_count_;
                ++*ref_count_;
            } else {
                ref_count_ = new std::size_t(0);
            }
        }
        return *this;
    }

    template<typename T>
    shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&other) noexcept {
        if (this != &other) {
            release();
            obj_ = other.obj_;
            ref_count_ = other.ref_count_;
            other.obj_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

    template<typename T>
    shared_ptr<T>::element_type &shared_ptr<T>::operator*() const {
        return *obj_;
    }

    template<typename T>
    std::size_t shared_ptr<T>::use_count() const {
        return *ref_count_;
    }

    template<typename T>
    void shared_ptr<T>::reset() requires (!std::is_array_v<T>) {
        if (ref_count_ && *ref_count_ == 1) {
            delete obj_;
        }
        obj_ = nullptr;
        --*ref_count_;
        if (*ref_count_ == 0) {
            return;
        }
        ref_count_ = new std::size_t(0);
    }

    template<typename T>
    void shared_ptr<T>::reset() requires std::is_array_v<T> {
        if (ref_count_ && *ref_count_ == 1) {
            delete[] obj_;
        }
        obj_ = nullptr;
        --*ref_count_;
        if (*ref_count_ == 0) {
            return;
        }
        ref_count_ = new std::size_t(0);
    }

    template<typename T>
    shared_ptr<T>::element_type *shared_ptr<T>::get() const {
        return obj_;
    }

    // make_shared

    template<typename T, typename... Args>
    shared_ptr<T> make_shared(Args &&... args) requires (!std::is_array_v<T>) {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<typename T>
    shared_ptr<T> make_shared(std::size_t N) requires std::is_array_v<T> {
        return shared_ptr<T>(new std::remove_extent_t<T>[N]);
    }

    template<typename T>
    shared_ptr<T> make_shared() requires std::is_array_v<T> && is_type_complete_v<T> {
        return shared_ptr<T>(new T);
    }

    template<typename T>
        requires (std::is_array_v<T> && !is_type_complete_v<T> && std::is_array_v<std::remove_extent_t<T>>)
    shared_ptr<T> make_shared(std::size_t N, const std::remove_extent_t<T> &u) {
        auto array = new std::remove_extent_t<T>[N];
        using elementary_type = std::remove_all_extents_t<T>;
        for (std::size_t i = 0; i < N; ++i) {
            auto array_1d = reinterpret_cast<elementary_type *>(array[i]);
            for (std::size_t j = 0; j < sizeof(std::remove_extent_t<T>) / sizeof(elementary_type); ++j) {
                auto u_1d = reinterpret_cast<const elementary_type *>(u);
                array_1d[j] = u_1d[j];
            }
        }
        return shared_ptr<T>(array);
    }

    template<typename T>
        requires (std::is_array_v<T> && !is_type_complete_v<T> && !std::is_array_v<std::remove_extent_t<T>>)
    shared_ptr<T> make_shared(std::size_t N, const std::remove_extent_t<T> &u) {
        auto array = new std::remove_extent_t<T>[N];
        for (std::size_t i = 0; i < N; ++i) {
            array[i] = u;
        }
        return shared_ptr<T>(array);
    }

    template<typename T>
        requires std::is_array_v<T> && is_type_complete_v<T> && std::is_array_v<std::remove_extent_t<T>>
    shared_ptr<T> make_shared(const std::remove_extent_t<T> &u) {
        auto array = shared_ptr<T>(new T);
        using elementary_type = std::remove_all_extents_t<T>;
        for (std::size_t i = 0; i < std::extent_v<T>; ++i) {
            auto array_1d = reinterpret_cast<elementary_type *>(array[i]);
            for (std::size_t j = 0; j < sizeof(std::remove_extent_t<T>) / sizeof(elementary_type); ++j) {
                auto u_1d = reinterpret_cast<const elementary_type *>(u);
                array_1d[j] = u_1d[j];
            }
        }
        return array;
    }

    template<typename T>
        requires (std::is_array_v<T> && is_type_complete_v<T> && !std::is_array_v<std::remove_extent_t<T>>)
    shared_ptr<T> make_shared(const std::remove_extent_t<T> &u) {
        auto array = shared_ptr<T>(new T);
        for (std::size_t i = 0; i < std::extent_v<T>; ++i) {
            array[i] = u;
        }
        return array;
    }
}  // namespace smart_pointer

#endif  // MP_CPP_HW1_SHARED_PTR
