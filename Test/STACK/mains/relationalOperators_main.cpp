/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relationalOperators_main.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 13:07:06 by hbaudet           #+#    #+#             */
/*   Updated: 2021/01/18 16:50:42 by hbaudet          ###   ########.fr       */
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
  stack<int> a, b, c;
  a.push(10);
  a.push(20);
  a.push(30);

  b.push(10);
  b.push(20);
  b.push(30);

  c.push(30);
  c.push(20);
  c.push(10);

  if (a==b) cout << "a and b are equal\n";
  if (b!=c) cout << "b and c are not equal\n";
  if (b<c) cout << "b is less than c\n";
  if (c>b) cout << "c is greater than b\n";
  if (a<=b) cout << "a is less than or equal to b\n";
  if (a>=b) cout << "a is greater than or equal to b\n";

  return 0;
}
