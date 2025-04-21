#include "Interrupts.h"
void Interrupts::setIE(Reg8Val ie) {
    this->ie = ie;
}
void Interrupts::setIF(Reg8Val  i_f) {
    this->i_f = i_f;
}

Reg8Val Interrupts::getIE() {
    return this->ie;
}
