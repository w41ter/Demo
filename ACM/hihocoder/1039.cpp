#include <iostream>
#include<string>
#include<vector>
using namespace std;

string GetString(const string& str)
{
	int len=str.size();
	if(len<=1)
		return str;
	vector<char> v;
	
	for(int i=0;i+1<len;++i)
	{
		if(str[i]==str[i+1])
		{
			while(i+1<len&&str[i]==str[i+1])
				++i;
		}
		else
			v.push_back(str[i]);
	}
	//最后一个元素
	if(str[len-2]!=str[len-1])
		v.push_back(str[len-1]);


		return string(v.begin(),v.end());
}
int main()
{
	int n;
	string s;
	cin>>n;
	string Insert="ABC";
	while(n--)
	{
		cin>>s;
		int max=s.size();
		//s=GetString(s);
		int min=s.size();
		/*
		while(min>GetString(s).size())
		{
			s=GetString(s);
			min=s.size();
		}
		*/
		string test;
		for(int i=0;i<s.size();++i)
		{
			for(int j=0;j<3;++j)
			{
				string str=s.substr(0,i+1)+Insert[j]+s.substr(i+1);
				int len=str.size();
				while(len>(str=GetString(str)).size())
				{
					len=str.size();
					test=str;
				}
				if(min>str.size())
					min=str.size();
			}
		}
		
		cout<<max-min+1<<endl;

	}
		
		return 0;
}