#include "GM_control.h"


GM_control::GM_control()
{
	fragments = std::vector<GMF*>();
	in_buffer = NULL;
	out_buffer = std::queue<std::string>();

	fragments.push_back(new GMF_0("0"));
	fragments.push_back(new GMF_1("1"));
	fragments.push_back(new GMF_0("2"));
}

std::queue<std::string>* GM_control::getInBuffer()
{
	return in_buffer;
}

std::queue<std::string>* GM_control::getOutBuffer()
{
	return &out_buffer;
}

GMF* GM_control::findFragmentById(std::string id)
{
	for (GMF* i : GM_control::fragments) {
		if (i->getId() == id) return i;
	}
	return NULL;
}

void GM_control::start() {
	buildPipeline();
}

void GM_control::buildPipeline() {
	in_buffer = findFragmentById("1")->getBuffer();
	findFragmentById("1")->setOutBuffer(findFragmentById("0")->getBuffer());
	findFragmentById("0")->setOutBuffer(findFragmentById("2")->getBuffer());
	findFragmentById("2")->setOutBuffer(&out_buffer);
}
