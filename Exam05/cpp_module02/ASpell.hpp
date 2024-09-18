#ifndef ASPELL_HPP
#define ASPELL_HPP

#include "ATarget.hpp"


using namespace std;

class ATarget;
class ASpell{
	protected:
		string name;
		string effects;
		ASpell();
	public:
		ASpell(const string& _name, const string& _effects);
		ASpell( const ASpell& );
		ASpell& operator=( const ASpell& );
		string	getName( void ) const;
		string	getEffects( void ) const;
		virtual ASpell*	clone( void ) const=0;
		void	launch( const ATarget& target ) const;
		virtual ~ASpell();
};

#endif
