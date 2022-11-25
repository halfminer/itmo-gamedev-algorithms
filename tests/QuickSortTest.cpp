#include <gtest/gtest.h>
#include "QuickSort.h"
#include "Array.h"
#include <random>

static constexpr auto lower_comp_int = [](int a, int b) { return a < b; };
static constexpr auto bigger_comp_int = [](int a, int b) { return a > b; };
static constexpr auto lower_comp_string = [](std::string& a, std::string& b) { return a < b; };
static constexpr auto bigger_comp_string = [](std::string& a, std::string& b) { return a > b; };

static std::string gen_string(const size_t length, std::mt19937& gen) {
	std::string res;
	res.resize(length);
	for (auto& i : res) {
		i = 'a' + (gen() % 26);
	}
	return res;
}

TEST(QuickSort, InsertionSortIntTest) {
	constexpr size_t ARRAY_SIZE = 10'000;
	std::vector<int> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = g();
	}

	insertion_sort(a.data(), a.data() + ARRAY_SIZE - 1, lower_comp_int);
	
	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	insertion_sort(a.data(), a.data() + ARRAY_SIZE - 1, bigger_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, InsertionSortStringTest) {
	constexpr size_t ARRAY_SIZE = 1'000;
	constexpr size_t STRING_MAX_SIZE = 10;
	std::vector<std::string> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
	}

	insertion_sort(a.data(), a.data() + a.size() - 1, lower_comp_string);

	for (size_t i = 1; i < a.size(); i++) {
		ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	insertion_sort(a.data(), a.data() + a.size() - 1, bigger_comp_string);

	for (size_t i = 1; i < a.size(); i++) {
		ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

//TEST(QuickSort, InsertionSortIntCustomArray) {
//	constexpr size_t ARRAY_SIZE = 10'000;
//	Array<int> a(ARRAY_SIZE);
//	std::mt19937 g;
//
//	for (auto& i : a) {
//		i = g();
//	}
//
//	insertion_sort(a.begin(), a.end(), lower_comp_int);
//
//	for (size_t i = 1; i < ARRAY_SIZE; i++) {
//		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
//	}
//
//	insertion_sort(a.begin(), a.end() + ARRAY_SIZE, bigger_comp_int);
//
//	for (size_t i = 1; i < ARRAY_SIZE; i++) {
//		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
//	}
//}

TEST(QuickSort, QuickSortIntTest) {
	constexpr size_t ARRAY_SIZE = 500'000;
	std::vector<int> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = g();
	}

	quicksort(a.data(), a.data() + ARRAY_SIZE - 1, lower_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	quicksort(a.data(), a.data() + ARRAY_SIZE - 1, bigger_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, QuickSortStringTest) {
	constexpr size_t ARRAY_SIZE = 500'000;
	constexpr size_t STRING_MAX_SIZE = 100;
	std::vector<std::string> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
	}

	quicksort(a.data(), a.data() + ARRAY_SIZE - 1, lower_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	quicksort(a.data(), a.data() + ARRAY_SIZE - 1, bigger_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, QuicksortInsertionSortModificationIntTest) {
	constexpr size_t ARRAY_SIZE = 500'000;
	std::vector<int> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = g();
	}

	quicksort_insertion_modification(a.data(), a.data() + ARRAY_SIZE - 1, lower_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	quicksort_insertion_modification(a.data(), a.data() + ARRAY_SIZE - 1, bigger_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, QuicksortInsertionSortModificationStringTest) {
	constexpr size_t ARRAY_SIZE = 500'000;
	constexpr size_t STRING_MAX_SIZE = 100;
	std::vector<std::string> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
	}

	quicksort_insertion_modification(a.data(), a.data() + ARRAY_SIZE - 1, lower_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	quicksort_insertion_modification(a.data(), a.data() + ARRAY_SIZE - 1, bigger_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, MySortIntTest) {
	constexpr size_t ARRAY_SIZE = 5'000'000;
	std::vector<int> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = g();
	}

	my_sort(a.data(), a.data() + ARRAY_SIZE, lower_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	my_sort(a.data(), a.data() + ARRAY_SIZE, bigger_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, MySortStringTest) {
	constexpr size_t ARRAY_SIZE = 500'000;
	constexpr size_t STRING_MAX_SIZE = 100;
	std::vector<std::string> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
	}

	my_sort(a.data(), a.data() + ARRAY_SIZE, lower_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	my_sort(a.data(), a.data() + ARRAY_SIZE, bigger_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, StdIntTest) {
	constexpr size_t ARRAY_SIZE = 5'000'000;
	std::vector<int> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = g();
	}

	std::sort(a.data(), a.data() + ARRAY_SIZE, lower_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	std::sort(a.data(), a.data() + ARRAY_SIZE, bigger_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(QuickSort, StdStringTest) {
	constexpr size_t ARRAY_SIZE = 500'000;
	constexpr size_t STRING_MAX_SIZE = 100;
	std::vector<std::string> a(ARRAY_SIZE);
	std::mt19937 g;

	for (auto& i : a) {
		i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
	}

	std::sort(a.data(), a.data() + ARRAY_SIZE, lower_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	std::sort(a.data(), a.data() + ARRAY_SIZE, bigger_comp_string);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
	}
}

TEST(Benchmark, InsertionSortInt) {
	constexpr size_t REPEAT_SIZE = 1'000'000;
	constexpr size_t MAX_ARRAY_SIZE = 32;
	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<int> a(array_size);
		for (size_t i = 0; i < a.size(); i++) {
			a[i] = a.size() - i;
		}
		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			insertion_sort(a.data(), a.data() + array_size - 1, lower_comp_int);
			insertion_sort(a.data(), a.data() + array_size - 1, bigger_comp_int);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by insertion sort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, QuickSortInt) {
	constexpr size_t REPEAT_SIZE = 1'000'000;
	constexpr size_t MAX_ARRAY_SIZE = 32;

	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<int> a(array_size);
		for (size_t i = 0; i < a.size(); i++) {
			a[i] = a.size() - i;
		}
		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			quicksort(a.data(), a.data() + array_size - 1, lower_comp_int);
			quicksort(a.data(), a.data() + array_size - 1, bigger_comp_int);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, MySortInt) {
	constexpr size_t REPEAT_SIZE = 1'000'000;
	constexpr size_t MAX_ARRAY_SIZE = 32;
	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<int> a(array_size);
		for (size_t i = 0; i < a.size(); i++) {
			a[i] = a.size() - i;
		}
		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			my_sort(a.data(), a.data() + array_size, lower_comp_int);
			my_sort(a.data(), a.data() + array_size, bigger_comp_int);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, StdSortInt) {
	constexpr size_t REPEAT_SIZE = 1'000'000;
	constexpr size_t MAX_ARRAY_SIZE = 32;
	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<int> a(array_size);
		for (size_t i = 0; i < a.size(); i++) {
			a[i] = a.size() - i;
		}
		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			std::sort(a.data(), a.data() + array_size, lower_comp_int);
			std::sort(a.data(), a.data() + array_size, bigger_comp_int);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, InsertionSortString) {
	constexpr size_t REPEAT_SIZE = 10'000;
	constexpr size_t STRING_MAX_SIZE = 100;
	constexpr size_t MAX_ARRAY_SIZE = 64;
	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<std::string> a(array_size);
		std::mt19937 g;

		for (auto& i : a) {
			i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
		}
		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			insertion_sort(a.data(), a.data() + array_size - 1, lower_comp_string);
			insertion_sort(a.data(), a.data() + array_size - 1, bigger_comp_string);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, QuickSortString) {
	constexpr size_t REPEAT_SIZE = 10'000;
	constexpr size_t STRING_MAX_SIZE = 100;
	constexpr size_t MAX_ARRAY_SIZE = 64;
	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<std::string> a(array_size);
		std::mt19937 g;

		for (auto& i : a) {
			i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
		}

		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			quicksort(a.data(), a.data() + array_size - 1, lower_comp_string);
			quicksort(a.data(), a.data() + array_size - 1, bigger_comp_string);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, MySortString) {
	constexpr size_t REPEAT_SIZE = 10'000;
	constexpr size_t MAX_ARRAY_SIZE = 64;
	constexpr size_t STRING_MAX_SIZE = 100;

	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<std::string> a(array_size);
		std::mt19937 g;

		for (auto& i : a) {
			i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
		}

		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			my_sort(a.data(), a.data() + array_size - 1, lower_comp_string);
			my_sort(a.data(), a.data() + array_size - 1, bigger_comp_string);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}

TEST(Benchmark, StdSortString) {
	constexpr size_t REPEAT_SIZE = 10'000;
	constexpr size_t MAX_ARRAY_SIZE = 64;
	constexpr size_t STRING_MAX_SIZE = 100;

	for (size_t array_size = 1; array_size <= MAX_ARRAY_SIZE; array_size++) {
		std::vector<std::string> a(array_size);
		std::mt19937 g;

		for (auto& i : a) {
			i = gen_string(g() % (STRING_MAX_SIZE - 1) + 1, g);
		}

		auto start = std::chrono::high_resolution_clock::now();

		for (size_t repeat = 0; repeat < REPEAT_SIZE; repeat++) {
			std::sort(a.data(), a.data() + array_size, lower_comp_string);
			std::sort(a.data(), a.data() + array_size, bigger_comp_string);
		}

		auto end = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << duration.count() << std::endl;
		//std::cout << "Time taken by quicksort on " << array_size << " elements is " << duration.count() << " microseconds" << std::endl;
	}
}