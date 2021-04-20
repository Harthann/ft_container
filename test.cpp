#include <iostream>

class A {
	public:
		A() { a = 1; std::cout << "Constructor called" << std::endl; };
		A(A const& x) {a = 2; std::cout << "Constructor copy called" << std::endl; };

		A &operator=(A const &x) {a = 5; std::cout << "Constructor assignation called" << std::endl; return (*this);};

		int &get() {return a;};
		~A() {};
	private:
		int a;
};

int main(void)
{
	A a;
	A b = a;
	A c(a);
	std::cout << a.get() << std::endl;
	std::cout << b.get() << std::endl;
	std::cout << c.get() << std::endl;
	b = a;
	std::cout << b.get() << std::endl;
	return (0);
}