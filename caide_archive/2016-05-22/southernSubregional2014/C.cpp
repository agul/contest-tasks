#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 32;


bool fs(int a, int b) {
	return a < b;
}

void solve(istream& ins, ostream& out) {
	int f = 0, k = 0;
	vector<int>ans(6);
	std::vector<int> p;
	for (int i = 0; i < 6; ++i) {
		p.emplace_back(i);
	}
	vector<string> vis(6);
	for (int i = 0; i < 6; i++)
	{
		ins >> vis[i];
	}
	vector<vector<int>> adj_for_vision(6, vector<int>(4, 0));
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			adj_for_vision[i][j] = vis[i][j + 1] - 'A';
		}
		sort(adj_for_vision[i].begin(), adj_for_vision[i].end(),fs);
	}
	do {
		vector<vector<int>> adj_for_perm(6, vector<int>(4, 0));
		adj_for_perm[0][0] = vis[p[1]][0] - 'A';
		adj_for_perm[0][1] = vis[p[2]][0] - 'A';
		adj_for_perm[0][2] = vis[p[3]][0] - 'A';
		adj_for_perm[0][3] = vis[p[4]][0] - 'A';
		adj_for_perm[1][0] = vis[p[0]][0] - 'A';
		adj_for_perm[1][1] = vis[p[2]][0] - 'A';
		adj_for_perm[1][2] = vis[p[4]][0] - 'A';
		adj_for_perm[1][3] = vis[p[5]][0] - 'A';
		adj_for_perm[2][0] = vis[p[0]][0] - 'A';
		adj_for_perm[2][1] = vis[p[1]][0] - 'A';
		adj_for_perm[2][2] = vis[p[3]][0] - 'A';
		adj_for_perm[2][3] = vis[p[5]][0] - 'A';
		adj_for_perm[3][0] = vis[p[0]][0] - 'A';
		adj_for_perm[3][1] = vis[p[2]][0] - 'A';
		adj_for_perm[3][2] = vis[p[4]][0] - 'A';
		adj_for_perm[3][3] = vis[p[5]][0] - 'A';
		adj_for_perm[4][0] = vis[p[0]][0] - 'A';
		adj_for_perm[4][1] = vis[p[1]][0] - 'A';
		adj_for_perm[4][2] = vis[p[3]][0] - 'A';
		adj_for_perm[4][3] = vis[p[5]][0] - 'A';
		adj_for_perm[5][0] = vis[p[1]][0] - 'A';
		adj_for_perm[5][1] = vis[p[2]][0] - 'A';
		adj_for_perm[5][2] = vis[p[3]][0] - 'A';
		adj_for_perm[5][3] = vis[p[4]][0] - 'A';
		for (int i = 0; i < 6; i++)
		{
			sort(adj_for_perm[i].begin(), adj_for_perm[i].end(), fs);
		}
		k = 0;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (adj_for_vision[p[i]][j]!=adj_for_perm[i][j])
				{
					k = 1;
					break;
				}
			}
			if (k==1)
			{
				break;
			}
		}
		if (k==0)
		{
			if (f==0)
			{
				for (int i = 0; i < 6; i++)
				{
					ans[i] = vis[p[i]][0]-'A';
				}
				f = 1;
			}
			else
			{
				vector<int>new_ans(6);
				int w = 0;
				for (int i = 0; i < 6; i++)
				{
					new_ans[i] = vis[p[i]][0]-'A';
				}
				vector<int>q(6);
				q[0] = new_ans[0];
				q[1] = new_ans[1];
				q[2] = new_ans[2];
				q[3] = new_ans[3];
				q[4] = new_ans[4];
				q[5] = new_ans[5];
				for (int i = 0; i < 4; i++)
				{
					int ff = 0;
					for (int j = 0; j < 6; j++)
					{
						if (ans[j]!=q[j])
						{
							ff = 1;
							break;
						}
					}
					if (ff == 0)
					{
						w = 1;
						break;
					}
					int q1 = q[1];
					q[1] = q[4];
					q[4] = q[3];
					q[3] = q[2];
					q[2] = q1;
				}
	
				q[0] = new_ans[1];
				q[1] = new_ans[0];
				q[2] = new_ans[2];
				q[3] = new_ans[5];
				q[4] = new_ans[4];
				q[5] = new_ans[3];
				for (int i = 0; i < 4; i++)
				{
					int ff = 0;
					for (int j = 0; j < 6; j++)
					{
						if (ans[j] != q[j])
						{
							ff = 1;
							break;
						}
					}
					if (ff == 0)
					{
						w = 1;
						break;
					}
					int q1 = q[1];
					q[1] = q[4];
					q[4] = q[3];
					q[3] = q[2];
					q[2] = q1;
				}

				q[0] = new_ans[2];
				q[1] = new_ans[0];
				q[2] = new_ans[3];
				q[3] = new_ans[5];
				q[4] = new_ans[1];
				q[5] = new_ans[4];
				for (int i = 0; i < 4; i++)
				{
					int ff = 0;
					for (int j = 0; j < 6; j++)
					{
						if (ans[j] != q[j])
						{
							ff = 1;
							break;
						}
					}
					if (ff == 0)
					{
						w = 1;
						break;
					}
					int q1 = q[1];
					q[1] = q[4];
					q[4] = q[3];
					q[3] = q[2];
					q[2] = q1;
				}

				q[0] = new_ans[3];
				q[1] = new_ans[0];
				q[2] = new_ans[2];
				q[3] = new_ans[5];
				q[4] = new_ans[4];
				q[5] = new_ans[1];
				for (int i = 0; i < 4; i++)
				{
					int ff = 0;
					for (int j = 0; j < 6; j++)
					{
						if (ans[j] != q[j])
						{
							ff = 1;
							break;
						}
					}
					if (ff == 0)
					{
						w = 1;
						break;
					}
					int q1 = q[1];
					q[1] = q[4];
					q[4] = q[3];
					q[3] = q[2];
					q[2] = q1;
				}

				q[0] = new_ans[4];
				q[1] = new_ans[0];
				q[2] = new_ans[3];
				q[3] = new_ans[5];
				q[4] = new_ans[1];
				q[5] = new_ans[2];
				for (int i = 0; i < 4; i++)
				{
					int ff = 0;
					for (int j = 0; j < 6; j++)
					{
						if (ans[j] != q[j])
						{
							ff = 1;
							break;
						}
					}
					if (ff == 0)
					{
						w = 1;
						break;
					}
					int q1 = q[1];
					q[1] = q[4];
					q[4] = q[3];
					q[3] = q[2];
					q[2] = q1;
				}

				q[0] = new_ans[5];
				q[1] = new_ans[1];
				q[2] = new_ans[2];
				q[3] = new_ans[3];
				q[4] = new_ans[4];
				q[5] = new_ans[1];
				for (int i = 0; i < 4; i++)
				{
					int ff = 0;
					for (int j = 0; j < 6; j++)
					{
						if (ans[j] != q[j])
						{
							ff = 1;
							break;
						}
					}
					if (ff == 0)
					{
						w = 1;
						break;
					}
					int q1 = q[1];
					q[1] = q[4];
					q[4] = q[3];
					q[3] = q[2];
					q[2] = q1;
				}

				if (w==0)
				{
					for (int i = 0; i < 6; i++)
					{
						out << char('A' + ans[i]);
					}
					out << endl;
					for (int i = 0; i < 6; i++)
					{
						out << char('A' + new_ans[i]);
					}
					out << endl;
					return;
				}
			}
		}

	} while (std::next_permutation(all(p)));
	if (f == 1) {
		for (int i = 0; i < 6; i++)
		{
			out << char('A' + ans[i]);
		}
	}
	else
	{
		out << "Impossible";
	}
}
