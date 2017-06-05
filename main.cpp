#include "Operand.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <regex>


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


//================ fonction pour trouver ) final===============
size_t findclose(std::string str)
{
  std::size_t pos;
  pos = str.find(")");
  // if (pos - std::string::npos == 0)
  //   std::cout << " ) : pas trouve ERROR" << std::endl;
  // else
  //   std::cout << "position de ) -> "<< pos << std::endl;
  return pos;
}

int checknumber(std::string nb, int point, int pos)
{
  int ret = 0;
  int nombredepoint = 0;
  int i = 0;
  std::cout << "'"<< nb << "'" << std::endl;
  while(nb[i] && i < pos)
  {
    if (nombredepoint > point)
    {
      std::cout << " . en trop pas le bon type" << std::endl;
      return 0;
    }
    if (nb[i] == '.')
      nombredepoint++;
    else if (!isdigit(nb[i]))
    {
      std::cout << " pas numerique";
      return 0;
    }
    std::cout << nb[i];
    i++;
  }
  if (nombredepoint != point)
  {
    std::cout << std::endl << "pas le bon nombre de ." << std::endl;
    return 0;
  }
  else
  {
    std::cout << std::endl << "if faut mettre dans la list" << std::endl;
    return 1;
  }
  return 0;
}

std::list<IOperand const *> checktype(std::string buff, std::list<IOperand const *> mylist)
{
//   if (buff[buff.length()-1] == '(')
//     std::cout << "==>( " << std::endl;
// else
//     std::cout << "error, il manque le ) final" << std::endl;
  // if (std::regex_match (buff, std::regex("(int8()(.*)") ))
  //     std::cout << "string literal matched\n";
  // else
  //   std::cout << "rine trouve\n";
  std::size_t pos;
  std::size_t init;
  std::string str;
  Factory fact;
  // std::list<IOperand const *> mylist;

  pos = findclose(buff);
  if (pos > 5 && pos != std::string::npos)
  {
      // std::cout << "position de ) -> "<< pos << std::endl;
    if (buff.substr(0,5).compare("int8(") == 0)
    {
      std::cout << "you enter int8(" << std::endl;
      if (checknumber(buff.substr(5,pos-5), 0, pos-5)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Int8,buff.substr(5,pos-5)));
    }
    else if (buff.substr(0,6).compare("int16(") == 0)
    {
      std::cout << "you enter int16( " << std::endl;
      if (checknumber(buff.substr(6,pos-6), 0, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Int16,buff.substr(6,pos-6)));
    }
    else if (buff.substr(0,6).compare("int32(") == 0)
    {
      std::cout << "you enter int32( " << std::endl;
      if (checknumber(buff.substr(6,pos-6), 0, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
      mylist.push_front (fact.createOperand(Int32,buff.substr(6,pos-6)));

    }
    else if (buff.substr(0,6).compare("float(") == 0)
    {
      std::cout << "you enter float( " << std::endl;
      if (checknumber(buff.substr(6,pos-6), 1, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Float,buff.substr(6,pos-6)));
    }
    else if (buff.substr(0,7).compare("double(") == 0)
    {
      std::cout << "you enter double( " << std::endl;
      if (checknumber(buff.substr(7,pos-7), 1, pos-7)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Double,buff.substr(7,pos-7)));
    }
  }
  else
    std::cout << " ) : RE pas trouve ERROR" << std::endl;

  return mylist;
  // mylist.push_front (fact.createOperand(Int32,buff));

}

std::list<IOperand const *> my_split(const std::string s, std::list<IOperand const *> mylist)
{
  std::istringstream iss(s);
  int i = 0;
  int pushok = 0;
  int assertok = 0;
  Factory fact;
  // std::list<IOperand const *> mylist;

  // std::cout << s << std::endl;
 while (iss)
 {
  //  std::cout << "i et pushok " << i << pushok << std::endl;
    std::string sub;
    iss >> sub;
    // parse_cmd(buff, mylist);
    // if (sub.compare("") != 0)
    //   std::cout << "VIDE !! " << sub << std::endl;
    if (i>1)
    {
      if (sub.substr(0,1).compare(";") == 0)
      std::cout << "commentaire avec ; " << sub << std::endl;
      else if (sub.compare("") != 0)
      std::cout << "Error trop de parametres " << sub << std::endl;
    }
    if ((sub.compare("push") == 0 && i == 0 )|| (sub.compare("assert") == 0 && i == 0))
    {
      pushok = 1;
      std::cout << "changer PUSH/ASSERT a faire " << sub << std::endl;
    }
    if (i == 1 && pushok == 1)
    {
      mylist = checktype(sub, mylist);
      // std::cout << "checktype OK " << sub << std::endl;
    }
    i++;
  }
  return mylist;
}

  // push      int8(  )

void parser(std::string str)
{
  Factory fact;
  std::string   buff;
  std::string myints[] = {""};
  std::list<IOperand const *> mylist;

  mylist = my_split(str, mylist);
  std::cout << "argv[0] : " << str << std::endl;

  if (!std::getline(std::cin, buff))
    exit(0);
    mylist = my_split(buff, mylist);
  mylist.push_front (fact.createOperand(Int32,buff));
  while(buff.compare(";;") != 0)
  {
    if (!std::getline(std::cin, buff))
      exit(0);//passer a la ligne suivante plutot
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
        mylist = my_split(buff, mylist);
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