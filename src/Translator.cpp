#include "../include/Translator.h"
#include "../include/Helper.h"

Translator::Translator(unordered_map<string, vector<string>> preprocessedFile) {
    this->program = preprocessedFile;
}

Translator::~Translator() {
}

void Translator::translate() {
    vector<string> translatedProgram;

    /* Section Data */
    /* Section Bss */
    /* Section Text */
    for (auto line : program["text"]) {
        translatedProgram.push_back(this->toIA32(line));
    }
}

string Translator::toIA32(string line) {
    auto lineContents = split(line, ' ', '\t');

    Line *l = getLineElements(lineContents);

    if (l->operation == "ADD") {

    } else if (l->operation == "SUB") {

    } else if (l->operation == "MULT") {
        
    } else if (l->operation == "DIV") {
        
    } else if (l->operation == "JMP") {
        
    } else if (l->operation == "JMPP") {
        
    } else if (l->operation == "JMPZ") {
        
    } else if (l->operation == "COPY") {
        
    } else if (l->operation == "LOAD") {
        
    } else if (l->operation == "STORE") {
        
    } else if (l->operation == "INPUT") {
        
    } else if (l->operation == "OUTPUT") {
        
    } else if (l->operation == "C_INPUT") {
        
    } else if (l->operation == "C_OUTPUT") {
        
    } else if (l->operation == "S_INPUT") {
        
    } else if (l->operation == "S_OUTPUT") {
        
    } else if (l->operation == "SPACE") {
        
    } else if (l->operation == "CONST") {
        
    } 
}