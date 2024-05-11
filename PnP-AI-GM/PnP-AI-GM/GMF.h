#ifndef GMF_H
#define GMF_H
#include <queue>
#include <string>
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/chrono.hpp>

// Base class for all GMF; abstract, override void process() in inheriting class
class GMF
{
public:
	GMF();
	virtual ~GMF() = default;
	std::string getId() { return id; };
	boost::lockfree::queue<std::string*>* getBuffer() { return &in_buffer; };
	void setOutBuffer(boost::lockfree::queue<std::string*>* b) { out_buffer = b; };
	boost::thread* start();
protected:
	virtual void process() = 0;
	std::string id;
	boost::lockfree::queue<std::string*> in_buffer{ 100 };
	boost::lockfree::queue<std::string*>* out_buffer;
	std::string in_id;
	std::string out_id;
};
#endif
