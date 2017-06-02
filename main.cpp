#include "Operand.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>


void parse_cmd(std::string buff, std::list<IOperand const *> mylist)
{
  Factory fact;
  if (buff.compare("push") == 0)
    std::cout << "you enter push " << std::endl;
  else if (buff.compare("push int8(") == 0)
    std::cout << "you enter push int8( " << std::endl;
  else if (buff.compare("push int16(") == 0)
    std::cout << "you enter push int16( " << std::endl;
  else if (buff.compare("push int32(") == 0)
    std::cout << "you enter push int32( " << std::endl;
  else if (buff.compare("push float(") == 0)
    std::cout << "you enter push float( " << std::endl;
  else if (buff.compare("push double(") == 0)
    std::cout << "you enter push double( " << std::endl;
  else if (buff.compare("add") == 0)
    std::cout << "you enter Add" << std::endl;
  else if (buff.compare("pop") == 0)
    std::cout << "you enter pop" << std::endl;
  else if (buff.compare("dump") == 0)
    std::cout << "you enter dump" << std::endl;
  else if (buff.compare("assert") == 0)
    std::cout << "you enter assert VALUE" << std::endl;
  else if (buff.compare("add") == 0)
    std::cout << "you enter add" << std::endl;
  else if (buff.compare("sub") == 0)
    std::cout << "you enter sub" << std::endl;
  else if (buff.compare("mul") == 0)
    std::cout << "you enter mul" << std::endl;
  else if (buff.compare("div") == 0)
    std::cout << "you enter div" << std::endl;
  else if (buff.compare("mod") == 0)
    std::cout << "you enter mod" << std::endl;
  else if (buff.compare("print") == 0)
    std::cout << "you enter print" << std::endl;
  else if (buff.compare("exit") == 0)
    std::cout << "you enter exit" << std::endl;
  mylist.push_front (fact.createOperand(Int32,buff));
    // push int8(
    // push int16(
    // push int32(
    // push float(
    // push double(
    // pop
    // dump
    // assert VALUE
    // add
    // sub
    // mul
    // div
    // mod
    // print

}

void my_split(const std::string s)
{
  std::istringstream iss(s);

 while (iss)
 {
    std::string sub;
    iss >> sub;
    if (sub.compare("") != 0)
      std::cout << "Substring: " << sub << std::endl;
  }
}

  // push      int8(  )

void parser(std::string str)
{
  my_split(str);

   std::cout << "argv[0] : " << str << std::endl;
  Factory fact;
  std::string   buff;
  std::string myints[] = {""};
  std::list<IOperand const *> mylist;

  if (!std::getline(std::cin, buff))
    exit(0);
  mylist.push_front (fact.createOperand(Int32,buff));
  while(buff.compare(";;") != 0)
  {
    if (!std::getline(std::cin, buff))
      exit(0);
    // else if (buff.compare("push") == 0)
    //   std::cout << "you enter push " << std::endl;
    // else if (buff.compare("push int8(") == 0)
    //   std::cout << "you enter push int8( " << std::endl;
    // else if (buff.compare("push int16(") == 0)
    //   std::cout << "you enter push int16( " << std::endl;
    // else if (buff.compare("push int32(") == 0)
    //   std::cout << "you enter push int32( " << std::endl;
    // else if (buff.compare("push float(") == 0)
    //   std::cout << "you enter push float( " << std::endl;
    // else if (buff.compare("push double(") == 0)
    //   std::cout << "you enter push double( " << std::endl;
    // else if (buff.compare("add") == 0)
    //   std::cout << "you enter Add" << std::endl;
    // else if (buff.compare("pop") == 0)
    //   std::cout << "you enter pop" << std::endl;
    // else if (buff.compare("dump") == 0)
    //   std::cout << "you enter dump" << std::endl;
    // else if (buff.compare("assert") == 0)
    //   std::cout << "you enter assert VALUE" << std::endl;
    // else if (buff.compare("add") == 0)
    //   std::cout << "you enter add" << std::endl;
    // else if (buff.compare("sub") == 0)
    //   std::cout << "you enter sub" << std::endl;
    // else if (buff.compare("mul") == 0)
    //   std::cout << "you enter mul" << std::endl;
    // else if (buff.compare("div") == 0)
    //   std::cout << "you enter div" << std::endl;
    // else if (buff.compare("mod") == 0)
    //   std::cout << "you enter mod" << std::endl;
    // else if (buff.compare("print") == 0)
    //   std::cout << "you enter print" << std::endl;
    // else if (buff.compare("exit") == 0)
    //   std::cout << "you enter exit" << std::endl;
    else
      {
        parse_cmd(buff, mylist);
        my_split(buff);
      }
      // mettre le bon type dans la stack
      // mylist.push_front (fact.createOperand(Int32,buff));
  }





  std::cout << "mylist contains:";
  // for (auto it : mylist)
  //   std::cout << ' ' << (*it).toString();
  for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
    std::cout << ' ' << (*it)->toString();

  std::cout << '\n';











  IOperand const *i = new Operand<int>(Int32, "42");
  // IOperand const *i = new Operand<double>(Double, "12.123456");
  IOperand const *j = new Operand<float>(Float, "21.1234567");
  IOperand const *k = *i + *j;

  std::cout << k->toString() << std::endl;

  std::cout << "=================== operator - ==================" << std::endl;
  i = new Operand<int>(Int32, "42");
  // i = new Operand<double>(Double, "42.123456");
  j = new Operand<float>(Float, "21.1234567");
  k = *i - *j;
  std::cout << k->toString() << std::endl;

  std::cout << "=================== operator * ==================" << std::endl;
  i = new Operand<int>(Int32, "42");
  // i = new Operand<double>(Double, "42.123456");
  j = new Operand<float>(Float, "21.1234567");
  k = *i * *j;
  std::cout << k->toString() << std::endl;

  std::cout << "=================== operator / ==================" << std::endl;
  i = new Operand<int>(Int32, "42");
  // i = new Operand<double>(Double, "42.123456");
  j = new Operand<float>(Float, "21.1234567");
  k = *i / *j;
  std::cout << k->toString() << std::endl;

  std::cout << "=================== operator % ==================" << std::endl;
  // i = new Operand<double>(Double, "42.123456");
  // j = new Operand<float>(Float, "21.1234567");
  i = new Operand<int>(Int32, "12");
  j = new Operand<int>(Int32, "42");
  // j = new Operand<int>(Int32, "0");
  k = *i % *j;
  std::cout << k->toString() << std::endl;
}

int main(int ac, char **av)
{
  if (ac != 2)
    return (0);//relancer la commande tant qu'on a pas exit
  else
    parser(av[1]);
  return (0);
}