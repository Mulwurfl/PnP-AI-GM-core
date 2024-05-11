#include "GMF_2.h"

GMF_2::GMF_2(std::string newId)
{
	id = newId;
}

void GMF_2::process()
{
	std::string* temp;
	while (1) {
		while (!in_buffer.empty()) {
			in_buffer.pop(temp);
			out_buffer->push(temp);
		}
	}
}
