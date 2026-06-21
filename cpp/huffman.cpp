#include "../headers/huffman.h"

struct Node{
    unsigned char ch;
    int freq;
    Node *left;
    Node *right;
    Node(unsigned char c,int f):
    ch(c),freq(f),left(nullptr),right(nullptr){}

};

struct Compare{
    bool operator()(Node* a,Node* b){
        return a->freq>b->freq;
    }
};

void buildCodes(Node* root,string str,unordered_map<unsigned char,string>&codes){
    if(!root) return;
    if(!root->left && !root->right){
        codes[root->ch]=str;
    }
    buildCodes(root->left,str+"0",codes);
    buildCodes(root->right,str+"1",codes);
}

unordered_map<unsigned char,string> encode(const unordered_map<unsigned char,int>&freq){
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

