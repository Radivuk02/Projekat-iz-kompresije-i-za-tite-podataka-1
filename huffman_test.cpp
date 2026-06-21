#include <iostream>
#include <unordered_map>
#include "headers/huffman.h"
using namespace std;

int main(){
    unordered_map<unsigned char,int> freq={
        {'A',3},
        {'B', 7},
        {'C', 12},
        {'D', 15},
        {'E', 16},
        {'F', 45}
    };
    auto codes=encode(freq);

    cout << "Huffman kodovi:"<<endl;
    for(auto&p :codes){
        cout<<p.first<<":"<<p.second<<endl;
    }
    return 0;
}