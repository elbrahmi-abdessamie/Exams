#include "Fwoosh.hpp"

Fwoosh::Fwoosh()
: ASpell("Fwoosh", "fwooshed")
{}

ASpell*	Fwoosh::clone( void ) const
{
	return new Fwoosh;
}
