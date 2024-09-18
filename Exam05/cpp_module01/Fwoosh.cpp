#include "Fwoosh.hpp"

Fwoosh::Fwoosh( void )
: ASpell("Fwoosh", "fwooshed")
{}

ASpell* Fwoosh::clone( void ) const { return new Fwoosh;}

Fwoosh::~Fwoosh( void ){}