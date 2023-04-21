// Copyright 2021 GHA Test Team
#include <textgen.h>
#include <fstream>


int main()
{
    setlocale(LC_ALL, "");
    std::wstring text;
    std::wstring line;

    std::wifstream in("fish.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            text += line + L"\n";
        }
    }
    in.close();

    Markov gen = Markov(text, 2);

    std::wofstream out;
    out.open("fish_generate.txt");
    if (out.is_open())
    {
        out << gen.Generate(3000) << std::endl;
    }
    out.close();
}