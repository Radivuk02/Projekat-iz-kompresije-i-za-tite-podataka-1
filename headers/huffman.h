#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <string>
#include <queue>
#include <vector>

using namespace std;

unordered_map<unsigned char,string> encode(const unordered_map<unsigned char,int>& freg);

#endif