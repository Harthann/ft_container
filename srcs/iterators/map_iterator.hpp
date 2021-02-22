#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "Map.hpp"
#include "ft_iterator.hpp"

namespace ft {

template <class T>
class map_iterator
{
	private:
		typedef T									__node;
		typedef typename __node::__node_pointer		__node_pointer;
		typedef	typename __node::__node_reference	__node_reference;

		template<class, class, class, class> friend class map;
	
	public:
		typedef typename __node::pointer			pointer;
		typedef typename __node::reference			reference;
		typedef typename __node::value_type			value_type;
		typedef typename __node::difference_type	difference_type;

		map_iterator() : node() {};
		map_iterator(__node_pointer const x) { node = x;};
		map_iterator &operator=(__node_pointer const x) {node = x; return *this; };

		reference operator*() {
			return ((*node).__pair);
		}

		pointer	operator->() {
			return (&(*node).__pair);
		}

	private:
		__node_pointer node;
};

}

#endif