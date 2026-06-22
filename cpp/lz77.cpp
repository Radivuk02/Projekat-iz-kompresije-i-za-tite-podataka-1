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