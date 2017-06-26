#include "Exception.hpp"

//======================= instanciation =======================
Except::Except (void)
{
  // std::cout << "Default constructor called" << std::endl;
  return;
}
Except::Except (const char * message) : msg(message)
{
  // std::cout << "Default constructor 2 called" << std::endl;
  return;
}

Except::Except (Except const & src)
{
  // std::cout << "Copy constructor called" << std::endl;
  *this = src;
  return;
}


Except::~Except (void) throw()
{
  // std::cout << "Destructor called" << std::endl;
  return;
}

Except & Except::operator=( Except const & nb)
{
  // std::cout << "Assignation operator called" << std::endl;
  return *this;
}

const char * Except::setExcept( const char * msg )
{
  std::ostringstream oss;
  oss << this->msg;
  std::cout << oss.str() << std::endl;
  // exit(0);
  this->msg = msg;
  // std::cout << "lopette " << std::endl;

  return msg;
}

const char* Except::what() const throw()
{
  // this->msg = "hello world";
  // std::cout << this->msg << std::endl;
  // return ("CLASS error");
  return this->msg;
}
