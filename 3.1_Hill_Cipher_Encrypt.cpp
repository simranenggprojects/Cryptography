// Author: Simran
// filler alphabet: X
// every letter will be converted to uppercase 
// and result will also be in uppercase
// if key isnt perfect square, key is wrapped
// e.g. key = ast --> transformed key --> asta

#include<bits/stdc++.h>
using namespace std;

string keypreprocess(string key)
{
	// we need to check if it's a perfect square
	// if it's a perfect square, no preprocessing
	// else preprocessing
	int count = sqrt(key.length());
	if (count == sqrt(key.length()))
		return key;
	else
	{
		// matrix will be of (count + 1) x (count + 1)
		// extra letters: (count + 1)*(count + 1) - key.length()
		string k = key;
		for(int i=0;i<(count + 1)*(count + 1) - key.length();i++)
			k += key[i];
		return k;
	}
}

string uppercase(string k)
{
	string newk = "";
	for(int i=0;i<k.length();i++)
		newk += toupper(k[i]);
	return newk;
}

string ptpreprocess(string p,string k)
{
	string pt = "";
	// firstly we need to remove spaces
	for(int i=0;i<p.length();i++)
	{
		if(p[i]!=' ')
			pt += p[i];
	}
	int length = int(sqrt(k.length()));
	int var = pt.length() % length;
	for(int i=1;i<=var;i++)
		pt += 'X';
	return pt;
}

int main()
{
	string pt, key;
	cout<<"Enter plain text: ";
	getline(cin,pt);
	cout<<"Enter key: ";
	getline(cin,key);
	key = keypreprocess(key);
	// convert key and plain text to upper case
	key = uppercase(key);
	pt = uppercase(pt);
	pt = ptpreprocess(pt,key);
	
	// create matrix for key
	int a[int(sqrt(key.length()))][int(sqrt(key.length()))];
	int p = 0, q = 0;
	for(int i=0;i<key.length();i++)
	{
		a[p][q] = key[i]-65;
		if(q+1 < int(sqrt(key.length())))
			q++;
		else{
			p++;
			q = 0;
		}
	}
	
	//encrypt plain text
	// 1. make matrix for plain text
	int cols = int(sqrt(key.length()));
	int rows = pt.length() / cols;
	int pt_matrix[rows][cols] = {0};
	int index = 0;
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			pt_matrix[i][j] = pt[index++]-65;
	}
	
	// 2. matrix multiplication of pt matrix and key matrix
	int ct_matrix[rows][cols] = {0};
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
		{
			for(int k=0;k<cols;k++)
			{
				ct_matrix[i][j] += pt_matrix[i][k] * a[k][j];
			}
			ct_matrix[i][j] %= 26;
		}
	}
	
	// 3. display cipher text
	cout<<"\nCipher text is: ";
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			cout<<char(ct_matrix[i][j]+65);
	}
	
}
