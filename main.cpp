#include "Operand.hpp"
#include "calcul.hpp"
#include "Exception.hpp"
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <fstream>



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
  Except err;

  int ret = 0;
  int nombredepoint = 0;
  int i = 0;
  // std::cout << "'"<< nb << "'" << std::endl;
  while(nb[i] && i < pos)
  {
    if (nombredepoint > point)
    {
      // std::cout << " . en trop pas le bon type" << std::endl;
      throw Except("\033[1;31m  . en trop pas le bon type \033[0m\n");

      return 0;
    }
    if (nb[i] == '.')
      nombredepoint++;
    else if (!isdigit(nb[i]) && nb[0] != '-')
    {
      // std::cout << " pas numerique" << std::endl;
      throw Except("\033[1;31m  pas numerique \033[0m\n");
      return 0;
    }
    i++;
  }
  if (nombredepoint != point)
  {
    // std::cout << std::endl << "pas le bon nombre de ." << std::endl;
    throw Except("\033[1;31m  pas le bon nombre de . \033[0m\n");

    return 0;
  }
  else
  {
    if ((nombredepoint == 1 && point == 1 && nb.find(".") >= 1 && nb.find(".") <= pos - 1) || point == 0) // on verifie le nombre "[0-9].[0.9]"
      return 1;    // std::cout << std::endl << "if faut mettre dans la list" << std::endl;
  }
  // std::cout << std::endl << "pas le bon nombre de [0-9].[0-9]" << std::endl;
  throw Except("\033[1;31m  pas le bon nombre de [0-9].[0-9] \033[0m\n");

  return 0;
}


//================== on ajoute dans la liste avec le bon typ pour la COMMANDE PUSH ===============
std::list<IOperand const *> checktype(std::string buff, std::list<IOperand const *> mylist)
{
  Except err;

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
    else
        // std::cout << "\033[1;31m - Error commande - \033[0m : " << buff << std::endl;
        throw Except("\033[1;31m  - Error commande - \033[0m\n");
  }
  else
    // std::cout << " ) : pas trouve ERROR" << std::endl;
    throw Except("\033[1;31m  ) pas trouve \033[0m\n");

  return mylist;
}


//===============on cherche le bon chiffre dans la liste pour ASSERT =================
void searchAssert(std::string nb, std::list<IOperand const *> mylist)
{
  Except err;

  for (std::list<IOperand const *>::iterator it=mylist.begin(); it != mylist.end(); ++it)
  {  // std::cout << ' ' << (*it)->toString();
    if ( (*it)->toString().compare(nb) != 0)
    {
      // std::cout << " ASSERT error pas trouve" << (*it)->toString() << std::endl;
      throw Except("\033[1;31m  - ASSERT error pas trouve - \033[0m\n");
    }
    return;
  }
}


//===============fonction ASSERT, on verifie lsliste chaine ==================
std::list<IOperand const *> checktypeAssert(std::string buff, std::list<IOperand const *> mylist)
{
  Except err;

  std::size_t pos;
  std::size_t init;
  std::string str;
  Factory fact;

  pos = findclose(buff);
  if (pos > 5 && pos != std::string::npos)
  {      // on recupere le debut int8( puis on verifie ce qu'il ya entre les ()
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
    else
      // std::cout << "\033[1;31m - Error commande - \033[0m : " << buff << std::endl;
      throw Except("\033[1;31m  - Error commande - \033[0m\n");
  }
  else
    // std::cout << " ) : RE pas trouve ERROR" << std::endl;
    throw Except("\033[1;31m  ) pas trouve \033[0m\n");
  return mylist;
  // mylist.push_front (fact.createOperand(Int32,buff));
}

//===================1ere verification nombre d'argument===============
int numberargument(const std::string s)
{
  std::istringstream iss(s);
  int i = 0;
  Factory fact;
  while (iss)
  {
     std::string sub;
     iss >> sub;
     if (sub.compare("") != 0)
      i++;
   }
  return i;
}


int checknumberargument(const std::string s)
{
  Except err;
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
        // std::cout << "\033[1;31m - ; commentaire - \033[0m\n" << sub << std::endl;
        throw Except("\033[1;31m - ; commentaire - \033[0m\n");
       else
        {
          // std::cout << "\033[1;31m - trop de parametres - \033[0m\n" << sub << std::endl;
          throw Except("\033[1;31m - trop de parametres - \033[0m\n");
          error = 1;
        }
     }
     if (sub.compare("") != 0)
      i++;
   }
  return error;  // std::cout <<"error : "<< error << " et i : " << i << std::endl;
}


//==================  CMD en entree ==================
std::list<IOperand const*> input_cmd(std::string str, std::list<IOperand const *> mylist)
{
  if (str.compare("dump") == 0)
    dump(mylist);
  else if (str.compare("add") == 0)
    mylist = cmd_add(mylist);
  else if (str.compare("sub") == 0)
    mylist = cmd_sub(mylist);
  else if (str.compare("mul") == 0)
    mylist = cmd_mul(mylist);
  else if (str.compare("div") == 0)
    mylist = cmd_div(mylist);
  else if (str.compare("mod") == 0)
    mylist = cmd_mod(mylist);
  else if (str.compare("print") == 0)
    mylist = cmd_print(mylist);
  else if (str.compare("pop") == 0)
    mylist = cmd_pop(mylist);
  else if (str.compare("assert") == 0)
    // std::cout << "\033[1;31m rajoute un type(nombre) apres assert\033[0m ";
    throw Except("\033[1;31m rajoute un type(nombre) apres assert\033[0m  ");
  else if (str.compare("exit") != 0)
    // std::cout << "\033[1;31m - ??? - \033[0m " << str << std::endl;
    throw Except("\033[1;31m - ??? - \033[0m ");

  return mylist;
}

//=========================== parser SPLIT ========================
std::list<IOperand const *> my_split(const std::string str, std::list<IOperand const *> mylist)
{
  Except err;
  std::string s = str;
  int i = 0;
  int pushok = 0;
  int assertok = 0;
  int cmdok = 0;
  Factory fact;

  if (str.find(";") != std::string::npos)   //on cherche tout les ;
    s = str.substr(0,str.find(";"));
  std::istringstream iss(s);
  // std::cout << "\033[1;31m debug |"<< s << "| \033[0m : "  << std::endl;
  if (!checknumberargument(s))
  {
   while (iss)
   {
      std::string sub;
      iss >> sub;
      if (i > 1)
      {
        if (sub.substr(0,1).compare(";") == 0)
          // std::cout << "\033[1;31m - commentaire present - \033[0m : " << sub << std::endl;
          throw Except("\033[1;31m - commentaire present - \033[0m");
        else if (sub.compare("") != 0)
          // std::cout << "\033[1;31m - Error trop de parametres et pas commentaire - \033[0m : " << sub << std::endl;
          throw Except("\033[1;31m - Error trop de parametres et pas commentaire - \033[0m :");

        if (cmdok == 1)
          // std::cout << "\033[1;31m - 2nd parametres ?- \033[0m : " << std::endl;
          throw Except("\033[1;31m - 2nd parametres ?- \033[0m ");
      }
      if (i == 0)
      {
        cmdok = check_cmd(sub);
        if (sub.compare("push") == 0)
          pushok = 1;
        else if (sub.compare("assert") == 0)
          assertok = 1;
        else if (sub.compare("") != 0 && numberargument(str) == 1)
          mylist = input_cmd(sub, mylist);
        else if (sub.compare("") != 0)
          mylist = input_cmd(sub, mylist);
      }
      if (i == 1)
      {
        if (pushok == 1)
          mylist = checktype(sub, mylist);
        else if (assertok == 1)
          mylist = checktypeAssert(sub, mylist);
        else if (cmdok == 1 && sub.substr(0,1).compare(";") == 0)
        // std::cout << "\033[1;31m - PK ce 2nd parametres - \033[0m : " << std::endl;
        throw Except("\033[1;31m - PK ce 2nd parametres - \033[0m ");
      }
      i++;
    }
  }
  // if ((cmdok == 0 && numberargument(str) == 1))
  // std::cout << "\033[1;31m - euh ? - \033[0m " << std::endl;
  return mylist;
}

//===================  PARSER ========================
void parser(std::string str)
{
  Except err;
  Factory fact;
  std::string   buff;
  std::string myints[] = {""};
  std::list<IOperand const *> mylist;
  int exitok = 0;

  mylist = my_split(str, mylist);//premiere ligne
  if (!std::getline(std::cin, buff))
    exit(0);
  if (buff.compare("exit") == 0)
    exitok++;
    mylist = my_split(buff, mylist);
  while(buff.compare(";;") != 0)
  {
    if (!std::getline(std::cin, buff))
      exit(0);//passer a la ligne suivante plutot
    else
      mylist = my_split(buff, mylist);
    if (buff.compare("exit") == 0)
      exitok++;
  }
  if (exitok == 0)
    // std::cout << "\033[1;31m - error - il manque un exit - \033[0m : " << std::endl;
    throw Except("\033[1;31m - error - il manque un exit - \033[0m ");


//====================================================================
//===================      A SUPPRIMER     ===========================
//====================================================================

  // std::cout << "\033[1;33mDEBUG => mylist contains : \033[0m" << std::endl;
  // dump(mylist);
  // std::cout << '\n';

//====================================================================
}

void lecture_fichier(std::string file)
{
  Except err;
  Factory fact;
  std::string   ligne;
  std::string myints[] = {""};
  std::list<IOperand const *> mylist;
  int exitok = 0;

  std::ifstream fichier(file, std::ios::in);  // on ouvre le fichier en lecture

      if(fichier)  // si l'ouverture a réussi
      {
        while(getline(fichier, ligne) && ligne.compare(";;") != 0)
        {
            mylist = my_split(ligne, mylist);
          if (ligne.compare("exit") == 0)
            exitok++;
        }
        if (exitok == 0)
          throw Except("\033[1;31m - error - il manque un exit - \033[0m ");
          // std::cout << "\033[1;31m - error - il manque un exit - \033[0m : " << std::endl;
        fichier.close();
      }
      else
      {
            throw Except("Impossible d'ouvrir le fichier !");
            exit(0);
            parser(file);
      }
}


int main(int ac, char **av)
{
  if (ac == 1)
  {
    try
    {
      parser("");
    }
    catch (std::exception & err)
    {
      std::cerr << err.what() << "\n";
    }
  }
  else if (ac == 2)
  {
    try
    {
      lecture_fichier(av[1]);
    }
    catch (std::exception & err)
    {
      std::cerr << err.what() << "\n";
    }
  }
  else if (ac > 2)
      return (0);//relancer la commande tant qu'on a pas exit
  return (0);


  // if (ac == 1)
  //   parser("");
  // else if (ac == 2)
  //     lecture_fichier(av[1]);
  // else if (ac > 2)
  //     return (0);//relancer la commande tant qu'on a pas exit
  // return (0);
}
