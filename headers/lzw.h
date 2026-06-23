#ifndef LZW_H
#define LZW_H

#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>

using namespace std;

vector<int> lzwComp(const string& ulaz);

string lzwDecomp(const vector<int>&compr);
#endif