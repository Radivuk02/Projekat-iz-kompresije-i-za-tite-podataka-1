#ifndef SHANNON_FANO_H
#define SHANNON_FANO_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Simbol{
    unsigned char ch;
    double prob;
    bool operator<(const Simbol& other) const {
        return prob > other.prob;
    }
};

void shaFanno(vector<Simbol>&simboli,int l,int r,unordered_map<unsigned char,string>&codes,string prefix);
vector<unsigned char> sfComp(const vector<unsigned char>& data,const unordered_map<unsigned char,string>& codes,size_t &validBits );
vector<unsigned char> sfDecomp(const vector<unsigned char>& compressed,const unordered_map<unsigned char,string>& codes,size_t validBits); 
#endif

