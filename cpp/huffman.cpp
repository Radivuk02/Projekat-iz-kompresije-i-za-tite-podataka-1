#include "../headers/huffman.h"


void buildCodes(Node* root,string str,unordered_map<unsigned char,string>&codes){
    if(!root) return;
    if(!root->left && !root->right){
        codes[root->ch]=str;
    }
    buildCodes(root->left,str+"0",codes);
    buildCodes(root->right,str+"1",codes);
}

unordered_map<unsigned char,string> huffEncode(const unordered_map<unsigned char,int>&freq){
    priority_queue<Node*,vector<Node *>,Compare>pq;
    for(auto& p:freq){
        pq.push(new Node(p.first,p.second));
    }

    while(pq.size()>1){
        Node* left=pq.top();
        pq.pop();
        Node* right=pq.top();
        pq.pop();
        Node *merged=new Node('\0',left->freq+right->freq);
        merged->left=left;
        merged->right=right;
        pq.push(merged);
    }
    unordered_map<unsigned char,string> codes;
    buildCodes(pq.top(),"",codes);
    return codes;
}

vector<unsigned char> huffCompress(const vector<unsigned char>&data,unordered_map<unsigned char,string>&codes)
{
   unordered_map<unsigned char,int> freq;

   for(auto b:data)
   freq[b]++;

   codes=huffEncode(freq);

   string bits;

   for(auto b: data){
    bits+=codes[b];
   }

   vector <unsigned char> compressed;
   for(size_t i=0;i<bits.size();i+=8){
    unsigned char byte=0;
    for(int j=0;j<8 && i+j<bits.size();j++){
        if(bits[i+1]=='1'){
            byte |=(1<<(7-j));
        }
    }
    compressed.push_back(byte);
   }
   return (compressed);
}

vector <unsigned char> huffmanDecomp(const vector<unsigned char>&compressed,const unordered_map<unsigned char,string>&codes){
    unordered_map<string,unsigned char> unazad;
    for(auto &c:codes){
        unazad[c.second]=c.first;
    }

    string bits;
    for(auto byte:compressed){
        for(int j=0;j<8;j++){
            bits+=((byte & (1<<(7-j))) ? '1':'0');
        }
    }
    vector<unsigned char> decompressed;
    string curr;
    for(char bit:bits){
        curr+=bit;
        if(unazad.count(curr)){
            decompressed.push_back(unazad[curr]);
            curr.clear();
        }
    }
    return decompressed;
}
