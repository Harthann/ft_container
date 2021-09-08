#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "tree_iterator.hpp"

namespace ft {

	template <class T, class Comp>
	class map_iterator : public tree_iterator<T,Comp> {

		private:
	     	typedef	tree_iterator<T,Comp>	__it__;
        	
		public:
			typedef	typename __it__::value_type			value_type;
			typedef	typename __it__::reference			reference;
			typedef	typename __it__::pointer				pointer;
			typedef	typename __it__::difference_type		difference_type;
			typedef	typename __it__::iterator_category		iterator_category;
		
		private:
			typedef ft::__map_node<value_type>		__node;
			typedef __node*							__node_pointer;
			typedef	__node&							__node_reference;
			typedef Comp							value_compare;
		
		public:
			map_iterator() : tree_iterator<T,Comp>() {};
			map_iterator(const __node_pointer x) : tree_iterator<T,Comp>(x) {};
			map_iterator(const map_iterator &x) : tree_iterator<T,Comp>(x) {};
			~map_iterator() {};

			map_iterator	&operator++() { __it__::operator++(); return *this; };
			map_iterator	&operator--() { __it__::operator--(); return *this; };
			map_iterator	operator++(int) {
				map_iterator tmp(*this);
				operator++();
				return tmp;
			};
			map_iterator	operator--(int)  {
				map_iterator tmp(*this);
				operator--();
				return tmp;
			};

			reference operator*() const {
				return (this->node->__pair);
			};

			pointer operator->() const {
				return &(this->node->__pair);
			};
	};

}

#endif