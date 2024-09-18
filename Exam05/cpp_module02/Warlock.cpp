#include "Warlock.hpp"

Warlock::Warlock(){}

Warlock::Warlock(const string &_name, const string &_title)
: name(_name), title(_title)
{
	cout << this->name << ": This looks like another boring day." << endl;
}

Warlock::Warlock(const Warlock& toCpy ) 
: name(toCpy.name), title(toCpy.title)
{}

Warlock& Warlock::operator=(const Warlock& src ) {
	if (this == &src)
		return *this;
	this->name = src.name;
	this->title = src.title;
	return *this;
}

const string& Warlock::getName( void ) const { return this->name; }

const string& Warlock::getTitle( void ) const { return this->title; }

void Warlock::setTitle( const string& newTitle ) { this->title = newTitle; }

void	Warlock::introduce( void ) const { cout << this->getName() << ": I am " << this->getName() << ", " << this->getTitle() << "!" << endl; }

void	Warlock::learnSpell( ASpell* spell )
{
	_gramorr.learnSpell(spell);
}

void	Warlock::forgetSpell(string spell_name)
{
	_gramorr.forgetSpell(spell_name);
	
}

void	Warlock::launchSpell(const string spell_name, const ATarget& target)
{
	ASpell* spell = _gramorr.createSpell(spell_name);
	
	spell->launch(target);
}


Warlock::~Warlock( void ) { 
	cout << this->getName() << ": My job here is done!" << endl;
}
