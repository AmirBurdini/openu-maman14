
#define BINARY_WORD_SIZE 14
#define MEMORY_START 0
#define REGS_SIZE 8
#define OP_SIZE 16
#define RAM_MEMORY_SIZE 4096
#define MAX_LABEL_LEN 31
#define MAX_LINE_LEN 81

/* Hash Table Hashsize (Result is currently 64)  */
#define HASHSIZE ((RAM_MEMORY_SIZE / (MAX_LABEL_LEN + 1)) / 4)

/* Masks for creation of to binary word memory image */
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
/* Given just random Numbers that will be different then 0*/
#define _TYPE_DATA 11
#define _TYPE_STRING 22
#define _TYPE_ENTRY 33
#define _TYPE_EXTERNAL 44
#define _TYPE_CODE 55