// #include "base_iterator.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>

template <class T>
class A
{
	public:
		A() {};
		A(T *ptr) : ptr(ptr) {};
		~A() {};
		T& operator*() {return (*ptr);};
		bool operator==(int i) {return (i == *ptr);};
	private:
		T *ptr;
};

template <class T>
class B : public A<T>
{
	public:
		B() {};
		B(T *ptr) : A<T>(ptr) {};
		~B() {};
		typedef A<T> __input__;
		using A<T>::operator*;
		using A<T>::operator==;
		bool operator==(std::string str) {return(0);};
		T delta(__input__ end);
};

template <class T>
T B<T>::delta(__input__ end)
{
	std::cout << *end << std::endl;
	return (*end - **this);
}

int main(void)
{
	std::vector<int> vec;
	std::list<int> lst;
	// std::vector<int>::iterator it;

	for (int i = 0; i < 10; i++)
		lst.push_back(i);
	vec.insert(vec.begin(), lst.begin(), lst.end());
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << std::endl;
	// std::cout << *it << std::endl;
	// *it = 2;
		// for (int i = 0; i < 10; i++)
		// lst.push_front(i);
	// std::vector<int>::iterator it(lst.begin());
	// it = vec.begin();
	// std::cout << *it;
	// for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	// 	*it = 4;
	// for (std::vector<int>::const_iterator it = vec.cbegin(); it != vec.cend(); it++)
	// 	std::cout << *it << std::endl;
	// std::cout << *it << std::endl;	
	// int a = 6;
	// int b = 9;
	// A<int> test(&a);
	// B<int> inheritance_test(&b);
	// B<int> inheritance_test2(&a);

	// std::cout << (test == 6) << std::endl;
	// std::cout << *inheritance_test << std::endl;
	// std::cout << (inheritance_test == "Hello") << std::endl;
	// std::cout << inheritance_test.delta(inheritance_test2) << std::endl;
	return (0);
}