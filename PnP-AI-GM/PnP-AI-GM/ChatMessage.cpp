#include "ChatMessage.h"

ChatMessage::ChatMessage(std::string newID, std::string newMessage, std::string newUser)
{
	id = newID;
	message = newMessage;
	user = newUser;
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
