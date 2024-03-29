/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_main.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/18 16:48:49 by hbaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "STACK_UC.HPP"
#include <list>
#include "VECTOR_UC.HPP"
#include "test_utils.hpp"
#include <stack>

#ifndef STD
# define NAMESPACE ft
#else
# define NAMESPACE std
#endif

using namespace NAMESPACE;

int main ()
{
  stack<int> myints;
  cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  cout << "2. size: " << myints.size() << '\n';

  return 0;
}
