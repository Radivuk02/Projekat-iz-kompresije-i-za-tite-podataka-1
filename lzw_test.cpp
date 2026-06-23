#include "headers/lzw.h"

using namespace std;

int main(){
    string ulaz="Testni string za testiranje testa";
    cout<<"Originalni string:"<<ulaz<<endl;

    auto compres=lzwComp(ulaz);
    cout<<"Kompresovani kodovi:"<<endl;

    for(int code:compres){
        cout<<code<<" ";
    }
    cout<<endl;

    string izlaz=lzwDecomp(compres);
    cout<<"Dekompresovan string:"<<izlaz<<endl;


    if(izlaz==ulaz){
        cout<<"Test uspesan:ulaz i izlaz se poklapaju"<<endl;
    }
    
    else{
        cout<<"Test neuspesan:ulaz i izlaz se ne poklapaju";    
    }
    return 0;
}