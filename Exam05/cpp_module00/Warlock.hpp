#ifndef WARLOCK_HPP
#define WARLOCK_HPP
#include <iostream>

using namespace std;

class Warlock{
    private:
        string name;
        string title;
        Warlock( void );
    public:
        Warlock(const string&, const string&);
        ~Warlock( void );
        Warlock( const Warlock& );
        Warlock& operator=(const Warlock&);
        const string&   getName( void ) const;
        const string&   getTitle( void ) const;
        void            setTitle(const string&);
        void            introduce( void ) const;
};


#endif