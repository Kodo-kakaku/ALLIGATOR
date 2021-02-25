#pragma once

#include <iostream>

template<typename T = int,class A = std::allocator<T>>
class keeper {
	public:
		using value_type = T;
	
        using reference = value_type &;
        using const_reference = const reference;
        using pointer = value_type*;
        using const_pointer = const pointer;

        using allocator_type = A;
        using const_allocator_type = const allocator_type;

        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        // constructor for the container
        explicit keeper() : alligator_(), size_(),capacity_(), data_(), start_(), end_() {}
	
		explicit keeper(size_type n) : alligator_(), size_(n), capacity_(n*capacity_increase_), data_(allocator().allocate(n*capacity_increase_)), start_(), end_(n) {
        	init(data_begin(),size(),value_type());
        }

        explicit keeper(size_type n,value_type v) : alligator_(), size_(n), capacity_(n*capacity_increase_), data_(allocator().allocate(n*capacity_increase_)), start_(), end_(n) {
        	init(data_begin(),size(),v);
        }

		explicit keeper(keeper& f): alligator_(f.allocator()), size_(f.size()), capacity_(f.capacity()), data_(allocator().allocate(f.capacity())), start_(f.head()), end_(f.tail()) {
        	memcpy(data_begin(),f.data_begin(),sizeof(value_type)*size());
        }

        explicit keeper(keeper&& f) : alligator_(std::move(f.alligator_)), size_(std::move(f.size_)), capacity_(std::move(f.capacity_)), data_(std::move(f.data_begin())), start_(std::move(f.start_)), end_(std::move(f.end_)) {
        	f.size_ = size_type();
            f.capacity_ = size_type();
            f.data_ = pointer();
        }

		// destructor for the container
        ~keeper() {
        	if (data_begin() != pointer()) {
        		for (size_type i = 0; i < size(); ++i) {
                    allocator().destroy(data_begin() + i);
        		}
                allocator().deallocate(data_begin(),capacity());
            }
        }
            
        // iterator for the container
        class iterator {

        	friend class keeper;

			public:
        		iterator() = default;
				iterator(const iterator&) = default;
				~iterator() = default;

				bool operator!=(const iterator & other) const {
					return other._p != _p;
				}

				pointer& operator++() {
					return _p == _end ? _p = _begin : ++_p;
				}

				reference operator*() const { return *_p; }
				pointer operator->() const { return _p; }
            private:
        		pointer _p;
                pointer _begin;
                pointer _end;

        		iterator(pointer p,pointer begin, pointer end) : _p(p), _begin(begin), _end(end) {}
            };

		// const iterator for the container
        class const_iterator {

        	friend class keeper;

	        public:
        		const_iterator() = default;
				const_iterator(const const_iterator&) = default;
				const_iterator(const iterator & it) : _p(it._p) {}
				~const_iterator() = default;

				bool operator!=(const const_iterator & other) const { return other._p != _p; }
				const_reference operator*() const { return *_p; }
				pointer operator->() const { return _p; }

             private:
        		pointer _p;
                explicit const_iterator(pointer p) : _p(p) {}
        };

        // methods to use as in classic stl containers
        size_type     size()     const { return size_; }
        size_type     capacity() const { return capacity_; }
        bool          empty()    const { return size_ == 0; }

        allocator_type& allocator() { return alligator_; }
        const_allocator_type& allocator() const { return alligator_; }

        iterator       begin()    const { return iterator((data_begin() + head()),data_begin(),(data_begin() + capacity() - 1)); }
        iterator       end()      const { return iterator((data_begin() + tail()),data_begin(),(data_begin() + capacity() - 1)); }

        const_iterator cbegin()   const { return static_cast<const_iterator>(begin()); }
        const_iterator cend()     const { return static_cast<const_iterator>(end()); }

        value_type pop() {
        	value_type some_data = value_type();
        	if (!empty()) {
        		some_data = *cbegin();
                ++start_;
                start_ %= capacity();
                --size_;
            }

            return some_data;
        }

        reference front() {
	        return *cbegin();
        }

       // TODO implementation of the push method
	
        void push(const value_type & value) {
        	if (size() + 1 == capacity()) {
        		pointer new_allocate = allocator().allocate(capacity()*capacity_increase_);

        		for (size_type i = 0; i < size(); ++i) {
        			*(new_allocate + i) = *(data_begin() + head());
                    ++start_;
                    start_ %= capacity();
                }

        		start_ = 0;
                end_ = size();

                allocator().deallocate(data_begin(),capacity());

				data_ = new_allocate;
        		capacity_ *= capacity_increase_;
        		
            }
            else if (size() == 0) {
            	data_ = allocator().allocate(capacity_increase_);

            	capacity_ = capacity_increase_;
                start_ = 0;
                end_ = 0;
            }

            *(data_begin() + tail()) = value;
            ++end_;
            end_ %= capacity();
        	++size_;
        }

        private:
            allocator_type alligator_;
            size_type      size_;
            size_type      capacity_;
            pointer        data_;
            size_type      start_;
            size_type      end_;

            const size_type capacity_increase_ = 2;

			void init(pointer d, size_type n, value_type v) {
                for (size_type i = 0; i < n; ++i) {
                    allocator().construct((d + i), v);
                }       
            }

            pointer data_begin()  const { return data_; }
            pointer data_end()    const { return data_ + size_; }
            size_type head()      const { return start_; }
            size_type tail()      const { return end_; }

 };
