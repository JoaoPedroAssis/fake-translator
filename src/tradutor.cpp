#include <iostream>
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

    PreProcessor* preProcessor = new PreProcessor(programFilepath, false);

    auto preProcessedFile = preProcessor->preProcess();

    Translator* translator = new Translator(preProcessedFile);

    translator->translate();

    return 0;
}
