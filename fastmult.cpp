/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Olof Persson
 * Version     : 1.0
 * Date        : 11/26/2022
 * Description : Implementation of Karatsuba Fast Multiplication Algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

/**
 * method that makes sure the two strings are the same length by padding the front with 0's and then returns their length
 */
int shiftlength(string& alocal, string& blocal){
    int len = alocal.length();
    int lenb = blocal.length();
    if(len > lenb){
        for(int i = 0; i < int(len - lenb); i++){
            blocal.insert(0,"0");
        }
        return len;
    }else{
      for(int i = 0; i < int(lenb - len); i++){
            alocal.insert(0,"0");
        }  
        return lenb;
    }
}
/**
 * the function that adds two integers that are string types
 */
string add(const string& a, const string& b){
    string temp = "";
    int carrynum = 1;
    string alocal = a;
    string blocal = b;
    bool carry = false;
    shiftlength(alocal,blocal);
    for(int i = alocal.length()-1; i >= 0; i--){
        if(carry){
            int add = int(alocal[i])%48 + int(blocal[i])%48 + carrynum;
            if(add >= 10){
                temp.insert(0,to_string(add - 10));
                carry = true;
            }else{
                temp.insert(0,to_string(add));
                carry = false;
            }
        }else{
            int add = int(alocal[i])%48 + int(blocal[i])%48;
            if(add >= 10){
                temp.insert(0,to_string(add - 10));
                carry = true;
            }else{
                temp.insert(0,to_string(add));
                carry = false;
            }
        }
    }
    if(carry){
        temp.insert(0,"1");
    }
    return temp;
}
/**
 * the function that subtracts two integers that are string types
 */
string sub(const string& a, const string& b){
    string temp = "";
    string alocal = a;
    string blocal = b;
    shiftlength(alocal,blocal);
    for(int i = alocal.length()-1; i >= 0; i--){
        int sub = int(alocal[i])%48 - int(blocal[i])%48;
        if(sub < 0){
            int carrier = 0;
            for(int j = i-1; j >= 0; j--){
                if(alocal[j] != '0'){
                    carrier = j;
                    break;
                }
            }
            alocal.replace(carrier, 1, to_string(int(a[carrier]-1)%48));
            for(int k = carrier+1; k < i; k++){
                alocal.replace(k, 1,"9");
            }
            temp.insert(0,to_string(sub + 10));
        }else{
            temp.insert(0,to_string(sub));
        }
    }
    return temp;
}
/**
 * the function that multiplys string a by 10^b (10 to the power of b) 
 */
string mult(const string& a, const string& b){
    string temp = a;
    for(int i = 0; i < stoi(b); i++){
        temp.append("0");
    }
    return temp;
}
/**
 * this is the implementation of the Karatsuba fast multiplication algorithm
 */
string karatsuba(string& a, string& b){
    int len = shiftlength(a, b);
    if(a.length() == 1 && b.length() == 1){
        return to_string((int(a[0])%48) * (int(b[0])%48));
    }
    int half = len/2;   
    int half2 = (len-half);
    string ahalf = a.substr(0, half);
    string ahalf2 = a.substr(half, half2);
    string bhalf = b.substr(0, half);
    string bhalf2 = b.substr(half, half2);
    string big = karatsuba(ahalf,bhalf);
    string mid = karatsuba(ahalf2, bhalf2);
    string firstadd = add(ahalf,ahalf2);
    string secondadd = add(bhalf, bhalf2);
    string small = karatsuba(firstadd,secondadd);
    string term1 = mult(big, to_string(2*half2));
    string term2 = mult(sub(sub(small,big),mid),to_string(half2));
    return add(add(term1, term2),mid);
}

int main(int argc, char * argv[]){
    string intone = argv[1];
    string inttwo = argv[2];
    shiftlength(intone,inttwo);
    string output = karatsuba(intone, inttwo);
    int i = 0;
    //takes away the leading zeros in the string returned from karatsuba
    while (output[i] == '0'){
        output.replace(i,1,"");
    }
    cout << output << endl;
    return 0;

}