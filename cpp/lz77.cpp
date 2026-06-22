#include "../headers/lz77.h"

vector <Token> lzComp(const string& input, int windowSize){
    vector<Token> tokeni;

    int i=0;

    while(i<input.size()){
        int bestlen =0;
        int bestOff=0;
        for(int j= max(0,i-windowSize);j<i;j++){
            int len=0;
            while(i+len<input.size() && input[j+len]==input[i+len])
            len++;
            if(len>bestlen){
                bestlen=len;
                bestOff=i-j;
            }
        }
        char nextChar=(i+bestlen<input.size())?input[i+bestlen]:'\0';
        tokeni.push_back({bestOff,bestlen,nextChar});
        i+=bestlen+1;
    }
    return tokeni;
}

string lzDecomp(const vector<Token>&tokeni){
    string izlaz;
    for(auto &t:tokeni){
        if(t.offset==0 && t.len==0){
            izlaz.push_back(t.next);
        }
        else{
            int start=(int)izlaz.size()-t.offset;
            for(int i=0;i<t.len;i++){
                izlaz.push_back(izlaz[start+i]);
            }
            if(t.next!='\0'){
                izlaz.push_back(t.next);
            }
        }
    }
    return izlaz;
}