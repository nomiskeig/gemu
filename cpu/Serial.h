#pragma once

#include <cstdint>
using Reg8Val = int8_t;
class Serial {
private:
    Reg8Val sb;
    Reg8Val sc;
public:
    void setSB(Reg8Val val);
    void setSC(Reg8Val val);
};
