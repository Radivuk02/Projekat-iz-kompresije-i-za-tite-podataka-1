#include "../headers/lz77.h"

vector <Token> lzComp(const string& input, int windowSize){
    vector<Token> tokeni;

    int i=0;

    while(i<input.size()){
        int bestlen =0;
        int bestOff=0;
        int startWin = max(0, i - windowSize);
        for(int j=startWin;j<i;j++){
            int len=0;
            while(i+len<input.size() && input[j+len]==input[i+len] && len<255)
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
                izlaz.push_back(izlaz[start]);
            }
            if(t.next!='\0'){
                izlaz.push_back(t.next);
            }
        }
    }
    return izlaz;
}

vector<unsigned char> lz77serial(const vector<Token>& tokens) {
    vector<unsigned char> bytes;
    uint32_t count = tokens.size();
    
    bytes.push_back((count >> 24) & 0xFF);
    bytes.push_back((count >> 16) & 0xFF);
    bytes.push_back((count >> 8) & 0xFF);
    bytes.push_back(count & 0xFF);
    
    for (auto& t : tokens) {

        bytes.push_back((t.offset >> 8) & 0xFF);
        bytes.push_back(t.offset & 0xFF);

        bytes.push_back((unsigned char)t.len)
;       bytes.push_back((unsigned char)t.next);
    }
    return bytes;
}

vector<Token>lz77deserial(const vector<unsigned char>& data){
    vector<Token> tokens;
    if (data.size() < 4) 
    return tokens;

    uint32_t count = ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) | ((uint32_t)data[2] << 8) | data[3];
    size_t pos = 4;

    for (uint32_t i=0; i<count && pos+4<=data.size(); i++) {
        int offset = (data[pos]<<8) | data[pos+1];
        int len = data[pos+2];
        char next = (char)data[pos+3];
        tokens.push_back({offset,len,next});
        pos += 4;
    }
    return tokens;
}