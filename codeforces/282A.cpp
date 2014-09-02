// 282 A
#include <iostream>
#include <cstdio>
using namespace std;

int check(char i)
{
	// cout << i << endl;
	if (i == '+')
		return 1;
	else if (i == '-')
		return -1;
	else
		return 0;
}

int main()
{
	int n;
	string inp;
	int val=0;
	cin >> n;
	for(int i=0; i<n; i++)
	{
		cin >> inp;
		if(inp[0]=='X')
			val += check(inp[1]);
		else {
			// cout << "check1 " << inp[0] << endl;
			val += check(inp[0]);
		}
			
	}
	cout << val << endl;
	return 0;
}