#include <gtest/gtest.h>
#include "Array.h"
#include <iostream>

class A {
public:
	A() {
		std::cout << "constructor" << std::endl;
	}
	~A() {
		std::cout << "destructor" << std::endl;
	}
};

TEST(HelloTest, BasicAssertions) {
	constexpr size_t ARRAY_MEMORY_SIZE = 1000000;
	constexpr size_t ALLOCATIONS_AMOUNT = 1000000;
	for (size_t i = 0; i < ALLOCATIONS_AMOUNT; i++) {
		auto a = malloc(ARRAY_MEMORY_SIZE);
		operator delete(a);
	}
}

TEST(DynamicArray, Foreach) {
	constexpr size_t VECTOR_SIZE = 1000;

	std::vector<int> v(VECTOR_SIZE);

	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		v[i] = i;
	}

	Array<int> a;

	for (auto i : v) {
		a.insert(i);
	}

	int ptr = 0;
	
	for (auto i : a) {
		EXPECT_EQ(i, v[ptr++]);
	}

	ptr = 0;

	for (const auto i : a) {
		EXPECT_EQ(i, v[ptr++]);
	}

	ptr = 0;

	for (auto& i : a) {
		EXPECT_EQ(i, v[ptr++]);
	}

	ptr = 0;

	for (const auto& i : a) {
		EXPECT_EQ(i, v[ptr++]);
	}
}

TEST(DynamicArray, Iterators) {
	constexpr size_t VECTOR_SIZE = 1000;

	std::vector<int> v(VECTOR_SIZE);

	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		v[i] = i + 1;
	}

	Array<int> a;

	for (auto i : v) {
		a.insert(i);
	}

	for (auto it = a.iterator(); it.hasNext(); it.next()) {
		it.set(it.get() * 2);
	}

	for (size_t i = 0; i < a.size(); i++) {
		EXPECT_EQ(a[i], v[i] * 2);
	}

	for (auto it = a.reverseIterator(); it.hasNext(); it.next()) {
		it.set(it.get() / 2);
	}

	for (size_t i = 0; i < a.size(); i++) {
		EXPECT_EQ(a[i], v[i]);
	}
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}