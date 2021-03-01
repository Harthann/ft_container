#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "map_iterator.hpp"
#include "vector.hpp"

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
		typedef	__node*									__node_pointer;
		typedef	__node&									__node_reference;

	public:
		typedef	Key												key_type;
		typedef T												mapped_type;
		typedef	std::pair<const Key, T> 						value_type;
		typedef	Compare											key_compare;
		struct value_compare {
			value_compare(key_compare key_comp = key_compare()) : kc(key_comp) {};
			bool operator()(value_type &first, value_type &second) {
				return (kc(first.first, second.first));
			}
			key_compare kc;
		};
		
		typedef	Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef ft::map_iterator<value_type, value_compare>			iterator;
		typedef ft::map_iterator<const value_type, value_compare>	const_iterator;
		typedef std::ptrdiff_t										difference_type;
		typedef	size_t												size_type;

		/*#######################\
		##		CONSTRUCTOR		##
		\#######################*/
		
		map(const key_compare& = key_compare(),
            const allocator_type& = allocator_type());
		template <class InputIT>
		map(InputIT,
			typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::type ,
			const key_compare& = key_compare(),
			const allocator_type& = allocator_type());

		map(const map&);
		map& operator=(const map&);
		~map() {
			if (head != ghost)
				clear();
			__destroyNode__(ghost);
		};


		/*#######################\
		##		CAPACITY		##
		\#######################*/
		size_type	max_size() const { return __node_allocator().max_size(); };
		size_type	size() const;
		bool		empty() const;

		mapped_type&	operator[](const key_type& k);

		/*#######################\
		##		ITERATOR		##
		\#######################*/

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		/*#######################\
		##		OBSERVERS		##
		\#######################*/

		key_compare		key_comp() const;
		value_compare	value_comp() const { return value_compare();};


		/*#######################\
		##		MODIFIERS		##
		\#######################*/

		std::pair<iterator ,bool>	insert(const value_type& val);
		template <class InputIT>
		typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::void_t
			insert(InputIT, InputIT);
		size_type					erase(const key_type& k);
		void						erase(iterator position);
		void						erase(iterator first, iterator last);
		void						clear();
		void						swap(map& x);

		void	print() {__print__(head); std::cout << std::endl;};
		void	__print__(__node_pointer node);
		/*#######################\
		##		OPERATIONS		##
		\#######################*/

		iterator		find(const key_type& k);
		const_iterator	find(const key_type& k) const;
		iterator		lower_bound(const key_type& k);
		// const_iterator	lower_bound(const key_type& k) const;
		iterator		upper_bound(const key_type& k);
		// const_iterator	lower_bound(const key_type& k) const;

	private:
		typedef typename allocator_type::template rebind<__node>::other		__node_allocator;
		typedef typename allocator_type::template rebind<value_type>::other	__pair_alloc;
		// template <class T, class Comp> friend class map_iterator;


		__node_pointer	__insert__(const value_type& val, __node_pointer node, std::pair<iterator ,bool>&,__node_pointer);
		int				__weight__(__node_pointer node);
		void			__print__(__node_pointer) const;
		__node_pointer	__leftRotate__(__node_pointer node);
		__node_pointer	__rightRotate__(__node_pointer node);
		bool			__update__(__node_pointer , bool = false, __node_pointer = NULL);
		__node_pointer	__erase__(__node_pointer, const key_type&);
		__node_pointer	__destroyNode__(__node_pointer node, __node_pointer ret = NULL);
		void			__disableGhost__();
		value_type		__findMin__(__node_pointer node);
		iterator		__find__(__node_pointer node, const key_type& k);
		size_type		__size__(__node_pointer) const;
		void			__clear__(__node_pointer);
		__node_pointer	__copy__(__node_pointer);
		__node_pointer	__assign__(const __node_pointer xnode, __node_pointer node);

		__node_pointer		head;
		__node_pointer		ghost;
		allocator_type		__alloc;
		__node_allocator	__node_alloc;
		key_compare			__key_comp__;
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
map<T, Key, Compare, Alloc>::map(const key_compare& kc, const allocator_type& alloc)
: head(0), __alloc(alloc), __key_comp__(kc)
{
	ghost = __node_alloc.allocate(1);
	__node_alloc.construct(ghost, value_type());
	ghost->parent = 0;
	ghost->left = 0;
	ghost->right = 0;
	ghost->__node_weight = 0;
}

template <class T, class Key, class Compare, class Alloc>
map<T, Key, Compare, Alloc>::map(const map &x)
{
	__key_comp__ = x.__key_comp__;
	__alloc = x.__alloc;
	__node_alloc = __node_allocator();
	head = __copy__(x.head);
	ghost = __node_alloc.allocate(1);
	__node_alloc.construct(ghost, value_type());
	__update__(head);
}

template <class T, class Key, class Compare, class Alloc>
template <class InputIT>
map<T, Key, Compare, Alloc>::map(
							InputIT first,
							typename ft::enable_if<ft::is_input_iterator<InputIT>::value, InputIT>::type last,
							const key_compare& comp,
							const allocator_type& alloc)
: head(0), __alloc(alloc), __key_comp__(comp)
{
	// while ()
}

template <class T, class Key, class Compare, class Alloc>
map<T,Key,Compare,Alloc>& map<T, Key, Compare, Alloc>::operator=(const map &x)
{
	__key_comp__ = key_comp();
	__alloc = allocator_type();
	__node_alloc = __node_allocator();
	head = __assign__(x.head, head);
	if (!ghost) {
		ghost = __node_alloc.allocate(1);
		__node_alloc.construct(ghost, value_type());
	}
	__update__(head);
	return *this;
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

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::const_iterator	map<T, Key, Compare, Alloc>::begin() const
{
	typedef __map_node<const value_type>*	__const_node;
	__node_pointer	tmp = head;

	while (tmp->left && tmp->__pair.first > tmp->left->__pair.first)
		tmp = tmp->left;
	return (reinterpret_cast<__const_node>(tmp));
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::const_iterator	map<T, Key, Compare, Alloc>::end() const
{
	typedef __map_node<const value_type>* __const_node;
	// __const_node const_ghost = reinterpret_cast<__const_node>(ghost);
	return (reinterpret_cast<__const_node>(ghost));
}

/*######################################################################*\
**	  ____  ____   _____ ______ _______      ________ _____   _____ 	##
**	 / __ \|  _ \ / ____|  ____|  __ \ \    / /  ____|  __ \ / ____|	##
**	| |  | | |_) | (___ | |__  | |__) \ \  / /| |__  | |__) | (___  	##
**	| |  | |  _ < \___ \|  __| |  _  / \ \/ / |  __| |  _  / \___ \ 	##
**	| |__| | |_) |____) | |____| | \ \  \  /  | |____| | \ \ ____) |	##
**	 \____/|____/|_____/|______|_|  \_\  \/   |______|_|  \_\_____/ 	##
**																		##
\*######################################################################*/

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::size_type	map<T, Key, Compare, Alloc>::size() const
{
	return (__size__(head));
}

template <class T, class Key, class Compare, class Alloc>
bool		map<T, Key, Compare, Alloc>::empty() const
{
	return (!size());
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::key_compare map<T, Key, Compare, Alloc>::key_comp() const
{
	return (__key_comp__);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::mapped_type&	map<T, Key, Compare, Alloc>::operator[](const key_type& k)
{
	std::pair<iterator, bool> tmp;

	tmp = insert(value_type(k, mapped_type()));
	return (tmp.first->second);
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

	__disableGhost__();
	head = __insert__(val, head, ret, NULL);
	__update__(head);
	return (ret);
}

template <class T, class Key, class Compare, class Alloc>
template <class InputIT>
typename ft::enable_if<is_input_iterator<InputIT>::value, InputIT>::void_t
map<T, Key, Compare, Alloc>::insert(InputIT first, InputIT last)
{
	while (first != last)
	{
		insert(*first);
		++first;
	}
}

template <class T, class Key, class Compare, class Alloc>
void	 map<T, Key, Compare, Alloc>::erase(iterator pos)
{
	__disableGhost__();
	head = __erase__(head, pos.node->__pair.first);
	__update__(head);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::size_type
map<T, Key, Compare, Alloc>::erase(const key_type& k)
{
	__disableGhost__();
	head = __erase__(head, k);
	__update__(head);
	return (1);
}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::erase(iterator first, iterator last)
{
	ft::vector<value_type> tmp;
	while (first != last) {
		tmp.push_back(*first);
		++first;
	}
	for (typename ft::vector<value_type>::iterator it = tmp.begin(); it != tmp.end(); ++it)
		erase((*it).first);
}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::clear()
{
	__disableGhost__();
	__clear__(head);
	head = ghost;
}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::swap(map& x)
{
	std::swap(head, x.head);
	std::swap(ghost, x.ghost);
}

/*###########################################################################\
**	  ____  _____  ______ _____         _______ _____ ____  _   _  _____ 	##
**	 / __ \|  __ \|  ____|  __ \     /\|__   __|_   _/ __ \| \ | |/ ____|	##
**	| |  | | |__) | |__  | |__) |   /  \  | |    | || |  | |  \| | (___  	##
**	| |  | |  ___/|  __| |  _  /   / /\ \ | |    | || |  | | . ` |\___ \ 	##
**	| |__| | |    | |____| | \ \  / ____ \| |   _| || |__| | |\  |____) |	##
**	 \____/|_|    |______|_|  \_\/_/    \_\_|  |_____\____/|_| \_|_____/ 	##
**																			##
\###########################################################################*/

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::iterator	map<T, Key, Compare, Alloc>::find(const key_type& k)
{
	return (__find__(head, k));
}

// template <class T, class Key, class Compare, class Alloc>
// typename map<T, Key, Compare, Alloc>::const_iterator	map<T, Key, Compare, Alloc>::find(const key_type& k) const
// {
// 	return (__find__(head, k));
// }

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::iterator	map<T, Key, Compare, Alloc>::lower_bound(const key_type& k)
{
	for (iterator it = begin(); it !=end(); ++it)
		if (!__key_comp__(it->first, k))
			return (it);
	return end();
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::iterator	map<T, Key, Compare, Alloc>::upper_bound(const key_type& k)
{
	for (iterator it = begin(); it !=end(); ++it)
		if (!__key_comp__(k, it->first))
			return (it);
	return end();
}

/*###########################################################################################################\
**	 _____  _____  _______      __  _______ ______  	 __  __ ______ _______ _    _  ____  _____   _____ 	##
**	|  __ \|  __ \|_   _\ \    / /\|__   __|  ____| 	|  \/  |  ____|__   __| |  | |/ __ \|  __ \ / ____|	##
**	| |__) | |__) | | |  \ \  / /  \  | |  | |__    	| \  / | |__     | |  | |__| | |  | | |  | | (___  	##
**	|  ___/|  _  /  | |   \ \/ / /\ \ | |  |  __|   	| |\/| |  __|    | |  |  __  | |  | | |  | |\___ \ 	##
**	| |    | | \ \ _| |_   \  / ____ \| |  | |____  	| |  | | |____   | |  | |  | | |__| | |__| |____) |	##
**	|_|    |_|  \_\_____|   \/_/    \_\_|  |______| 	|_|  |_|______|  |_|  |_|  |_|\____/|_____/|_____/ 	##
**																											##
\###########################################################################################################*/

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer
map<T, Key, Compare, Alloc>::__insert__(const value_type& val, __node_pointer node,
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
		node->left = __insert__(val, node->left, ret, node);
	}
	else if (val.first > node->__pair.first) {
		node->right = __insert__(val, node->right, ret, node);
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
typename map<T, Key, Compare, Alloc>::__node_pointer
map<T, Key, Compare, Alloc>::__leftRotate__(__node_pointer node)
{
	__node_pointer	tmp_right = node->right;
	
	node->right = tmp_right->left;
	tmp_right->left = node;

	node->__node_weight = 1 + std::max(__weight__(node->left), __weight__(node->right));
	tmp_right->__node_weight = 1 + std::max(__weight__(tmp_right->left), __weight__(tmp_right->right));
	return (tmp_right);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer
map<T, Key, Compare, Alloc>::__rightRotate__(__node_pointer node)
{
	__node_pointer tmp_left = node->left;
	
	node->left = tmp_left->right;
	tmp_left->right = node;

	node->__node_weight = 1 + std::max(__weight__(node->left), __weight__(node->right));
	tmp_left->__node_weight = 1 + std::max(__weight__(tmp_left->left), __weight__(tmp_left->right));
	return (tmp_left);
}

template <class T, class Key, class Compare, class Alloc>
int		map<T, Key, Compare, Alloc>::__weight__(__node_pointer node)
{	return (node ? node->__node_weight : 0 );	}

template <class T, class Key, class Compare, class Alloc>
bool	map<T, Key, Compare, Alloc>::__update__(__node_pointer node, bool ghosted, __node_pointer parent)
{
	if (!node || node == ghost)
		return ghosted;
	node->parent = parent;
	ghosted = __update__(node->right, ghosted, node);
	if ((!node->right || node->right == ghost) && !ghosted) {
		ghost->right = node;
		ghost->left = node;
		ghost->parent = node;
		node->right = ghost;
		ghosted = true;
	}
	ghosted = __update__(node->left, ghosted, node);
	return ghosted;
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer
map<T, Key, Compare, Alloc>::__erase__(__node_pointer node, const key_type& val)
{
	if (!node)
		return (NULL);
	if (node->__pair.first > val)
		node->left = __erase__(node->left, val);
	else if (node->__pair.first < val)
		node->right = __erase__(node->right, val);
	else {
		if (!node->left && (!node->right || node->right == ghost))
			return (__destroyNode__(node));
		else if (!node->left || !node->right || node->right == ghost) {
			return (__destroyNode__(node, !node->left ? node->right : node->left));
		}
		else {
			__pair_alloc().destroy(&node->__pair);
			__pair_alloc().construct(&node->__pair, __findMin__(node->right));
			node->right = __erase__(node->right, node->__pair.first);
		}
	}
	return (node);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::value_type
map<T, Key, Compare, Alloc>::__findMin__(__node_pointer node)
{
	while (node->left)
		node = node->left;
	return node->__pair;
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer	map<T, Key, Compare, Alloc>::__destroyNode__(__node_pointer node, __node_pointer ret)
{
	__node_alloc.destroy(node);
	__node_alloc.deallocate(node, 1);
	return (ret);
}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::__disableGhost__()
{
	if (ghost->right) {
		ghost->right->right = NULL;
		ghost->right = NULL;
		ghost->left = NULL;
		ghost->parent = NULL;
	}
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::iterator	map<T, Key, Compare, Alloc>::__find__(__node_pointer node, const key_type& k)
{
	if (!node || node == ghost)
		return ghost;
	if (!__key_comp__(k, node->__pair.first) && !__key_comp__(node->__pair.first, k))
		return (node);
	if (__key_comp__(k, node->__pair.first))
		return (__find__(node->left, k));
	return (__find__(node->right, k));
}

template <class T, class Key, class Compare, class Alloc>
void	map<T, Key, Compare, Alloc>::__print__(__node_pointer node)
{
	if (node && node != ghost) {
		__print__(node->left);
		std::cout << node->__pair.first << " | " << node << " | " << node->parent <<" | "<< node->right<<" | "<<node->left <<"\n";
		__print__(node->right);
	}
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::size_type		map<T, Key, Compare, Alloc>::__size__(__node_pointer node) const
{
	if (!node || node == ghost)
		return 0;
	return (1 + __size__(node->left) + __size__(node->right));
}

template <class T, class Key, class Compare, class Alloc>
void		map<T, Key, Compare, Alloc>::__clear__(__node_pointer node)
{
	if (!node)
		return ;
	__clear__(node->left);
	__clear__(node->right);
	__destroyNode__(node);
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer map<T, Key, Compare, Alloc>::__copy__(const __node_pointer xnode)
{
	__node_pointer node = NULL;
	if (xnode && ((!xnode->left && !xnode->right) || xnode->left != xnode->right)) {
		node = __node_alloc.allocate(1);
		__node_alloc.construct(node, xnode->__pair);
		node->left = __copy__(xnode->left);
		node->right = __copy__(xnode->right);
	}
	return node;
}

template <class T, class Key, class Compare, class Alloc>
typename map<T, Key, Compare, Alloc>::__node_pointer map<T, Key, Compare, Alloc>::__assign__(const __node_pointer xnode, __node_pointer node)
{
	if (!xnode || (xnode->left == xnode->right && xnode->left != NULL)) {
		__clear__(node);
		return NULL;
	}
	if (!node) {
		node = __node_alloc.allocate(1);
		__node_alloc.construct(node, xnode->__pair);
		node->left = __assign__(xnode->left, NULL);
		node->right = __assign__(xnode->right, NULL);
	}
	else {
		__pair_alloc().destroy(&node->__pair);
		__pair_alloc().construct(&node->__pair, xnode->__pair);
		node->left = __assign__(xnode->left, node->left);
		node->right = __assign__(xnode->right, node->right);
	}
	return node;
}

}

#endif