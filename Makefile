gemu: 
	g++ main.cpp cpu/Disassembler.cpp cpu/Instruction.cpp cpu/CPU.cpp cpu/instructions/*.cpp -o gemu
