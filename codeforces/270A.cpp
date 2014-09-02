// 270A
#include <iostream>
#include <cstdio>

using namespace std;

void check(int angle)
{
	int center = 180 - angle;
	if ((360%center) == 0)
		cout << "YES" << endl;
	else
		cout << "NO" << endl;	
}

int main()
{
	int t;
	int angle;
	cin >> t;
	for(int i=0; i < t; i++)
	{
		cin >> angle;
		if ((angle > 0) && (angle < 180))
			check(angle);
		else
			cout << "NO" << endl;
	}
	return 0;
}