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

TEST(Sort, AllSortsIntTestValidness) {
	std::mt19937 g;
	for (int arr_size = 1000; arr_size > 0; arr_size-=7) {
		std::vector<int> input((size_t)arr_size);
		for (auto& i: input) {
			i = g();
		}
		std::vector<int> right_ans_inc, right_ans_dec;
		// Test std::sort
		std::vector<int> a = input;
		std::sort(a.begin(), a.end(), lower_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "std::sort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}
		right_ans_inc = a;
		std::sort(a.begin(), a.end(), bigger_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "std::sort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}
		right_ans_dec = a;

		// Test insertion sort
		a = input;
		
		insertion_sort(a.data(), a.data() + a.size() - 1, lower_comp_int);
		
		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "insertion sort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		insertion_sort(a.data(), a.data() + a.size() - 1, bigger_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "insertion sort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}

		// Test quicksort
		a = input;

		quicksort(a.data(), a.data() + a.size() - 1, lower_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "quicksort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		quicksort(a.data(), a.data() + a.size() - 1, bigger_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "quicksort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}
		
		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}
		// Test quicksort insertion sort modification
		a = input;

		quicksort_insertion_modification(a.data(), a.data() + a.size() - 1, lower_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "quicksort insertion sort modification exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		quicksort_insertion_modification(a.data(), a.data() + a.size() - 1, bigger_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "quicksort insertion sort modification exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}

		// Test my_sort
		a = input;

		my_sort(a.data(), a.data() + a.size(), lower_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "my_sort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		my_sort(a.data(), a.data() + a.size(), bigger_comp_int);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "my_sort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}
	}
}

TEST(Sort, AllSortsStringTestValidness) {
	std::mt19937 g;
	constexpr size_t STRING_MAX_SIZE = 10;
	for (int arr_size = 1000; arr_size > 0; arr_size -= 7) {
		std::vector<std::string> input((size_t)arr_size);
		for (auto& i : input) {
			i = gen_string(g() % STRING_MAX_SIZE + 1, g);
		}
		std::vector<std::string> right_ans_inc, right_ans_dec;
		// Test std::sort
		std::vector<std::string> a = input;
		std::sort(a.begin(), a.end(), lower_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "std::sort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}
		right_ans_inc = a;
		std::sort(a.begin(), a.end(), bigger_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "std::sort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}
		right_ans_dec = a;

		// Test insertion sort
		a = input;

		insertion_sort(a.data(), a.data() + a.size() - 1, lower_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "insertion sort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		insertion_sort(a.data(), a.data() + a.size() - 1, bigger_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "insertion sort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}

		// Test quicksort
		a = input;

		quicksort(a.data(), a.data() + a.size() - 1, lower_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "quicksort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		quicksort(a.data(), a.data() + a.size() - 1, bigger_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "quicksort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}
		// Test quicksort insertion sort modification
		a = input;

		quicksort_insertion_modification(a.data(), a.data() + a.size() - 1, lower_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "quicksort insertion sort modification exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		quicksort_insertion_modification(a.data(), a.data() + a.size() - 1, bigger_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "quicksort insertion sort modification exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}

		// Test my_sort
		a = input;

		my_sort(a.data(), a.data() + a.size(), lower_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!lower_comp_string(a[i], a[i - 1])) << "my_sort exception a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_inc[i]) << "does not equal to std::sort res a[" << i << "] in inc";
		}

		my_sort(a.data(), a.data() + a.size(), bigger_comp_string);

		for (size_t i = 1; i < a.size(); i++) {
			ASSERT_TRUE(!bigger_comp_string(a[i], a[i - 1])) << "my_sort exception a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
		}

		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i], right_ans_dec[i]) << "does not equal to std::sort res a[" << i << "] in dec";
		}
	}
}

TEST(Sort, InsertionSortIntCustomArray) {
	constexpr size_t ARRAY_SIZE = 1000 - 7;
	Array<int> a;
	std::mt19937 g;

	for (size_t i = 0; i < ARRAY_SIZE; i++) {
		a.insert(g());
	}

	insertion_sort(a.begin(), a.end(), lower_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!lower_comp_int(a[i], a[i - 1])) << "a[" << i << "] >= a[" << i - 1 << "]" << " get " << a[i] << " < " << a[i - 1];
	}

	insertion_sort(a.begin(), a.end(), bigger_comp_int);

	for (size_t i = 1; i < ARRAY_SIZE; i++) {
		ASSERT_TRUE(!bigger_comp_int(a[i], a[i - 1])) << "a[" << i << "] <= a[" << i - 1 << "]" << " get " << a[i] << " > " << a[i - 1];
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