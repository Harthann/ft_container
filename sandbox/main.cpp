// #include "base_iterator.hpp"
#include <iostream>
#include <string>

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
	int a = 6;
	int b = 9;
	// A<int> test(&a);
	B<int> inheritance_test(&b);
	B<int> inheritance_test2(&a);

	// std::cout << (test == 6) << std::endl;
	// std::cout << *inheritance_test << std::endl;
	// std::cout << (inheritance_test == "Hello") << std::endl;
	std::cout << inheritance_test.delta(inheritance_test2) << std::endl;
	return (0);
}