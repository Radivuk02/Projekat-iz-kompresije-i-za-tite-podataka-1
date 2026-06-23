#include "../headers/lzw.h"

vector<int> lzwComp(const string& ulaz){
    unordered_map<string,int> dict;
    for(int i=0;i<256;i++)
    dict[string(1,i)]=i;
    int code=256;
    string curr;
    vector<int> izlaz;
    for(char c:ulaz){
        string next=curr+c;
        if(dict.count(next)){
            curr=next;
        }
        else{
            izlaz.push_back(dict[curr]);
            dict[next]=code++;
            curr=string(1,c);
        }
    }
    if(!curr.empty())
    izlaz.push_back(dict[curr]);
    return izlaz;
}

string lzwDecomp(const vector<int>&compr){
    unordered_map<int,string>dict;
    int dictSize=256;
    for(int i=0;i<dictSize;i++){
        string ch(1,(char)i);
        dict[i]=ch;
    }

    string w(1,(char)compr[0]);
    string izlaz=w;

    for(size_t i=1;i<compr.size();i++){
        int k=compr[i];
        string unos;

        if(dict.count(k)){
            unos=dict[k];
        }
        else if(k==dictSize){
            unos=w+w[0];
        }
        else{
            throw runtime_error("Neispravan LZW kod");
        }
        izlaz+=unos;
        dict[dictSize++]=w+unos[0];
        w=unos;
    }
    return izlaz;

}