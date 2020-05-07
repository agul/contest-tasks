#pragma comment(linker, "/STACK:66777216")

#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

#ifdef _MSC_VER
#include <intrin.h>

#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#define ll int64_t

#ifdef _MSC_VER

#endif

using namespace std;

void solve(istream& in, ostream& out) {
	int c;
	in >> c;
	for (int ii = 0; ii < c; ii++)
	{
		ll n, t;
		in >> n >> t;
		vector< vector<int> > time(n, vector<int>(5, 0));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				in >> time[i][j];
			}
		}
		vector<ll>db(n, 1000001);
		vector<ll>de(n, 1000001);
//		vector<char>db(n, 'F');
//		vector<char>de(n, 'F');
		db[0] = 1000001;
		de[0] = time[0][0];
		string ans1(n, 'F'), ans2(n, 'F');
		int f1 = 1, f2 = 1;
		for (int i = 1; i < n; i++)
		{
			if (db[i - 1] + time[i - 1][1]<de[i - 1] + time[i - 1][3])
			{
				db[i] = db[i - 1] + time[i - 1][1];
			}
			else
			{
				db[i] = de[i - 1] + time[i - 1][3];
			}
			if (db[i - 1] + time[i - 1][2]<de[i - 1] + time[i - 1][4])
			{
				de[i] = db[i - 1] + time[i - 1][2];
			}
			else
			{
				de[i] = de[i - 1] + time[i - 1][4];
			}
			ll tr=db[i];
			db[i] = de[i] + time[i][0];
			de[i] = tr + time[i][0];
			if (db[i]>t &&de[i]>t)
			{
				f1 = 0;
				break;
			}
		}
		ll answer1;
		if (f1)
		{
			if (db[n-1]+time[n-1][1]<de[n - 1] + time[n - 1][3])
			{
				if (db[n - 1] + time[n - 1][1]>t)
				{
					f1 = 0;
				}
				else
				{
					answer1 = db[n - 1] + time[n - 1][1];
					ans1[n - 1] = 'B';
				}
			}
			else
			{
				if (de[n - 1] + time[n - 1][3]>t)
				{
					f1 = 0;
				}
				else
				{
					answer1 = de[n - 1] + time[n - 1][3];
				}
			}
			if (f1==1)
			{
				for (int i = n - 2; i >= 0; i--)
				{
					if (ans1[i + 1] == 'B')
					{
						ll a = db[i + 1] - time[i + 1][0];
						if (a == db[i] + time[i][2])
						{
							ans1[i] = 'B';
						}
					}
					else
					{
						ll a = de[i + 1] - time[i + 1][0];
						if (a == db[i] + time[i][1])
						{
							ans1[i] = 'B';
						}
					}
				}
				t = answer1;
			}
		}
		db[0] = time[0][0];
		de[0] = 1000001;
		ans2[0] = 'B';
		for (int i = 1; i < n; i++)
		{
			if (db[i - 1] + time[i - 1][1]<de[i - 1] + time[i - 1][3])
			{
				db[i] = db[i - 1] + time[i - 1][1];
			}
			else
			{
				db[i] = de[i - 1] + time[i - 1][3];
			}
			if (db[i - 1] + time[i - 1][2]<de[i - 1] + time[i - 1][4])
			{
				de[i] = db[i - 1] + time[i - 1][2];
			}
			else
			{
				de[i] = de[i - 1] + time[i - 1][4];
			}
			ll tr = db[i];
			db[i] = de[i] + time[i][0];
			de[i] = tr + time[i][0];
			if (db[i]>t &&de[i]>t)
			{
				f2 = 0;
				break;
			}
		}
		ll answer2;
		if (f2)
		{
			if (db[n - 1] + time[n - 1][2]<de[n - 1] + time[n - 1][4])
			{
				if (db[n - 1] + time[n - 1][2]>t)
				{
					f2 = 0;
				}
				else
				{
					answer2 = db[n - 1] + time[n - 1][2];
					ans2[n - 1] = 'B';
				}
			}
			else
			{
				if (de[n - 1] + time[n - 1][4]>t)
				{
					f2 = 0;
				}
				else
				{
					answer2 = de[n - 1] + time[n - 1][4];
				}
			}
			if (f2==1)
			{
				for (int i = n - 2; i >= 0; i--)
				{
					if (ans2[i + 1] == 'B')
					{
						ll a = db[i + 1] - time[i + 1][0];
						if (a == db[i] + time[i][2])
						{
							ans2[i] = 'B';
						}
					}
					else
					{
						ll a = de[i + 1] - time[i + 1][0];
						if (a == db[i] + time[i][1])
						{
							ans2[i] = 'B';
						}
					}
				}
			}
		}
		if (f2)
		{
			out << ans2 << endl;
			continue;
		}
		if (f1)
		{
			out << ans1 << endl;
			continue;
		}
		out << "IMPOSSIBLE" << endl;
	}
}

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

