#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <iostream>
#include <sstream>
#include <string>

class Except : public std::exception
{
  public:
    Except( void );//constructeur
    Except(const char * message);

    Except( Except const & src);//constructeur par copie = avec comme parametre une instance de la clase declaree
    virtual ~Except( void ) throw();//destructeur
    Except & operator=( Except const & nb);//operateur egal :  operateur d'assignation = mise a jour de l'instance courante

    const char * setExcept( const char * msg );

    virtual const char* what() const throw();

    const char * msg;
};

// //======================= instanciation =======================
// Except::Except (void)
// {
//   // std::cout << "Default constructor called" << std::endl;
//   return;
// }
// Except::Except (const char * message) : msg(message)
// {
//   // std::cout << "Default constructor 2 called" << std::endl;
//   return;
// }
//
// Except::Except (Except const & src)
// {
//   // std::cout << "Copy constructor called" << std::endl;
//   *this = src;
//   return;
// }
//
//
// Except::~Except (void) throw()
// {
//   // std::cout << "Destructor called" << std::endl;
//   return;
// }
//
// Except & Except::operator=( Except const & nb)
// {
//   // std::cout << "Assignation operator called" << std::endl;
//   return *this;
// }
//
// const char * Except::setExcept( const char * msg )
// {
//   std::ostringstream oss;
//   oss << this->msg;
//   std::cout << oss.str() << std::endl;
//   // exit(0);
//   this->msg = msg;
//   // std::cout << "lopette " << std::endl;
//
//   return msg;
// }
//
// const char* Except::what() const throw()
// {
//   // this->msg = "hello world";
//   // std::cout << this->msg << std::endl;
//   // return ("CLASS error");
//   return this->msg;
// }


#endif
