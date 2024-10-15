#include "GMF_0.h"
#include <Python.h>
#include <thread>
#include <exception>
#include <json.hpp>

// for convenience
using json = nlohmann::json;

GMF_0::GMF_0(std::string newId)
{
	id = newId;
	Py_Initialize();
	name = PyUnicode_FromString((char*)"assistant_caller");
	load_module = PyImport_Import(name);
	std::cout << "GMF_0 created\n";

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
			//std::cout << "process passing GMF_0\n";
			in_buffer.pop(temp);
			//std::cout << "message reads: " << *temp << "\n";
			if (temp->find("#!#!#!") != std::string::npos)
			{
				//std::cout << "command detected\n";
				*temp = process_commmand(*temp);
			}
			else 
			{
				//std::cout << "no command detected\n";
				*temp = py_process(*temp, 0, 1);
			}
			out_buffer->push(temp);
		}
	}
}

std::string GMF_0::py_process(std::string message, int mode, int additional_arg)
{
	new_milestone = false;
	std::string return_str = "";
	std::string str_tmp = "";
	int int_tmp = additional_arg; // range between 1 and 100; pass 0 when unused paramm
	boost::chrono::high_resolution_clock::time_point t1;
	boost::chrono::high_resolution_clock::time_point t2;
	boost::chrono::microseconds total_t;
	switch (mode)
	{
	case -1:
		func = PyObject_GetAttrString(load_module, (char*)"test");
		// Python calls break when using umlauts. Prolly need to cast message to UTF-8 first, but I'm not sure. May be a pure Win10 Problem.
		args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)message.c_str()));
		callfunc = PyObject_CallObject(func, args);
		try
		{
			if (!callfunc)
			{
				if (PyErr_Occurred()) {
					PyErr_Print();  // Print the Python error to stderr
				}
				throw std::runtime_error("Python function call failed.");
			}

			return_str = _PyUnicode_AsString(callfunc);
			if (return_str == "") throw std::runtime_error("Failed to convert PyObject to string.");
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		break;
	case 0:
		//std::cout << "session id is: " << session_id << "\n";
		func = PyObject_GetAttrString(load_module, (char*)"send_msg");
		// Python calls break when using umlauts. Prolly need to cast message to UTF-8 first, but I'm not sure. May be a pure Win10 Problem.
		args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)message.c_str()));
		callfunc = PyObject_CallObject(func, args);
		
		// create run 
		func = PyObject_GetAttrString(load_module, (char*)"run");
		args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)str_tmp.c_str()));
		callfunc = PyObject_CallObject(func, args);
		// extract run id
		try
		{
			if (!callfunc)
			{
				if (PyErr_Occurred()) {
					PyErr_Print();  // Print the Python error to stderr
				}
				throw std::runtime_error("Python function call failed.");
			}

			str_tmp = _PyUnicode_AsString(callfunc);
			if (str_tmp == "") throw std::runtime_error("Failed to convert PyObject to string.");
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		//std::cout << "the new runs id is: " << str_tmp << "\n";
		if (str_tmp.find("run_") == std::string::npos)
		{
			return "#!#!#! process error: run not initiated correctly";
		}

		// fish for run update
		while (true)
		{
			func = PyObject_GetAttrString(load_module, (char*)"get_run");
			args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)str_tmp.c_str()));
			callfunc = PyObject_CallObject(func, args);
			return_str = _PyUnicode_AsString(callfunc);
			//std::cout << "i";
			if (return_str == "")
			{
				return "#!#!#! process error: could not retrieve run object";
			}
			
			// assess run status
			if (return_str == "completed")
			{
				break;
			}
			else if (return_str == "expired")
			{
				return "#!#!#! process error: run expired";
			}
			else if (return_str == "failed")
			{
				return "#!#!#! process error: run failed";
			}
			else if (return_str == "incomplete")
			{
				return "#!#!#! process error: run incomplete due to token limits";
			}
		}
		
		// retrieve response message
		return_str = py_process("", 2, 2); // temporarily retrieves 2 messages, for self-retrieval fix
		//std::cout << "message fetched: " << return_str << "\n";
		if (return_str.find("#!#!#! message_list t") != std::string::npos)
		{
			int_tmp = return_str.find("#:{", 50) + 2;
			if (new_milestone) {
				return_str = "#!#!#! process answer x: " + return_str.substr(int_tmp);
			}
			else {
				return_str = "#!#!#! process answer: " + return_str.substr(int_tmp);
			}
		}
		else
		{
			return_str = "#!#!#! process error, received the following unexpected output: " + return_str;
		}
		//std::cout << "sending back: " + return_str << "\n";
		break;
	case 1:
		// new thread
		//std::cout << "py_process case 1 check\n";
		func = PyObject_GetAttrString(load_module, (char*)"create_thread");
		callfunc = PyObject_CallObject(func, NULL);
		try
		{
			if (!callfunc)
			{
				if (PyErr_Occurred()) {
					PyErr_Print();  // Print the Python error to stderr
				}
				throw std::runtime_error("Python function call failed.");
			}

			return_str = _PyUnicode_AsString(callfunc);
			if (return_str == "") throw std::runtime_error("Failed to convert PyObject to string.");
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		//std::cout << "python returns: " << return_str << "\n";
		// cut out thread id
		if (return_str.find("thread_") != std::string::npos) 
		{
			//std::cout << "thread created check\n";
			session_id = return_str;
			return_str = "id: " + return_str;
		}
		else
		{
			//std::cout << "thread not created check\n";
			return_str = "error: failed to create chat_thread_id";
		}
		break;
	case 2:
		// get all msgs
		//std::cout << "fetching messages with arg = " << std::to_string(int_tmp) << "\n";
		func = PyObject_GetAttrString(load_module, (char*)"get_msg_list");
		// Python calls break when using umlauts. Prolly need to cast message to UTF-8 first, but I'm not sure. May be a pure Win10 Problem.
		args = PyTuple_Pack(2, PyUnicode_FromString((char*)session_id.c_str()), PyUnicode_FromString((char*)std::to_string(int_tmp).c_str()));
		callfunc = PyObject_CallObject(func, args);
		try
		{
			if (!callfunc)
			{
				if (PyErr_Occurred()) {
					PyErr_Print();  // Print the Python error to stderr
				}
				throw std::runtime_error("Python function call failed.");
			}
			if (!PyUnicode_Check(callfunc)) {
				throw std::runtime_error("Expected a Python list, got something else.");
			}

			str_tmp = _PyUnicode_AsString(callfunc);
			auto messages = json::parse(str_tmp);
			int_tmp = 0;

			// Combine all messages into one string in the following format (example for 7 chat messages and tmp_int 100, which is the max value):
			// "#!#!#! message_list total(7):  #:{id_1}:{message 1}:{user} #:{id_2}:{message 2}:{assistant} ..... #:{id_7}:{message 7}:{user}"
			for (auto& msg : messages)
			{
				if (((std::string)msg["value"]).find("Next section") != std::string::npos) {
					new_milestone = true;
				}
				int f = ((std::string)msg["value"]).find("$$:") + 3;
				return_str = " #:{" + (std::string)msg["id"] + "}:{" + ((std::string)msg["value"]).substr(f) + "}:{" + (std::string)msg["role"] + "}" + return_str;
				int_tmp++;
			}
			return_str = "#!#!#! message_list total(" + std::to_string(int_tmp) + "):" + return_str;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}

		//std::cout << "py output for messages: " << str_tmp << "\n";
		if (return_str == "")
		{
			return_str = "error: no messages found";
		}
		break;
	case 3:
		// set thread
		func = PyObject_GetAttrString(load_module, (char*)"retrieve_thread");
		args = PyTuple_Pack(1, PyUnicode_FromString((char*)message.c_str()));
		callfunc = PyObject_CallObject(func, args);
		try
		{
			if (!callfunc)
			{
				if (PyErr_Occurred()) {
					PyErr_Print();  // Print the Python error to stderr
				}
				throw std::runtime_error("Python function call failed.");
			}

			str_tmp = _PyUnicode_AsString(callfunc);
			if (str_tmp == "") throw std::runtime_error("Failed to convert PyObject to string.");
		}
		catch (const std::exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		// check return value
		//std::cout << "python return val: " << str_tmp << "\n";
		if (str_tmp.find("thread_") != std::string::npos)
		{
			session_id = str_tmp;
			return_str = "id: " + str_tmp;
		}
		else
		{
			return_str = "error: failed to load thread " + str_tmp;
		}
		break;
	}

	return return_str;
}

std::string GMF_0::process_commmand(std::string cmd_str)
{
	if (cmd_str.find("#!#!#! get_thread") != std::string::npos)
	{
		//std::cout << "process_command get_thread check\n";
		if (session_id != "")
		{
			//std::cout << "id exists check\n";
			return "#!#!#! thread_id id: " + session_id;
		}
		else
		{
			//std::cout << "id empty check\n";
			return "#!#!#! thread_id " + py_process("", 1);
		}	
	}
	else if (cmd_str.find("#!#!#! set_thread") != std::string::npos)
	{
		cmd_str = cmd_str.substr(18);
		//std::cout << "process_command set_thread " << cmd_str << "\n";
		return "#!#!#! thread_id " + py_process(cmd_str, 3);
	}
	else if (cmd_str.find("#!#!#! get_msg_list") != std::string::npos) // does not return invis messages
	{
		int arg = std::stoi(cmd_str.substr(20));
		return py_process("", 2, arg);
	}

	return "#!#!#! invalid command";
}
