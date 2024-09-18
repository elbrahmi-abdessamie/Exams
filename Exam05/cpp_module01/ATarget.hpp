#ifndef ATARGET_HPP
#define ATARGET_HPP

#include "ASpell.hpp"

using namespace std;
class ASpell;

class ATarget{
    protected:
        string type;
        ATarget( void );
    public:
        ATarget(const string&);
        ATarget(const ATarget&);
        ATarget& operator=(const ATarget&);
        const string&  getType( void ) const;
        void    getHitBySpell(const ASpell&) const;
        virtual ATarget* clone( void ) const=0;
        virtual ~ATarget( void );

};


#endif