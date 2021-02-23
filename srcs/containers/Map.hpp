#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "map_iterator.hpp"

namespace ft {

// template <class T1, class T2>
// struct pair {
// 	typedef T1 first_type;
// 	typedef T2 second_type;

// 	first_type	first;
// 	second_type	second;

// 	pair() : first(), second() {};
// 	pair(first_type const &first, second_type const &second) : first(first), second(second) {};

// 	pair &operator=(const pair& other) {this->first = other.first; this->second = other.second; return *this};
// };

template <class T>
struct __map_node
{
	typedef T				value_type;
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


template <class Key,
			class T,
			class Compare = std::less<Key>,
			class Alloc = std::allocator<std::pair<const Key,T> > >
class map 
{
	private:
		typedef	__map_node<std::pair<const Key, T> >	__node;
		typedef	__node*					__node_pointer;
		typedef	__node&					__node_reference;

	public:
		typedef	Key											key_type;
		typedef T											mapped_type;
		typedef	std::pair<const Key, T> 					value_type;
		typedef	Compare										key_compare;
		// typedef	...			value_compa
		typedef	Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::map_iterator<__node>					iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef	size_t										size_type;

		/*#######################\
		##		CONSTRUCTOR		##
		\#######################*/
		
		map(const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());

		size_type	max_size() const { return __node_allocator().max_size(); };

		/*#######################\
		##		ITERATOR		##
		\#######################*/

		iterator begin();
		iterator end();

		/*#######################\
		##		MODIFIERS		##
		\#######################*/

		std::pair<iterator ,bool>	insert(const value_type& val);
		void						erase(iterator position);

	private:
		typedef typename allocator_type::template rebind<__node>::other	__node_allocator;

		__node_pointer	__insert_(const value_type& val, __node_pointer node, std::pair<iterator ,bool>&,__node_pointer);
		int							__weight__(__node_pointer node);
		void						__print__(__node_pointer) const;
		__node_pointer				__leftRotate__(__node_pointer node);
		__node_pointer				__rightRotate__(__node_pointer node);
		void						__updateGhost__();
		void						__erase__(__node_pointer);

		__node_pointer		head;
		__node_pointer		ghost;
		allocator_type		__alloc;
		__node_allocator	__node_alloc;
};

/*###################################################################################\
**	  _____ ____  _   _  _____ _______ _____  _    _  _____ _______ ____  _____  	##
**	 / ____/ __ \| \ | |/ ____|__   __|  __ \| |  | |/ ____|__   __/ __ \|  __ \ 	##
**	| |   | |  | |  \| | (___    | |  | |__) | |  | | |       | | | |  | | |__) |	##
**	| |   | |  | | . ` |\___ \   | |  |  _  /| |  | | |       | | | |  | |  _  / 	##
**	| |___| |__| | |\  |____) |  | |  | | \ \| |__| | |____   | | | |__| | | \ \ 	##
**	 \_____\____/|_| \_|_____/   |_|  |_|  \_\\____/ \_____|  |_|  \____/|_|  \_\	##
**																					##
\###################################################################################*/                                                                              

template <class T, class Key, class Compare, class Alloc>
map<T, Key, Compare, Alloc>::map(const key_compare&, const allocator_type& alloc)
: head(0), __alloc(alloc)
{
	ghost = __node_alloc.allocate(1);
	__node_alloc.construct(ghost, value_type());
	ghost->parent = 0;
	ghost->left = 0;
	ghost->right = 0;
	ghost->__node_weight = 0;
}


/*###############################################################\
**	 _____ _______ ______ _____         _______ ____  _____  	##
**	|_   _|__   __|  ____|  __ \     /\|__   __/ __ \|  __ \ 	##
**	  | |    | |  | |__  | |__) |   /  \  | | | |  | | |__) |	##
**	  | |    | |  |  __| |  _  /   / /\ \ | | | |  | |  _  / 	##
**	 _| |_   | |  | |____| | \ \  / ____ \| | | |__| | | \ \ 	##
**	|_____|  |_|  |______|_|  \_\/_/    \_\_|  \____/|_|  \_\	##
**	                                                         	##
\###############################################################*/

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::iterator	map<T, Key, Compare, Alloc>::begin()
{
	__node_pointer tmp = head;

	while (tmp->left && tmp->__pair.first > tmp->left->__pair.first)
		tmp = tmp->left;
	return (tmp);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::iterator	map<T, Key, Compare, Alloc>::end()
{
	return (ghost);
}

/*###################################################################\
**	 __  __  ____  _____ _____ ______ _____ ______ _____   _____ 	##
**	|  \/  |/ __ \|  __ \_   _|  ____|_   _|  ____|  __ \ / ____|	##
**	| \  / | |  | | |  | || | | |__    | | | |__  | |__) | (___  	##
**	| |\/| | |  | | |  | || | |  __|   | | |  __| |  _  / \___ \ 	##
**	| |  | | |__| | |__| || |_| |     _| |_| |____| | \ \ ____) |	##
**	|_|  |_|\____/|_____/_____|_|    |_____|______|_|  \_\_____/ 	##
**	                                                             	##
\###################################################################*/

template <class T, class Key, class Compare, class Alloc>
std::pair<typename map<T, Key, Compare, Alloc>::iterator, bool> map<T, Key, Compare, Alloc>::insert(const value_type& val)
{
	std::pair<iterator, bool> ret;

	head = __insert_(val, head, ret, NULL);
	__updateGhost__();
	return (ret);
}

template <class T, class Key, class Compare, class Alloc>
void	 map<T, Key, Compare, Alloc>::erase(iterator pos)
{
	__erase__(pos.node);
}


/*###################################################################################################\
**	 _____  _____  _______      __  _______ ______   __  __ ______ __  __ ____  ______ _____  		##	
**	|  __ \|  __ \|_   _\ \    / /\|__   __|  ____| |  \/  |  ____|  \/  |  _ \|  ____|  __ \ 		##	
**	| |__) | |__) | | |  \ \  / /  \  | |  | |__    | \  / | |__  | \  / | |_) | |__  | |__) |		##	
**	|  ___/|  _  /  | |   \ \/ / /\ \ | |  |  __|   | |\/| |  __| | |\/| |  _ <|  __| |  _  / 		##	
**	| |    | | \ \ _| |_   \  / ____ \| |  | |____  | |  | | |____| |  | | |_) | |____| | \ \ 		##	
**	|_|    |_|  \_\_____|   \/_/    \_\_|  |______| |_|  |_|______|_|  |_|____/|______|_|  \_\		##
**																									##
\###################################################################################################*/

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer
map<T, Key, Compare, Alloc>::__insert_(const value_type& val, __node_pointer node,
std::pair<typename map<T, Key, Compare, Alloc>::iterator, bool> &ret, __node_pointer parent)
{
	int		balance;
	if (!node || node == ghost)
	{
		node = __node_alloc.allocate(1);
		__node_alloc.construct(node, val);
		node->parent = parent;
		ret = std::pair<iterator, bool>(node, true);
		return (node);
	}
	else if (val.first == node->__pair.first) {
		ret = std::pair<iterator, bool>(node, false);
		return (node);
	}
	else if (val.first < node->__pair.first) {
		node->left = __insert_(val, node->left, ret, node);
	}
	else if (val.first > node->__pair.first) {
		node->right = __insert_(val, node->right, ret, node);
	}

	node->__node_weight = 1 + std::max(__weight__(node->left), __weight__(node->right));
	balance = __weight__(node->left) - __weight__(node->right);
	if (balance < -1 && val.first > node->right->__pair.first) // RR
		return (__leftRotate__(node));
	if (balance < -1 && val.first < node->right->__pair.first) { // RL
		node->right = __rightRotate__(node->right);
		return (__leftRotate__(node));
	}
	if (balance > 1 && val.first < node->left->__pair.first) // LL
		return (__rightRotate__(node));
	if (balance > 1 && val.first > node->left->__pair.first) { // LR
		node->left = __leftRotate__(node->left);
		return (__rightRotate__(node));
	}
	return (node);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer map<T, Key, Compare, Alloc>::__leftRotate__(__node_pointer node)
{
	__node_pointer	tmp_right = node->right;
	__node_pointer	tmp_parent = node->parent;
	
	node->right = tmp_right->left;
	node->parent = tmp_right;
	tmp_right->left = node;
	tmp_right->parent = tmp_parent;
	if (node->right)
		node->right->parent = node;

	node->__node_weight = 1 + std::max(__weight__(node->left), __weight__(node->right));
	tmp_right->__node_weight = 1 + std::max(__weight__(tmp_right->left), __weight__(tmp_right->right));
	return (tmp_right);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer map<T, Key, Compare, Alloc>::__rightRotate__(__node_pointer node)
{
	__node_pointer tmp_left = node->left;
	__node_pointer	tmp_parent = node->parent;
	
	node->left = tmp_left->right;
	node->parent = tmp_left;
	tmp_left->right = node;
	tmp_left->parent = tmp_parent;
	if (node->left)
		node->left->parent = node;

	node->__node_weight = 1 + std::max(__weight__(node->left), __weight__(node->right));
	tmp_left->__node_weight = 1 + std::max(__weight__(tmp_left->left), __weight__(tmp_left->right));
	return (tmp_left);
}

template <class T, class Key, class Compare, class Alloc>
int		map<T, Key, Compare, Alloc>::__weight__(__node_pointer node)
{	return (node ? node->__node_weight : 0 );	}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::__updateGhost__()
{
	__node_pointer tmp = head;

	while (tmp->right && tmp->__pair.first < tmp->right->__pair.first)
		tmp = tmp->right;
	tmp->right = ghost;
	ghost->right = tmp;
	ghost->left = tmp;
	ghost->parent = tmp;
}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::__erase__(__node_pointer node)
{
	int	balance;
	balance = __weight__(node->left) - __weight__(node->right);
	if (balance > 0) {
		//	up left node
		if (node->left)
			node->left->parent = node->parent;
		if (node->parent && node->parent->right == node)
			node->parent->right = node->left;
		if (node->parent && node->parent->left == node)
			node->parent->left = node->left;

	}
	else {
		// up right node
	}
}


}

#endif