#include "Head.h"
#include "IO/IO.h"
#include "Maths.h"
#include "HashMap.h"

using namespace std;

int __;
IO io;
const int MAXN = 128;

enum Commands {
	ADD,
	SUB,
	NEG,
	NOT,
	CALL,
	RET
};

const char* COMS[] = { "ADD", "SUB", "NEG", "NOT", "CALL", "RET" };


ll val[MAXN];
int com[MAXN];
char s[8];

const ll MOD = 1LL << 60;

int st[1111111], stack_top;
oaht::hash_map<pli, ll> used;


ll run(ll acc, int addr) {
	if (used.count({ acc, addr })) {
		return used[{acc, addr}];
	}
	ll& cur = used[{acc, addr}];
	if (com[addr] == ADD) {
		return cur = run((acc + val[addr]) % MOD, addr + 1);
	}
	if (com[addr] == SUB) {
		ll x = val[addr];
		return cur = run((x - acc) % MOD, addr + 1);
	}
	if (com[addr] == NEG) {
		return cur = run(-acc, addr + 1);
	}
	if (com[addr] == NOT) {
		return cur = run(~acc, addr + 1);
	}
	if (com[addr] == CALL) {
		st[++stack_top] = addr;
		return cur = run(acc, val[addr]);
	}
	if (com[addr] == RET) {
		if (stack_top == -1) {
			return cur = acc;
		}
		return cur = run(acc, st[stack_top--] + 1);
	}
	assert(false);
	return -1;
}

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n >> __;
	for (int i = 0; i < n; ++i) {
		
		int x;
		ins >> x >> s;
		for (int j = 0; j < 6; ++j) {
			if (strcmp(s, COMS[j]) == 0) {
				com[i] = j;
			}
		}
		if (com[i] == ADD || com[i] == SUB || com[i] == CALL) {
			ins >> val[i];
		}
	}
	io << __ << endl;
	for (int _ = 0; _ < __; ++_) {
		long long x;
		ins >> x;
		stack_top = -1;
		io << run(x, 0) << endl;
	}
}
