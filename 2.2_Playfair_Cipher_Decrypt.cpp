//Author: Simran

#include<iostream>
using namespace std;

struct node{
		int i;
		int j;
};
	
struct node search(char a[5][5],char p)
{
		struct node l;
		for(int u=0;u<5;u++)
		{
			for(int v=0;v<5;v++)
			{
				if(a[u][v]==p)
				{
					l.i = u;
					l.j = v;
					return l;
				}
			}
		}
}

string decryption(string ct,string key)
{
	//step1: creation of 5x5 playfair matrix
	char a[5][5];
	bool visited[26]={0};
	
	int p=0,q=0;
	//step1.1: creating matrix for keyword
	for(int i=0;i<key.length();i++)
	{
		if(visited[key[i]-65]==0)
		{
			a[p][q] = key[i];
			visited[key[i]-65] = 1;
			if(q+1 < 5)
				q++;
			else{
				p++;
				q=0;
			}
		}
	}
	//step1.2: creating matrix for leftover words
	for(char t='A';t<='Z';t++)
	{
		if(t!='J'){
			if(visited[t-65]==0)
			{
				a[p][q] = t;
				visited[t-65] = 1;
				if(q+1 < 5)
					q++;
				else
				{
					q=0;
					p++;
				}
			}
		}
	}
	
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//step2: decrypt the cipher text
	string pt = "";
	
	for(int r=0;r<ct.length();r=r+2)
	{
		struct node x = search(a,ct[r]);
		struct node y = search(a,ct[r+1]);
		// if same row
		if (x.i == y.i)
		{
			pt = pt + a[x.i][(5+((x.j)-1))%5];
			pt = pt + a[y.i][(5+((y.j)-1))%5];
		}
		// if same col
		else if (x.j == y.j)
		{
			pt = pt + a[(5+((x.i)-1))%5][x.j];
			pt = pt + a[(5+((y.i)-1))%5][y.j];
		}
		// diagonal
		else
		{
			pt = pt + a[x.i][y.j];
			pt = pt + a[y.i][x.j];
		}
	}
	//step3: return plain text
	return pt;
}

string keypreprocess(string k)
{
	string key = "";
	for(int i=0;i<k.length();i++)
	{
		if(k[i]!=' ')
		{
			if(toupper(k[i])=='J')
				key += 'I';
			else
				key += toupper(k[i]);	
		}	
	}
	return key;
}

int main()
{
	string ct,key;
	cout<<"Enter cipher text: ";
	getline(cin,ct);
	cout<<"Enter key: ";
	getline(cin,key);
	key = keypreprocess(key);
	cout<<ct<<" "<<key<<endl;
	cout<<decryption(ct,key);
}
