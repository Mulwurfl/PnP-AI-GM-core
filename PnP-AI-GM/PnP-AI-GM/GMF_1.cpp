#include "GMF_1.h"

GMF_1::GMF_1(std::string newId)
{
	id = newId;
}

void GMF_1::process()
{
	std::string* temp;
	while (1) {
		while (!in_buffer.empty()) {
			in_buffer.pop(temp);
			out_buffer->push(temp);
		}
	}
}
