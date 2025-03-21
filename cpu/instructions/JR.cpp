
#include "../Instruction.h"

void JR::execute(CPU *cpu) {
    if (cpu->get_flag(this->flag) == kSet) {
        cpu->increasePC(2 + this->offset);
    } else {
        cpu->increasePC(2);
    }


}

JR::JR(Flag flag, E8 offset) {
    this->flag = flag;
    this->offset = offset;
    this->text_string = "JR";
    // TODO: this needs two differnet timings based on whether the jump is taken or not

}
