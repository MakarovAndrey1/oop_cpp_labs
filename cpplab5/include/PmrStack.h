#ifndef PMR_STACK_H
#define PMR_STACK_H

#include <vector>
#include <memory_resource>

template <typename T>
class PmrStack {
public:
    explicit PmrStack(std::pmr::memory_resource* mr)
        : alloc_(mr), data_(alloc_) {}

    void push(const T& value) { data_.push_back(value); }
    void push(T&& value) { data_.push_back(std::move(value)); }

    void pop() { if (!data_.empty()) data_.pop_back(); }

    T& top() { return data_.back(); }
    const T& top() const { return data_.back(); }

    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }

    void clear() { data_.clear(); }

    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using iterator = typename std::vector<T, allocator_type>::iterator;
    using const_iterator = typename std::vector<T, allocator_type>::const_iterator;

    iterator begin() { return data_.begin(); }
    const_iterator begin() const { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator end() const { return data_.end(); }

private:
    allocator_type alloc_;
    std::vector<T, allocator_type> data_;
};

#endif // PMR_STACK_H