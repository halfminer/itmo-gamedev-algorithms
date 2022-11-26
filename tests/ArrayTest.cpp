#include <gtest/gtest.h>
#include "Array.h"
#include <iostream>



TEST(Array, DefaultConstructor) {
	Array<int> a;

	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.capacity(), ARRAY_DEFAULT_CAPACITY);

	Array<std::string> s;

	ASSERT_EQ(s.size(), 0);
	ASSERT_EQ(s.capacity(), ARRAY_DEFAULT_CAPACITY);
}

TEST(Array, CapacityConstructor) {
	constexpr size_t capacity = 1000 - 7;
	Array<int> a(capacity);

	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.capacity(), capacity);

	Array<std::string> s(capacity);

	ASSERT_EQ(s.size(), 0);
	ASSERT_EQ(s.capacity(), capacity);
}

TEST(Array, PushBack) {
	constexpr size_t PUSHBACK_TIMES = 1000 - 7;
	Array<int> a;

	for (size_t i = 0; i < PUSHBACK_TIMES; i++) {
		ASSERT_EQ(a.insert(i), i);
		ASSERT_EQ(a.size(), i + 1);
		ASSERT_EQ(a[a.size() - 1], i);
	}

	Array<std::string> s_arr;

	for (size_t i = 0; i < PUSHBACK_TIMES; i++) {
		char c = 'a' + i;
		std::string s(i + 1, c);
		ASSERT_EQ(s_arr.insert(s), i);
		ASSERT_EQ(s_arr.size(), i + 1);
		ASSERT_EQ(s_arr[s_arr.size() - 1], s);
	}
}

TEST(Array, Insert) {
	constexpr size_t INSERT_TIMES = 1000 - 7;
	Array<int> a;

	for (size_t i = 0; i < INSERT_TIMES; i++) {
		ASSERT_EQ(a.insert(0, i), 0);
		ASSERT_EQ(a.size(), i + 1);
		for (size_t i = 0; i < a.size(); i++) {
			ASSERT_EQ(a[i] + 1, a.size() - i);
		}
	}

	Array<std::string> s_arr;

	for (size_t i = 0; i < INSERT_TIMES; i++) {
		char c = 'a' + i;
		std::string s(i + 1, c);
		ASSERT_EQ(s_arr.insert(0, s), 0);
		ASSERT_EQ(s_arr.size(), i + 1);
		for (size_t i = 0; i < s_arr.size(); i++) {
			ASSERT_EQ(s_arr[s_arr.size() - i - 1], std::string(i + 1, i + 'a'));
		}
	}
}

TEST(Array, Remove) {
	constexpr size_t REMOVE_TIMES = 1000 - 7;
	Array<int> a;

	for (size_t i = 0; i < REMOVE_TIMES; i++) {
		a.insert(i);
	}

	for (size_t i = 0; i < REMOVE_TIMES - 1; i++) {
		a.remove(0);
		for (size_t j = 0; j < a.size(); j++) {
			ASSERT_EQ(a[j], j + i + 1);
		}
	}

	Array<std::string> s;

	for (size_t i = 0; i < REMOVE_TIMES; i++) {
		s.insert(std::string(i + 1, 'a' + i));
	}

	for (size_t i = 0; i < REMOVE_TIMES - 1; i++) {
		s.remove(0);
		for (size_t j = 0; j < s.size(); j++) {
			ASSERT_EQ(s[j], std::string(i + j + 2, i + j + 1 + 'a'));
		}
	}
}

TEST(Array, Foreach) {
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

TEST(Array, Iterators) {
	constexpr size_t VECTOR_SIZE = 1000 - 7;

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

	
	Array<std::string> string_array;
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		string_array.insert(std::string(i + 1, 'a' + i));
	}

	const Array<std::string> const_string_array(string_array);

	auto constIterator = const_string_array.iterator();
	auto constReverseIterator = const_string_array.reverseIterator();

	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		ASSERT_TRUE(constIterator.hasNext());
		ASSERT_EQ(constIterator.get(), const_string_array[i]);
		ASSERT_EQ(constIterator.get(), string_array[i]);
		constIterator.next();
	}

	ASSERT_FALSE(constIterator.hasNext());

	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		ASSERT_TRUE(constReverseIterator.hasNext());
		ASSERT_EQ(constReverseIterator.get(), const_string_array[const_string_array.size() - i - 1]);
		ASSERT_EQ(constReverseIterator.get(), string_array[string_array.size() - i - 1]);
		constReverseIterator.next();
	}

	ASSERT_FALSE(constReverseIterator.hasNext());
}

TEST(Array, Assigment) {
	constexpr size_t VECTOR_SIZE = 1000 - 7;

	std::vector<int> v(VECTOR_SIZE);
	Array<int> a;
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		v[i] = i + 1;
		a.insert(i + 1);
	}
	Array<int> b = a;
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		ASSERT_EQ(a[i], v[i]);
		ASSERT_EQ(a[i], b[i]);
	}

	std::vector<std::string> v_string(VECTOR_SIZE);
	Array<std::string> a_string;

	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		v_string[i] = std::string(i + 1, 'a' + i);
		a_string.insert(v_string[i]);
	}
	Array<std::string> b_string = a_string;
	for (size_t i = 0; i < VECTOR_SIZE; i++) {
		ASSERT_EQ(a_string[i], v_string[i]);
		ASSERT_EQ(a_string[i], b_string[i]);
	}
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}