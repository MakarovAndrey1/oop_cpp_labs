#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data_;
    size_t size_;
    size_t capacity_;
    
    static constexpr size_t INITIAL_CAPACITY = 10;
    static constexpr double GROWTH_FACTOR = 1.5;
    
    void resize(size_t new_capacity) {
        auto new_data = std::make_unique<T[]>(new_capacity);
        
        for (size_t i = 0; i < size_; ++i) {
            if constexpr (std::is_move_assignable_v<T>) {
                new_data[i] = std::move(data_[i]);
            } else {
                new_data[i] = data_[i];
            }
        }
        
        data_ = std::move(new_data);
        capacity_ = new_capacity;
    }
    
public:
    Array() : size_(0), capacity_(INITIAL_CAPACITY) {
        data_ = std::make_unique<T[]>(capacity_);
    }
    
    explicit Array(size_t initial_capacity) : size_(0), capacity_(initial_capacity) {
        data_ = std::make_unique<T[]>(capacity_);
    }
    
    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::make_unique<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : data_(std::move(other.data_)), 
          size_(other.size_), 
          capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }
    
    ~Array() = default;
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            auto new_data = std::make_unique<T[]>(other.capacity_);
            for (size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
            
            data_ = std::move(new_data);
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    void push_back(const T& value) {
        if (size_ == capacity_) {
            resize(static_cast<size_t>(capacity_ * GROWTH_FACTOR) + 1);
        }
        data_[size_++] = value;
    }
    
    void push_back(T&& value) {
        if (size_ == capacity_) {
            resize(static_cast<size_t>(capacity_ * GROWTH_FACTOR) + 1);
        }
        data_[size_++] = std::move(value);
    }
    
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }
    
    void clear() {
        size_ = 0;
    }
    
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    
    T* begin() { return data_.get(); }
    T* end() { return data_.get() + size_; }
    const T* begin() const { return data_.get(); }
    const T* end() const { return data_.get() + size_; }
    
    T* data() { return data_.get(); }
    const T* data() const { return data_.get(); }
};

#endif