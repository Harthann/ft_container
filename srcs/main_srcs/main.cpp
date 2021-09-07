#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include <map.hpp>
	#include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

#include <list>
#include <map>

int main(int argc, char** argv) {
	ft::map<int, char> lst;

	lst.insert(ft::pair<int, char>(1, 'q'));
	lst.insert(ft::pair<int, char>(2, 't'));
	lst.insert(ft::pair<int, char>(5, 'c'));

	lst[1] = 'u';

	for (ft::map<int, char>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << it->first << ' ' << it->second << std::endl;
	std::cout << std::endl;
}
