#ifndef MAP_ANNEX_HPP
#define MAP_ANNEX_HPP

namespace ft {

	template <class T>
	struct __map_node
	{
		typedef T					value_type;
		typedef	value_type*			pointer;
		typedef	value_type&			reference;
		typedef	std::ptrdiff_t	difference_type;

		typedef	__map_node*	__node_pointer;
		typedef	__map_node&	__node_reference;

		__map_node() : __pair(), left(0), right(0), parent(0), __node_weight(1) {};
		__map_node(value_type const &x) : __pair(x), left(0), right(0), parent(0), __node_weight(1) {};
		__map_node(const __map_node& x) : __pair(x.__pair), left(x.left), right(x.right), parent(x.parent), __node_weight(x.__node_weight) {};
		__map_node &operator=(const __map_node& x) {
			__pair = x.__pair;
			left = x.left; right = x.right; parent = x.parent;
			__node_weight = x.__node_weight;
			return *this;
		};

		value_type			__pair;
		__node_pointer		left;
		__node_pointer		right;
		__node_pointer		parent;
		int					__node_weight;
	};

	template <class T1, class T2>
	struct pair {
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		// pair() : first(), second() {};
		pair(const T1& x = first_type(), const T2& y = second_type()) : first(x), second(y) {};
		~pair() {};

		pair&	operator=(const pair& p)
		{
			this->first = p.first;
			this->second = p.second;
			return *this;
		}
	};


	template<class T1, class T2>
		bool	operator==(const ft::pair<T1, T2>& left, const ft::pair<T1, T2>& right)
		{
			return left.first == right.first && left.second == right.second;
		}

	template<class T1, class T2>
		bool	operator==(ft::pair<T1, T2>& left, ft::pair<T1, T2>& right)
		{
			return left.first == right.first && left.second == right.second;
		}
		
	template<class T1, class T2>
		bool	operator<(const ft::pair<T1, T2>& left, const ft::pair<T1, T2>& right)
		{
			return left.first < right.first || (left.first == right.first && left.second < right.second);
		}

	template<class T1, class T2>
		bool	operator!=(const ft::pair<T1, T2>& left, const ft::pair<T1, T2>& right)
		{
			return (!(left == right));
		}

	template<class T1, class T2>
		bool	operator>(const ft::pair<T1, T2>& left, const ft::pair<T1, T2>& right)
		{
			return (right < left);
		}

	template<class T1, class T2>
		bool	operator<=(const ft::pair<T1, T2>& left, const ft::pair<T1, T2>& right)
		{
			return (!(right < left));
		}

	template<class T1, class T2>
		bool	operator>=(const ft::pair<T1, T2>& left, const ft::pair<T1, T2>& right)
		{
			return (!(left < right));
		}

}

#endif