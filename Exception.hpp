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

#endif
