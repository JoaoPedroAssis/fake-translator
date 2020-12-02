#include <iostream>
#include <sys/wait.h>
#include <string.h>
#include "../include/PreProcessor.h"
#include "../include/Translator.h"

using namespace std;

int main(int argc, char const *argv[]) {

    string programFilepath;

    if (argc == 2) {
        programFilepath = argv[1];
    } else {
        cout << "Número incorreto de argumentos (apenas 1 argumento esperado)." << endl;
        cout << "Para traduzir digite: \"./tradutor <nome_do_programa.asm>\"" << endl;
        return 0;
    }

    /* Get program filename */
    string file = programFilepath.substr(programFilepath.find_last_of("/") + 1);
    string programFilename = file.substr(0, file.find_last_of('.'));

    /* Pre processing stage */
    PreProcessor* preProcessor = new PreProcessor(programFilepath, false);

    auto preProcessedFile = preProcessor->preProcess();

    /* Translation stage */
    Translator* translator = new Translator(preProcessedFile);

    translator->translate();
    translator->printToFile(programFilename);


    cout << "Programa traduzido salvo em " + programFilename + ".s" << endl;

    cout << "Montando programa: " << endl;

    string command = "nasm -f elf32 -o " + programFilename + ".o " + programFilename + ".s";
    cout << command << endl;
    int exit = system(command.c_str());
    
    cout << "\nLigando programa: " << endl;

    command = "ld -m elf_i386 -o " + programFilename + " " + programFilename + ".o";
    cout << command << endl;
    exit = system(command.c_str());
    return 0;
}
