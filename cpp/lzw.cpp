#include "../headers/lzw.h"

vector<int> lzwCompress(const string& ulaz){
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