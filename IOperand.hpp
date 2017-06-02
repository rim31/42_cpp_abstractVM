#ifndef IOPERAND_HPP
# define IOPERAND_HPP
#include <iostream>
#include <string>
#include <locale>
#include <iomanip>
#include <stdexcept>

// template<typename T>
// enum cmdType {push, pop, dump, assert, add, sub, mul, div, mod, print};
enum eOperandType {Int8, Int16, Int32, Float, Double };
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


class IOperand {
public:
  virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
  virtual eOperandType getType( void ) const = 0; // Type of the instance
  virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
  virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
  virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
  virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
  virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
  virtual std::string const & toString( void ) const = 0; // String representation of the instance
  virtual ~IOperand( void ) {}
};



#endif

//
// //factory : design patern  (evite les new partout)
//
// interface : https://www.youtube.com/watch?v=DK6vSUVfyug
//
// pattern abstact factory : interdit de faire new
//
// public iterface BFactory {
//   public Babst createB();
// }
//
// Bfactoty bf;
// Bast = Bf.createB();
//
// pb de l'unique instance : singleton
// methode de classe (static) :
// la classe est respondable de la methode
// les objects sont responsable des ethodes non static
//
// instance()
//
// static A singleton=null;
// publi static A intance() {
//   if (singleton==null) singleton new A();
//   return singleton;
// }
// private A() {}
// //avant A a = new A();
// //apres A a = A.instance();

