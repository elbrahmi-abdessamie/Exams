#include "ASpell.hpp"

// ASpell::ASpell( void ){}
ASpell::ASpell(const string& _name, const string& _effects)
: name(_name), effects(_effects)
{}

ASpell::ASpell(const ASpell& toCpy)
: name(toCpy.name), effects(toCpy.effects)
{}
ASpell& ASpell::operator=(const ASpell& src)
{
    if (this != &src)
    {
        this->name = src.name;
        this->effects = src.effects;
    }
    return *this;
}

string ASpell::getName( void ) const { return this->name; }
string ASpell::getEffects( void ) const { return this->effects; }

void    ASpell::launch(const ATarget& target) const
{
    target.getHitBySpell(*this);
}

ASpell::~ASpell( void )
{}




