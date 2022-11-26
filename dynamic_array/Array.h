#include <iterator>
#include <memory>

constexpr size_t ARRAY_DEFAULT_CAPACITY = 16;

template<typename T>
class Array final {
public:
	Array(size_t capacity) :
		_size(0),
		_capacity(capacity),
		_data(static_cast<T*>(operator new(sizeof(T)* capacity))) {}

	Array(): Array(ARRAY_DEFAULT_CAPACITY) {}

	~Array() {
		for (size_t i = 0; i < _size; i++) {
			_data[i].~T();
		}
		operator delete(_data);
	}

	Array(const Array& other): 
		_size(other._size),
		_capacity(other._capacity),
		_data(static_cast<T*>(operator new(sizeof(T) * other._capacity))) {
		for (size_t i = 0; i < _size; i++) {
			new (_data + i) T(other._data[i]);
		}
	}

	Array(Array&& other) :
		_size(other._size),
		_capacity(other._capacity),
		_data(other._data) {
		other._data = nullptr;
		other._size = 0;
	}

	Array& operator=(const Array& other) {
		if (this != &other) {
			Array(other).swap(*this);
		}
		return *this;
	}

	Array& operator=(Array&& other) {
		if (this != &other) {
			for (size_t i = 0; i < _size; i++) {
				_data[i].~T();
			}
			_size = other.size;
			_capacity = other._capacity;
			_data = other._data;
			other._data = nullptr;
		}
		return *this;
	}

	size_t insert(size_t index, const T& value) {
		assert(index >= 0 && index <= _size);

		if (_size == _capacity) {
			size_t new_capacity = _capacity * 2;
			T* new_data = static_cast<T*>(operator new(sizeof(T) * new_capacity));
			for (size_t i = 0; i < index; i++) {
				new (new_data + i) T(std::move(_data[i]));
			}
			for (size_t i = index; i < _size; i++) {
				new (new_data + i + 1) T(std::move(_data[i]));
			}
			for (size_t i = 0; i < _size; i++) {
				_data[i].~T();
			}
			operator delete(_data);
			_data = new_data;
			_capacity = new_capacity;
			new (_data + index) T(value);
		} else {
			if (index == _size) {
				new (_data + index) T(value);
			} else {
				if (_size) {
					new (_data + _size) T(std::move(_data[_size - 1]));
					for (size_t i = _size - 1; i > index; i--) {
						_data[i] = std::move(_data[i - 1]);
					}
				}
				_data[index] = value;
			}
		}
		_size++;
		return index;
	}

	void remove(size_t index) {
		assert(_size > 0);
		assert(index >= 0 && index < _size);

		for (size_t i = index; i < _size - 1; i++) {
			_data[i] = std::move(_data[i + 1]);
		}

		_data[_size - 1].~T();
		_size--;
	}

	size_t insert(const T& value) {
		return insert(_size, value);
	}

	T& operator[](size_t index) const {
		assert(index >= 0 && index < _size);

		return _data[index];
	}

	size_t size() const {
		return _size;
	}

	size_t capacity() const {
		return _capacity;
	}

	T* data() const {
		return _data;
	}

	using simple_iterator = T*;

	simple_iterator begin() const {
		return _data;
	}

	simple_iterator end() const {
		return begin() + size();
	}

	simple_iterator cbegin() const {
		return end() - 1;
	}

	simple_iterator cend() const {
		return begin() - 1;
	}

	class Iterator {
	public:
		Iterator(simple_iterator cur, simple_iterator end):
			_cur(cur), _end(end) {}

		const T& get() const {
			return *_cur;
		}

		void set(const T& value) {
			*_cur = value;
		}

		void next() {
			if (_cur != _end) {
				_cur < _end ? _cur++ : _cur--;
			}
		}

		bool hasNext() const {
			return _cur != _end;
		}
	protected:
		simple_iterator _cur, _end;
	};

	class ConstIterator : public Iterator {
	public:
		ConstIterator(simple_iterator cur, simple_iterator end): 
			Iterator(cur, end) {}

		void set(const T& value) = delete;
	};



	Iterator iterator() {
		return Iterator(begin(), end());
	}

	ConstIterator iterator() const {
		return ConstIterator(begin(), end());
	}
	
	Iterator reverseIterator() {
		return Iterator(cbegin(), cend());
	}
	
	ConstIterator reverseIterator() const {
		return ConstIterator(cbegin(), cend());
	}

private:

	void swap(Array& other) noexcept {
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
		std::swap(_data, other._data);
	}

	size_t _size;
	size_t _capacity;
	T* _data;
};