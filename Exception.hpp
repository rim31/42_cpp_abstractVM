#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <iostream>
#include <sstream>
#include <string>

class Except : public std::exception
{

  public:
    Except( void );//constructeur
    Except( Except const & src);//constructeur par copie = avec comme parametre une instance de la clase declaree
    virtual ~Except( void ) throw();//destructeur

    Except & operator=( Except const & nb);//operateur egal :  operateur d'assignation = mise a jour de l'instance courante

    void setExcept( const char * msg );

    virtual const char* what() const throw();

    const char * msg;
};

  //======================= instanciation =======================
  Except::Except (void)
  {
    std::cout << "Default constructor called" << std::endl;
    return;
  }

  Except::Except (Except const & src)
  {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
    return;
  }


  Except::~Except (void) throw()
  {
    std::cout << "Destructor called" << std::endl;
    return;
  }

  Except & Except::operator=( Except const & nb)
  {
    std::cout << "Assignation operator called" << std::endl;
    return *this;
  }

  void Except::setExcept( const char * msg )
  {
    std::ostringstream oss;
    oss << this->msg;
    std::cout << "ERROR -> " << oss.str() << std::endl;
    exit(0);
    // this->msg = msg;
    return;
  }

  const char* Except::what() const throw()
  {
    return ("CLASS error");
    // return this->msg.c_str();
  }




#endif