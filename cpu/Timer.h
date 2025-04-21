#pragma once

#include <cstdint>
using Reg8Val = int8_t;
class Timer {
private:
    Reg8Val tac;
public:
    void setTAC(Reg8Val val);
};

