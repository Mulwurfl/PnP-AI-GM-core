#include "GM_control.h"
#include <iostream>

int main()
{
	GM_control control;
	control.start();

	std::string strin;
	std::string* pstrin = &strin;
	std::string empty_string = "";
	std::string* pstrout = &empty_string;
	bool processing = false; // Currently waiting for request to be processed? = 1
	bool input = true; // 1 = input mode; 0 = output mode
	boost::chrono::high_resolution_clock::time_point t1;
	boost::chrono::high_resolution_clock::time_point t2;
	boost::chrono::microseconds total_t;
	std::string thread_id;
	std::cout << "Please enter thread ID. Leave empty for new game:\n";
	//std::cin >> thread_id;
	std::cout << "\n";
	bool thread_initiated = false;
	
	/*
	while (!thread_initiated) {
		if (thread_id == "") {
			// control.new_thread();
		}
		else {
			// if (control.thread_exists()) {
			//	control.load_thread();
			//	thread_initiated = true;
			// }
			// else {
			//	std::cout << "Invalid thread id. Please try again or leave field empty to start a new adventure:\n";
			//	std::cin >> thread_id;
			//	std::cout << "\n";
		}
	}*/
	
	


	while (true) {
		if (!control.getOutBuffer()->empty()) processing = 0; // Checks whether system has finished processing inputs

		if (!processing) { // If processing == 0
			if (input) { // If input == 1
				t1 = boost::chrono::high_resolution_clock::now();
				std::cout << "Ready for input!\n";
				std::getline(std::cin, strin);
				std::cout << "strin value is: " << strin << "\n";
				std::cout << "pstrin value is: " << *pstrin << "\n";
				control.getInBuffer()->push(pstrin);
				processing = 1;
				input = 0;
			}
			else {
				t2 = boost::chrono::high_resolution_clock::now();
				control.getOutBuffer()->pop(pstrout);

				// sort output commands
				if (pstrout->find("#!#!#!") != std::string::npos)
				{
					std::cout << "command response received: " << *pstrout << "\n";

					if (pstrout->find("#!#!#! thread_id") != std::string::npos)
					{
						std::cout << "command response thread_id\n";
						if (pstrout->find("#!#!#! thread_id error") != std::string::npos)
						{
							std::cout << "command response thread_id error\n";
							*pstrout = pstrout->substr(7);
							std::cout << *pstrout << "\n";
						}
						else if (pstrout->find("#!#!#! thread_id id") != std::string::npos)
						{
							std::cout << "command response thread_id id\n";
							control.setThread_ID(pstrout->substr(21));
							std::cout << "Now using chat thread: " << control.getThread_ID() << "\n";
						}
					}
					else if (pstrout->find("#!#!#! process") != std::string::npos)
					{
						if (pstrout->find("#!#!#! process error") != std::string::npos)
						{
							*pstrout = pstrout->substr(7);
							std::cout << *pstrout << "\n";
						}
						else if (pstrout->find("#!#!#! process answer") != std::string::npos)
						{
							*pstrout = control.addToChatHistory(pstrout->substr(23));
							std::cout << *pstrout << "\n";
							total_t = (boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1));
							std::cout << "\nExecution time: " << total_t << "\n";
							input = 1;
						}
					}
					else if (pstrout->find("#!#!#! message_list") != std::string::npos)
					{
						if (pstrout->find("#!#!#! message_list error") != std::string::npos)
						{
							*pstrout = pstrout->substr(7);
							std::cout << *pstrout << "\n";
						}
						else if (pstrout->find("#!#!#! message_list total") != std::string::npos)
						{
							control.updateChatHistory(pstrout->substr(26));
						}
					}
				}
			}
		}
		pstrout = &empty_string;
	}
}


