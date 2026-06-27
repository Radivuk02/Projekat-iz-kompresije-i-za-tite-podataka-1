#include "../headers/sub_fun.h"


void sortSimboli(vector<Simbol>& simboli) {
    for (size_t i = 0; i < simboli.size(); i++) {
        for (size_t j = i + 1; j < simboli.size(); j++) {
            if (simboli[j].prob > simboli[i].prob) {
                Simbol tmp = simboli[i];
                simboli[i] = simboli[j];
                simboli[j] = tmp;
            }
        }
    }
}

vector<pair<unsigned char,string>>getSimbols( unordered_map<unsigned char,string> codes){
        vector<pair<unsigned char,string>> vecCodes;

        for(auto& p:codes){
            vecCodes.push_back(p);
        }
        return vecCodes;
}


