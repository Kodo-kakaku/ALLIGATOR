#pragma once

#include <memory>
#include <vector>

template <typename T, unsigned const BuffSize = 10>
struct custom_alligator {
	using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;

    template <typename U>
    struct rebind {
    	using other = custom_alligator<U>;
    };

	custom_alligator() : is_buff_(true) {
		buffer_.reserve(BuffSize);
    }

	~custom_alligator() {
		if (is_buff()) {
            for (const auto& p : head_) {
                std::free(p);
            }
        }
    }

	custom_alligator(const custom_alligator<T, BuffSize>& alligator) {
		is_buff_ = alligator.is_buff();
	}

    template<typename U>
    explicit custom_alligator(const custom_alligator<U>&) {
		is_buff_ = false;
	}

    pointer allocate(const size_type n) {
		if (is_buff() && n == 1) {
			if (buffer_.empty()) {
				auto* p = std::malloc(BuffSize*sizeof(T));

				if (!p) {
                    throw std::bad_alloc();
				}
                auto* alligator_type = reinterpret_cast<pointer>(p);
				for (size_type i = 1; i < BuffSize; ++i) {
                    buffer_.emplace_back(alligator_type + i);
				}     
                 head_.emplace_back(alligator_type);
            }

            pointer p = buffer_.at(buffer_.size() - 1);    
            buffer_.pop_back();
			return p;
        }
        else {
        	auto* p = std::malloc(n*sizeof(T));
        	if (!p) {
                throw std::bad_alloc();
        	}

        	return reinterpret_cast<pointer>(p);
        }
    }

    void deallocate(pointer p, size_type n) {
        if (is_buff() && n == 1) {
            buffer_.emplace_back(p);
        }
        else {
            std::free(p);
        }
	}

	template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
		new(p) U(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
		p->~value_type();
    }


	bool is_buff() const { return is_buff_; }

    private:
		bool is_buff_;
        std::vector<pointer> buffer_;
        std::vector<pointer> head_;
};
