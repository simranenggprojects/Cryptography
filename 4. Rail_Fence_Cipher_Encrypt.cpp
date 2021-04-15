/*
Author: SIMRAN
Cipher: Rail Fence Cipher Encryption
*/

#include<iostream>
using namespace std;

string preprocess(string pt){
	string p = "";
	for(int i=0;i<pt.length();i++){
		if (pt[i]!=' '){
			p += toupper(pt[i]);
		}
	}
	return p;
}

string encrypt(string pt){
	string ct = "";
	for(int i=0;i<pt.length();i=i+2)
		ct += pt[i];
	for(int i=1;i<pt.length();i=i+2)
		ct += pt[i];
	return ct;
}

int main()
{
	string pt;
	cout<<"Enter the plaintext: ";
	getline(cin,pt);
	pt = preprocess(pt);
	cout<<encrypt(pt);
}
