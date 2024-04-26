#pragma once
#include <vector>
#include <string>
#include "GMF.h"
#include "GMF_0.h"
#include "GMF_1.h"
#include "GMF_2.h"
class GM_control
{
public:
	explicit GM_control();
	void findFragmentById(std::string);
private:
	std::vector<GMF*> fragments;
};

