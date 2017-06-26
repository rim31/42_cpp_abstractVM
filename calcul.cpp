#include "Operand.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <regex>
#include "Exception.hpp"


//==================  CMD en entree ==================
int check_cmd(std::string str)
{
  if (str.compare("dump") == 0 || str.compare("add") == 0 || str.compare("sub") == 0
  || str.compare("mul") == 0 || str.compare("div") == 0 || str.compare("mod") == 0
  || str.compare("print") == 0 || str.compare("pop") == 0 || str.compare("exit") == 0)
  // || str.compare("push") == 0 || str.compare("assert") == 0)
    return 1;
  return 0;
}


void dump(std::list<IOperand const *> mylist)
{
  for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
      std::cout << ' ' << (*it)->toString()<< std::endl;;
}

//===================== +++++++++++++ ===============
std::list<IOperand const *> cmd_add(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 2)
  {
    IOperand const *nb1 = mylist.front();
    IOperand const *nb2 = *std::next(mylist.begin());
    mylist.pop_front();
    mylist.pop_front();
    IOperand const *nb = *nb1 + *nb2;
    mylist.push_front(nb);    // std::cout << nb->toString();
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");

  return mylist;
}

//===================== ---------------- ===============
std::list<IOperand const *> cmd_sub(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 2)
  {
    IOperand const *nb1 = mylist.front();
    IOperand const *nb2 = *std::next(mylist.begin());
    mylist.pop_front();
    mylist.pop_front();
    IOperand const *nb = *nb2 - *nb1;
    mylist.push_front(nb);    // std::cout << nb->toString();
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");
  return mylist;
}

//===================== ****************** ===============
std::list<IOperand const *> cmd_mul(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 2)
  {
    IOperand const *nb1 = mylist.front();
    IOperand const *nb2 = *std::next(mylist.begin());
    mylist.pop_front();
    mylist.pop_front();
    IOperand const *nb = *nb1 * *nb2;
    mylist.push_front(nb);    // std::cout << nb->toString();
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");
  return mylist;
}


//===================== ///////////////////// ===============
std::list<IOperand const *> cmd_div(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 2)
  {
    IOperand const *nb1 = mylist.front();
    IOperand const *nb2 = *std::next(mylist.begin());
    // std::cout << nb2->toString();;;
    if (std::stoi(nb2->toString()) == 0)
    {
      // std::cout << "\033[1;31m - erreur - division par 0 - y a pas ecrit qui divise qui :-P - \033[0m\n";
      throw Except("\033[1;31m - erreur - division par 0 - y a pas ecrit qui divise qui :-P - \033[0m\n");

      return mylist;
    }
    mylist.pop_front();
    mylist.pop_front();
    IOperand const *nb = *nb2 / *nb1;
    mylist.push_front(nb);    // std::cout << nb->toString();
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");
  return mylist;
}

//===================== %%%%%%%%%%%%%%%%%%%%%%%% ===============
std::list<IOperand const *> cmd_mod(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 2)
  {
    IOperand const *nb1 = mylist.front();
    IOperand const *nb2 = *std::next(mylist.begin());
    // std::cout << nb2->toString();;;
    if (std::stoi(nb2->toString()) == 0)
    {
      // std::cout << "\033[1;31m - erreur - modulo par 0 - y a pas ecrit qui modulo qui :-P - \033[0m\n";
      throw Except("\033[1;31m - erreur - division par 0 - y a pas ecrit qui divise qui :-P - \033[0m\n");

      return mylist;
    }
    mylist.pop_front();
    mylist.pop_front();
    IOperand const *nb = *nb2 % *nb1;
    mylist.push_front(nb);    // std::cout << nb->toString();
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");
  return mylist;
}

//===================== %print% ===============
std::list<IOperand const *> cmd_print(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 1)
  {
    IOperand const *nb1 = mylist.front();
    if (std::stoi(nb1->toString()) >= 0 && std::stoi(nb1->toString()) <= 128 )
    {
      //mettre unIF pour les caractere imprimables seulement ??????????
      char val = std::stoi(nb1->toString());
      std::cout << val << std::endl;
    }
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");
  return mylist;
}


//===================== +++++++++++++ ===============
std::list<IOperand const *> cmd_pop(std::list<IOperand const *> mylist)
{
  Except err;

  if (mylist.size() >= 1)
  {
    IOperand const *nb1 = mylist.front();
    mylist.pop_front();
  // std::cout << nb1->toString();
  }
  else
    // std::cout << "\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n";
    throw Except("\033[1;31m - erreur - pas assez de nombre dans la pile - \033[0m\n");
  return mylist;
}
