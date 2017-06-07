#include "factory.hpp"
#include "Operand.hpp"
// #include "Operand.hpp"
#include <iostream>

  //publlic constructor
  Factory::Factory(void) {
    this->create[0] = &Factory::createInt8;
    this->create[1] = &Factory::createInt16;
    this->create[2] = &Factory::createInt32;
    this->create[3] = &Factory::createFloat;
    this->create[4] = &Factory::createDouble;
  }//constructeur par defaut

  Factory::~Factory(void) {} // destructeur

  Factory::Factory( Factory const & src)
  {
    *this = src;//on aurait pu construire ici en mettant les createInt...
  }//constructeur par copie

  Factory & Factory::operator=( Factory const & rhs)//operateur egal
  {
    this->create[0] = &Factory::createInt8;
    this->create[1] = &Factory::createInt16;
    this->create[2] = &Factory::createInt32;
    this->create[3] = &Factory::createFloat;
    this->create[4] = &Factory::createDouble;
    return (*this);
  }

//=================function check Type  value =================
template<typename T>
 bool Factory::checkTypeCreateOperand(std::string const & value) const
{
  std::stringstream ss(value);
  long double       nb;
//
  ss >> nb;
  // std::cout << nb <<std::endl;
  // std::cout << std::to_string(std::numeric_limits<T>::lowest()) <<std::endl;
  // std::cout << std::to_string(std::numeric_limits<T>::max()) <<std::endl;

  if (nb >= std::numeric_limits<T>::lowest() && nb <= std::numeric_limits<T>::max())
    return true;
  std::cout << "error taille" <<std::endl;
  return false;//error format
}


// tableau pointeur sur fonction
  IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const{
    if (type <= 4 && type >= 0)
      return (this->*create[type])(value);
    return NULL;
  }


  IOperand const * Factory::createInt8( std::string const & value ) const
  {
    //fucntion check
    std::cout << "Factory createInt8 => " << std::to_string(checkTypeCreateOperand<char>(value)) <<std::endl;

    if (!checkTypeCreateOperand<char>(value))
      exit(0);
    return (new Operand<char>(Int8, value));
  }

  IOperand const * Factory::createInt16( std::string const & value ) const
  {
    //fucntion check
    std::cout << "Factory createInt16 => " << std::to_string(checkTypeCreateOperand<short int>(value)) <<std::endl;

    if (!checkTypeCreateOperand<short int>(value))
      exit(0);
    return (new Operand<short int>(Int16, value));
  }

  IOperand const * Factory::createInt32( std::string const & value ) const
  {
    //fucntion check
    std::cout << "Factory createInt32 => " << std::to_string(checkTypeCreateOperand<signed int>(value)) <<std::endl;

    if (!checkTypeCreateOperand<signed int>(value))
      exit(0);
    return (new Operand<signed int>(Int32, value));
  }

  IOperand const * Factory::createFloat( std::string const & value ) const
  {
    //fucntion check
    std::cout << "Factory float => " << std::to_string(checkTypeCreateOperand<float>(value)) <<std::endl;

    if (!checkTypeCreateOperand<float>(value))
      exit(0);
    return (new Operand<float>(Float, value));
  }

  IOperand const * Factory::createDouble( std::string const & value ) const
  {
    //fucntion check
    std::cout << "Factory double => " << std::to_string(checkTypeCreateOperand<double>(value)) <<std::endl;

    if (!checkTypeCreateOperand<double>(value))
      exit(0);
    return (new Operand<double>(Double, value));
  }


