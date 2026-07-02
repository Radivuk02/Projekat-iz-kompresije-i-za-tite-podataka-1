#include <iostream>
#include "headers/file_manager.h"
#include "headers/entropy.h"
#include "headers/sha_fanno.h"
#include "headers/huffman.h"
#include "headers/lz77.h"
#include "headers/lzw.h"
#include "headers/sub_fun.h"
#include <fstream>
using namespace std;

int main() {
    ofstream clearReport("report.txt", ios::trunc);
    clearReport.close();

    string ulazni = "bin/ulaz.bin";
    auto data = FileManager::readFile(ulazni);

    string poruka = "Ulazni fajl: " + ulazni + " (" + to_string(data.size()) + " bajtova)\n";
    cout << poruka;
    FileManager::writeReport(poruka);

    double H = calculate(ulazni);
    poruka = "Entropija ulaznog fajla: " + to_string(H) + " bita po bajtu\n";
    cout << poruka;
    FileManager::writeReport(poruka);

    unordered_map<unsigned char,int> freq;
    for(auto b:data) freq[b]++;

    vector<Simbol> simboli;
    for(auto& p:freq)
        simboli.push_back({p.first,(double)p.second/data.size()});

    sortSimboli(simboli);
    unordered_map<unsigned char,string> sfCodes;
    shaFanno(simboli,0,simboli.size()-1,sfCodes,"");

    vector<pair<unsigned char,string>> codesVec = getSimbols(sfCodes);
    FileManager::writeCodes("codes/sha_fanno_codes.txt", codesVec);
    size_t validBits;
    auto sfC = sfComp(data, sfCodes,validBits);
    FileManager::writeBin("compress/sf.bin", sfC);
    FileManager::writeMeta("meta/sf.txt",validBits);
    validBits=FileManager::readMeta("meta/sf.txt");
    auto sfDC = sfDecomp(sfC, sfCodes,validBits);
    FileManager::writeBin("decompress/sf.bin", sfDC);

    if (FileManager::compareFiles(ulazni, "decompress/sf.bin")) {
        cout << "Shannon–Fano uspešan" << endl;
        FileManager::writeReport("Shannon–Fano uspešan\n");
    } else {
        cout << "Shannon–Fano neuspešan" << endl;
        FileManager::writeReport("Shannon–Fano neuspešan\n");
    }

    auto huffCodes = huffEncode(freq);
    codesVec.clear();
    codesVec = getSimbols(huffCodes);
    FileManager::writeCodes("codes/huff_codes.txt", codesVec);

    size_t bitCount;
    auto huffComp = huffCompress(data, huffCodes, bitCount);
    FileManager::writeBin("compress/huff.bin", huffComp);

    ofstream meta("meta/huff.txt");
    meta << bitCount;
    meta.close();

    ifstream metaIn("meta/huff.txt");
    size_t bitCountRead;
    metaIn >> bitCountRead;
    metaIn.close();

    auto huffDecomp = huffmanDecomp(huffComp, huffCodes, bitCountRead);
    FileManager::writeBin("decompress/huff.bin", huffDecomp);

    string inputStr(data.begin(), data.end());
    auto lz77comp = lzComp(inputStr, 1024);
    auto lz77Bytes = lz77serial(lz77comp);
    FileManager::writeBin("compress/lz77.bin", lz77Bytes);
    auto lz77R = FileManager::readFile("compress/lz77.bin");
    auto tokens = lz77deserial(lz77R);
    auto lz77decomp = lzDecomp(tokens);
    FileManager::writeBin("decompress/lz77.bin",vector<unsigned char>(lz77decomp.begin(), lz77decomp.end()));

    if (lz77decomp == inputStr) {
        cout << "LZ77 uspešan" << endl;
        FileManager::writeReport("LZ77 uspešan\n");
    } 
    else {
        cout << "LZ77 neuspešan" << endl;
        FileManager::writeReport("LZ77 neuspešan\n");
    }

    auto wComp = lzwComp(inputStr);
    vector<unsigned char>wcompBytes(wComp.begin(),wComp.end());
    FileManager::writeBin("compress/lzw.bin", wcompBytes);
    string wDecomp = lzwDecomp(wComp);
    FileManager::writeText("decompress/lzw.bin", wDecomp);
    if(wDecomp == inputStr) {
        cout << "LZW uspešan" << endl;
        FileManager::writeReport("LZW uspešan\n");
    } else {
        cout << "LZW neuspešan" << endl;
        FileManager::writeReport("LZW neuspešan\n");
    }

    return 0;
}