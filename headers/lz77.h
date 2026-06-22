#ifndef LZ77_H
#define LZ77_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Token{
    int offset;
    int len;
    char next;
};

vector<Token> lzComp(const string& input, int windowSize);

string lzDecomp(const vector<Token>&tokeni);
#endif
