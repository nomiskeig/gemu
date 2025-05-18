#include "../Instruction.h"
#include <ios>
#include <sstream>
#include "../../config.h"

int CALL::execute(CPU *cpu) {
    PUSH push(this->retAddress);
    push.execute(cpu);
    JP jump(this->address);
    jump.execute(cpu);
   GEMU_PRINT_CALL_GRAPH("Call 0x%x with return address 0x%x", this->address, this->retAddress );
    return 6;
};

CALL::CALL(A16 address, A16 retAddress) {
    this->address = address;
    this->retAddress = retAddress;
    auto stream = std::stringstream();
    stream << "Call " << std::hex << this->address;
    this->text_string = stream.str();
}
