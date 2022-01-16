#pragma once

#include "node_data.h"
#include <ranges>
#include <string>
#include <vector>

template<class data_type>
auto initialize_linked_list(const std::initializer_list<data_type>& values)
{
	using node_type = linked_list_node<data_type>;
	using node_ptr_type = link_list_node_ptr_type<data_type>;

	node_ptr_type root_node = nullptr;
	node_type* prior_node = nullptr;

	for (const auto& value : values)
	{
		auto node = std::make_unique<linked_list_node<data_type>>(value);
		const auto node_ptr = node.get();

		auto& list_node = (prior_node == nullptr)
			            ? root_node
			            : prior_node->next;

		list_node = std::move(node);
		prior_node = node_ptr;
	}

	return std::move(root_node);
}

template<class data_type>
auto to_vector(const link_list_node_ptr_type<data_type>& values) -> std::vector<data_type>
{
	if (values == nullptr) return {};

	return { values->cbegin(), values->cend() };
}

template<class data_type>
auto to_ranges_view(const typename linked_list_node<data_type>::ptr_type& values)
{
	const auto& vec = to_vector(values);
	return std::ranges::subrange(vec.begin(), vec.end());
}

template<class data_type>
auto to_vector_nodes(typename linked_list_node<data_type>::ptr_type& values)
{
	using ptr_type = linked_list_node<data_type>::ptr_type;

	std::vector<ptr_type> vector_nodes;

	auto node = std::move(values);

	while (node != nullptr)
	{
		vector_nodes.push_back(std::move(node));
		node = std::move(vector_nodes.back()->next);
	}

	return vector_nodes;
}
