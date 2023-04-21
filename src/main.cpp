// Copyright 2021 GHA Test Team
#include <textgen.h>
#include <fstream>
#include <iostream>


int main() {
    setlocale(LC_ALL, "");
    std::wstring text = L"You have brains in your head.\
        You have feet in your shoes.\
        You can steer yourself any direction you choose.";

    Markov gen = Markov(text, 2);

    std::wofstream out;
    std::wcout << gen.Generate(500);
}
