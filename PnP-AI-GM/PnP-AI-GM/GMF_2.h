#ifndef GMF_2_H
#define GMF_2_H
#include "GMF.h"
#include <string>
class GMF_2 :
    public GMF
{
public:
    explicit GMF_2(std::string);
    ~GMF_2() override = default;
private:
    void process() override;

};
#endif