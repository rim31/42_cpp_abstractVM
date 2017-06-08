#include "Operand.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <regex>

void bonus(std::list<IOperand const *> mylist)
{
  for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << (*it)->toString() << std::endl;
}


std::list<IOperand const *> cmd_add(std::list<IOperand const *> mylist)
{
  if (mylist.size() >= 2)
  {
    IOperand const *nb1 = mylist.front();
    IOperand const *nb2 = *std::next(mylist.begin());
    mylist.pop_front();
    mylist.pop_front();
    IOperand const *nb = *nb1 + *nb2;
    mylist.push_front(nb);    // std::cout << nb->toString() << std::endl;
  }
  else
    std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n" << std::endl;

  // for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
  // {
  //   //std::cout << ' ' << (*it)->toString() << std::endl;
  //   i++;
  //   if (i == 1)
  //   nb1 = (*it)->toString();
  //   if (i == 2)
  //   nb2 = (*it)->toString();
  // }
  // if (i >1)
  // {
  //   nb = std::to_string(std::stoi(nb1) + std::stoi(nb2));
  //   // IOperand const *k = nb1 +  nb2;
  //   // std::cout << k->toString() << std::endl;
  //   std::cout << nb << std::endl;
  // }
  // else
  //   std::cout << "erreur - pas assez de nombre dans la pile" << std::endl;
  return mylist;
}
