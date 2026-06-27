#include <iostream>
#include "headers/file_manager.h"
#include "headers/entropy.h"
#include "headers/sha_fanno.h"
#include "headers/huffman.h"
#include "headers/lz77.h"
#include "headers/lzw.h"
#include "headers/sub_fun.h"

int main(){
    string ulazni="bin/entropy.bin";
    auto data= FileManager::readFile(ulazni);
    cout<<"Ulazni fajl: "<<ulazni<<" ("<<data.size()<<" bajtova)"<<endl;

    double H=calculate(ulazni);
    cout << "Entropija ulaznog fajla:" << H << "bita po bajtu" <<endl;

    unordered_map <unsigned char,int> freq;
    for(auto b:data)
    freq[b]++;
    vector<Simbol> simboli;

    for(auto& p:freq)
     simboli.push_back({p.first,(double)p.second/data.size()});

    sortSimboli(simboli);
    unordered_map<unsigned char,string> sfCodes;
    shaFanno(simboli,0,simboli.size()-1,sfCodes,"");

    vector<pair<unsigned char,string>>codesVec=getSimbols(sfCodes);
  
    FileManager::writeCodes("codes/sha_fanno_codes.txt",codesVec);

    auto huffCodes=huffEncode(freq);
    codesVec.clear();
    codesVec=getSimbols(huffCodes);
    FileManager::writeCodes("codes/huff_codes.txt",codesVec);

    string inputStr(data.begin(),data.end());
    auto lz77comp=lzComp(inputStr,8);
    auto lz77decomp=lzDecomp(lz77comp);
    FileManager::writeText("decompress/lz77.bin",lz77decomp);
    if(lz77decomp==inputStr){
        cout<<"Lz77 uspesan"<<endl;
    }
    else{
        cout<<"LZ77 neuspesan"<<endl;
    }

    auto wComp=lzwComp(inputStr);
    string wDecomp=lzwDecomp(wComp);
    FileManager::writeText("decompress/lzw.bin",wDecomp);
    if(wDecomp==inputStr){
        cout<<"LzW uspesan"<<endl;
    }
    else{
        cout<<"LZW neuspesan"<<endl;
    }
}