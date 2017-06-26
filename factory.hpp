#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "IOperand.hpp"

class Factory
{
  //publlic constructor
  public:
  Factory(void);//constructeur par defaut

  virtual ~Factory(void);// destructeur

  Factory( Factory const & rhs);//constructeur par copie

  Factory & operator=( Factory const & rhs);//operateur egal

  IOperand const * createOperand( eOperandType type, std::string const & value ) const;

  IOperand const * createInt8( std::string const & value ) const;
  IOperand const * createInt16( std::string const & value ) const;
  IOperand const * createInt32( std::string const & value ) const;
  IOperand const * createFloat( std::string const & value ) const;
  IOperand const * createDouble( std::string const & value ) const;

  IOperand const *(Factory::*create[5])(std::string const &) const;//// tableau pointeur sur fonction

  template<typename T>
  bool checkTypeCreateOperand(std::string const & value) const;

};

#endif
