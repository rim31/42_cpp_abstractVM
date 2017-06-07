#include "Operand.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <regex>

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
}


//================ fonction pour trouver ) final===============
size_t findclose(std::string str)
{
  std::size_t pos;
  pos = str.find(")");
  if (str.find(";") == pos + 1 || str.find(";") == std::string::npos)
    return pos;//on regarde si on a bien un ; apres le )
  else
    return std::string::npos;
}

//=============== on regarde si on a bien un nombre +/- et . ==================
int checknumber(std::string nb, int point, int pos)
{
  int ret = 0;
  int nombredepoint = 0;
  int i = 0;
  // std::cout << "'"<< nb << "'" << std::endl;
  while(nb[i] && i < pos)
  {
    if (nombredepoint > point)
    {
      std::cout << " . en trop pas le bon type" << std::endl;
      return 0;
    }
    if (nb[i] == '.')
      nombredepoint++;
    else if (!isdigit(nb[i]) && nb[0] != '-')
    {
      std::cout << " pas numerique" << std::endl;
      return 0;
    }
    i++;
  }
  if (nombredepoint != point)
  {
    std::cout << std::endl << "pas le bon nombre de ." << std::endl;
    return 0;
  }
  else
  {
    // std::cout << std::endl << "if faut mettre dans la list" << std::endl;
    return 1;
  }
  return 0;
}


//================== on ajoute dans la liste avec le bon typ pour la COMMANDE PUSH ===============
std::list<IOperand const *> checktype(std::string buff, std::list<IOperand const *> mylist)
{
  std::size_t pos;
  std::size_t init;
  std::string str;
  Factory fact;

  pos = findclose(buff);
  if (pos > 5 && pos != std::string::npos)
  {
      // on recupere le debut int8( puis on verifie ce qu'il ya entre les ()
    if (buff.substr(0,5).compare("int8(") == 0 && checknumber(buff.substr(5,pos-5), 0, pos-5)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Int8,buff.substr(5,pos-5)));//on met dan la pile si . et digit OK
    else if (buff.substr(0,6).compare("int16(") == 0 && checknumber(buff.substr(6,pos-6), 0, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Int16,buff.substr(6,pos-6)));
    else if (buff.substr(0,6).compare("int32(") == 0 && checknumber(buff.substr(6,pos-6), 0, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
      mylist.push_front (fact.createOperand(Int32,buff.substr(6,pos-6)));
    else if (buff.substr(0,6).compare("float(") == 0 && checknumber(buff.substr(6,pos-6), 1, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Float,buff.substr(6,pos-6)));
    else if (buff.substr(0,7).compare("double(") == 0 && checknumber(buff.substr(7,pos-7), 1, pos-7)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        mylist.push_front (fact.createOperand(Double,buff.substr(7,pos-7)));
  }
  else
    std::cout << " ) : RE pas trouve ERROR" << std::endl;
  return mylist;
}


//===============on cherche le bon chiffre dans la liste pour ASSERT =================
void searchAssert(std::string nb, std::list<IOperand const *> mylist)
{
  for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
  {  // std::cout << ' ' << (*it)->toString();
    if ( (*it)->toString().compare(nb) == 0)
    {
      std::cout << ' ' << (*it)->toString() << std::endl;
      return;
    }
  }
}

//===============fonction ASSERT, on verifie lsliste chaine ==================
std::list<IOperand const *> checktypeAssert(std::string buff, std::list<IOperand const *> mylist)
{
  std::size_t pos;
  std::size_t init;
  std::string str;
  Factory fact;

  pos = findclose(buff);
  if (pos > 5 && pos != std::string::npos)
  {
      // on recupere le debut int8( puis on verifie ce qu'il ya entre les ()
    if (buff.substr(0,5).compare("int8(") == 0 && checknumber(buff.substr(5,pos-5), 0, pos-5)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        searchAssert(buff.substr(5,pos-5), mylist);//on met dan la pile si . et digit OK
    else if (buff.substr(0,6).compare("int16(") == 0 && checknumber(buff.substr(6,pos-6), 0, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        searchAssert(buff.substr(6,pos-6), mylist);
    else if (buff.substr(0,6).compare("int32(") == 0 && checknumber(buff.substr(6,pos-6), 0, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        searchAssert(buff.substr(6,pos-6), mylist);
    else if (buff.substr(0,6).compare("float(") == 0 && checknumber(buff.substr(6,pos-6), 1, pos-6)/*PENSER A VERIFIER LA TAILLE DU INT*/)
        searchAssert(buff.substr(6,pos-6), mylist);
    else if (buff.substr(0,7).compare("double(") == 0 && checknumber(buff.substr(7,pos-7), 1, pos-7)/*PENSER A VERIFIER LA TAILLE DU INT*/)
    searchAssert(buff.substr(7,pos-7), mylist);
  }
  else
    std::cout << " ) : RE pas trouve ERROR" << std::endl;

  return mylist;
  // mylist.push_front (fact.createOperand(Int32,buff));
}


int checknumberargument(const std::string s)
{
  std::istringstream iss(s);
  int i = 0;
  int error = 0;
  Factory fact;
  //1ere verification nombre d'argument
  while (iss)
  {
     std::string sub;
     iss >> sub;
     if (i==3)
     {
       if (sub.substr(0,1).compare(";") == 0)
        std::cout << "commentaire avec ; " << sub << std::endl;
       else
        {
          std::cout << "trop de parametres " << sub << std::endl;
          error = 1;
        }
     }
     if (sub.compare("") != 0)
      i++;
   }
  // std::cout <<"error : "<< error << " et i : " << i << std::endl;
  return error;
}

std::list<IOperand const *> my_split(const std::string str, std::list<IOperand const *> mylist)
{
  //on cherche tout les ;
  std::string s = str;
  if (str.find(";") != std::string::npos)
      s = str.substr(0,str.find(";"));

  std::istringstream iss(s);
  int i = 0;
  int pushok = 0;
  int assertok = 0;
  Factory fact;

  if (!checknumberargument(s))
  {
   while (iss)
   {
      std::string sub;
      iss >> sub;

      if (i>1)
      {
        if (sub.substr(0,1).compare(";") == 0)
          std::cout << "commentaire avec ; " << sub << std::endl;
        else if (sub.compare("") != 0)
          std::cout << "Error trop de parametres et pas commentaire" << sub << std::endl;
      }
      if ((sub.compare("push") == 0 && i == 0 ))
      {
        pushok = 1;
        std::cout << "tu viens de PUSH" << sub << std::endl;
      }
      if (sub.compare("assert") == 0 && i == 0)
      {
        assertok = 1;
        std::cout << "tu viens de ASSERT " << sub << std::endl;
      }
      if (i == 1 && pushok == 1)
        mylist = checktype(sub, mylist);
      if (i == 1 && assertok == 1)
        mylist = checktypeAssert(sub, mylist);
      i++;
    }
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
  // std::cout << "argv[0] : " << str << std::endl;

  if (!std::getline(std::cin, buff))
    exit(0);
    mylist = my_split(buff, mylist);
  while(buff.compare(";;") != 0)
  {
    if (!std::getline(std::cin, buff))
      exit(0);//passer a la ligne suivante plutot
    else
      mylist = my_split(buff, mylist);
  }





  std::cout << "mylist contains:";
  // for (auto it : mylist)
  //   std::cout << ' ' << (*it).toString();
  for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
    std::cout << ' ' << (*it)->toString();

  std::cout << '\n';



//=====================OPERATION=========================


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