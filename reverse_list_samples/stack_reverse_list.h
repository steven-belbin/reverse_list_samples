#pragma once

#include "node_data.h"
#include <algorithm>
#include <vector>

/// <summary>
/// Reverse the linked list using a stack concepts of pointers to the nodes
/// and only swapping the data within the nodes.
/// </summary>
/// 
/// <notes>
/// This approach is practical since the nodes remain chained in the same sequence.
/// Thus, the nodes' '.next' member are unchanged. While swapping the '.data' of
/// each node.
/// 
/// This is an approach that was taught in computer science course, since the act
/// of swapping goes midway through the collection.
/// 
/// In addition, I like it because
///    1. with trivial data types, such as int, double, char*, this is efficient.
///    2. simple by inspection, such that there isn't conditional branching for special cases.
///    3. the swap could be converted to use a concurrent algorithm.
/// </notes>
template<class data_type>
void stack_reverse_list(link_list_node_ptr_type<data_type>& linked_list)
{
	std::vector<linked_list_node<data_type>*> stack;

	for (auto* node = linked_list.get(); node != nullptr; node = node->next.get())
		stack.insert(std::begin(stack), node);

	for (auto [first, last] = std::tuple{ std::begin(stack), std::end(stack) };
		 first != last && first != --last;
		 ++first)
		std::swap((*first)->data, (*last)->data);
}
