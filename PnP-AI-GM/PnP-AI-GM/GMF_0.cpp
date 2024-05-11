#include "GMF_0.h"
#include <thread>

GMF_0::GMF_0(std::string newId)
{
	id = newId;

}

void GMF_0::process()
{
	std::string* temp;
	while (1) {
		while (!in_buffer.empty()) {
			in_buffer.pop(temp);
			out_buffer->push(temp);
		}
	}
}