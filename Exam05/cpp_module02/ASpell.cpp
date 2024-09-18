#include "ASpell.hpp"

ASpell::ASpell(){}

ASpell::ASpell(const string& _name, const string& _effects)
: name(_name), effects(_effects)
{}

ASpell::ASpell(const ASpell& src)
: name(src.name), effects(src.effects)
{}

ASpell& ASpell::operator=(const ASpell& toCpy)
{
	if (this == &toCpy)
		return *this;
	this->name = toCpy.name;
	this->effects = toCpy.effects;
	return *this;
}

string	ASpell::getName( void ) const{ return this->name; }
string	ASpell::getEffects( void ) const { return this->effects; }

void	ASpell::launch( const ATarget& target ) const
{ target.getHitBySpell(*this); }

ASpell::~ASpell(){}
