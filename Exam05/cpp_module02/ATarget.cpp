#include "ATarget.hpp"

ATarget::ATarget(){}

ATarget::ATarget(const string& _type)
: type(_type)
{}

ATarget::ATarget(const ATarget& src)
: type(src.type)
{}

ATarget& ATarget::operator=(const ATarget& toCpy)
{
	if (this == &toCpy)
		return *this;
	this->type = toCpy.type;
	return *this;
}

const string&	ATarget::getType( void ) const{ return this->type; }

void	ATarget::getHitBySpell( const ASpell& spell ) const
{
	cout << this->getType() << " has been " << spell.getEffects() << "!" << endl;
}

ATarget::~ATarget(){}

