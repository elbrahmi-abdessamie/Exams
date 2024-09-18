#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(){}

TargetGenerator::TargetGenerator(const TargetGenerator& toCpy) { *this = toCpy; }
TargetGenerator& TargetGenerator::operator=(const TargetGenerator& src)
{
    if (this != &src)
        this->_targets = src._targets;
    return *this;
}

void    TargetGenerator::learnTargetType(ATarget* target)
{
    if (target)
        _targets.insert(make_pair(target->getType(), target->clone()));

}

void TargetGenerator::forgetTargetType(std::string const & target)
{
	if (_targets.find(target) != _targets.end())
		_targets.erase(_targets.find(target));
}

ATarget* TargetGenerator::createTarget(std::string const &target)
{
	ATarget* tmp = NULL;
	if (_targets.find(target) != _targets.end())
		tmp = _targets[target];
	return (tmp);
}
TargetGenerator::~TargetGenerator()
{
	for (map<string, ATarget*>::iterator it = _targets.begin(); it != _targets.end(); it++)
		delete it->second;
	_targets.clear();
}