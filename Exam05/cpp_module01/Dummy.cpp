#include "Dummy.hpp"

Dummy::Dummy( void )
: ATarget("Target Practice Dummy")
{}

ATarget*    Dummy::clone( void ) const
{
    return new Dummy;
}
Dummy::~Dummy( void ){}