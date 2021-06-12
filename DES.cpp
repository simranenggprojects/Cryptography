/*
Author: Simran
Note: Input must be in binary 
Key size must be 64 bits
Plaintext must be 64 bits
*/

#include<iostream>
#include<string>
#include<cmath>
#include<sstream>
using namespace std;

// global variables
string keys[16];

string pc1(string key){
	int pc1_mat[56] = { 57, 49, 41, 33, 25, 17, 9,
                     	1, 58, 50, 42, 34, 26, 18,
                     	10, 2, 59, 51, 43, 35, 27,
                     	19, 11, 3, 60, 52, 44, 36,
                     	63, 55, 47, 39, 31, 23, 15,
                     	7, 62, 54, 46, 38, 30, 22,
                     	14, 6, 61, 53, 45, 37, 29,
                     	21, 13, 5, 28, 20, 12, 4 };
    string k = ""; 
    for(int i=0;i<56;i++){
    	k += key[pc1_mat[i]-1];
	}
	return k;
}

string lshift(string key, int shift_val){
	return key.substr(shift_val,key.length()-shift_val) + key.substr(0,shift_val);
}

void generate1_keys(string key){
	int lshift_val[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	string left = key.substr(0, 28);
    string right = key.substr(28, 28);
    for(int i=0;i<16;i++){
    	left = lshift(left,lshift_val[i]);
		right = lshift(right,lshift_val[i]);
    	keys[i] = left + right;
	}
}

string pc2_compute(string key){
	int pc2[48] = { 14, 17, 11, 24, 1, 5,
                    3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32 };
    string k = "";
    for(int i=0;i<48;i++){
    	k += key[pc2[i]-1];
	}
	return k;
}

void generate2_keys(){
    for(int i=0;i<16;i++){
    	keys[i] = pc2_compute(keys[i]);
	}
}

string expansion(string r){
	int exp[48] = { 32, 1, 2, 3, 4, 5, 
					4, 5, 6, 7, 8, 9, 
					8, 9, 10, 11, 12, 13, 
					12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21, 
					20, 21, 22, 23, 24, 25, 
					24, 25, 26, 27, 28, 29, 
					28, 29, 30, 31, 32, 1 };
	string t = "";
	for(int i=0;i<48;i++){
		t += r[exp[i]-1];
	}
	return t;
}

char xored(char a, char b){
	if(a=='0' && b=='0')
		return '0';
	else if(a=='0' && b=='1')
		return '1';
	else if(a=='1' && b=='0')
		return '1';
	else
		return '0';
}

string xoring(string a, string b){
	string c = "";
	for(int i=0;i<a.length();i++){
		c += xored(a[i],b[i]);
	}
	return c;
}

int d2b1(string k){
	if (k=="00")
		return 0;
	else if(k=="01")
		return 1;
	else if(k=="10")
		return 2;
	else 
		return 3;
}

int d2b2(string k){
	if(k=="0000")
		return 0;
	else if(k=="0001")
		return 1;
	else if(k=="0010")
		return 2;
	else if(k=="0011")
		return 3;
	else if(k=="0100")
		return 4;
	else if(k=="0101")
		return 5;
	else if(k=="0110")
		return 6;
	else if(k=="0111")
		return 7;
	else if(k=="1000")
		return 8;
	else if(k=="1001")
		return 9;
	else if(k=="1010")
		return 10;
	else if(k=="1011")
		return 11;
	else if(k=="1100")
		return 12;
	else if(k=="1101")
		return 13;
	else if(k=="1110")
		return 14;
	else
		return 15;
}

string sbox(string p){
	int s[8][4][16]=
    {{
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
        0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
        4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
        15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
    },
    {
        15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
        3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
        0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
        13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
    },


    {
        10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
        13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
        13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
        1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
    },
    {
        7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
        13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
        10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
        3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
    },
    {
        2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
        14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
        4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
        11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
    },
    {
        12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
        10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
        9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
        4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
    },
    {
        4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
        13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
        1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
        6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
    },
    {
        13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
        1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
        7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
        2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    }};
    
    string c;
    int round = 0;
    for(int i=0;i<=42;i+=6){
    	string temp1 = "";
    	string temp2 = "";
    	temp1 += p[i];
    	temp1 += p[i+5];
		temp2 += p[i+1];
		temp2 += p[i+2];
		temp2 += p[i+3];
		temp2 += p[i+4];
    	int row = d2b1(temp1);
    	int col = d2b2(temp2);
    	int n = s[round][row][col];
	    unsigned int num = 0;
	    for(int i=0;n > 0;i++)
	    {
	        num += n % 2 *  pow(10,i);
	        n = n/2;
	    }
	    string tt;
	    stringstream ss;  
  		ss << num;  
  		ss >> tt;
  		int l = 4 - tt.length();
  		for(int k=0;k<l;k++)
  			c += '0';
  		c += tt;
    	round++;	
	}
    return c;
}

string initial_permutation(string pt){
	string p = "";
	int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };
    for(int i=0;i<64;i++)
    	p += pt[initial_perm[i]-1];
    return p;
}

string permutation_func(string r){
	int per[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };
    string p = "";
    for(int i=0;i<32;i++)
    	p += r[per[i]-1];
    return p;
}

string ip_inverse(string c){
	string ct = "";
	int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                           39, 7, 47, 15, 55, 23, 63, 31,
                           38, 6, 46, 14, 54, 22, 62, 30,
                           37, 5, 45, 13, 53, 21, 61, 29,
                           36, 4, 44, 12, 52, 20, 60, 28,
                           35, 3, 43, 11, 51, 19, 59, 27,
                           34, 2, 42, 10, 50, 18, 58, 26,
                           33, 1, 41, 9, 49, 17, 57, 25 };
    for(int i=0;i<64;i++)
    	ct += c[final_perm[i]-1];
    return ct;
}

string des_encrypt(string pt){
	string c = "";
	string l = pt.substr(0,32);
	string r = pt.substr(32,32);
	for(int i=0;i<16;i++)
	{
		string lnext = r;
		string rnext;
		r = expansion(r);
		r = xoring(r,keys[i]);
		r = sbox(r);
		r = permutation_func(r);
		rnext = xoring(l,r);
		l = lnext;
		r = rnext;
	}
	
	//32 bit swap
	c += r;
	c += l;
	
	//IP Inverse
	c = ip_inverse(c);
	return c;
}

int main(){
	string pt = "0000000100100011010001010110011110001001101010111100110111101111";
	string key = "0001001100110100010101110111100110011011101111001101111111110001";
	
	//generate pc1 - to reduce keysize from 64 bits to 56 bits
	key = pc1(key);

	//key generation for 16 rounds
	generate1_keys(key); //left shift on keys
	generate2_keys();    //convert 56 bits to 48 bits
	
	pt = initial_permutation(pt); //Initial Permutation
	string ct1 = des_encrypt(pt);
	cout<<"Cipher text after DES1: "<<ct1<<endl;
	
	string key2 = "1111001100110100010101110111100110011011101111001100000111110001";
	
	//generate pc1 - to reduce keysize from 64 bits to 56 bits
	key2 = pc1(key2);

	//key generation for 16 rounds
	generate1_keys(key2); //left shift on keys
	generate2_keys();    //convert 56 bits to 48 bits
	
	ct1 = initial_permutation(ct1); //Initial Perumtation
	string ct2 = des_encrypt(ct1);
	cout<<"Cipher text after DES2: "<<ct2<<endl;
	
	string key3 = "1111001100100100010101110001000110011011101111001100000111110001";
	
	//generate pc1 - to reduce keysize from 64 bits to 56 bits
	key3 = pc1(key3);

	//key generation for 16 rounds
	generate1_keys(key3); //left shift on keys
	generate2_keys();    //convert 56 bits to 48 bits
	
	ct2 = initial_permutation(ct2); //Initial Permutation
	string ct3 = des_encrypt(ct2);
	cout<<"Cipher text after DES3: "<<ct3<<endl;
}
