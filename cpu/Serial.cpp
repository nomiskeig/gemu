#include "Serial.h"
#include <cstdio>
extern int serialFD;
void Serial::setSB(Reg8Val val) { this->sb = val; };
void Serial::setSC(Reg8Val val) { this->sc = val;
    if (this->sc | 0x8) {
        dprintf(serialFD, "0x%hhx\n", this->sb);

    }
};
