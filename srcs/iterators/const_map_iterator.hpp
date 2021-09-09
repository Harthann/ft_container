#ifndef CONST_MAP_ITERATOR_HPP
#define CONST_MAP_ITERATOR_HPP

#include "tree_iterator.hpp"

namespace ft {

	template <class T, class Comp>
	class const_map_iterator : public tree_iterator<T,Comp> {

		private:
	     	typedef	tree_iterator<T,Comp>	__it__;
        	
		public:
			typedef	typename __it__::value_type				value_type;
			typedef	const value_type &						reference;
			typedef	const value_type *						pointer;
			typedef	typename __it__::difference_type		difference_type;
			typedef	typename __it__::iterator_category		iterator_category;
		
		private:
			typedef ft::__map_node<value_type>		__node;
			typedef __node*							__node_pointer;
			typedef	__node&							__node_reference;
			typedef Comp							value_compare;
		
		public:
			const_map_iterator() : tree_iterator<T,Comp>() {};
			const_map_iterator(const __it__ &x) : tree_iterator<T,Comp>(x) {};
			const_map_iterator(const __node_pointer x) : tree_iterator<T,Comp>(x) {};
			~const_map_iterator() {};

			const_map_iterator	&operator++() { __it__::operator++(); return *this;};
			const_map_iterator	&operator--() { __it__::operator--(); return *this; };
			const_map_iterator	operator++(int) { return __it__::operator++(0); };
			const_map_iterator	operator--(int) { return __it__::operator--(0); };

			reference operator*() const {
				return (this->node->__pair);
			};

			pointer operator->() const {
				return &(this->node->__pair);
			};
	};

}

#endif