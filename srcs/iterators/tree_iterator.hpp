#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "map_annex.hpp"
#include "ft_iterator.hpp"
#include "map_iterator.hpp"
#include <cstddef>

namespace ft {

    template <class T, class Comp>
    class tree_iterator {

        public:
			typedef T								value_type;
			typedef	value_type&						reference;
			typedef value_type*						pointer;
			typedef std::ptrdiff_t					difference_type;
			
			typedef ft::bidirectional_iterator_tag	iterator_category;
		protected:
			typedef ft::__map_node<value_type>		__node;
			typedef __node*							__node_pointer;
			typedef	__node&							__node_reference;
			typedef Comp							value_compare;
			template<class, class, class, class>
			friend class map;

			__node_pointer	__findMin__(__node_pointer);
			__node_pointer	__findMax__(__node_pointer);


        public:
            tree_iterator() : node() {};
            tree_iterator(const __node_pointer x) : node(x) {};
            tree_iterator(const tree_iterator &x) : node(x.node) {};
            tree_iterator	operator=(const tree_iterator &x) {
                this->node = x.node;
                return *this;
            };
            virtual ~tree_iterator() {};

            tree_iterator &operator++();
            tree_iterator operator++(int);
            tree_iterator &operator--();
            tree_iterator operator--(int);

            bool operator==(const tree_iterator &rhs) const;
            bool operator!=(const tree_iterator &rhs) const;

        protected:
		    __node_pointer node;
    };

    template <class T, class Comp>
    tree_iterator<T,Comp>   &tree_iterator<T,Comp>::operator++() {
        if (!node->right && node->parent && value_compare()(node->__pair, node->parent->__pair))
			node = node->parent;
		else if (!node->right && node->parent && value_compare()(node->parent->__pair, node->__pair))
		{
			__node_pointer dest = node->parent;
			while (value_compare()(dest->__pair, node->__pair) && dest->parent)
				dest = dest->parent;
			node = dest;
		}
		else
			node = __findMin__(node->right);
		return *this;
    }

    template <class T, class Comp>
    tree_iterator<T,Comp>   &tree_iterator<T,Comp>::operator--() {
        if ((!node->left && node->parent && Comp()(node->parent->__pair, node->__pair)) || (node->left == node->parent))
			node = node->parent;
		else if (!node->left && node->parent && Comp()(node->__pair, node->parent->__pair))
		{
			__node_pointer dest = node->parent;
			while (value_compare()(node->__pair, dest->__pair) && dest->parent)
				dest = dest->parent;
			node = dest;
		}
		else
			node = __findMax__(node->left);
		return *this;
    }

    template <class T, class Comp>
    tree_iterator<T,Comp>	tree_iterator<T,Comp>::operator++(int) {
        tree_iterator tmp(*this);
        operator++();
        return tmp;
    }

    template <class T, class Comp>
    tree_iterator<T,Comp> tree_iterator<T,Comp>::operator--(int) {
        tree_iterator tmp(*this);
        operator--();
        return tmp;
    }

	template <typename T, class Comp>
	bool	tree_iterator<T, Comp>::operator==(const tree_iterator &rhs) const {
		return (this->node == rhs.node);
	}

	template <typename T, class Comp>
	bool	tree_iterator<T, Comp>::operator!=(const tree_iterator &rhs) const {
		return (this->node != rhs.node);
	}

    	template <class T, class Comp>
	typename tree_iterator<T,Comp>::__node_pointer tree_iterator<T,Comp>::__findMin__(__node_pointer node)
	{
		if (!node || (node->parent == node->left))
			return node;
		while (node->left)
			node= node->left;
		return (node);
	}

	template <class T, class Comp>
	typename tree_iterator<T,Comp>::__node_pointer tree_iterator<T,Comp>::__findMax__(__node_pointer node)
	{
		if (!node || (node->parent == node->right))
			return node;
		while (node->right)
			node= node->right;
		return (node);
	}
}



#endif