#include "GM_control.h"


GM_control::GM_control()
{
	fragments.push_back(new GMF_0("0"));
	fragments.push_back(new GMF_1("1"));
	fragments.push_back(new GMF_0("2"));
}

GMF* GM_control::findFragmentById(std::string id)
{
	for (GMF* i : GM_control::fragments) {
		if (i->getId() == id) return i;
	}
	return NULL;
}