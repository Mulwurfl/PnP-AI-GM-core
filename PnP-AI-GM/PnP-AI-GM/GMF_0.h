#ifndef GMF_0_H
#define GMF_0_H
#include "GMF.h"
#include <string>
class GMF_0 :
    public GMF
{
public:
    explicit GMF_0(std::string);
    ~GMF_0() override = default;
private:
    void process() override;

};
#endif
