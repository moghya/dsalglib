#ifndef DSALGLIB_UNIQUE_PTR_H
#define DSALGLIB_UNIQUE_PTR_H

#include "../alginc.h"

namespace dsa {

template <class T>
class unique_ptr {
public:
    unique_ptr(T* ptr = nullptr) : ptr_(ptr) {}

    ~unique_ptr() {
        delete ptr_;
    }

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& rhs) : ptr_(rhs.ptr_) {
        rhs.ptr_ = nullptr;
    }

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr& operator=(unique_ptr&& rhs) {
        // calling delete on nullptr is not an error
        delete ptr_;
        ptr_ = rhs.ptr_;
        rhs.ptr_ = nullptr;
        return *this;
    }

    T* get() {
        return ptr_;
    }

    const T* get() const {
        return ptr_;
    }

    T& operator*() {
        return *ptr_;
    }
    const T& operator*() const {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }
    const T* operator->() const {
        return ptr_;
    }

    operator bool() const {
        return ptr_ != nullptr;
    }

private:
    T* ptr_;
};

template <class T, class... Args>
unique_ptr<T> make_unique(Args... args) {
    return unique_ptr<T>(new T(rvalue_cast(args)...));
}

} // namespace dsa

#endif // DSALGLIB_UNIQUE_PTR_H
