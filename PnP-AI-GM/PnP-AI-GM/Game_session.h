#ifndef Game_SESSION_H
#define Game_SESSION_H
#include <string>
#include <vector>

// This class is pretty much a data container and exists for better readability

class Game_session
{
public:
	explicit Game_session(std::string);
	std::string getChatThreadID();
	void setChatThreadID(std::string);
	std::vector<std::string> getHiddenMessagesList();
	void addHiddenMessages(std::vector<std::string>);

private:
	std::string chat_thread_id;
	std::vector<std::string> hidden_messages;
};

#endif