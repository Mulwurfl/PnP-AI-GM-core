#include "GM_control.h"
#include <iostream>
#include <array>

std::string system_msg(std::string msg, int step, std::string trigger, std::string section) {
	switch (step) {
	case 0:
		msg = "This is a setup message. The user is not here yet. Use file search to retrieve the whole contents of 'Section 0 - Intro'. The user will not be aware of this interaction.\n$$: " + msg;
		break;
	case 1:
		msg = "Begin section. " + trigger + "\n$$: " + msg;
		break;
	case 2:
		msg = "Continue section. " + trigger + "\n$$: " + msg;
		break;
	case 3:
		msg = "Retrieve " + section + " using file search. The user will not see this interaction.\n$$: " + msg;
		break;
	}

	return msg;
}

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
	
	// Milestone stuff auf die Schnelle
	int milestone = 0; // 0 - 5
	int step = 0; // 0 setup, 1 begin, 2 continue, 3 retrieve
	std::array<std::string, 6> milestone_trigger = {
		"Trigger for next section is going or looking into the cellar.",
		"Trigger for next section is going or looking through the hole in the wall.",
		"Trigger for next section is turning or peaking the corner.",
		"Trigger for next section is going or looking through the door at the end of the corridor.",
		"Trigger for next section is saying the password to open the secret door.",
		"Trigger for next section is arriving home and going to bed."
	};
	std::array<std::string, 6> section_name = {
		"'Section 0 - Intro'",
		"'Section 1 - Beer Cellar'",
		"'Section 2 - Corridor'",
		"'Section 3 - Mosaic Puzzle'",
		"'Section 4 - Storage Room'",
		"'Section 5 - Secret Chamber'"
	};



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
				std::cout << "-----------------------------------------------------------------------\n" << "Your input:\n";
				std::getline(std::cin, strin);
				//std::cout << "strin value is: " << strin << "\n";
				//std::cout << "pstrin value is: " << *pstrin << "\n";
				if (strin.find("#!#!#!") != std::string::npos) {
					if (strin.find("#!#!#! force") != std::string::npos) {
						if (strin.find("retrsc") != std::string::npos) { //#!#!#! force retrsc [section]
							milestone = std::stoi(strin.substr(20));
							step = 2;
							strin = system_msg("...", 3, milestone_trigger[milestone], section_name[milestone]);
						}
						else if (strin.find("contsc") != std::string::npos) {//#!#!#! force contsc [section] [text]
							milestone = std::stoi(strin.substr(20, 21));
							step = 2;
							strin = system_msg(strin.substr(22), 2, milestone_trigger[milestone], section_name[milestone]);
						}
					}
					else if (strin.find("#!#!#! begin") != std::string::npos) {
						milestone = 0;
						strin = system_msg("...", 0, milestone_trigger[milestone], section_name[milestone]);
						step = 1;
					}
				}
				else {
					strin = system_msg(strin, step, milestone_trigger[milestone], section_name[milestone]);
					if (step < 2) step++;
				}
				control.getInBuffer()->push(pstrin);
				processing = 1;
				input = 0;
			}
			else
			{
				t2 = boost::chrono::high_resolution_clock::now();
				control.getOutBuffer()->pop(pstrout);
				std::cout << "-----------------------------------------------------------------------\n";

				// sort output commands
				if (pstrout->find("#!#!#!") != std::string::npos)
				{
					//std::cout << "command response received: " << *pstrout << "\n";

					if (pstrout->find("#!#!#! thread_id") != std::string::npos)
					{
						//std::cout << "command response thread_id\n";
						if (pstrout->find("#!#!#! thread_id error") != std::string::npos)
						{
							//std::cout << "command response thread_id error\n";
							*pstrout = pstrout->substr(7);
							std::cout << *pstrout << "\n";
							input = 1;
						}
						else if (pstrout->find("#!#!#! thread_id id") != std::string::npos)
						{
							//std::cout << "command response thread_id id\n";
							control.setThread_ID(pstrout->substr(21));
							std::cout << "Now using chat thread: " << control.getThread_ID() << "\n";
							input = 1;
						}
					}
					else if (pstrout->find("#!#!#! process") != std::string::npos)
					{
						//std::cout << "process response: " << *pstrout << "\n";
						if (pstrout->find("#!#!#! process error") != std::string::npos)
						{
							*pstrout = pstrout->substr(7);
							std::cout << *pstrout << "\n";
							input = 1;
						}
						else if (pstrout->find("#!#!#! process answer:") != std::string::npos)
						{
							*pstrout = control.addToChatHistory(pstrout->substr(23));
							std::cout << *pstrout << "\n";
							total_t = (boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1));
							std::cout << "\nExecution time: " << total_t << "\n";
							input = 1;
						}
						else if (pstrout->find("#!#!#! process answer x:") != std::string::npos)
						{
							milestone++;
							//step = 3;
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
							input = 1;
						}
						else if (pstrout->find("#!#!#! message_list total") != std::string::npos)
						{
							control.updateChatHistory(pstrout->substr(26));
							input = 1;
						}
					}
				}
				if (input == 0)
				{
					std::cout << "invalid output: " + *pstrout + "\n";
					input = 1;
				}
				pstrout = &empty_string;
			}
		}
	}
}


