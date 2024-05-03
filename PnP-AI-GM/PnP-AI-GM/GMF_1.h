#ifndef GMF_1_H
#define GMF_1_H
#include <string>
#include "GMF.h"
class GMF_1 :
    public GMF
{
public:
    explicit GMF_1(std::string);
private:
    void process() override;

};
#endif