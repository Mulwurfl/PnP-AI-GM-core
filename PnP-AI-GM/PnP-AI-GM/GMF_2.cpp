#include "GMF_2.h"

GMF_2::GMF_2(std::string newId)
{
	id = newId;
	std::cout << "GMF_2 created\n";
}

void GMF_2::process()
{
	std::string* temp;
	while (1) {
		while (!in_buffer.empty()) {
			//std::cout << "process passing GMF_2\n";
			in_buffer.pop(temp);
			out_buffer->push(temp);
		}
	}
}
