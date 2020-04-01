#include<iostream>
using namespace std;

bool inputValidityCheck(string input);
void hammingParityCheck(string input);
bool *stringToBits(string input, bool* bitsdata);
int main(){
    string bitPart;

    //input handler
    cout<<"Masukkan 7 bit boolean dalam 1 baris !\n";
    cout<<"Bits: ";
    cin>>bitPart;

    //input validity check
    if(inputValidityCheck(bitPart)){

    }else{
        cout<<"Input tidak valid\n";
        return 0;
    }

    //paritycheck
    hammingParityCheck(bitPart);
    return 0;
}

bool inputValidityCheck(string input){
    if(input.length()==7){
        for(int i=0; i<7; i++){
            if(!(input.at(i)=='1' || input.at(i)=='0')){
                cout<<"Terdapat karakter yang salah\n";
                return false;
            }
        }
    }else{
        cout<<"Panjang input tidak 7 bit\n";
    }
    return true;
}

void hammingParityCheck(string input){
    bool bits[input.length()];
    bool error = false;

    stringToBits(input, bits);

    for(int i=0; i<sizeof(bits); i++){
        cout<<bits[i]<<endl;
    }

    bool d1 = bits[0],
        d2 = bits[1],
        d3 = bits[2],
        d4 = bits[3],
        p1 = bits[4],
        p2 = bits[5],
        p3 = bits[6];

    error = !((p1 == d1^d2^d4) &&
            (p2 == d1^d3^d4) &&
            (p3 == d2^d3^d4));

    if(!error){
        cout<<"Tidak ada data error\n";
    }else{
        cout<<"Ada data error\n";
    }
}

bool *stringToBits(string input, bool* bitsdata){
    bool* bits;
    bits = bitsdata;

    for(int i=0; i<input.length(); i++){
        if(input.at(i)=='0'){
            bits[i] = 0;
        }else if(input.at(i)=='1'){
            bits[i] = 1;
        }else{
            return NULL;
        }
    }

    return bits;
}