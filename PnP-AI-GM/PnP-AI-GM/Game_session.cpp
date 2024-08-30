#include "Game_session.h"

Game_session::Game_session(std::string thread_id)
{
	chat_thread_id = "";
}

std::string Game_session::getChatThreadID()
{
	return chat_thread_id;
}

void Game_session::setChatThreadID(std::string newID)
{
	chat_thread_id = newID;
}

std::vector<std::string> Game_session::getHiddenMessagesList()
{
	return hidden_messages;
}

void Game_session::addHiddenMessages(std::vector<std::string> newMessages)
{
	for (auto message : newMessages) {
		hidden_messages.push_back(message);
	}
}

std::forward_list<ChatMessage*> Game_session::getChatHistory()
{
	return chat_history;
}

void Game_session::updateChatHistory(std::forward_list<ChatMessage*> newHistory)
{
	chat_history = newHistory;
}

void Game_session::addToChatHistory(ChatMessage* message)
{
	chat_history.push_front(message);
}
