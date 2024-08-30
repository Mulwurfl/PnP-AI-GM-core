#ifndef GAME_SESSION_H
#define GAME_SESSION_H
#include <string>
#include <vector>
#include <forward_list>
#include "ChatMessage.h"

// This class is pretty much a data container and exists for better readability

class Game_session
{
public:
	explicit Game_session(std::string);
	std::string getChatThreadID();
	void setChatThreadID(std::string);
	std::vector<std::string> getHiddenMessagesList();
	void addHiddenMessages(std::vector<std::string>);
	std::forward_list<ChatMessage*> getChatHistory();
	void updateChatHistory(std::forward_list<ChatMessage*>);
	void addToChatHistory(ChatMessage*);
private:
	std::string chat_thread_id;
	std::vector<std::string> hidden_messages;
	std::forward_list<ChatMessage*> chat_history;
};

#endif