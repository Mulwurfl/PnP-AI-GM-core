#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H
#include <string>
class ChatMessage
{
public:
	explicit ChatMessage(std::string, std::string, std::string);
	std::string getMessage();
	std::string getUser();
	std::string getID();
private:
	std::string message;
	std::string user;
	std::string id;
};

#endif