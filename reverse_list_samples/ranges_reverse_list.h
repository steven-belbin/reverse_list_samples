#pragma once

#include "node_data.h"
#include "linked_list.h"
#include <algorithm>
#include <ranges>

/// <summary>
/// Reverse the linked list using C++ ranges feature.
/// </summary>
/// <notes>
/// Since the link_list is a user defined data structure without a back iterator
/// it became necessary to populate into a STL collection such as a vector which 
/// supports a back iterator.
/// 
/// Although it's inefficient with a user defined data structure collection, the
/// ranges approach could be novel with further research with providing an adaptor
/// for  user defined data structure collection that only provide a forward
/// iterator and the C++ ranges with concepts could provide an intermediary
/// collection.
/// 
/// If so then the logic is simple of constructing a new list in reverse
/// order.
/// </notes>
template<class data_type>
void ranges_reverse_list(link_list_node_ptr_type<data_type>& linked_list)
{
	const auto nodes = to_vector_nodes<data_type>(linked_list);

	linked_list = nullptr;
	linked_list_node<data_type>* previous = nullptr;

	for (auto& node : nodes | std::views::reverse)
	{
		const auto current = node.get();

		if (linked_list == nullptr)
			linked_list = std::move(node);
		else
			previous->next = std::move(node);

		previous = current;
	}
}
