
#include <cstdint>
using Reg8Val = int8_t;
class Graphics {

private:
    Reg8Val ly;
    Reg8Val lyc;
    Reg8Val stat;
    Reg8Val scx;
    Reg8Val scy;
    Reg8Val wy;
    Reg8Val wx;
    Reg8Val lcdc;
    Reg8Val bgp;

public:
    void setSCX(Reg8Val val);
    void setSCY(Reg8Val val);
    void setStat(Reg8Val val);
    void setWY(Reg8Val val);
    void setWX(Reg8Val val);
    void setLCDC(Reg8Val val);
    void setBGP(Reg8Val val);

};
