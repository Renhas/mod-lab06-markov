// Copyright 2021 GHA Test Team
#pragma once
#include <stdlib.h>
#include <deque>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

typedef std::deque<std::wstring> prefix;
typedef std::vector<std::wstring> suffix;

class Markov {
 private:
    std::map<prefix, suffix> statetab;

 public:
    explicit Markov(std::wstring text, int nPref = 2);
    explicit Markov(std::map<prefix, suffix> table);
    std::wstring Generate(int maxLen, int seed = 1);
    const std::map<prefix, suffix> GetTable();
};

std::vector<std::wstring> split(std::wstring s, std::wstring delimiter);
