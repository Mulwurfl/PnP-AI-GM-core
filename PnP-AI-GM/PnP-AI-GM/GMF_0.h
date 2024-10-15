#ifndef GMF_0_H
#define GMF_0_H
#include "GMF.h"
#include <Python.h>
#include <string>
#include <vector>
class GMF_0 :
    public GMF
{
public:
    explicit GMF_0(std::string);
    ~GMF_0() override = default;
    
private:
    void process() override;
    PyObject* name;
    PyObject* load_module;
    PyObject* func;
    PyObject* callfunc;
    PyObject* args;
    std::string py_process(std::string, int, int = 0);
    std::string process_commmand(std::string);
    std::string session_id;
    std::vector<std::string> hidden_messages;
    bool new_milestone = false;
};
#endif
