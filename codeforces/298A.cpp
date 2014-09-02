// 298 A
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int n;
	cin >> n;
	string s;
	cin >> s;

	int l, r, start = 0, end =0;
	bool check = false;
	for(int i=0; i < n; i++)
	{
		if(s[i] == '.') {
			if (check) {
				r = i - 1;
				break;
			}
		}
		else if (!check) {
			l = i;
			check = true;
		}
	}
	if (s[l] == 'R')
	{
		start = l;
		if (s[r] == 'R') 
		{
			end = r + 1;
			cout << start + 1<< " " << end + 1<< endl;
		} else {
			int i = l;
			for(;i<=r;i++)
			{
				if (s[i] == 'L') {
					end = i - 1;
					break;
				}
			}
			cout << start + 1<< " " << end + 1<< endl;
		}
	} else if (s[l] == 'L') {
		start = r;
		end = l;
		cout << start + 1<< " " << end<< endl;
	}
	return 0;
}