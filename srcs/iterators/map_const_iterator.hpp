#ifndef MAP_CONST_ITERATOR
#define MAP_CONST_ITERATOR

#include "map_iterator.hpp"

namespace ft {

	template <class T, class Comp>
	class map_const_iterator : public map_iterator<const T, Comp>
	{
		public:
			map_const_iterator() : map_iterator<const T,Comp>() {};
			map_const_iterator(ft::__map_node<const T>* const x) : map_iterator<const T,Comp>(x) {};
			map_const_iterator(map_const_iterator& x) : map_iterator<const T,Comp>(x) {};
			map_const_iterator(const map_const_iterator &x) {
				map_iterator<const T, Comp>::node = x.node;
			}
			map_const_iterator operator=(const map_const_iterator &x) {
				map_iterator<const T, Comp>::node = x.node;
				return *this;
			}
			map_const_iterator &operator=(map_iterator<T, Comp> & x) {
				map_iterator<const T, Comp>::node = x.node;
				return *this;
			};
			// using map_iterator<const T,Comp>::operator=;

	};

}

#endif