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

    return;
}

string Translator::toIA32(string line) {
    auto lineContents = split(line, ' ', '\t');
    string translatedLine = "";

    Line *l = getLineElements(lineContents);

    if (l->operation == "ADD") {

        translatedLine += "ADD " + accumulatorRegister + "[" + l->args[0] + "]";

    } else if (l->operation == "SUB") {

        translatedLine += "SUB " + accumulatorRegister + "[" + l->args[0] + "]";

    } else if (l->operation == "MULT") {

        translatedLine += "MOV EAX, " + accumulatorRegister + "\n";
        translatedLine += "IMULT [" + l->args[0] + "]";
        //verificar overflow interrupção de software
        
    } else if (l->operation == "DIV") {

        translatedLine += "MOV EAX, " + accumulatorRegister + "\n";
        translatedLine += "CDQ\n";
        translatedLine += "IDIV [" + l->args[0] + "]";
        
    } else if (l->operation == "JMP") {
        
        translatedLine += "JMP " + l->args[0];

    } else if (l->operation == "JMPN") {
        
        translatedLine += "CMP " + accumulatorRegister + "0";
        translatedLine += "JL " + l->args[0];

    } else if (l->operation == "JMPP") {
        
        translatedLine += "CMP " + accumulatorRegister + "0";
        translatedLine += "JG " + l->args[0];

    } else if (l->operation == "JMPZ") {

        translatedLine += "CMP " + accumulatorRegister + "0";
        translatedLine += "JE " + l->args[0];
        
    } else if (l->operation == "COPY") {

        translatedLine += "MOV [" + l->args[1] + "], " + "[" + l->args[0] + "]";

    } else if (l->operation == "LOAD") {

        translatedLine += "MOV [" + accumulatorRegister + "], " + l->args[0];
        
    } else if (l->operation == "STORE") {

        translatedLine += "MOV [" + l->args[0] + "], " + accumulatorRegister;
        
    } else if (l->operation == "INPUT") {
        
    } else if (l->operation == "OUTPUT") {
        
    } else if (l->operation == "C_INPUT") {
        
    } else if (l->operation == "C_OUTPUT") {
        
    } else if (l->operation == "S_INPUT") {
        
    } else if (l->operation == "S_OUTPUT") {
        
    } else if (l->operation == "SPACE") {

        if (l->args.size() == 0) {
            translatedLine += l->label + " RESB 1";
        } else {
            translatedLine += l->label + " RESB " + l->args[0];
        }
        
    } else if (l->operation == "CONST") {
        
        translatedLine += l->label + " DD '" + l->args[0];

    }

    return translatedLine;
}