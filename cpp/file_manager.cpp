#include "../headers/file_manager.h"

vector<unsigned char> FileManager::readFile(const string& filename)
{
    ifstream file(filename,ios::binary);
    return vector<unsigned char>((istreambuf_iterator<char>(file)),(istreambuf_iterator<char>()));
}


void FileManager::writeBin(const string& filename,const vector<unsigned char>&data){
    ofstream file(filename,ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()),data.size());
}

void FileManager::writeText(const string& filename,const string& data){
    ofstream file(filename);
    file<<data;
}

void FileManager::writeCodes(const string& filename,const vector<pair<unsigned char,string>>&codes){
    ofstream file(filename);
    for(auto c:codes){
        file<<(int)c.first<<" : "<<c.second<< "\n";
    }
}

bool FileManager::compareFiles(const string& file1,const string& file2){
    auto f1=readFile(file1);
    auto f2=readFile(file2);
    return f1==f2;
}

void FileManager::writeReport(const string& text){
        ofstream report("report.txt",ios::app);
        report<<text<<"\n";
}   

void FileManager::writeMeta(const string& filename, size_t x){
    ofstream file(filename);
    file<<x;
}

size_t FileManager::readMeta(const string& filename){
    ifstream file(filename);
    size_t x;
    file>>x;
    return x;
}