#include <iterator>
#include <memory>
constexpr size_t DEFAULT_CAPACITY = 16;

template<typename T>
class Array final {
public:
	Array(): 
		_size(0), 
	    _capacity(DEFAULT_CAPACITY),
		_data(static_cast<T*>(malloc(sizeof(T)* DEFAULT_CAPACITY))) 
	{
		assert(_data !=               nullptr);
	}

	Array(int capacity): 
		_size(0),
		_capacity(capacity)
	{
		assert(capacity >= 0);

		_data = static_cast<T*>(malloc(sizeof(T) * capacity));

		assert(_data != nullptr);
	}

	~Array() {
		if constexpr (std::is_destructible<T>()) {
			std::destroy(begin(), end());
		}

		free(_data);
	}

	Array(Array const& other): 
		Array() {
		_size = other._size;
		extend_buffer(other._capacity);

		for (size_t i = 0; i < other._size(); i++) {
			new (_data + i) T(other._data[i]);
		}
	}

	Array& operator=(Array const& other) {
		Array(other).swap(*this);
	}
	 
	int insert(const T& value) {
		assert(_size <= _capacity);

		if (_size == _capacity) {
			T tmp = value;

			size_t new_capacity = 2 * capacity;
			
			assert(new_capacity >= _capacity);

			T* new_data = static_cast<T*>(malloc(sizeof(T) * new_capacity));

			try {
				new (_data + _size) T(tmp);
			}
			catch (...) {
				free(new_data);
				throw;
			}

			try {
				if constexpr (std::is_nothrow_move_constructible<T>::value || !std::is_copy_constructible<T>::value) {
					std::uninitialized_move(begin(), end(), new_data);
				} else {
					std::uninitialized_copy(begin(), end(), new_data);
				}
			}
			catch (...) {
				free(new_data);
				throw;
			}

			_data = new_data;
			_capacity = new_capacity;
		} else {
			new (_data + _size) T(value);
		}

		return _size++;
	}

	int insert(int index, const T& value) {
		assert(index >= 0 && index < _size);

		if (_size == _capacity) {
			T tmp = value;

			size_t new_capacity = 2 * capacity;

			T* new_data = static_cast<T*>(malloc(sizeof(T) * new_capacity));

			try {
				new (_data + index) T(tmp);
			}
			catch (...) {
				free(new_data);
				throw;
			}

			try {
				if constexpr (std::is_nothrow_move_constructible<T>::value || !std::is_copy_constructible<T>::value) {
					std::uninitialized_move(begin(), begin() + iter, new_data);
					std::uninitialized_move(begin() + iter + 1, end(), new_data + iter);
				} else {
					std::uninitialized_copy(begin(), begin() + iter, new_data);
					std::uninitialized_copy(begin() + iter + 1, end(), new_data + iter);
				}
			}
			catch (...) {
				free(new_data);
				throw;
			}

			_data = new_data;
			_capacity = new_capacity;
		}
		else {
			new (_data + _size) T(value);
		}

		return _size++;
	}

	T& operator[](int index) {
		assert(index >= 0 && index < _size);

		return _data[index];
	}

	T const& operator[](int index) const {
		assert(index > 0 && index < _size);

		return _data[index];
	}

	int size() {
		return _size;
	}

	using simple_iterator = T*;
	using simple_const_iterator = const T*;

	simple_iterator begin() noexcept {
		return _data;
	}

	simple_iterator end() noexcept {
		return begin() + size();
	}

	simple_const_iterator cbegin() const noexcept {
		return _data();
	}

	simple_const_iterator cend() const noexcept {
		return begin() + size();
	}

	class Iterator {
	public:
		Iterator(simple_iterator cur, simple_iterator end):
			cur(cur),
			end(end) {
		}

		const T& get() const {
			return *cur;
		}

		void set(const T& value) {
			*cur = value;
		}

		void next() {
			cur < end ? std::next(cur) : std::prev(cur);
		}

		bool hasNext() const {
			return cur != end;
		}

	private:
		simple_iterator cur, end;
	};

	using ConstIterator = const Iterator;

	Iterator iterator() {
		return Iterator(begin(), end());
	}

	ConstIterator iterator() const {
		return ConstIterator(begin(), end());
	}
	
	Iterator reverseIterator() {
		return Iterator(std::prev(end()), std::prev(begin()));
	}
	
	ConstIterator reverseIterator() const {
		return ConstIterator(std::prev(end()), std::prev(begin()));
	}

private:

	void swap(Array& other) noexcept {
		std::swap(_size, other._size());
		std::swap(_capacity, other._capacity);
		std::swap(_data, other._data);
	}

	size_t _size;
	size_t _capacity;
	T* _data;
};