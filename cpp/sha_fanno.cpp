#include "../headers/sha_fanno.h"

void shaFanno(vector<Simbol>&simboli,int l,int r,unordered_map<unsigned char,string>&codes,string prefix){    
    if(l>r)
        return;
    if(l==r){
        codes[simboli[l].ch]=prefix;
        return;
    }

    double ukupno=0;
    for(int i=l;i<=r;i++)
    ukupno+=simboli[i].prob;

    double pola=ukupno/2;
    double sum=0;
    int mid=l;

    for(mid=l;mid<=r;mid++){
        sum+=simboli[mid].prob;
        if(sum>=pola)
        break;
    }
    shaFanno(simboli,l,mid,codes,prefix+"0");
    shaFanno(simboli,mid+1,r,codes,prefix+"1");
}

vector<unsigned char> sfComp(const vector<unsigned char>& data,const unordered_map<unsigned char,string>& codes) {
    string bits;
    for (auto b : data) {
        bits += codes.at(b); 
    }

    vector<unsigned char> comp;
    for (size_t i = 0; i < bits.size(); i += 8) {
        unsigned char byte = 0;
        for (size_t j = 0; j < 8 && i + j < bits.size(); j++) {
            if (bits[i + j] == '1')
                byte |= (1 << (7 - j));
        }
        comp.push_back(byte);
    }
    return comp;
}

vector<unsigned char> sfDecomp(const vector<unsigned char>& compressed,const unordered_map<unsigned char,string>& codes) {
    unordered_map<string,unsigned char> unazad;
    for (auto& p : codes) {
        unazad[p.second] = p.first;
    }

    string bitString;
    for (auto byte : compressed) {
        for (int j = 7; j >= 0; j--) {
            bitString += ((byte >> j) & 1) ? '1' : '0';
        }
    }

    vector<unsigned char> decompressed;
    string curr;
    for (char bit : bitString) {
        curr += bit;
        if (unazad.count(curr)) {
            decompressed.push_back(unazad[curr]);
            curr.clear();
        }
    }
    return decompressed;
}