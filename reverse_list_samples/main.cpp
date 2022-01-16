#include "node_data.h"
#include "linked_list.h"
#include "inplace_reverse_list.h"
#include "ranges_reverse_list.h"
#include "stack_reverse_list.h"
#include <fmt/ranges.h>
#include <algorithm>
#include <format>
#include <iostream>
#include <ranges>
#include <vector>

using namespace std::string_literals;

namespace
{
	int test_count = 0;
	int test_passed = 0;
	int test_failed = 0;
}


template<class data_type>
bool verify_reversal(const std::initializer_list<data_type>& input,
                     const link_list_node_ptr_type<data_type>& linked_list)
{
	const auto expected = std::ranges::reverse_view(input);
	const auto values = to_vector(linked_list);

	const auto result = std::ranges::equal(values, expected);

	if (result)
		fmt::print("PASSED.\n\n");
	else
		fmt::print("FAILED.\n"
			       "Got     : {}\n"
			       "Expected: {}\n\n\n",
			       values,
			       expected);

	return true;
}

template<class data_type>
constexpr void test(const std::initializer_list<data_type>& input,
	                const auto function)
{
	auto linked_list = initialize_linked_list(input);

	fmt::print("Linked list: {}\n", to_vector(linked_list));

	function(linked_list);

	fmt::print("Reversed linked list: {}\n", to_vector(linked_list));

	test_count++;

	if (verify_reversal(input, linked_list))
		++test_passed;
	else
		++test_failed;
}

int main()
{
	//const auto fn = [](auto& linked_list) { stack_reverse_list(linked_list); };
	const auto fn = [](auto& linked_list) { inplace_reverse_list(linked_list); };
	//const auto fn = [](auto& linked_list) { ranges_reverse_list(linked_list); };

	test({ "dog"s, "cat"s, "fish"s, "goat"s }, fn);
	test<std::string>({}, fn);
	test({ "dog"s }, fn);
	test({ "ant"s, "spider"s, "wasp"s }, fn);
	test({ "jack"s, "jill"s, "andy"s, "george"s, "steven"s, "paul"s, "eric"s}, fn);

	test({ 5, 10, 15, 20 }, fn);
	test<int>({}, fn);
	test({ 99 }, fn);
	test({ 10, 26, 31 }, fn);
	test({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 }, fn);

	test({ 5.5, 10.10, 15.15, 20.20 }, fn);
	test<double>({}, fn);
	test({ 99.99 }, fn);
	test({ 10.10, 26.26, 31.31 }, fn);
	test({ 10.0, 9.1, 8.2, 7.3, 6.4, 5.5, 4.6, 3.7, 2.8, 1.9, 0.10 }, fn);

	fmt::print("Tests Results: {}\n"
	           "Count : {}\n"
	           "Passed: {}\n"
		       "Failed: {}\n",
		       (test_failed == 0) ? "PASSED" : "FAILED",
		       test_count,
		       test_passed,
		       test_failed);

	return 0;
}
