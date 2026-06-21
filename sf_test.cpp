#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "headers/sha_fanno.h"

using namespace std;

int main(){
    vector<Simbol> simboli={
        {'A', 0.25},
        {'B', 0.20},
        {'C', 0.15},
        {'D', 0.15},
        {'E', 0.10},
        {'F', 0.15}
    };

    sort(simboli.begin(),simboli.end());

    unordered_map<unsigned char,string>codes;
    shaFanno(simboli,0,simboli.size()-1,codes,"");

    cout<< "SF kodovi su:"<<endl;
    for(auto &s:simboli){
        cout<<s.ch<<":"<<codes[s.ch]<<endl;
    }
    return 0;

}