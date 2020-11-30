#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <iostream>
#include "../include/File.h"

using namespace std;

typedef struct {
    unsigned short int args, opcode;
} Instruction;

typedef struct {
    unsigned short int args, size;
    string name;
} Directive;

class Translator {
private:
    File* program;
public:
    Translator();
    ~Translator();

    void translate();
};


#endif // TRANSLATOR_H
