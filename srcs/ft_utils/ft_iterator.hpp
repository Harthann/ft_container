#ifndef FT_ITERATOR__HPP
#define FT_ITERATOR__HPP

#include "sfinae_template.hpp"

namespace ft {

struct input_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <class T = void, bool B = !ft::is_arithmetic<T>::value >
struct is_input_iterator {
	static const bool value = false;};

template <class T>
struct is_input_iterator<T, true> {
	static const bool value = ft::is_same<typename T::iterator_category, ft::input_iterator_tag>::value ||
		ft::is_same<typename T::iterator_category, ft::forward_iterator_tag>::value ||
		ft::is_same<typename T::iterator_category, ft::bidirectional_iterator_tag>::value ||
		ft::is_same<typename T::iterator_category, ft::random_access_iterator_tag>::value;
};


template <class T>
struct is_input_iterator<T*, true> {
	static const bool value = true;
};

template <class it>
struct iterator_traits {
    typedef typename it::difference_type difference_type;
    typedef typename it::value_type value_type;
    typedef typename it::pointer pointer;
    typedef typename it::reference reference;
    typedef typename it::iterator_category iterator_category;
};

template <class it>
struct iterator_traits<it*> {
    typedef std::ptrdiff_t difference_type;
    typedef it value_type;
    typedef it* pointer;
    typedef it& reference;
    typedef ft::random_access_iterator_tag iterator_category;
};

template<class It>
void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
                ft::input_iterator_tag)
{
    while (n > 0) {
        --n;
        ++it;
    }
}
 
template<class It>
void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
                ft::bidirectional_iterator_tag)
{
    while (n > 0) {
        --n;
        ++it;
    }
    while (n < 0) {
        ++n;
        --it;
    }
}
 
template<class It>
void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
                ft::random_access_iterator_tag)
{
    it += n;
}

template<class It>
void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
                std::input_iterator_tag)
{
    while (n > 0) {
        --n;
        ++it;
    }
}
 
template<class It>
void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
                std::bidirectional_iterator_tag)
{
    while (n > 0) {
        --n;
        ++it;
    }
    while (n < 0) {
        ++n;
        --it;
    }
}
 
template<class It>
void do_advance(It& it, typename ft::iterator_traits<It>::difference_type n,
                std::random_access_iterator_tag)
{
    it += n;
}
 
template<class It, class Distance>
void advance(It &it, Distance n)
{
    ft::do_advance(it, typename ft::iterator_traits<It>::difference_type(n), 
                       typename ft::iterator_traits<It>::iterator_category());
}

template <class BidirIt>
BidirIt prev(BidirIt it, typename ft::iterator_traits<BidirIt>::difference_type n = 1)
{
    ft::advance(it, -n);
    return (it);
}

template <class BidirIt>
BidirIt next(BidirIt it, typename ft::iterator_traits<BidirIt>::difference_type n = 1)
{
    ft::advance(it, n);
    return (it);
}

template <class InputIT>
size_t  distance(InputIT its, InputIT ite)
{
    size_t i = 0;
    while (ite != its) {
        ++i;
        ++its;
    }
    return (i);
}

}


#endif
