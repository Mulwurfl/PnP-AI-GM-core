#pragma once
#include <queue>
#include <string>

// Base class for all GMF; abstract, override void process() in inheriting class
class GMF
{
public:
	GMF();
protected:
	virtual void process();
	std::string id;
	std::queue<std::string> in_buffer;
	std::queue<std::string>& out_buffer;
	std::string& in_id;
	std::string& out_id;
};

