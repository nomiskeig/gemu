#include "../Instruction.h"

int STOP::execute(CPU *cpu) {
    cpu->increasePC(2);
    return 1;

}
STOP::STOP(N8 val) {
    this->val = val;
    this->text_string = "STOP";
}
