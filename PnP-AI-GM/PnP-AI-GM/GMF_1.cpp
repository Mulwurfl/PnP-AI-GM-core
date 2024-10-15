#include "GMF_1.h"

GMF_1::GMF_1(std::string newId)
{
	id = newId;
	std::cout << "GMF_2 created\n";
}

void GMF_1::process()
{
	std::string* temp;
	while (1) {
		while (!in_buffer.empty()) {
			//std::cout << "process passing GMF_1\n";
			in_buffer.pop(temp);
			out_buffer->push(temp);
		}
	}
}
