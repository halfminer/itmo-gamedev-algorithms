#include <algorithm>

template<typename T, typename Compare>
void insertion_sort(T* first, T* last, Compare& comp) {
	T* insert_position;
	for (T* i = first + 1; i <= last; i++) {
		T safe = std::move(*i);
		for (insert_position = i - 1; insert_position >= first && comp(safe, *insert_position); insert_position--) {
			*(insert_position + 1) = std::move(*insert_position);
		}
		*(insert_position + 1) = std::move(safe);
	}
}

template<typename T, typename Compare>
static T& middleOfThreePointers(T* a, T* b, T* c, Compare& comp) {
	if (comp(*a, *b)) {
		if (comp(*c, *a)) {
			return *a;
		}
		if (comp(*b, *c)) {
			return *b;
		}
		return *c;
	} 
	if (comp(*c, *b)) {
		return *b;
	}
	if (comp(*a, *c)) {
		return *a;
	}
	return *c;
	
}

template<typename T, typename Compare>
static T* partition(T* first, T* last, const Compare& comp) {
	T* l = first;
	T* r = last;
	T pivot = middleOfThreePointers(l, r, l + (r - l) / 2, comp);


	while (true) {
		while (comp(*l, pivot)) {
			l++;
		}

		while (comp(pivot, *r)) {
			r--;
		}

		if (l >= r) {
			break;
		}

		std::swap(*l, *r);
		l++;
		r--;
	}
	
	return r;
}

template<typename T, typename Compare>
void quicksort(T* first, T* last, Compare& comp) {
	while (last > first) {
		T* p = partition(first, last, comp);

		if (p - first > last - p) {
			quicksort(p + 1, last, comp);
			last = p;
		} else {
			quicksort(first, p, comp);
			first = p + 1;
		}
	}
}

constexpr ptrdiff_t shouldUseInsertionSort = 18;

template<typename T, typename Compare>
void quicksort_insertion_modification(T* first, T* last, Compare& comp) {
	while (last - first > shouldUseInsertionSort) {
		T* p = partition(first, last, comp);

		if (p - first > last - p) {
			quicksort_insertion_modification(p + 1, last, comp);
			last = p;
		} else {
			quicksort_insertion_modification(first, p, comp);
			first = p + 1;
		}
	}

	insertion_sort(first, last, comp);
}

template<typename T, typename Compare>
void my_sort(T* first, T* last, Compare& comp) {
	if (first == nullptr || last == nullptr) {
		return;
	}
	last--;
	if (last <= first) {
		return;
	}
	quicksort_insertion_modification(first, last, comp);
}