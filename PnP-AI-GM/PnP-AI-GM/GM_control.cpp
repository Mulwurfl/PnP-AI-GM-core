#include "GM_control.h"


GM_control::GM_control()
{
	fragments = std::vector<GMF*>();
	in_buffer = NULL;
	//out_buffer = boost::lockfree::queue<std::string>(100);

	fragments.push_back(new GMF_0("0"));
	fragments.push_back(new GMF_1("1"));
	fragments.push_back(new GMF_2("2"));
}

boost::lockfree::queue<std::string*>* GM_control::getInBuffer()
{
	return in_buffer;
}

boost::lockfree::queue<std::string*>* GM_control::getOutBuffer()
{
	return &out_buffer;
}

std::string GM_control::getThread_ID()
{
	return session->getChatThreadID();
}

void GM_control::setThread_ID(std::string id)
{
	session->setChatThreadID(id);
}

std::string GM_control::getChatHistory()
{
	return std::string();
}

void GM_control::updateChatHistory(std::string messages)
{
	std::forward_list<ChatMessage*> chat;
	std::string str_tmp = "";
	std::string p1, p2, p3;
	int int_tmp = 0;
	int c = std::stoi(messages.substr(0, messages.find("):")));

	// "7):  #!#!#94:{message 1}:{user}:{id_1} #!#!#95:{message 2}:{assistant}:{id_2} ..... #!#!#100:{message 7}:{user}:{id_7}"
	for (int i = 0; i < c; i++)
	{
		int_tmp = messages.find(":{") + 2;
		p1 = messages.substr(int_tmp, messages.find("}:{", int_tmp) - int_tmp);
		int_tmp = messages.find("}:{", int_tmp) + 3;
		p2 = messages.substr(int_tmp, messages.find("}:{", int_tmp) - int_tmp);
		int_tmp = messages.find("}:{", int_tmp) + 3;
		p3 = messages.substr(int_tmp, messages.find("}") - int_tmp);

		chat.push_front(new ChatMessage(p1, p2, p3));
	}

	session->updateChatHistory(chat);
}

std::string GM_control::addToChatHistory(std::string newMessage)
{
	// :{message 1}:{user}:{id_1}
	std::string p1, p2, p3;
	int i = newMessage.find("}:{");
	p1 = newMessage.substr(2, i - 2);
	i += 3;
	p2 = newMessage.substr(i, newMessage.find("}:{", i) - i);
	i = newMessage.find("}:{", i) + 3;
	p3 = newMessage.substr(i, newMessage.find("}") - i);
	session->addToChatHistory(new ChatMessage(p1, p2, p3));
	
	return p1;
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

	boost::thread* t_0 = findFragmentById("0")->start();
	boost::thread* t_1 = findFragmentById("1")->start();
	boost::thread* t_2 = findFragmentById("2")->start();

}
