#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>
#include "ASpell.hpp"
using namespace std;

class ASpell;

class ATarget{
	protected:
		string type;
		ATarget();
	public:
		ATarget(const string& _type);
		ATarget(const ATarget&);
		ATarget& operator=(const ATarget&);
		const string& getType( void ) const;
		virtual ATarget* clone() const=0;
		void	getHitBySpell( const ASpell& spell ) const;
		virtual ~ATarget();
};

#endif
