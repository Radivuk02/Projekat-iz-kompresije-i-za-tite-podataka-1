#include<iostream>
#include<string>
#include "headers/lz77.h"

using namespace std;

int main(){
    string ulaz="ABABABABABBABABABAB";
    int winSize=6;
    cout<<"Originalni string:"<<ulaz<<endl;
    auto compressed=lzComp(ulaz,winSize);

    cout<<"Kompresovani podaci (offset,length,next):"<<endl;
    for(auto& t:compressed){
        cout<<"("<<t.offset<<","<<t.len<<","<<t.next<<")"<<endl;
    }
    string izlaz=lzDecomp(compressed);
    cout<<"Dekompresovan string:"<<izlaz<<endl;
    if(izlaz==ulaz){
        cout<<"Test uspesan:ulaz i izlaz su isti";
    }
    else{
        cout<<"Test neuspesan ulaz i izlaz se razlikuju";
    }
}