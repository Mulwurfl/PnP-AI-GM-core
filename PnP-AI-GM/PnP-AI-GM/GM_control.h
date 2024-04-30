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
	GMF* findFragmentById(std::string);
	void start();
	void buildPipeline();
	std::queue<std::string>* getInBuffer();
	std::queue<std::string>* getOutBuffer();
private:
	std::vector<GMF*> fragments;
	std::queue<std::string>* in_buffer;
	std::queue<std::string> out_buffer;
};

