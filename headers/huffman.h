#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <string>
#include <queue>
#include <vector>

using namespace std;

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


void buildCodes(Node* root,string str,unordered_map<unsigned char,string>&codes);
unordered_map<unsigned char,string> huffEncode(const unordered_map<unsigned char,int>& freg);

vector<unsigned char> huffCompress(const vector<unsigned char>&data,unordered_map<unsigned char,string>&codes);
vector<unsigned char> huffCompress(const vector<unsigned char>&data,unordered_map<unsigned char,string>&codes);
#endif