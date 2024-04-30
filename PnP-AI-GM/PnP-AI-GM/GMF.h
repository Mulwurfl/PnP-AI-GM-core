#ifndef GMF_H
#define GMF_H
#include <queue>
#include <string>

// Base class for all GMF; abstract, override void process() in inheriting class
class GMF
{
public:
	GMF();
	std::string getId() { return id;};
	std::queue<std::string>* getBuffer() { return &in_buffer; };
	void setOutBuffer(std::queue<std::string>* b) { out_buffer = b; };
protected:
	virtual void process();
	std::string id;
	std::queue<std::string> in_buffer;
	std::queue<std::string>* out_buffer;
	std::string in_id;
	std::string out_id;
};
#endif