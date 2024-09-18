#include "ATarget.hpp"

ATarget::ATarget( void ){}
ATarget::ATarget(const string& _type)
: type(_type)
{}
ATarget::ATarget(const ATarget& toCpy)
: type(toCpy.type)
{}
ATarget& ATarget::operator=(const ATarget& src)
{
    if (this != &src)
        this->type = src.type;
    return *this;
}

const string& ATarget::getType( void ) const { return this->type; }

void    ATarget::getHitBySpell(const ASpell& spell) const
{
    cout << this->getType() << " has been " << spell.getEffects() << "!" << endl;
}

ATarget::~ATarget( void )
{}
