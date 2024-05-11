#include "GMF.h"

GMF::GMF()
{
	//in_buffer = boost::lockfree::queue<std::string>(100);
	//out_buffer = NULL;
}

boost::thread* GMF::start() {
	boost::thread t([this] {process(); });
	return &t;
}
