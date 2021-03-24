//Author: Simran

// NOTE: Instead of I, there is J
// Output will always be in uppercase
// Filler alphabet: X

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

string encryption(string pt,string key)
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
	
	//step2: encrypt the plain text
	string ct = "";
	
	for(int r=0;r<pt.length();r=r+2)
	{
		struct node x = search(a,pt[r]);
		struct node y = search(a,pt[r+1]);
		// if same row
		if (x.i == y.i)
		{
			ct = ct + a[x.i][((x.j)+1)%5];
			ct = ct + a[y.i][((y.j)+1)%5];
		}
		// if same col
		else if (x.j == y.j)
		{
			ct = ct + a[((x.i)+1)%5][x.j];
			ct = ct + a[((y.i)+1)%5][y.j];
		}
		// diagonal
		else
		{
			ct = ct + a[x.i][y.j];
			ct = ct + a[y.i][x.j];
		}
	}
	//step3: return cipher text
	return ct;
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

string ptpreprocess(string p)
{
	string pt = "", pp = "";
	
	//removing space & replace J with I
	for(int i=0;i<p.length();i++)
	{
		if(toupper(p[i])=='J')
			pp += 'I';
		else if(p[i]!=' ')
			pp += p[i]; 
	}
	for(int i=0;i<pp.length();i+=2)
	{
		if(pp[i]==pp[i+1]){
			pt += toupper(pp[i]);
			pt += 'X';
			i--;
		}
		else{
				if(i==pp.length()-1)
				{
					pt += toupper(pp[i]);
					pt += 'X';
				}
				else{
					pt += toupper(pp[i]);
					pt += toupper(pp[i+1]);
				}
		}
	}
	return pt;
}

int main()
{
	string pt,key;
	cout<<"Enter plain text: ";
	getline(cin,pt);
	cout<<"Enter key: ";
	getline(cin,key);
	pt = ptpreprocess(pt);
	key = keypreprocess(key);
	cout<<pt<<" "<<key<<endl;
	cout<<encryption(pt,key);
}
