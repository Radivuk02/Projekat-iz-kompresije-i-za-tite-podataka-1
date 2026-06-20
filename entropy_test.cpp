#include<iostream>
#include "headers/entropy.h"
using namespace std;

int main(){
    try{
        string filename="bin/entropy.bin";
        double H=calculate(filename);
        cout<<"Entropija fajla:"<<H<<"bita po simbolu"<<endl;
    }
    catch(const exception& e){
        cout<<"Greska:"<<e.what()<<endl;
    }
}