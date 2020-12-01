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
    translatedProgram.push_back(lerChar() + "\n");
    translatedProgram.push_back(escreverChar() + "\n");
    translatedProgram.push_back(lerString() + "\n");
    translatedProgram.push_back(escreverString() + "\n");

    /* Program start */
    translatedProgram.push_back("_start:");

    
    for (string line : program["text"]) {
        translatedProgram.push_back(this->toIA32(line));
    }

    /* Section Data */
    if (program.find("data") != program.end()) {
        translatedProgram.push_back("\nsection .data\n");

        for (string line : program["data"]) {
            translatedProgram.push_back(this->toIA32(line));
        }
    }

    /* Section Bss */
    if (program.find("bss") != program.end()) {
        translatedProgram.push_back("\nsection .bss\n");

        for (string line : program["bss"]) {
            translatedProgram.push_back(this->toIA32(line));
        }
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

        translatedLine += "MOV EAX, " + accumulatorRegister.substr(0, accumulatorRegister.length() - 2) + "\n";
        translatedLine += "IMUL " + l->args[0];
        //verificar overflow interrupção de software
        
    } else if (l->operation == "DIV") {

        translatedLine += "MOV EAX, " + accumulatorRegister.substr(0, accumulatorRegister.length() - 2) + "\n";
        translatedLine += "CDQ\n";
        translatedLine += "IDIV " + l->args[0];
        
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
        "MOV [" + accumulatorRegister.substr(0, accumulatorRegister.length() - 2) + "], " + l->args[0];
        
    } else if (l->operation == "STORE") {

        translatedLine +=
        "MOV [" + l->args[0] + "], " + accumulatorRegister.substr(0, accumulatorRegister.length() - 2);
        
    } else if (l->operation == "INPUT") {
        
    } else if (l->operation == "OUTPUT") {
        
    } else if (l->operation == "C_INPUT") {
        
        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "CALL LerChar";
        
    } else if (l->operation == "C_OUTPUT") {

        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "CALL EscreverChar";
        
    } else if (l->operation == "S_INPUT") {

        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "PUSH " + l->args[1] + "\n";
        translatedLine += "CALL LerString";
        
    } else if (l->operation == "S_OUTPUT") {

        translatedLine += "PUSH " + l->args[0] + "\n";
        translatedLine += "PUSH " + l->args[1] + "\n";
        translatedLine += "CALL EscreverString";
        
    } else if (l->operation == "SPACE") {

        if (l->args.size() == 0) {
            translatedLine += l->label + " RESB 1";
        } else {
            translatedLine += l->label + " RESB " + l->args[0];
        }
        
    } else if (l->operation == "CONST") {
        
        translatedLine += l->label + " DD '" + l->args[0] + "'";

    } else if (l->operation == "STOP") {
        translatedLine += "MOV " + accumulatorRegister + "1\n";
        translatedLine += "INT 80h";
    }

    return translatedLine;
}

void Translator::printToFile(string inputFilePath) {
    
    string file = inputFilePath.substr(inputFilePath.find_last_of("/") + 1);
    string programFilename = file.substr(0, file.find_last_of('.'));

    ofstream out("./" + programFilename + ".s");
    for (string line : this->translatedProgram) {
        out << line << endl;
    }
    out.close();
}

string Translator::lerChar() {
    string func = "";
    func += "LerChar:\n";
    func += "ENTER 0, 0\n";
    func += "MOV EAX, 3\n";
    func += "MOV EBX, 0\n";
    func += "MOV ECX, [EBP + 8]\n";
    func += "MOV EDX, 1\n";
    func += "INT 80h\n";
    func += "LEAVE\n";
    func += "RET 4";

    return func;
}

string Translator::escreverChar() {
    string func = "";
    func += "EscreverChar:\n";
    func += "ENTER 0, 0\n";
    func += "MOV EAX, 4\n";
    func += "MOV EBX, 1\n";
    func += "MOV ECX, [EBP + 8]\n";
    func += "MOV EDX, 1\n";
    func += "INT 80h\n";
    func += "LEAVE\n";
    func += "RET 4";

    return func;
}

string Translator::lerString() {
    string func = "";
    func += "LerString:\n";
    func += "ENTER 0, 0\n";
    func += "MOV EAX, 3\n";
    func += "MOV EBX, 0\n";
    func += "MOV ECX, [EBP + 12]\n";
    func += "MOV EDX, [EBP + 8]\n";
    func += "INT 80h\n";
    func += "LEAVE\n";
    func += "RET 8";

    return func;
}

string Translator::escreverString() {
    string func = "";
    func += "EscreverString:\n";
    func += "ENTER 0, 0\n";
    func += "MOV EAX, 4\n";
    func += "MOV EBX, 1\n";
    func += "MOV ECX, [EBP + 12]\n";
    func += "MOV EDX, [EBP + 8]\n";
    func += "INT 80h\n";
    func += "LEAVE\n";
    func += "RET 8";

    return func;
}
