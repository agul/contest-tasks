#pragma comment(linker, "/STACK:66777216")
#pragma warning(disable : 4996)

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#pragma hdrstop

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>

#else
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#ifdef _MSC_VER

#endif

template<typename T, size_t N>
struct MakeVector {
	
};

template<typename T>
struct MakeVector<T, 1> {
	/// caide keep
	template<typename R = std::vector<T>>
	static R make_vector(std::size_t size, const T& value) {
		return R(size, value);
	}
};

#ifdef _MSC_VER

#else
#define LLD "%lld"
#define LLU "%llu"
#endif

#include <iterator>

using namespace std;

void solve(std::istream& in, std::ostream& out) {
	vector<double> x(5);
	vector<double> y(5);
	for (int i = 0; i < 4; i++)
	{
		in >> x[i] >> y[i];
	}
	x[4] = x[0];
	y[4] = y[0];
	double Volume = 124;
	double mat_ojid = 100 / Volume * 5;
	//x=0.5 - на кости 3
	int f1, f2;
	double x1, y1, x2, y2,goodVolume;
	f1 = -1;
	f2 = -1;
	goodVolume = 0;
	for (int i = 0; i < 4; i++)
	{
		if (max(x[i],x[i+1]) >= 0.5 && min(x[i], x[i + 1]) <= 0.5)
		{
			double A, B, C;
			A = y[i] - y[i + 1];
			B = x[i + 1] - x[i];
			C = -A*x[i] - B*y[i];
			if (f1==-1)
			{
				f1 = i;
				x1 = 0.5;
				y1 = -(A*x1 + C) / B;
				if (x[i+1]>=0.5)
				{
					goodVolume += (x[i + 1] - x1)*(y1 + y[i + 1]);
				}
				else
				{
					goodVolume += (x1 - x[i])*(y1 + y[i]);
				}
			}
			else
			{
				f2 = i;
				x2 = 0.5;
				y2 = -(A*x2 + C) / B;
				if (x[i + 1] >= 0.5)
				{
					goodVolume += (x[i + 1] - x2)*(y2 + y[i + 1]);
				}
				else
				{
					goodVolume += (x2 - x[i])*(y2 + y[i]);
				}
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (x[i] >= 0.5 && x[i + 1] >= 0.5)
		{
			goodVolume += (x[i + 1] - x[i])*(y[i + 1] + y[i]);
		}
	}
	goodVolume = abs(goodVolume) / 2.0;
	mat_ojid += 3 * goodVolume * 5 / Volume;

//x=-0.5 4-на грани

	f1 = -1;
	f2 = -1;
	goodVolume = 0;
	for (int i = 0; i < 4; i++)
	{
		if (max(x[i], x[i + 1]) >= -0.5 && min(x[i], x[i + 1]) <= -0.5)
		{
			double A, B, C;
			A = y[i] - y[i + 1];
			B = x[i + 1] - x[i];
			C = -A*x[i] - B*y[i];
			if (f1 == -1)
			{
				f1 = i;
				x1 = -0.5;
				y1 = -(A*x1 + C) / B;
				if (x[i + 1] <= -0.5)
				{
					goodVolume += (x[i + 1] - x1)*(y1 + y[i + 1]);
				}
				else
				{
					goodVolume += (x1 - x[i])*(y1 + y[i]);
				}
			}
			else
			{
				f2 = i;
				x2 = -0.5;
				y2 = -(A*x2 + C) / B;
				if (x[i + 1] <= -0.5)
				{
					goodVolume += (x[i + 1] - x2)*(y2 + y[i + 1]);
				}
				else
				{
					goodVolume += (x2 - x[i])*(y2 + y[i]);
				}
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (x[i] <= -0.5 && x[i + 1] <= -0.5)
		{
			goodVolume += (x[i + 1] - x[i])*(y[i + 1] + y[i]);
		}
	}
	goodVolume = abs(goodVolume) / 2.0;
	mat_ojid += 4 * goodVolume * 5 / Volume;

//y=0.5 6- на грани
	f1 = -1;
	f2 = -1;
	goodVolume = 0;
	for (int i = 0; i < 4; i++)
	{
		if (max(y[i], y[i + 1]) >= 0.5 && min(y[i], y[i + 1]) <= 0.5)
		{
			double A, B, C;
			A = y[i] - y[i + 1];
			B = x[i + 1] - x[i];
			C = -A*x[i] - B*y[i];
			if (f1 == -1)
			{
				f1 = i;
				y1 = 0.5;
				x1 = -(B*y1 + C) / A;
				if (y[i + 1] >= 0.5)
				{
					goodVolume += (y[i + 1] - y1)*(x1 + x[i + 1]);
				}
				else
				{
					goodVolume += (y1 - y[i])*(x1 + x[i]);
				}
			}
			else
			{
				f2 = i;
				y2 = 0.5;
				x2 = -(B*y2 + C) / A;
				if (y[i + 1] >= 0.5)
				{
					goodVolume += (y[i + 1] - y2)*(x2 + x[i + 1]);
				}
				else
				{
					goodVolume += (y2 - y[i])*(x2 + x[i]);
				}
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (y[i] >= 0.5 && y[i + 1] >= 0.5)
		{
			goodVolume += (y[i + 1] - y[i])*(x[i + 1] + x[i]);
		}
	}
	goodVolume = abs(goodVolume);
	mat_ojid += 6 * goodVolume / 2.0 * 5 / Volume;

// y=-0.5 1 на грани

	f1 = -1;
	f2 = -1;
	goodVolume = 0;
	for (int i = 0; i < 4; i++)
	{
		if (max(y[i], y[i + 1]) >= -0.5 && min(y[i], y[i + 1]) <= -0.5)
		{
			double A, B, C;
			A = y[i] - y[i + 1];
			B = x[i + 1] - x[i];
			C = -A*x[i] - B*y[i];
			if (f1 == -1)
			{
				f1 = i;
				y1 = -0.5;
				x1 = -(B*y1 + C) / A;
				if (y[i + 1] <= -0.5)
				{
					goodVolume += (y[i + 1] - y1)*(x1 + x[i + 1]);
				}
				else
				{
					goodVolume += (y1 - y[i])*(x1 + x[i]);
				}
			}
			else
			{
				f2 = i;
				y2 = -0.5;
				x2 = -(B*y2 + C) / A;
				if (y[i + 1] <= -0.5)
				{
					goodVolume += (y[i + 1] - y2)*(x2 + x[i + 1]);
				}
				else
				{
					goodVolume += (y2 - y[i])*(x2 + x[i]);
				}
				break;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (y[i] <= -0.5 && y[i + 1] <= -0.5)
		{
			goodVolume += (y[i + 1] - y[i])*(x[i + 1] + x[i]);
		}
	}
	goodVolume = abs(goodVolume);
	mat_ojid += goodVolume / 2.0 * 5 / Volume;

	out << mat_ojid;
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

