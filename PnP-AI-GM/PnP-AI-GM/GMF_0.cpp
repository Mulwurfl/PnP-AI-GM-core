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
		while (!in_buffer.empty())
		{
			in_buffer.pop(temp);
			if (temp->find("#!#!#!") != std::string::npos)
			{
				*temp = process_commmand(*temp);
			}
			else 
			{
				*temp = py_process(*temp, 0);
			}
			out_buffer->push(temp);
		}
	}
}

std::string GMF_0::py_process(std::string message, int mode)
{
	std::string return_str = "";
	std::string str_tmp;
	int int_tmp;
	switch (mode)
	{
	case 0:
		func = PyObject_GetAttrString(load_module, (char*)"test");
		// Python calls break when using umlauts. Prolly need to cast message to UTF-8 first, but I'm not sure. May be a pure Win10 Problem.
		args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)message.c_str()));
		callfunc = PyObject_CallObject(func, args);
		return_str = _PyUnicode_AsString(callfunc);
	case 1:
		// new thread
		func = PyObject_GetAttrString(load_module, (char*)"create_thread");
		callfunc = PyObject_CallObject(func, NULL);
		return_str = _PyUnicode_AsString(callfunc);
		// cut out thread id
		if (return_str.find("thread_") != std::string::npos) 
		{
			int_tmp = return_str.find("thread_");
			return_str = return_str.substr(int_tmp, return_str.find("\"") - int_tmp);
		}
		else
		{
			return_str = "error: failed to create chat_thread_id";
		}	
	case 2:
		// get all msgs
		func = PyObject_GetAttrString(load_module, (char*)"get_msg_list");
		// Python calls break when using umlauts. Prolly need to cast message to UTF-8 first, but I'm not sure. May be a pure Win10 Problem.
		int_tmp = 100; //min 0, max 100
		args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)std::to_string(int_tmp).c_str()));
		callfunc = PyObject_CallObject(func, args);
		str_tmp = _PyUnicode_AsString(callfunc);
		for (int i= int_tmp; i>0; i--) // messages get delivered in reverse order, so we account for that
		{
			// Combine all messages into one string in the following format (example for 7 chat messages and tmp_int 100, which is the max value):
			// "#!#!#! message_list total(7):  #!#!#94:{message 1}:{user}:{id_1} #!#!#95:{message 2}:{assistant}:{id_2} ..... #!#!#100:{message 7}:{user}:{id_7}"
			if (i = int_tmp)
			{
				int_tmp = 0;
			}
			if (str_tmp.find("\"id\": \"") != std::string::npos) // make sure there are still unprocessed messages
			{
				int_tmp = str_tmp.find("\"id\": \"", int_tmp) + 7;
				return_str = ":{" + str_tmp.substr(int_tmp, str_tmp.find("\",", int_tmp) - int_tmp) + "}" + return_str;
				int_tmp = str_tmp.find("\"role\": \"", int_tmp) + 9;
				return_str = ":{" + str_tmp.substr(int_tmp, str_tmp.find("\",", int_tmp) - int_tmp) + "}" + return_str;
				int_tmp = str_tmp.find("\"text\": {", int_tmp);
				int_tmp = str_tmp.find("\"value\"", int_tmp) + 10;
				return_str = " #!#!#" + std::to_string(i) + ":{" + str_tmp.substr(int_tmp, str_tmp.find("\",\n", int_tmp) - int_tmp) + "}" + return_str;
			}
			else // if no messages are left, construct a "header" for return_str and leave loop
			{
				if (int_tmp == 0)
				{
					return_str = "#!#!#! message_list error: no messages found";
				}
				else
				{
					return_str = "#!#!#! message_list total(" + std::to_string(int_tmp - i) + "):" + return_str;
				}
				break;
			}
		}
	}

	return return_str;
}

std::string GMF_0::process_commmand(std::string cmd_str)
{
	if (cmd_str == "#!#!#! get_thread")
	{
		if (session_id != "")
		{
			return "#!#!#! thread_id " + session_id;
		}
		else 
		{
			return "#!#!#! thread_id " + py_process("",1);
		}
	}
	else if (cmd_str.find("#!#!#! get_msg_list") != std::string::npos) // does not return invis messages
	{
		std::string all_msgs = py_process("", 2);
		// sub invis_msgs from all msgs and return
	}

	return "#!#!#! invalid command";
}
