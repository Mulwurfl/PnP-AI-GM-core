#include "GM_control.h"
#include <iostream>

int main()
{
	GM_control control;
	control.start();

	std::string strin;
	std::string* pstrin = &strin;
	std::string* pstrout;
	bool processing = false; // Currently waiting for request to be processed? = 1
	bool input = true; // 1 = input mode; 0 = output mode
	boost::chrono::high_resolution_clock::time_point t1;
	boost::chrono::high_resolution_clock::time_point t2;
	boost::chrono::microseconds total_t;
	control.getInBuffer()->push(pstrin);

	while (true) {
		if (!control.getOutBuffer()->empty()) processing = 0; // Checks whether system has finished processing inputs

		if (!processing) { // If processing == 0
			if (input) { // If input == 1
				t1 = boost::chrono::high_resolution_clock::now();
				std::cout << "Ready for input!\n";
				std::cin >> strin;
				processing = 1;
				input = 0;
			}
			else {
				t2 = boost::chrono::high_resolution_clock::now();
				control.getOutBuffer()->pop(pstrout);
				std::cout << *pstrout;

				total_t = (boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1));
				std::cout << "\nExecution time: " << total_t << "\n";
				input = 1;
			}
			
		}
	}
}
