#pragma once

#include "node_data.h"

/// <summary>
/// Reverse the linked list by advancing through the linked list and changing
/// each node's '.next' member to point to the previous node.
/// 
/// As for the root/head it keeps advancing until it reaches the last valid
/// note.
/// </summary>
/// 
/// <notes>
/// Need to be cautious with the edge cases such as passing in a root/head
/// that is null reference, such as an empty list.
/// 
/// The algorithm requires keeping track of the previous & current nodes then
/// setting the '.next' member in a precise manner such that to advance the
/// head/root of the linked list just prior to changing the current node's
/// '.next' to the previous node.
/// 
/// This user defined structure collection uses C++ unique_ptr, which is totally
/// valid for that user defined structure collection. However, for this algorithm
/// the assignment has to be done in the correct sequence since otherwise it
/// results in prematurely releasing of the node.
/// </notes>
template<class data_type>
void inplace_reverse_list(link_list_node_ptr_type<data_type>& linked_list)
{
	using ptr_type = link_list_node_ptr_type<data_type>;

	ptr_type previous = nullptr;

	while (linked_list != nullptr && linked_list->next != nullptr)
	{
		auto current = std::move(linked_list);
		linked_list = std::move(current->next);
		current->next = std::move(previous);
		previous = std::move(current);
	}

	if (linked_list != nullptr)
		linked_list->next = std::move(previous);
}
