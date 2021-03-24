// Author: Simran

#include<iostream>
using namespace std;

string encryption(string s,int key)
{
	string result = "";
	for(int i=0;i<s.length();i++)
	{
		if(isupper(s[i]))
			result = result + char((int(s[i])+key-65)%26 + 65);
		else
			result = result + char((int(s[i])+key-97)%26 + 97);
	}
	return result;
}

int main()
{
	string s;
	cout<<"Enter the text to be encrypted (plain text): ";
	getline(cin,s);
	
	int key;
	cout<<"Enter key (for instance 3 or -3): ";
	cin>>key;
	
	cout<<"Cipher Text (Encrypted Text): "<<encryption(s,key%26); // s b/w 0-25
	
	string str; int k;
	cout<<"\nEnter text to be decrypted (cipher text): ";
	cin.ignore(); getline(cin,str);
	cout<<"Enter key (for instance 3 or -3): ";
	cin>>k;
	cout<<"Plain Text (Decrypted Text): "<<encryption(str,26 - (k%26));
	
	return 0;
}
