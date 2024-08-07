#include "GMF_0.h"
#include <Python.h>
#include <iostream>
#include <thread>

GMF_0::GMF_0(std::string newId)
{
	id = newId;
	Py_Initialize();
	name = PyUnicode_FromString((char*)"assistant_caller");
	load_module = PyImport_Import(name);


	if (load_module == nullptr)
	{
		PyErr_Print();
		std::exit(1);
	}
}

void GMF_0::process()
{
	std::string* temp;
	while (1) {
		while (!in_buffer.empty()) {
			in_buffer.pop(temp);
			*temp = py_process(*temp);
			out_buffer->push(temp);
		}
	}
}

std::string GMF_0::py_process(std::string message)
{
	//std::cout << "name" << " - " << name;
	func = PyObject_GetAttrString(load_module,(char*)"send_msg");
	args = PyTuple_Pack(1, PyUnicode_FromString((char*)message.c_str()));
	callfunc = PyObject_CallObject(func, args);

	return _PyUnicode_AsString(callfunc);
}