#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include "IOperand.hpp"
#include "factory.hpp"
#include <iostream>
#include <sstream>
#include <string>

//http://www.cplusplus.com/reference/list/list/

template <typename T>
class Operand: public IOperand {

public:
  //============== constructeur form canonique ===========
  Operand( void );//constructeur
  Operand( const eOperandType type, const std::string value );
  Operand( Operand const & rhs);//constructeur par copie = avec comme parametre une instance de la clase declaree
  Operand & operator=( Operand const & rhs);//operateur egal :  operateur d'assignation = mise a jour de l'instance courante
  virtual ~Operand( void );//destructeur

  // IOperand const * createOperand( eOperandType type, std::string const & value ) const;
  virtual std::string const & toString( void ) const; // String representation of the instance

  //=============== getter ===============
  eOperandType getType (void) const;
  int          getPrecision (void) const;

  virtual IOperand const * operator+( IOperand const & rhs ) const; // Sum
  virtual IOperand const * operator-( IOperand const & rhs ) const; // Difference
  virtual IOperand const * operator*( IOperand const & rhs ) const; // Product
  virtual IOperand const * operator/( IOperand const & rhs ) const; // Quotient
  virtual IOperand const * operator%( IOperand const & rhs ) const; // Modulo


private:
  T             _value;
  eOperandType  _type;
  std::string   _svalue;
  Factory       *_fact;
};


//======================= instanciation =======================
template <typename T>
Operand<T>::Operand( const eOperandType type, const std::string svalue ) : _type(type), _svalue(svalue)
{
  std::stringstream ss(svalue);
  ss >> _value;// evite d'avoir un getValue
  _fact = new Factory();
}


template <typename T>
Operand<T>::Operand( Operand const & rhs) : _type(rhs.getType())
{
  std::stringstream ss(rhs.toString());
  ss >> _value;
  _fact = new Factory();
}

template <typename T>
Operand<T>::~Operand( void )
{
}

//======= TOSTRING ===== std::string const & toString( void ) const
template <typename T>
std::string const &Operand<T>::toString() const
{
  return (this->_svalue);
}

// ====================getType================
template <typename T>
eOperandType Operand<T>::getType (void) const
{
  return (this->_type);
}
//======================getPrecision================
template <typename T>
int Operand<T>::getPrecision (void) const
{
  int i = 0;
  std::string str;

  if (this->_type == Double || this->_type == Float)
  {
    i = this->_svalue.find('.');
    // std::cout << "ya un ." << std::endl;
    if (i != -1)
      return (this->_svalue.size() - 1 - i);// a tester en vrai, apres avoir fait un operand
  }
  // std::cout << "c'est un INT" << std::endl;
  return (0);
}


//===================== OPERATOR ======================
template <typename T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const
{
  // const Operand<T>  *l = NULL;
  // eOperandType      type;
  std::stringstream ss, ss1(this->toString()), ss2(rhs.toString());
  long double       i, j, k;
  int               prec;

  ss1 >> i;
  ss2 >> j;
  //====== operation ======
  k = i + j;
  // std::cout << "i :" << std::fixed << std::setprecision(7) << i << std::endl;
  // std::cout << "j :" << j << std::endl;
  if (this->getType() >= Float || rhs.getType() >=  Float)//verification de la precision
  {
    prec = this->getPrecision();
    if (rhs.getPrecision() >= this->getPrecision())
      prec = rhs.getPrecision();
    // std::cout <<"precision : " << prec << std::endl;
    ss << std::fixed << std::setprecision(prec) << k;
  }
  else
    ss << k;
  // std::cout << " somme : " << ss.str() << std::endl;

    //retourner le bon type (float ou double pour la precision)
    if (this->getType() > rhs.getType())
      return _fact->createOperand(this->getType(), ss.str());
    else
      return _fact->createOperand(rhs.getType(), ss.str());


  return NULL;

}

template <typename T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
  std::stringstream ss, ss1(this->toString()), ss2(rhs.toString());
  long double       i, j, k;
  int               prec;

  ss1 >> i;
  ss2 >> j;
  //====== operation ======
  k = i - j;
  if (this->getType() >= Float || rhs.getType() >=  Float)//verification de la precision
  {
    prec = this->getPrecision();
    if (rhs.getPrecision() >= this->getPrecision())
      prec = rhs.getPrecision();// std::cout <<"precision : " << prec << std::endl;
    ss << std::fixed << std::setprecision(prec) << k;
  }
  else
    ss << k;// std::cout << " somme : " << ss.str() << std::endl;
  if (this->getType() > rhs.getType())    //retourner le bon type (float ou double pour la precision)
    return _fact->createOperand(this->getType(), ss.str());
  else
    return _fact->createOperand(rhs.getType(), ss.str());

  return NULL;
}

template <typename T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
  std::stringstream ss, ss1(this->toString()), ss2(rhs.toString());
  long double       i, j, k;
  int               prec;

  ss1 >> i;
  ss2 >> j;
  //====== operation ======
  k = i * j;
  if (this->getType() >= Float || rhs.getType() >=  Float)//verification de la precision
  {
    prec = this->getPrecision();
    if (rhs.getPrecision() >= this->getPrecision())
      prec = rhs.getPrecision();// std::cout <<"precision : " << prec << std::endl;
    ss << std::fixed << std::setprecision(prec) << k;
  }
  else
    ss << k;// std::cout << " somme : " << ss.str() << std::endl;
  if (this->getType() > rhs.getType())    //retourner le bon type (float ou double pour la precision)
    return _fact->createOperand(this->getType(), ss.str());
  else
    return _fact->createOperand(rhs.getType(), ss.str());

  return NULL;
}

template <typename T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
  std::stringstream ss, ss1(this->toString()), ss2(rhs.toString());
  long double       i, j, k;
  int               prec;

  ss1 >> i;
  ss2 >> j;
  if (j == 0)
  {
    std::cout << " error :division par 0 (check du IOperand)  y a  encore un autre check apre :-P" << std::endl;
    exit(0);
  }
  //====== operation ======
  k = i / j;
  if (this->getType() >= Float || rhs.getType() >=  Float)//verification de la precision
  {
    prec = this->getPrecision();
    if (rhs.getPrecision() >= this->getPrecision())
      prec = rhs.getPrecision();// std::cout <<"precision : " << prec << std::endl;
    ss << std::fixed << std::setprecision(prec) << k;
  }
  else
    ss << k;// std::cout << " somme : " << ss.str() << std::endl;
  if (this->getType() > rhs.getType())    //retourner le bon type (float ou double pour la precision)
    return _fact->createOperand(this->getType(), ss.str());
  else
    return _fact->createOperand(rhs.getType(), ss.str());

  return NULL;
}

template <typename T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
  std::stringstream ss, ss1(this->toString()), ss2(rhs.toString());
  long int       i, j, k;
  int               prec;

  ss1 >> i;
  ss2 >> j;
  if (j == 0)
  {
    std::cout << " error : % 0, les nombres doivent etre des int IOperand" << std::endl;
    exit(0);
  }
  //====== operation ======
  k = i % j;
  if (this->getType() >= Float || rhs.getType() >=  Float)//verification de la precision
  {
    prec = this->getPrecision();
    if (rhs.getPrecision() >= this->getPrecision())
      prec = rhs.getPrecision();// std::cout <<"precision : " << prec << std::endl;
    ss << std::fixed << std::setprecision(prec) << k;
  }
  else
    ss << k;// std::cout << " somme : " << ss.str() << std::endl;
  if (this->getType() > rhs.getType())    //retourner le bon type (float ou double pour la precision)
    return _fact->createOperand(this->getType(), ss.str());
  else
    return _fact->createOperand(rhs.getType(), ss.str());

  return NULL;
}

#endif