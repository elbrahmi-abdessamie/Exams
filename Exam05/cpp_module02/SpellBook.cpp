#include "SpellBook.hpp"

SpellBook::SpellBook(){}

SpellBook::SpellBook(const SpellBook& toCpy) { *this = toCpy; }

SpellBook& SpellBook::operator=(const SpellBook& src)
{
    if (this != &src)
        return *this;
    this->gramorr = src.gramorr;
    return *this;
}

void    SpellBook::learnSpell(ASpell* spell)
{
    if (spell)
        gramorr.insert(make_pair(spell->getName(), spell->clone()));

}

void    SpellBook::forgetSpell(const string& spell_name)
{
    map<string, ASpell*>::iterator it_spell = gramorr.find(spell_name);
    if (it_spell != gramorr.end())
    {
        delete it_spell->second;
        gramorr.erase(it_spell);
    }
}

ASpell* SpellBook::createSpell(const string& spell_name)
{
    ASpell* tmp = NULL;
    map<string, ASpell*>::iterator it_spell = gramorr.find(spell_name);
    if (it_spell != gramorr.end())
        tmp = it_spell->second;
    return tmp;
}

SpellBook::~SpellBook()
{
    for (map<string, ASpell*>::iterator it = gramorr.begin(); it != gramorr.end(); it++)
	{
		delete it->second;
	}
	gramorr.clear();
}