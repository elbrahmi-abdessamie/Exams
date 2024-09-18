#ifndef WARLOCK_HPP
#define WARLOCK_HPP
#include <map>
#include "ASpell.hpp"

using namespace std;

class Warlock{
	private:
		string name;
		string title;
		map<string, ASpell*>	gramorr;
		Warlock();
	public:
		Warlock(const string& _name, const string &_title);
		Warlock(const Warlock& toCpy);
		Warlock& operator=(const Warlock& src);
		const string &getName( void ) const;
		const string &getTitle( void ) const;
		void	setTitle(const string& netTitle);
		void	introduce( void ) const;
		void	learnSpell( ASpell* );
		void	forgetSpell( string );
		void	launchSpell( const string, const ATarget& );
		~Warlock( void );
};

#endif