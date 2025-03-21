#include "./cpu/CPU.h"
#include "./cpu/Disassembler.h"
#include <cstdio>
#include <cstdlib>
#include <error.h>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
char *program;
int main() {
    int fd = open("./Pokemon Red (UE) [S][!].gb", O_RDONLY, 0600);
    if (fd == -1) {
        perror("Error opening game file");
        exit(EXIT_FAILURE);
    }
    struct stat st;
    stat("./Pokemon Red (UE) [S][!].gb", &st);
    long size = st.st_size;
    program = (char *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (program == MAP_FAILED) {
        perror("Error mapping game file");
        exit(EXIT_FAILURE);
    }
    std::cout << "Program pointer " << std::hex << (long)program << "\n";
    Disassembler *disassembler = new Disassembler((long)program);
    CPU *cpu = new CPU(disassembler);
    cpu->run();
}
