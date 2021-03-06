#include "Queue.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <stdlib.h>
#include "utils.hpp"

template <class T>
void	all_tests(std::ostream& output)
{
	T queue;
	header("ALL_TESTS", output);
	output<< "\t\t== INSERTING AN ELEMENT ==\n";
	output << " Queue is empty ? " << queue.empty() << std::endl;
	output << "Queue size is : " << queue.size() << std::endl;
	queue.push(5);
	output << " Queue is empty ? " << queue.empty() << std::endl;
	output << "Queue size is : " << queue.size() << std::endl;
	output << "Queue front is : " << queue.front() << std::endl;
	output << "Queue back is : " << queue.back() << std::endl;
	output<< "\t\t== INSERTING MULTIPLE ELEMENT ==\n";
	queue.push(5);
	queue.push(56246);
	queue.push(6787);
	queue.push(912387);
	queue.push(234);
	queue.push(-452523);
	queue.push(63463);
	output << " Queue is empty ? " << queue.empty() << std::endl;
	output << "Queue size is : " << queue.size() << std::endl;
	output << "Queue front is : " << queue.front() << std::endl;
	output << "Queue back is : " << queue.back() << std::endl;
	output<< "\t\t== RMOVING ALL ELEMENTS USING POP ==\n";
	while (!queue.empty()) {
		output << "Queue size is : " << queue.size() << std::endl;
		output << "Queue front is : " << queue.front() << std::endl;
		output << "Queue back is : " << queue.back() << std::endl;
		queue.pop();
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

void test_queue(void)
{
	std::ofstream stl_output;
	std::ofstream ft_output;

	stl_output.open(QUEUE_STL_OUTPUT);
	ft_output.open(QUEUE_FT_OUTPUT);

	all_tests<std::queue<int> >(stl_output);
	all_tests<ft::queue<int> >(ft_output);
	comparison_tests<std::queue<int> >(stl_output);
	comparison_tests<ft::queue<int> >(ft_output);
}