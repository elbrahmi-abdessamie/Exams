#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

using namespace std;

class SpellBook{
    private:
        SpellBook(const SpellBook&);
        SpellBook& operator=(const SpellBook&);
        map<string, ASpell*> gramorr;
    public:
        SpellBook();
        ~SpellBook();
        void learnSpell(ASpell*);
        void forgetSpell(string const &);
        ASpell* createSpell(string const &);
};

#endif