#ifndef GM_CONTROL_H
#define GM_CONTROL_H
#include <vector>
#include <string>
#include "GMF.h"
#include "GMF_0.h"
#include "GMF_1.h"
#include "GMF_2.h"
#include "Game_session.h"
class GM_control
{
public:
	explicit GM_control();
	GMF* findFragmentById(std::string);
	void start();
	void buildPipeline();
	boost::lockfree::queue<std::string*>* getInBuffer();
	boost::lockfree::queue<std::string*>* getOutBuffer();
	std::string getThread_Id();
private:
	std::vector<GMF*> fragments;
	boost::lockfree::queue<std::string*>* in_buffer;
	boost::lockfree::queue<std::string*> out_buffer{ 100 };
	Game_session* session = new Game_session("");
};
#endif