#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
using namespace std;

class FileManager{
    public:
    static vector<unsigned char> readFile(const string& fileName);
    static void writeBin(const string& filename,const vector<unsigned char>&data );
    static void writeText(const string& filename,const string& data);
    static void writeCodes(const string& filename,const vector<pair<unsigned char,string>>& codes);
    static bool compareFiles(const string &file1,const string& file2);

};
#endif