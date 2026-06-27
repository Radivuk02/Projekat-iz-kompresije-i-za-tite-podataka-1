#include <iostream>
#include "headers/file_manager.h"
#include "headers/entropy.h"
#include "headers/sha_fanno.h"
#include "headers/huffman.h"
#include "headers/lz77.h"
#include "headers/lzw.h"

using namespace std;
void sortSimboli(vector<Simbol>& simboli) {
    for (size_t i = 0; i < simboli.size(); i++) {
        for (size_t j = i + 1; j < simboli.size(); j++) {
            if (simboli[j].prob > simboli[i].prob) {
                Simbol tmp = simboli[i];
                simboli[i] = simboli[j];
                simboli[j] = tmp;
            }
        }
    }
}
int main(){
    string ulazni="bin/entropy.bin";
    auto data= FileManager::readFile(ulazni);
    cout<<"Ulazni fajl: "<<ulazni<<" ("<<data.size()<<" bajtova)"<<endl;

    double H=calculate(ulazni);
    cout << "Entropija ulaznog fajla:" << H << "bita po bajtu" <<endl;
    cout<<"C1"<<endl;
    unordered_map <unsigned char,int> freq;
    for(auto b:data)
    freq[b]++;
    vector<Simbol> simboli;
    cout<<"C2"<<endl;
    for(auto& p:freq)
     simboli.push_back({p.first,(double)p.second/data.size()});
    if(simboli.empty())
        cout<<"C2.1"<<endl;
    else{
        cout<<"IMA NESTO"<<endl;
    }
    sortSimboli(simboli);
    unordered_map<unsigned char,string> sfCodes;
    shaFanno(simboli,0,simboli.size()-1,sfCodes,"");
    cout<<"C2.2"<<endl;
    vector<pair<unsigned char,string>>codesVec;
    for(auto& p:sfCodes){
        codesVec.push_back(p);
    }
    cout<<"C3"<<endl;
    FileManager::writeCodes("codes/sha_fanno_codes.txt",codesVec);

    auto huffCodes=huffEncode(freq);
    codesVec.clear();
    for(auto &p:huffCodes){
        codesVec.push_back(p);
    }
    FileManager::writeCodes("codes/huff_codes.txt",codesVec);
    cout<<"C4"<<endl;
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