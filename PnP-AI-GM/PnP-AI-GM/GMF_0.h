#ifndef GMF_0_H
#define GMF_0_H
#include "GMF.h"
#include <string>
#include <Python.h>
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
    std::string py_process(std::string);
};
#endif
