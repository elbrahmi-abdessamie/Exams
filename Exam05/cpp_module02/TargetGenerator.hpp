#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include <map>
#include "ATarget.hpp"
using namespace std;

class TargetGenerator{

    private:
        TargetGenerator(const TargetGenerator&);
        TargetGenerator& operator=(const TargetGenerator&);
        map<string, ATarget*> _targets;
    public:
        TargetGenerator();
        ~TargetGenerator();
        void learnTargetType(ATarget*);
        void forgetTargetType(string const &);
        ATarget* createTarget(string const &);
};

#endif