#pragma once

#include <cstdint>
using Reg8Val = int8_t;
class Audio {
private:
    Reg8Val nr52;
    Reg8Val nr51;
    Reg8Val nr50;
    Reg8Val nr41;
public:
    void setNR52(Reg8Val val);
    void setNR51(Reg8Val val);
    void setNR50(Reg8Val val);
    void setNR41(Reg8Val val);
};

