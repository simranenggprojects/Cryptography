/*
Author: SIMRAN
Cipher: Row Transposition Cipher Encryption
Filler Alphabet: X
Assumption: Key is filled in correct manner
*/

#include<iostream>
#include<cmath>
using namespace std;

string preprocess(string pt, unsigned short int max){
	string p = "";
	for(int i=0;i<pt.length();i++){
		if(pt[i]!=' ')
			p += toupper(pt[i]);
	}
	float l = p.length()/(max+0.0);
	if (floor(l) == ceil(l))
		return p;
	else{
		int x = max * ceil(l) - p.length();
		for(int i=0;i<x;i++)
			p += 'X';
		return p;
	}
}

string encrypt(string pt,unsigned short int key[], int size, unsigned short int max){
	char a[pt.length()/max][max];
	int m=0,n=0;
	for(int i=0;i<pt.length();i++){
		a[m][n] = pt[i];
		if(n+1 < max)
			n++;
		else{
			m++;
			n = 0;
		}
	}
	string ct = "";
	for(int i=0;i<size;i++){
		for(int k=0;k<pt.length()/max;k++){
			ct += a[k][key[i]-1];
		}
	}
	return ct;
}

int main()
{
	string pt; unsigned short int size;
	cout<<"Enter the plaintext: ";
	getline(cin,pt);
	cout<<"Enter size of key: ";
	cin>>size;
	unsigned short int key[size];
	cout<<"Enter key with spaces eg if key is 123 enter 1 2 3: ";
	for(int i=0;i<size;i++)
		cin>>key[i];
	unsigned short int max = size;	
	pt = preprocess(pt,max);
	cout<<"Encrypted text: "<<encrypt(pt,key,size,max);
}
