#include "ChatMessage.h"

ChatMessage::ChatMessage(std::string newMessage, std::string newUser, std::string newID)
{
	message = newMessage;
	user = newUser;
	id = newID;
}

std::string ChatMessage::getMessage()
{
	return message;
}

std::string ChatMessage::getUser()
{
	return user;
}

std::string ChatMessage::getID()
{
	return id;
}
