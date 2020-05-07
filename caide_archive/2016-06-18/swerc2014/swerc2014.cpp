#include "base/header.hpp"
#include "graph/dsu.hpp"
#include "stack.hpp"

using namespace std;

int __;
const int MAXN = 2222;

const ll MOD = 1000000007;

void solve(std::istream& in, std::ostream& out) {
	int k;
	in >> k;
	vector<int>numb(2 * k + 1);
	vector<char>znak(2 * k + 1);
	for (int i = 1; i <= k; i++)
	{
		in >> numb[i]>>znak[i];
		numb[k + i] = numb[i];
		znak[k + i] = znak[i];
	}
	vector< vector<ll> >max_val(k + 1, vector<ll>(2*k + 1, -LINF));
	vector< vector<ll> >min_val(k + 1, vector<ll>(2*k + 1, LINF));
	for (int i = 1; i < 2*k; i++)
	{
		max_val[1][i] = numb[i];
		min_val[1][i] = numb[i];
	}
	for (int st = 2; st < k+1; st++)
	{
		for (int i = 1; i < 2*k-st+1; i++)
		{
			for (int j = i; j < i+st-1; j++)
			{
				int first = j - i + 1;
				int second = st - first;
				switch (znak[j])
				{
				case '?':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * min_val[second][j + 1]);
					break;
				case '+':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] + min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] + min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] + min_val[second][j + 1]);
					break;
				case '-':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] - min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] - min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] - min_val[second][j + 1]);
					break;
				case '*':
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					max_val[st][i] = max(max_val[st][i], min_val[first][i] * min_val[second][j + 1]);

					min_val[st][i] = min(min_val[st][i], max_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], max_val[first][i] * min_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * max_val[second][j + 1]);
					min_val[st][i] = min(min_val[st][i], min_val[first][i] * min_val[second][j + 1]);
					break;
				default:
					break;
				}
			}
		}
	}
	for (int i = 1; i < k+1; i++)
	{
		out << abs(min_val[k][i]) << abs(max_val[k][i]);
	}
	return;
}
