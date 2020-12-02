#include <fstream>
#include "../include/Translator.h"
#include "../include/Helper.h"

Translator::Translator(unordered_map<string, vector<string>> preprocessedFile) {
    this->program = preprocessedFile;
}

Translator::~Translator() {
}

void Translator::translate() {

    /* Section Text */
    translatedProgram.push_back("global _start");
    translatedProgram.push_back("\nsection .text\n");

    /* Print Funções Assembly */

    ifstream funcs("IA-32/io.asm");
    if (!funcs) {
        cout << "Não foi possível abrir o arquivo com funções de IO" << endl;
        exit(1);
    }

    string line;
    while(getline(funcs, line)) {
        translatedProgram.push_back(line);
    }

    /* Program start */
    translatedProgram.push_back("_start:");

    for (string line : program["text"]) {
        translatedProgram.push_back(this->toIA32(line));
    }

    /* Section Data */
    translatedProgram.push_back("\nsection .data\n");

    for (string line : program["data"]) {
        translatedProgram.push_back(this->toIA32(line));
    }

    /* Section Bss */
    translatedProgram.push_back("\nsection .bss\n");

    /* Useful variables */
    translatedProgram.push_back("BUFFER RESB 12");
    translatedProgram.push_back("BUFFER_SIZE EQU 12");

    for (string line : program["bss"]) {
        translatedProgram.push_back(this->toIA32(line));
    }
    
}

string Translator::toIA32(string line) {
    vector<string> lineContents = split(line, ' ', '\t');
    string translatedLine = "";

    Line *l = getLineElements(lineContents);

    if (l->operation == "ADD") {

        translatedLine += "ADD " + accumulatorRegister + "[" + l->args[0] + "]";

    } else if (l->operation == "SUB") {

        translatedLine += "SUB " + accumulatorRegister + "[" + l->args[0] + "]";

    } else if (l->operation == "MULT") {

        translatedLine += "MOV EAX, [" + l->args[0] + "]\n";
        translatedLine += "IMUL DWORD" + accumulatorRegister.substr(0, accumulatorRegister.length() - 2);
        translatedLine += "MOV " + accumulatorRegister + "EAX";
        
    } else if (l->operation == "DIV") {

        translatedLine += "MOV EAX, " + accumulatorRegister.substr(0, accumulatorRegister.length() - 2);
        translatedLine += "CDQ\n";
        translatedLine += "IDIV DWORD [" + l->args[0] + "]\n";
        translatedLine += "MOV " + accumulatorRegister + "EAX";
        
    } else if (l->operation == "JMP") {
        
        translatedLine += "JMP " + l->args[0];

    } else if (l->operation == "JMPN") {
        
        translatedLine += "CMP " + accumulatorRegister + "0\n";
        translatedLine += "JL " + l->args[0];

    } else if (l->operation == "JMPP") {
        
        translatedLine += "CMP " + accumulatorRegister + "0\n";
        translatedLine += "JG " + l->args[0];

    } else if (l->operation == "JMPZ") {

        translatedLine += "CMP " + accumulatorRegister + "0\n";
        translatedLine += "JE " + l->args[0];
        
    } else if (l->operation == "COPY") {

        translatedLine += "MOV [" + l->args[1] + "], " + "[" + l->args[0] + "]";

    } else if (l->operation == "LOAD") {

        translatedLine +=
        "MOV " + accumulatorRegister.substr(0, accumulatorRegister.length() - 2) + ", " + "[" + l->args[0] + "]";
        
    } else if (l->operation == "STORE") {

        translatedLine +=
        "MOV [" + l->args[0] + "], " + accumulatorRegister.substr(0, accumulatorRegister.length() - 2);
        
    } else if (l->operation == "INPUT") {
        
        translatedLine += "CALL LerInteiro\n";
        translatedLine += "MOV [" + l->args[0] + "], EAX";

    } else if (l->operation == "OUTPUT") {

        translatedLine += "PUSH DWORD [" + l->args[0] + "]\n";
        translatedLine += "CALL EscreverInteiro";
        
    } else if (l->operation == "C_INPUT") {
        
        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "CALL LerChar";
        
    } else if (l->operation == "C_OUTPUT") {

        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "CALL EscreverChar";
        
    } else if (l->operation == "S_INPUT") {

        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "PUSH DWORD" + l->args[1] + "\n";
        translatedLine += "CALL LerString";
        
    } else if (l->operation == "S_OUTPUT") {

        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "PUSH DWORD" + l->args[1] + "\n";
        translatedLine += "CALL EscreverString";
        
    } else if (l->operation == "SPACE") {

        if (l->args.size() == 0) {
            translatedLine += l->label + " RESB 1";
        } else {
            translatedLine += l->label + " RESB " + l->args[0];
        }
        
    } else if (l->operation == "CONST") {
        
        translatedLine += l->label + " DD " + l->args[0];

    } else if (l->operation == "STOP") {
        translatedLine += "MOV EAX, 1\n";
        translatedLine += "INT 80h";
    }

    return translatedLine;
}

void Translator::printToFile(string inputFilename) {
    
    ofstream out("./" + inputFilename + ".s");
    for (string line : this->translatedProgram) {
        out << line << endl;
    }
    out.close();
}
