
#include "../Instruction.h"
#include <ios>
#include <sstream>

int JR::execute(CPU *cpu) {
    int res = 0;
    switch (this->action) {
    case kJRCond: {

        if (this->type == kJRCondNormal) {

            if (cpu->get_flag(this->flag) == kSet) {
                res = 3;
                cpu->increasePC(2 + this->offset);
            } else {
                res = 2;
                cpu->increasePC(2);
            }
        }
        if (this->type == kJRCondNot) {
            if (cpu->get_flag(this->flag) == kCleared) {
                res = 3;
                cpu->increasePC(2 + this->offset);
            } else {
                res = 2;
                cpu->increasePC(2);
            }
        }
        break;
    }

    case kJRUncond: {
        res = 3;
        cpu->increasePC(2 + this->offset);

        break;
    }
    }
    return res;
}
static std::string jrCondTypeToName(JRCondType type) {
    switch (type) {

    case kJRCondNormal:
        return "";
    case kJRCondNot:
        return "N";
    default:
        return "";
    }
}
JR::JR(Flag flag, JRCondType type, E8 offset) {
    this->flag = flag;
    this->type = type;
    this->offset = offset;
    auto stream = std::stringstream();
    stream << "JR  " << jrCondTypeToName(type) << std::hex << flagToName(flag);
    this->text_string = stream.str();
    this->action = kJRCond;
    // TODO: this needs two differnet timings based on whether the jump is taken
    // or not
}

JR::JR(E8 offset) {
    this->action = kJRUncond;
    this->offset = offset;
    auto stream = std::stringstream();
    stream << "JR uncond " << std::hex << (int)offset;
    this->text_string = stream.str();
}
