#include <iostream>
#include <string.h>
#include "../include/Error.h"

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


    return 0;
}
