#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	string s;
	priority_queue<pair<ll,string>> q;
	
	while(cin >> s)
	{
		if(s == "V")
		{
			if(!q.empty())
			{
				pair<ll,string> p = q.top();
				q.pop();
				cout << p.second << endl;
			}
			else
				cout << endl;
		}
		else
		{
			ll n;
			cin >> n;
			q.push(pair<ll,string>(n,s));
		}	
	}
	
	return 0;
}
