// Copyright 2021 GHA Test Team
#include "textgen.h"

Markov::Markov(std::wstring text, int nPref) {
    if (nPref >= text.length())
        throw std::invalid_argument("Number of prefix must be < text length");

    statetab = std::map<prefix, suffix>();

    prefix pr = prefix();
    std::vector<std::wstring> words = split(text, L" ");
    for (int i = 0; i < nPref; i++) {
        pr.push_back(words[i]);
    }
    for (int i = nPref; i < words.size(); i++) {
        if (statetab.find(pr) == statetab.end()) {
            suffix sf = suffix();
            sf.push_back(words[i]);
            statetab[pr] = sf;
        } else {
            statetab[pr].push_back(words[i]);
        }
        pr.pop_front();
        pr.push_back(words[i]);
    }
}

Markov::Markov(std::map<prefix, suffix> table) {
    statetab = table;
}

std::wstring Markov::Generate(int maxLen, int seed) {
    std::wstring result;
    prefix pr = statetab.begin()->first;
    std::srand(seed);
    while (result.length() < maxLen) {
        if (statetab.find(pr) == statetab.end()) {
            break;
        }
        suffix sf = statetab[pr];
        int id = std::rand() % sf.size();
        result += sf[id] + L" ";
        pr.pop_front();
        pr.push_back(sf[id]);
    }
    return result;
}

const std::map<prefix, suffix> Markov::GetTable() {
    return statetab;
}

std::vector<std::wstring> split(std::wstring s, std::wstring delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::wstring token;
    std::vector<std::wstring> res;
    pos_end = s.find(delimiter, pos_start);
    while (pos_end != std::wstring::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
        pos_end = s.find(delimiter, pos_start);
    }

    res.push_back(s.substr(pos_start));
    return res;
}
