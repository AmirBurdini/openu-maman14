
#define BINARY_WORD_SIZE 14
#define MEMORY_START 100
#define REGS_SIZE 8
#define OP_SIZE 16
#define RAM_MEMORY_SIZE 4096
#define MAX_LABEL_LEN 31
#define MAX_LINE_LEN 81

#define HASHSIZE ((RAM_MEMORY_SIZE / (MAX_LABEL_LEN + 1)) / 4)

#define A 00
#define R 10
#define E 01
#define IMMEDIATE_ADDR 00
#define DIRECT_ADDR 01
#define INDEX_ADDR 10
#define REGISTER_DIRECT_ADDR 11

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define R4 4
#define R5 5
#define R6 6
#define R7 7

#define DATA ".data"
#define STRING ".string"
#define ENTRY ".entry"
#define EXTERNAL ".extern"
#define DEFINE ".define"

#define _TYPE_DATA 1001
#define _TYPE_STRING 1002
#define _TYPE_ENTRY 1003
#define _TYPE_EXTERNAL 1004
#define _TYPE_DEFINE 1005
#define _TYPE_CODE 1006

#define _TOKEN_FORMAT " \t\n\f\r"
#define _TOKEN_FORMAT_SECOND ", \t\n\f\r"
#define _TOKEN_FORMAT_DEFINE "= \t\n\f\r"

