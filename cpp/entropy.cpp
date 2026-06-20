#include "../headers/entropy.h"
double calculate(const string& filename)
{
    ifstream file(filename, ios::binary);
    if(!file.is_open()){
        throw runtime_error("Fajl se ne moze otvoriti");
    }

    vector<unsigned long long> freq(256,0);
    unsigned long long ukupno=0;
    unsigned char byte;

    while(file.read(reinterpret_cast<char *>(&byte),1)){
        freq[byte]++;
        ukupno++;
    }

    double entropy=0.0;
    for(int i=0;i<256;i++){
        if(freq[i]>0){
            double p=static_cast<double>(freq[i]/ukupno);
            entropy=entropy-(p*log2(p));
        }
    }
    return entropy;
}