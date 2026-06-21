#include "../headers/sha_fanno.h"

void shaFanno(vector<Simbol>&simboli,int l,int r,unordered_map<unsigned char,string>&codes,string prefix){
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