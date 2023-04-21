// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include <textgen.h>

TEST(prefix_count, first) {
    std::wstring t = L"first second third";
    int nPref = 2;
    Markov m = Markov(t, nPref);
    auto table = m.GetTable();
    for (const auto& element : table) {
        EXPECT_EQ(element.first.size(), nPref);
    }
}

TEST(prefix_suffix_pair, pair) {
    std::wstring t = L"first second third";
    Markov m = Markov(t);
    auto table = m.GetTable();
    prefix pr = prefix();
    pr.push_back(L"first");
    pr.push_back(L"second");
    EXPECT_EQ(table[pr][0], L"third");
}

TEST(prefix_suffix_pair, one_suffix) {
    std::wstring t = L"first second";
    int nPref = 1;
    Markov m = Markov(t, nPref);
    auto table = m.GetTable();
    prefix pr = prefix();
    pr.push_back(L"first");
    EXPECT_EQ(table[pr][0], L"second");
}

TEST(prefix_suffix_pair, many_suffix) {
    std::wstring t = L"first first second";
    Markov m = Markov(t, 1);
    auto table = m.GetTable();
    prefix pr = prefix();
    pr.push_back(L"first");
    suffix sf = suffix();
    sf.push_back(L"first");
    sf.push_back(L"second");
    EXPECT_EQ(table[pr][0], sf[0]);
    EXPECT_EQ(table[pr][1], sf[1]);
}

TEST(text_generate, with_length) {
    auto table = std::map<prefix, suffix>();
    prefix pr = prefix();
    suffix sf = suffix();
    pr.push_back(L"first");
    sf.push_back(L"second");
    sf.push_back(L"third");
    table[pr] = sf;
    pr.clear();
    pr.push_back(L"second");
    sf.clear();
    sf.push_back(L"first");
    sf.push_back(L"third");
    table[pr] = sf;
    pr.clear();
    pr.push_back(L"third");
    sf.clear();
    sf.push_back(L"first");
    sf.push_back(L"second");
    table[pr] = sf;
    Markov m = Markov(table);
    std::wstring expected = L"third second first second third first second first second first third second third second third second ";
    EXPECT_EQ(expected, m.Generate(100, 1));
}