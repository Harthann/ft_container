#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "list_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class T>
struct	__list_node {
	typedef T						value_type;
	typedef T*						pointer;
	typedef T&						reference;
	typedef std::ptrdiff_t		difference_type;
	typedef __list_node<value_type>	__node;
	typedef __node*					__node_pointer;
	typedef __node&					__node_reference;

	__list_node() : data(0), next(0), previous(0) {};
	__list_node(value_type const &data, __node_pointer const &next, __node_pointer const& prev) : data(data), next(next), previous(prev) {};
	__list_node(const __list_node& base) : data(base.data), next(base.next), previous(base.previous) {};

	__list_node &operator=(const __list_node& base) {
		data = base.data;
		next = base.next;
		previous = base.previous;
	};

	value_type		data;
	__node_pointer	next;
	__node_pointer	previous;
};

template <class T, class Alloc = std::allocator<T> >
class list
{
	
	public:

		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::list_iterator<value_type>							iterator;
		typedef ft::list_iterator<const value_type >					const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t													size_type;


		list(const allocator_type &alloc = allocator_type())
			: __alloc(alloc), __node_alloc() { ghost = __node_alloc.allocate(1); ghost->next = ghost; ghost->previous = ghost; head = ghost;};
		list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
		template <class InputIT>
		list(InputIT its, typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type ite, const allocator_type &alloc = allocator_type());
		list(const list<T,Alloc>& tmp);
		list<T,Alloc> & operator=(list<T,Alloc> const &base);
		~list() {
			while (!empty())
				pop_front();
			delete ghost;
		};
		
		//		ITERATORS

		iterator begin() { return (head); };
		iterator end() { return (ghost); };
		reverse_iterator rbegin() { return (ft::prev(iterator(ghost))); };
		reverse_iterator rend() { return (ft::prev(iterator(head))); };
		const_iterator begin() const {
			typedef __list_node<const value_type>* __const_node;
			__const_node const_head = reinterpret_cast<__const_node>(head);
			return (const_head);
		};
		const_iterator end() const {
			typedef __list_node<const value_type>* __const_node;
			__const_node const_ghost = reinterpret_cast<__const_node>(ghost);
			return (const_ghost);
		};
		const_reverse_iterator rbegin() const { return (ft::prev(iterator(ghost))); };
		const_reverse_iterator rend() const { return (ft::prev(iterator(begin))); };

		//		CAPACITY

		bool empty() const {return (head == ghost); };
		size_type	size() const {
			return (ft::distance(begin(), end())); };
		size_type	max_size() const { return (__node_allocator().max_size()); };

		//		ELEMENT ACCESS

		reference front() { return head->data;};
		const_reference front() const {return head->data;};
		reference back() {return *ft::prev(end());};
		const_reference back() const {return ft::prev(end());};

		//		MODIFIERS

		template <class InputIT>
		typename ft::enable_if<ft::is_input_iterator<InputIT>::value, bool>::
		void_t		assign(InputIT its, InputIT ite);
		void		assign(size_type n, value_type const &val);
		void		push_front(const value_type& tmp);
		void		pop_front() ;
		void		push_back(const value_type& tmp);
		void		pop_back();
		iterator	insert(iterator pos, const value_type &val);
		void		insert(iterator pos, size_type n, const value_type &val);
		template <class InputIT>
		typename ft::enable_if<ft::is_input_iterator<InputIT>::value, bool>::
		void_t		insert(iterator pos, InputIT its, InputIT ite);
		iterator	erase(iterator pos);
		iterator	erase(iterator first, iterator last);
		void		resize (size_type n, value_type val = value_type());
		void		clear() { while (!empty()) erase(begin(), end()); };
		void		swap(list& x);

		//		OPERATIONS

		void		splice(iterator pos, list& x);
		void		splice(iterator pos, list& x, iterator i);
		void		splice(iterator position, list& x, iterator first, iterator last);
		void		remove(const value_type& val);
		template <class Predicate>
		void		remove_if(Predicate pred);
		void		unique();
		template <class BinaryPredicate>
  		void	unique(BinaryPredicate binary_pred);
		void	merge(list<T>& x);
		template <class Compare>
		void	merge(list<T>& x, Compare comp);
		void		sort();
		template <class Compare>
		void		sort(Compare comp);
		void		reverse();
	private:
		typedef ft::__list_node<value_type>									__node;
		typedef typename allocator_type::template rebind<__node>::other	__node_allocator;
		typedef ft::__list_node<value_type>*								__node_pointer;

		void		__exchange__(iterator first, iterator second);
		iterator	__unlink__(iterator it);
		iterator	__link__(iterator pos, iterator it);
		template <class Compare>
		iterator	__find_sorted_pos__(value_type &val, Compare comp);
		
		__node_pointer		head;
		__node_pointer		ghost;
		allocator_type		__alloc;
		__node_allocator	__node_alloc;

};



//###################################
//##	CONSTRUCTOR/DESTRUCTOR		#
//###################################

template <class T, class A>
template <class InputIT>
list<T,A>::list(InputIT its, typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::type ite,  const allocator_type &alloc)
{
	__alloc = alloc;
	__node_alloc = __node_allocator();
	ghost = __node_alloc.allocate(1);
	ghost->next = ghost;
	ghost->previous = ghost;
	head = ghost;
	while (its != ite)
	{
		push_back(*its);
		++its;
	}
}

template <class T, class A>
list<T,A>::list(const list<T,A>& base)
{
	__alloc = base.__alloc;
	__node_alloc = base.__node_alloc;
	ghost = __node_alloc.allocate(1);
	ghost->next = ghost;
	ghost->previous = ghost;
	head = ghost;
	for (const_iterator cit = base.begin(); cit != base.end(); ++cit)
		push_back(*cit);
}

template <class T, class A>
list<T,A>::list(size_type n, const value_type &val, const allocator_type &alloc)
{
	__alloc = alloc;
	__node_alloc = __node_allocator();
	ghost = __node_alloc.allocate(1);
	ghost->next = ghost;
	ghost->previous = ghost;
	head = ghost;
	for (; n > 0; --n)
		push_front(val);
}

template <class T, class A>
list<T,A> &list<T,A>::operator=(const list<T,A>& base)
{
	for (const_iterator cit = base.begin(); cit != base.end(); ++cit)
		push_back(*cit);
	return (*this);
}

//####################################
//###		PUSH/POP FRONT/BACK		##
//####################################


template <class T, class A>
void list<T,A>::push_front(const value_type& value)
{
	__node_pointer tmp = __node_alloc.allocate(1);
	tmp->data = value;
	tmp->next = (head != ghost) ? head : ghost;
	tmp->previous = ghost;
	ghost->next = tmp;
	head->previous = tmp;
	head = tmp;
}

template <class T, class A>
void list<T,A>::push_back(const value_type& value)
{
	__node_pointer tmp = __node_alloc.allocate(1);
	tmp->data = value;
	tmp->next = ghost;
	if (head == ghost) {
		tmp->previous = ghost;
		head = tmp;
		ghost->next = tmp;
	}
	else {
		tmp->previous = ghost->previous;
		ghost->previous->next = tmp;
	}
	ghost->previous = tmp;
}

template <class T, class A>
void	list<T,A>::pop_front()
{
	__node_pointer tmp = head->next;
	__node_alloc.destroy(head);
	delete head;
	head = tmp;
}

template <class T, class A>
void	list<T,A>::pop_back()
{
	__node_pointer tmp = ghost->previous;
	if (tmp == head) {
		head = ghost;
		ghost->next = 0;
		ghost->previous = 0;
	}
	else {
		tmp->previous->next = ghost;
		ghost->previous = tmp->previous;
	}
	__node_alloc.destroy(tmp);
	delete tmp;
}

//###############################
//##		INSERTION	#
//###############################

template <class T, class A>
template <class InputIT>
typename ft::enable_if<ft::is_input_iterator<InputIT>::value, bool>::
void_t	list<T,A>::assign(InputIT its, InputIT ite)
{
	while (!empty())
		pop_front();
	for (; its != ite; ++its)
		push_back(*its);
}


template < class T, class A>
void	list<T,A>::assign(size_type n, value_type const &val)
{
	while (!empty())
		pop_front();
	for (; n > 0; --n)
		push_front(val);
	
}

//############################
//##		ERASE			##
//############################

template <class T, class A>
typename list<T,A>::iterator	list<T,A>::erase(list<T,A>::iterator pos)
{
	list<T,A>::iterator ret = ft::next(pos);
	pos.node->previous->next = pos.node->next;
	pos.node->next->previous = pos.node->previous;
	if (pos == begin())
		head = pos.node->next;
	__node_alloc.destroy(pos.node);
	delete pos.node;
	return ret;
}

template <class T, class A>
typename list<T,A>::iterator	list<T,A>::erase(list<T,A>::iterator first, list<T,A>::iterator last)
{
	while (first != last) {
		first = erase(first);
	}
	return last;
}


//###################
//#		INSERT		#
//###################

template <class T, class A>
typename list<T,A>::iterator	list<T,A>::insert(iterator pos, const value_type &val)
{
	insert(pos, 1, val);
	return (ft::prev(pos));
}

template <class T, class A>
void	list<T,A>::insert(iterator pos, size_type n, const value_type &val)
{
	__node_pointer new_node;

	while (n > 0)
	{
		new_node = __node_alloc.allocate(1);
		new_node->data = val;
		new_node->next = pos.node;
		new_node->previous = pos.node->previous;
		if (pos == begin())
		{
			head = new_node;
			ghost->next = head;
		}
		else
		{
			pos.node->previous->next = new_node;
			pos.node->previous = new_node;
		}
		if (pos == end())
			ghost->previous = new_node;
		--n;
	}
}

template <class T, class A>
template <class InputIT>
typename ft::enable_if<ft::is_input_iterator<InputIT>::value, bool>::
void_t	list<T,A>::insert(iterator pos, InputIT first, InputIT last)
{
	while (last != first)
	{
		insert(pos, *first);
		++first;
	}
}

template <class T, class A>
void	list<T,A>::resize(size_type n, value_type val)
{
	while (n > size())
		push_back(val);
	while (size() > n)
		pop_back();
}

template <class T, class A>
void	list<T,A>::swap(list& x)
{
	__node_pointer tmp;

	tmp = x.head;
	x.head = this->head;
	this->head = tmp;
	tmp = x.ghost;
	x.ghost = this->ghost;
	this->ghost = tmp;
}

//###################
//#		SPLCIE		#
//###################s

template <class T, class A>
void		list<T,A>::splice(iterator pos, list& x, iterator i)
{
	x.__unlink__(i);
	__link__(pos, i);
}

template <class T, class A>
void	list<T,A>::splice(iterator pos, list&x)
{
	splice(pos, x, x.begin(), x.end());
}


template <class T, class A>
void	list<T,A>::splice(iterator pos, list&x, iterator first, iterator last)
{
	__node_pointer tmp = last.node->previous;

	first.node->previous->next = last.node;
	last.node->previous = first.node->previous;
	if (first.node == x.head)
		x.head = last.node;
	first.node->previous = pos.node->previous;
	first.node->previous->next = first.node;
	pos.node->previous = tmp;
	tmp->next = pos.node;
}


//########################
//##		REMOVE		##
//########################

template <class T, class A>
void list<T,A>::remove(const value_type& val)
{
	iterator it = begin();
	while (it != end())
	{
		if (*it == val)
		{
			++it;
			erase(ft::prev(it));
		}
		else
			++it;
	}
}

template <class T, class A>
template <class Predicate>
void list<T,A>::remove_if(Predicate pred)
{
	iterator it = begin();
	while (it != end())
	{
		if (pred(*it))
		{
			++it;
			erase(ft::prev(it));
		}
		else
			++it;
	}
}

//################################//
//###		SORT/MERGE/UNIQUE	##//
//################################//

template <class T, class A>
void	list<T,A>::sort()
{
	iterator tmp;
	for (size_type i = 0; i < size() - 1; ++i)
	{
		tmp = ft::next(begin(), i);
		for (iterator it = tmp; it != end(); ++it)
		{
			if (*it < *tmp)
				tmp = it;
		}
		__unlink__(tmp);
		__link__(ft::next(begin(), i), tmp);
	}
}


template <class T, class A>
template <class Compare>
void	list<T,A>::sort(Compare comp)
{
	iterator tmp;
	for (size_type i = 0; i < size() - 1; ++i)
	{
		tmp = ft::next(begin(), i);
		for (iterator it = tmp; it != end(); ++it)
		{
			if (comp(*it, *tmp))
				tmp = it;
		}
		__unlink__(tmp);
		__link__(ft::next(begin(), i), tmp);
	}
}

template <class T, class A>
void	list<T,A>::unique()
{
	for (iterator it = ft::next(begin()); it != end(); ++it)
	{
		if (*it == *ft::prev(it))
		{
			--it;
			erase(ft::next(it));
		}
	}
}

template <class T,class A>
template <class BinaryPredicate>
void	list<T,A>::unique(BinaryPredicate binary_pred)
{
	for (iterator it = ft::next(begin()); it != end(); ++it)
	{
		if (binary_pred(*it, *ft::prev(it)))
		{
			--it;
			erase(ft::next(it));
		}
	}
}

template <class T, class A>
void	list<T,A>::reverse()
{
	std::swap(ghost->previous, ghost->next);
	head = ghost->next;
	for (iterator it = begin(); it != end(); ++it)
		std::swap(it.node->previous, it.node->next);
}

template <class T, class A>
void	list<T,A>::merge(list<T>& x)
{
	iterator pos = begin();
	iterator tmp;
	while (!x.empty() && &x != this)
	{
		tmp = x.begin();
		x.__unlink__(tmp);
		for (iterator it = begin(); it != end(); ++it)
		{
			if ( *tmp < *it)
				break;
			pos = it;
		}
		__link__(pos, tmp);
	}
}

template <class T, class A>
template <class Compare>
typename list<T,A>::iterator	list<T,A>::__find_sorted_pos__(value_type &val, Compare comp)
{
	iterator it = begin();

	while (it != end())
	{
		if (comp(val, *it))
			break ;
		++it;
	}
	return (it);
}

template <class T, class A>
template <class Compare>
void	list<T,A>::merge(list<T>& x, Compare comp)
{
	iterator pos;
	iterator tmp;
	while (!x.empty() && &x != this)
	{
		tmp = x.begin();
		pos = begin();
		x.__unlink__(tmp);
		pos = __find_sorted_pos__(*tmp, comp);
		__link__(pos, tmp);
	}
}

//#############################//
//###	PRIVATE MEMBER		 ##//
//#############################//

template <class T, class A>
typename list<T,A>::iterator	list<T,A>::__unlink__(iterator it)
{
	iterator ret = ft::next(it);
	__node_pointer prev = it.node->previous;
	__node_pointer next = it.node->next;
	prev->next = next;
	next->previous = prev;
	it.node->previous = 0;
	it.node->next = 0;
	if (it == begin())
		head = ret.node;
	return ret;
}

template <class T, class A>
typename list<T,A>::iterator	list<T,A>::__link__(iterator pos, iterator it)
{
	it.node->next = pos.node;
	it.node->previous = pos.node->previous;
	pos.node->previous = it.node;
	it.node->previous->next = it.node;
	if (pos == begin())
		head = it.node;
	return it;
}

template <class T, class A>
void	list<T,A>::__exchange__(iterator first, iterator second)
{
	iterator pos_first;
	iterator pos_second;
	pos_second = __unlink__(second);
	pos_first = __unlink__(first);
	__link__(pos_first, second);
	__link__(pos_second, first);
}

//################################//
//#		NON MEMEBR OVERLOAD		##//
//################################//

template <class T, class Alloc>
void swap (list<T,Alloc>& x, list<T,Alloc>& y) { x.swap(y); }

//####################//
//##	COMPARISON	##//
//####################//

template <class T, class Alloc>
bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
}

}

#endif
