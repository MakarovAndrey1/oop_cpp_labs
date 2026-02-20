#ifndef FIXED_BLOCK_MEMORY_RESOURCE_H
#define FIXED_BLOCK_MEMORY_RESOURCE_H

#include <memory_resource>
#include <vector>
#include <cstddef>
#include <mutex>
#include <unordered_map> // Добавлен заголовочный файл
#include <cstdlib> // Для std::malloc и std::free
#include <new> // Для std::bad_alloc

class FixedBlockMemoryResource : public std::pmr::memory_resource {
public:
    explicit FixedBlockMemoryResource(std::size_t block_size, std::size_t initial_pool_size = 1024 * 1024)
        : block_size_(block_size), pool_size_(initial_pool_size) {

        pool_ = static_cast<std::byte*>(std::malloc(pool_size_));
        if (!pool_) {
            throw std::bad_alloc();
        }
        free_blocks_.reserve(pool_size_ / block_size_);

        // Изначально все блоки свободны
        for (std::size_t i = 0; i < pool_size_ / block_size_; ++i) {
            free_blocks_.push_back(i * block_size_);
        }
    }

    FixedBlockMemoryResource(const FixedBlockMemoryResource&) = delete;
    FixedBlockMemoryResource& operator=(const FixedBlockMemoryResource&) = delete;

    // Убрана спецификация исключений, так как у базового класса ее нет
    ~FixedBlockMemoryResource() override {
        std::free(pool_);
    }

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (bytes > block_size_ || alignment > block_size_) {
            // В данном случае, если запрашиваемый блок слишком велик,
            // мы не можем его выделить и должны бросить исключение.
            // Если бы мы хотели обрабатывать такие случаи иначе,
            // можно было бы делегировать другому memory_resource.
            throw std::bad_alloc();
        }

        if (free_blocks_.empty()) {
            // Можно добавить логику перевыделения пула, если нужно
            throw std::bad_alloc();
        }

        // Берем первый свободный блок
        std::size_t block_offset = free_blocks_.back();
        free_blocks_.pop_back();

        // Сохраняем реальный запрошенный размер (bytes), хотя в этом ресурсе он не используется
        allocated_blocks_[block_offset] = bytes; 
        return static_cast<void*>(pool_ + block_offset);
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        std::lock_guard<std::mutex> lock(mutex_);

        if (!p) return;

        std::byte* ptr = static_cast<std::byte*>(p);
        std::size_t offset = ptr - pool_;

        // Проверяем, что блок был действительно выделен этим ресурсом
        // и удаляем его из карты выделенных блоков
        auto it = allocated_blocks_.find(offset);
        if (it == allocated_blocks_.end()) {
            // Если блок не найден, возможно, он был выделен другим ресурсом
            // или уже был освобожден. В данном случае игнорируем.
            return;
        }

        allocated_blocks_.erase(it);
        free_blocks_.push_back(offset);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }

private:
    std::byte* pool_ = nullptr; // Инициализация nullptr
    std::size_t block_size_;
    std::size_t pool_size_;
    std::vector<std::size_t> free_blocks_;           // Список свободных блоков (смещения)
    std::unordered_map<std::size_t, std::size_t> allocated_blocks_; // Выделенные блоки
    std::mutex mutex_;
};

#endif // FIXED_BLOCK_MEMORY_RESOURCE_H