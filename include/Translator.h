#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <iostream>
#include <unordered_map>
#include "../include/File.h"

using namespace std;

typedef struct {
    unsigned short int args, opcode;
} Instruction;

typedef struct {
    unsigned short int args, size;
} Directive;

class Translator {
private:
    string accumulatorRegister = "EAX, ";

    unordered_map<string, vector<string>> program;

    unordered_map<string, Instruction> Instructions = {
        {"ADD",     (Instruction) {1, 1}},
        {"SUB",     (Instruction) {1, 2}},
        {"MULT",    (Instruction) {1, 3}},
        {"DIV",     (Instruction) {1, 4}},
        {"JMP",     (Instruction) {1, 5}},
        {"JMPN",    (Instruction) {1, 6}},
        {"JMPP",    (Instruction) {1, 7}},
        {"JMPZ",    (Instruction) {1, 8}},
        {"COPY",    (Instruction) {2, 9}},
        {"LOAD",    (Instruction) {1, 10}},
        {"STORE",   (Instruction) {1, 11}},
        {"INPUT",   (Instruction) {1, 12}},
        {"OUTPUT",  (Instruction) {1, 13}},
        {"C_INPUT", (Instruction) {1, 15}},
        {"C_OUTPUT",(Instruction) {1, 16}},
        {"S_INPUT", (Instruction) {2, 19}},
        {"S_OUTPUT",(Instruction) {2, 20}},
        {"STOP",    (Instruction) {0, 14}}
    };

    unordered_map<string, Directive> Directives = {
        {"SECTION", (Directive) {1, 0}},
        {"SPACE",   (Directive) {0, 1}},
        {"CONST",   (Directive) {1, 1}},
        {"EQU",     (Directive) {1, 0}},
        {"IF",      (Directive) {1, 0}},

    };

    string toIA32(string);
public:
    Translator(unordered_map<string, vector<string>>);
    ~Translator();

    void translate();
};


#endif // TRANSLATOR_H
