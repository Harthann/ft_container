#ifndef STACK_HPP
#define STACK_HPP


 //	missing operaotr []
 //	operator non member =/-
 //	const/non const comparison it

#include "vector.hpp"
#include <cstddef>

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		stack(const container_type& ctnr = container_type()) : c(ctnr) {};

		bool		empty() const {return c.empty();};
		size_type	size() const {return c.size();};

		value_type& top() { return c.back(); };
		const value_type& top() const { return c.back(); };

		void	push(const value_type& val) { c.push_back(val); };
		void	pop() { c.pop_back(); };

		template <class A, class C>
		friend bool operator==(const stack<A,C>& lhs, const stack<A,C>& rhs);
		template <class A, class C>
		friend bool operator!=(const stack<A,C>& lhs, const stack<A,C>& rhs);
		template <class A, class C>
		friend bool operator<(const stack<A,C>& lhs, const stack<A,C>& rhs);
		template <class A, class C>
		friend bool operator<=(const stack<A,C>& lhs, const stack<A,C>& rhs);
		template <class A, class C>
		friend bool operator>(const stack<A,C>& lhs, const stack<A,C>& rhs);
		template <class A, class C>
		friend bool operator>=(const stack<A,C>& lhs, const stack<A,C>& rhs);

	protected:
		container_type c;
};

//####################//
//##	COMPARISON	##//
//####################//

template <class T, class Container>
bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c == rhs.c);
}

template <class T, class Container>
bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c != rhs.c);
}

template <class T, class Container>
bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c < rhs.c);
}

template <class T, class Container>
bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c <= rhs.c);
}

template <class T, class Container>
bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c > rhs.c);
}

template <class T, class Container>
bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
	return (lhs.c >= rhs.c);
}

}

#endif