#pragma once
#include <string>
#include <stdio.h>
#define GEMU_LOG_DISASSEMBLER
#define GEMU_DEBUG_CALL_GRAPH
#define GEMU_DEBUG_HIGHMEM_WRITES
#define GEMU_DEBUG_INSTRUCTIONS
extern int callGraphFD;
extern int highMemFD;
extern int instructionsFD;
#ifdef GEMU_DEBUG_CALL_GRAPH
#define GEMU_PRINT_CALL_GRAPH(...) \
    dprintf(callGraphFD, __VA_ARGS__); \
    dprintf(callGraphFD, "\n");
#else
#define GEMU_PRINT_CALL_GRAPH(...)
#endif
#ifdef GEMU_DEBUG_HIGHMEM_WRITES
#define GEMU_PRINT_HIGHMEM_WRITES(...) \
    dprintf(highMemFD, __VA_ARGS__); \
    dprintf(highMemFD, "\n");
#else
#define GEMU_PRINT_HIGHMEM_WRITES(...)
#endif
#ifdef GEMU_DEBUG_INSTRUCTIONS
#define GEMU_PRINT_INSTURUCTIONS(...) \
    dprintf(instructionsFD, __VA_ARGS__); \
    dprintf(instructionsFD, "\n");
#else
#define GEMU_PRINT_INSTURUCTIONS(...)
#endif
