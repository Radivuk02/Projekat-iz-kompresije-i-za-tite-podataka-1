#ifndef SUB_FUN_H
#define SUB_FUN_H
#include<iostream>
#include<vector>
#include<string>
#include "sha_fanno.h"
using namespace std;

void sortSimboli(vector<Simbol>& simboli);

vector<pair<unsigned char,string>>getSimbols( unordered_map<unsigned char,string> codes);
#endif