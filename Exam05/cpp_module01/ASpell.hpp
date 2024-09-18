#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <iostream>
#include "ATarget.hpp"
using namespace std;

class ATarget;

class ASpell{
    protected:
        string name;
        string effects;
    public:
        ASpell(const string&, const string&);
        ASpell(const ASpell&);
        ASpell& operator=(const ASpell&);
        string  getName( void ) const;
        string  getEffects( void ) const;
        void    launch(const ATarget& target) const;
        virtual ASpell* clone( void ) const=0;
        virtual ~ASpell( void );

};

#endif