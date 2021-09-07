#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "map_annex.hpp"
#include "ft_iterator.hpp"
#include <cstddef>

namespace ft {

	template <class T, class Comp>
	class const_map_iterator;

	template <class T, class Comp>
	class map_iterator {
		
		public:
			typedef T								value_type;
			typedef	value_type&						reference;
			typedef value_type*						pointer;
			typedef ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;
			
		protected:
			typedef ft::__map_node<value_type>		__node;
			typedef __node*							__node_pointer;
			typedef	__node&							__node_reference;
			typedef Comp							value_compare;
			typedef map_iterator<T, Comp>					__it__;
			template<class, class, class, class>
			friend class map;
			
			__node_pointer	__findMin__(__node_pointer);
			__node_pointer	__findMax__(__node_pointer);
		
		public:
			map_iterator() : node() {};
			map_iterator(const map_iterator &x) {
				this->node = x.node;
			};
			map_iterator &operator=(const map_iterator &x) {
				this->node = x.node;
				return *this;
			};
			map_iterator(__node_pointer const x) : node(x) {};

			operator const_map_iterator<T,Comp>() {
				return const_map_iterator<T,Comp>(this->node);
			}

			reference		operator*() const {
				return (*this->node).__pair;
			}

			pointer			operator->() const {
				return &((*this->node).__pair);
			}
			
			map_iterator operator++() {
			if (!node->right && node->parent && value_compare()(node->__pair, node->parent->__pair))
				node = node->parent;
			else if (!node->right && node->parent && value_compare()(node->parent->__pair, node->__pair))
				node = node->parent->parent;
			else
				node = __findMin__(node->right);
			return *this;
			};
	
			map_iterator operator--() {
				if ((!node->left && node->parent && Comp()(node->parent->__pair, node->__pair)) || (node->left == node->parent))
					node = node->parent;
				else if (!node->left && node->parent && Comp()(node->__pair, node->parent->__pair))
					node = node->parent->parent;
				else
					node = __findMax__(node->left);
				return *this;
			};

			map_iterator operator++(int) {
				map_iterator tmp(*this);
				operator++();
				return (tmp);
			};
			map_iterator operator--(int) {
				map_iterator tmp(*this);
				operator--();
				return (tmp);
			};


			bool	operator==(const map_iterator &rhs) const;
			bool	operator!=(const map_iterator &rhs) const;
		private:
			__node_pointer node;
	};

	template <typename T, class Comp>
	bool	map_iterator<T, Comp>::operator==(const map_iterator &rhs) const {
		return (this->node == rhs.node);
	}

	template <typename T, class Comp>
	bool	map_iterator<T, Comp>::operator!=(const map_iterator &rhs) const {
		return (this->node != rhs.node);
	}

		template <class T, class Comp>
	typename map_iterator<T,Comp>::__node_pointer map_iterator<T,Comp>::__findMin__(__node_pointer node)
	{
		if (!node || (node->parent == node->left))
			return node;
		while (node->left)
			node= node->left;
		return (node);
	}

	template <class T, class Comp>
	typename map_iterator<T,Comp>::__node_pointer map_iterator<T,Comp>::__findMax__(__node_pointer node)
	{
		if (!node || (node->parent == node->right))
			return node;
		while (node->right)
			node= node->right;
		return (node);
	}

}

#endif