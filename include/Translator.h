#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <iostream>
#include <unordered_map>
#include "../include/File.h"

using namespace std;

class Translator {
private:
    string accumulatorRegister = "EAX, ";

    unordered_map<string, vector<string>> program;
    vector<string> translatedProgram;

    string toIA32(string);
public:
    Translator(unordered_map<string, vector<string>>);
    ~Translator();

    void translate();
    void printToFile(string);
};


#endif // TRANSLATOR_H
