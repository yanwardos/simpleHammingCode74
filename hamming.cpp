#include<iostream>
using namespace std;

bool inputValidityCheck(string input);
void hammingParityCheck(string input);
void stringToBits(string input, bool* bitsdata);
string boolToString(bool input);

int main(int argc, char *argv[]){
    string bitPart;

    //input handler
    cout<<"Masukkan 7 bit boolean dalam 1 baris !\n";
    cout<<"Input boolean: ";
    try
    {
        cin>>bitPart;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    cout<<"--------------------\n";
    cout<<"Proses cek: ";

    //input validity check
    if(inputValidityCheck(bitPart)){
        //jika lolos uji validitas, lakukan pengecekan
        hammingParityCheck(bitPart);
        return 0;
    }else{
        cout<<"Input tidak valid\n";
        cout<<"--------------------\n\n";
        return 0;
    }

    return 0;
}


void hammingParityCheck(string input){
    bool bits[input.length()];
    string errorLog = "";

    stringToBits(input, bits);

    //Hamming code metode manual (tanpa metode aljabar linear)
    bool a = bits[0],
        b = bits[1],
        c = bits[2],
        d = bits[3],
        x = bits[4],
        y = bits[5],
        z = bits[6],
        xcek, ycek, zcek;
    
    xcek = !x == (a^b^d);
    ycek = !y == (a^c^d);
    zcek = !z == (b^c^d);

    string state;
    state = boolToString(xcek);
    state += boolToString(ycek);
    state += boolToString(zcek);

    //parity checking dengan meninjau 8 kemungkinan
    if(state=="000"){
        //Semua parity sesuai,
        errorLog = "";
    }else if(state=="001"){
        //parity z tidak sama
        errorLog = "Databit ok | Paritybit z error";
        z = !z;
    }else if(state=="010"){
        //parity y tidak sama
        errorLog = "Databit ok | Paritybit y error";
        y = !y;
    }else if(state=="011"){
        //parity yz tidak sama
        //error di data bit c
        errorLog = "Databit error: bit c";
        c = !c;
    }else if(state=="100"){
        //parity x tidak sama
        errorLog = "Databit ok | Paritybit x error";
        x = !x;
    }else if(state=="101"){
        //parity xz tidak sama
        errorLog = "Databit error: bit b";
        b = !b;
    }else if(state=="110"){
        //parity xy tidak sama
        errorLog = "Databit error: bit a";
        a = !a;
    }else if(state=="111"){
        //parity xyz tidak sama
        errorLog = "Databit error: bit d";
        d = !d;
    }

    //Rearrange Data
    bits[0] = a;
    bits[1] = b;
    bits[2] = c;
    bits[3] = d;
    bits[4] = x;
    bits[5] = y;
    bits[6] = z;

    if(errorLog==""){
        cout<<"Tidak terdapat error!\n";
        cout<<"--------------------\n";
    }else{
        cout<<"Terdapat eror!\n";
        cout<<errorLog<<endl;
        cout<<"Boolean bits diperbaiki\n";
        cout<<"--------------------\n";
    }

    cout<<"Final boolean: \n";
    for(int i=0; i<sizeof(bits); i++){
        cout<<bits[i];
    }

    cout<<endl<<endl;
}

/*
Validity Check, sebelum input diolah, dicek terlebih dahulu validitasnya
*/
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
        return false;
    }
    return true;
}

/*
Fungsi untuk mengkonversi boolean ke string
IS: input parameter berupa sebuah boolean
FS: nilai balik berupa string
*/
string boolToString(bool input){
    if(input) return "1";
    else return "0";
}

/*
Fungsi untuk mengkonversi string ke boolean
IS: input parameter berupa sebuah boolean
FS: nilai balik berupa string
*/
void stringToBits(string input, bool* bitsdata){
    bool* bits;
    bits = bitsdata;

    for(int i=0; i<input.length(); i++){
        if(input.at(i)=='0'){
            bits[i] = 0;
        }else if(input.at(i)=='1'){
            bits[i] = 1;
        }else{
            return ;
        }
    }
}