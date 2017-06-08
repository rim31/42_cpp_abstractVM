#include "Operand.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <regex>


//===============on cherche le bon chiffre dans la liste pour ASSERT =================
void dump(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_add(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_sub(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_mul(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_div(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_mod(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_print(std::list<IOperand const *> mylist);
std::list<IOperand const *> cmd_pop(std::list<IOperand const *> mylist);



