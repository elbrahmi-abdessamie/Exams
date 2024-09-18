#include "Warlock.hpp"

Warlock::Warlock( void ){}
Warlock::Warlock(const string& _name, const string& _title)
: name(_name), title(_title)
{
    cout << this->name << ": This looks like another boring day." << endl;
}

Warlock::Warlock(const Warlock& toCpy)
: name(toCpy.name), title(toCpy.title)
{}

Warlock& Warlock::operator=(const Warlock& src)
{
    if (this != &src)
    {
        this->name = src.name;
        this->title = src.title;
    }
    return *this;
}

const string& Warlock::getName( void ) const { return this->name; }
const string& Warlock::getTitle( void ) const { return this->title; }

void    Warlock::setTitle(const string& newTitle){ this->title = newTitle; }
void    Warlock::introduce( void ) const {
    cout << this->getName() << ": I am " << this->getName()
    << ", " << this->getTitle() << "!" << endl;
}

Warlock::~Warlock( void ){
    cout << this->getName() << ": My job here is done!" << endl;
    for(map<string, ASpell*>::iterator it = gramorr.begin(); it!= gramorr.end();it++)
        delete it->second;
    gramorr.clear();
}

void    Warlock::learnSpell( ASpell* spell )
{
    if (spell)
        gramorr.insert(make_pair(spell->getName(), spell->clone()));
}

void    Warlock::forgetSpell( string spell_name )
{
    map<string, ASpell*>::iterator it = gramorr.find(spell_name);
    if (it != gramorr.end())
    {
        delete it->second;
        gramorr.erase(it);
    }
}

void    Warlock::launchSpell( string spell_name, const ATarget& target)
{
    map<string, ASpell*>::iterator it = gramorr.find(spell_name);
    if (it != gramorr.end())
        (it->second)->launch(target);   
}