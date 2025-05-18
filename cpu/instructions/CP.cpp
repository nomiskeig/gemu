#include "../Instruction.h"
static void _setFlagZ(CPU *cpu, uint8_t res) {
    if (res == 0) {
        cpu->set_flag(kFlagZ);
    } else {
        cpu->clear_flag(kFlagZ);
    }
}
static void _setFlagC(CPU *cpu, uint8_t val) {
    if (val > cpu->get_reg_8(kRegA)) {
        cpu->set_flag(kFlagC);
    } else {
        cpu->clear_flag(kFlagC);
    }
}
static void _setFlagH(CPU *cpu, uint8_t val) {
    if (get_bit(val, 4) > get_bit(cpu->get_reg_8(kRegA), 4)) {
        cpu->set_flag(kFlagH);
    } else {
        cpu->clear_flag(kFlagH);
    }
}
int CP::execute(CPU *cpu) {
    int cycles = 0;
    cpu->set_flag(kFlagN);
    switch (this->type) {

    case kN8: {

        cycles = 2;
        this->cycles = 2;
        Reg8Val regA = cpu->get_reg_8(kRegA);
        uint8_t res = regA - this->n8;
        _setFlagZ(cpu, res);
        cpu->increasePC(2);
        break;
    }
    default:
        exit_with_error("Unknown case in CP execute");
    }
    return cycles;
}

CP::CP(N8 n8) {
    this->type = kN8;
    this->n8 = n8;
    this->text_string = "CP";
}
