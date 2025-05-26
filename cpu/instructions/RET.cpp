

#include "../../config.h"
#include "../Instruction.h"

int RET::execute(CPU *cpu) {
    int res = 0;
    switch (this->action) {

    case kRETCond: {
        cpu->increasePC(1);
        res = 2;
        if ((cpu->get_flag(this->flag) == kSet &&

             this->type == kRETCondNormal) ||
            (cpu->get_flag(this->flag) == kCleared &&
             this->type == kRETCondNot)) {
            res = 5;
            ProgramCounter pc =
                cpu->read_memory(cpu->get_reg_16(kRegSP)) & 0xFF;
            cpu->modifySP(1);
            pc |= cpu->read_memory(cpu->get_reg_16(kRegSP)) << 0x08;
            cpu->modifySP(1);
            cpu->setPC(pc);
            GEMU_PRINT_CALL_GRAPH("RET cc to 0x%x", pc);
        }
        break;
    }
    case kRetUncond: {
        res = 4;
        ProgramCounter pc = cpu->read_memory(cpu->get_reg_16(kRegSP)) & 0xFF;
        cpu->modifySP(1);
        pc |= cpu->read_memory(cpu->get_reg_16(kRegSP)) << 0x08;
        cpu->modifySP(1);
        cpu->setPC(pc);
        GEMU_PRINT_CALL_GRAPH("RET to 0x%x", pc);
        break;
    }
    default:
        exit_with_error("Ret action not implemented");
    }
    return res;
}

RET::RET(Flag flag, RETCondType type) {
    this->flag = flag;
    this->text_string = "RET cc";
    this->action = kRETCond;
    this->type = type;
}
RET::RET() {
    this->text_string = "RET";
    this->action = kRetUncond;
}
