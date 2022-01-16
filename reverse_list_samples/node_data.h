#pragma once

#include <iterator>
#include <string>
#include <memory>
#include <format>

template<class data_type>
struct linked_list_node
{
	using ptr_type = std::unique_ptr<linked_list_node>;

	data_type data;
	ptr_type next;

	constexpr linked_list_node(const data_type& data_)
	: data(data_)
	{}

	linked_list_node() = delete;
	linked_list_node(const linked_list_node&) = delete;
	linked_list_node& operator=(const linked_list_node&) = delete;

	class iterator
	{
		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = data_type;
			using pointer = data_type*;
			using reference = data_type&;

			iterator() : ptr(nullptr) {}
			iterator(linked_list_node* ptr) : ptr(ptr) {}
			iterator operator++() { ptr = ptr->next.get(); return *this; }
			reference operator*() { return ptr->data; }
			const reference operator*() const { return ptr->data; }

			friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.ptr == rhs.ptr; }
			friend bool operator!=(const iterator& lhs, const iterator& rhs) { return lhs.ptr != rhs.ptr; }
		private:
			linked_list_node* ptr;
	};

	class const_iterator
	{
		public:
			using iterator_category = std::forward_iterator_tag;
			using difference_type = std::ptrdiff_t;
			using value_type = const data_type;
			using pointer = const data_type*;
			using reference = const data_type&;

			const_iterator() : ptr(nullptr) {}
			const_iterator(const linked_list_node* ptr) : ptr(ptr) {}
			const_iterator operator++() { ptr = ptr->next.get(); return *this; }
			reference operator*() const { return ptr->data; }

			friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) { return lhs.ptr == rhs.ptr; }
			friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) { return lhs.ptr != rhs.ptr; }
		private:
			const linked_list_node* ptr;
	};

	auto begin() { return iterator(this); }
	auto end() { return iterator(); }

	auto begin() const { return const_iterator(this); }
	auto end() const { return const_iterator(); }

	auto cbegin() const { return const_iterator(this); }
	auto cend() const { return const_iterator(); }
};

template<class data_type>
using link_list_node_ptr_type = std::unique_ptr<linked_list_node<data_type>>;

template<class data_type, class char_type>
struct std::formatter<linked_list_node<data_type>, char_type>
{
	constexpr auto parse(auto& ctx)
	{
		return std::end(ctx);
	}

	constexpr auto format(const linked_list_node<data_type>& nodes, auto& ctx)
	{
		format_to(ctx.out(), "[");
		format_nodes(nodes, ctx);
		return format_to(ctx.out(), "]");
	}

	private:

	constexpr auto format_nodes(const linked_list_node<data_type>& nodes, auto& ctx)
	{
		if (nodes.next == nullptr) return format_to(ctx.out(), "{}", nodes.data);

		format_to(ctx.out(), "{}, ", nodes.data);

		return format_nodes(*(nodes.next), ctx);
	}
};

template<class data_type, class char_type>
struct std::formatter<link_list_node_ptr_type<typename data_type>, char_type>
{
	constexpr auto parse(auto& ctx)
	{
		return std::end(ctx);
	}

	constexpr auto format(const link_list_node_ptr_type<typename data_type>& ptr, auto& ctx)
	{
		if (ptr == nullptr) return ctx.out();

		std::formatter<linked_list_node<data_type>, char_type> formatter;

		return formatter.format(*ptr, ctx);
	}
};
