#include "Head.h"
#include "maths.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

int n,T=0;
vector<int> k(500);
vector<ll> W(500,ll(0));
vector<ll> P(500,0);
vector<ll> ext_ans(500);
vector<ll> first_lab_in_sub(500);
vector<ll> min_in_sub(500);
vector<int>p(50000);
vector<int>w(50000);
vector<int>ans(50000);
vector<int>second_parm(50000);
vector<int>Second_parm(500);

ll find_external_positions(int first_ind, int last_ind) {
	ll sum = 0;
	for (int i = first_ind; i < last_ind; i++)
	{
		sum += P[i];
	}
	for (int i = first_ind; i < last_ind; i++)
	{
		Second_parm[i] = sum - P[i];
	}
	ll min_pen = 0;
	for (int qq = last_ind - 1; qq > first_ind; qq--)
	{
		int t = ans[qq];
		ll min_penalty = W[qq] * Second_parm[qq];
		for (int i = first_ind; i < qq; i++)
		{
			if (min_penalty > W[i] * Second_parm[i]) {
				min_penalty = W[i] * Second_parm[i];
				t = i;
			}
		}
		int l = ext_ans[qq];
		ext_ans[qq] = ext_ans[t];
		ext_ans[t] = l;
		l = W[qq];
		W[qq] = W[t];
		W[t] = l;
		l = Second_parm[qq];
		Second_parm[qq] = Second_parm[t];
		Second_parm[t] = l;
		min_pen += min_penalty;
		for (int i = first_ind; i < qq; i++)
		{
			Second_parm[i] -= P[ext_ans[qq]];
		}
	}
	return min_pen;
}

ll find_internal_positions(int first_ind, int last_ind) {
	ll sum=0;
	for (int i = first_ind; i < last_ind; i++)
	{
		sum += p[i];
	}
	for (int i = first_ind; i < last_ind; i++)
	{
		second_parm[i] = sum;
	}
	ll min_pen=0;
	for (int qq = last_ind-1; qq >= first_ind; qq--)
	{
		int t = ans[qq];
		ll min_penalty = w[qq] * second_parm[qq];
		for (int i = first_ind; i < qq; i++)
		{
			if (min_penalty > w[i] * second_parm[i]) {
				min_penalty = w[i] * second_parm[i];
				t = i;
			}
		}
		int l = ans[qq];
		ans[qq] = ans[t];
		ans[t] = l;
		l = w[qq];
		w[qq] = w[t];
		w[t] = l;
		l = second_parm[qq];
		second_parm[qq] = second_parm[t];
		second_parm[t] = l;
		min_pen += min_penalty;
		for (int i = first_ind; i < qq; i++)
		{
			second_parm[i] -= p[ans[qq]];
		}
	}
	return min_pen;
}

void solve(istream& in, ostream& out) {
	in >> n;
	for (int i = 0; i < n; i++)
	{
		in >> k[i];
		T += k[i];
	}
	for (int i = 0; i < T; i++)
	{
		in >> p[i];
	}
	for (int i = 0; i < T; i++)
	{
		in >> w[i];
		ans[i] = i;
	}
	int curr_ind = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k[i]; j++)
		{
			W[i] += w[curr_ind];
			P[i] += p[curr_ind];
			curr_ind++;
		}
	}
	curr_ind = 0;
	ll anss = 0;
	for (int i = 0; i < n; i++)
	{
		min_in_sub[i] = find_internal_positions(curr_ind,curr_ind+k[i]);
		first_lab_in_sub[i] = curr_ind;
		curr_ind += k[i];
		anss += min_in_sub[i];
	}
	anss+=find_external_positions(0, n);
	out << anss << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < k[ext_ans[i]]; j++)
		{
			out << ans[first_lab_in_sub[i]+j]+1<< " ";
		}
	}
}
