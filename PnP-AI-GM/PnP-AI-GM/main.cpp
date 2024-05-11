#include "GM_control.h"
#include <iostream>

int main()
{
	GM_control control;
	control.start();

	std::string strin;
	std::string* pstrin = &strin;
	std::string* pstrout;
	std::cin >> strin;
	boost::chrono::high_resolution_clock::time_point t1 = boost::chrono::high_resolution_clock::now();
	control.getInBuffer()->push(pstrin);

	while (true) {
		while (!control.getOutBuffer()->empty()) {
			boost::chrono::high_resolution_clock::time_point t2 = boost::chrono::high_resolution_clock::now();
			control.getOutBuffer()->pop(pstrout);
			std::cout << *pstrout;

			boost::chrono::microseconds total_t;
			total_t = (boost::chrono::duration_cast<boost::chrono::milliseconds>(t2 - t1));
			std::cout << "\nExecution time: " << total_t << "\n";
		}
	}
}
