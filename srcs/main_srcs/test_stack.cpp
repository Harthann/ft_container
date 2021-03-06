#include "Stack.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>
#include <stdlib.h>
#include "utils.hpp"

template <class T>
void	all_tests(std::ostream& output)
{
	T stack;
	header("ALL_TESTS", output);
	output<< "\t\t== INSERTING AN ELEMENT ==\n";
	output << " stack is empty ? " << stack.empty() << std::endl;
	output << "stack size is : " << stack.size() << std::endl;
	stack.push(5);
	output << " stack is empty ? " << stack.empty() << std::endl;
	output << "stack size is : " << stack.size() << std::endl;
	output << "stack top is : " << stack.top() << std::endl;
	output<< "\t\t== INSERTING MULTIPLE ELEMENT ==\n";
	stack.push(5);
	stack.push(56246);
	stack.push(6787);
	stack.push(912387);
	stack.push(234);
	stack.push(-452523);
	stack.push(63463);
	output << " stack is empty ? " << stack.empty() << std::endl;
	output << "stack size is : " << stack.size() << std::endl;
	output << "stack top is : " << stack.top() << std::endl;
	output<< "\t\t== RMOVING ALL ELEMENTS USING POP ==\n";
	while (!stack.empty()) {
		output << "stack size is : " << stack.size() << std::endl;
		output << "stack top is : " << stack.top() << std::endl;
		stack.pop();
	}
}

template <class T>
void	comparison_tests(std::ostream& output)
{
	T A;
    T B;
    T C;
 
	A.push(4);
	A.push(87);
	A.push(12);
	B.push(21);
	B.push(8745);
	B.push(34);
	B.push(9);
	C.push(4);
	C.push(87);
	C.push(12);
 
    // Compare non equal containers
    output << "A == B returns " << (A == B) << '\n';
    output << "A != B returns " << (A != B) << '\n';
    output << "A <  B returns " << (A < B) << '\n';
    output << "A <= B returns " << (A <= B) << '\n';
    output << "A >  B returns " << (A > B) << '\n';
    output << "A >= B returns " << (A >= B) << '\n';
 
    output << '\n';
 
    // Compare equal containers
    output << "A == C returns " << (A == C) << '\n';
    output << "A != C returns " << (A != C) << '\n';
    output << "A <  C returns " << (A < C) << '\n';
    output << "A <= C returns " << (A <= C) << '\n';
    output << "A >  C returns " << (A > C) << '\n';
    output << "A >= C returns " << (A>= C) << '\n';
}

void test_stack(void)
{
	std::ofstream stl_output;
	std::ofstream ft_output;

	stl_output.open(STACK_STL_OUTPUT);
	ft_output.open(STACK_FT_OUTPUT);

	all_tests<std::stack<int> >(stl_output);
	all_tests<ft::stack<int> >(ft_output);
	comparison_tests<std::stack<int> >(stl_output);
	comparison_tests<ft::stack<int> >(ft_output);
}