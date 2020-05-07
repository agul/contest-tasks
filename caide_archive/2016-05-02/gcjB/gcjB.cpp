#include "Head.h"
#include "IO/IO.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 111111;

char s[MAXN], t[MAXN], as[MAXN], at[MAXN];
string ax, ay;

void brute() {
	int ls = strlen(s);
	int best = INF;
	for (int i = 0; i < 1000; ++i) {
		std::string str = std::to_string(i);
		while (str.length() < ls) {
			str = "0" + str;
		}
		if (str.length() > ls) {
			break;
		}
		bool ok = true;
		for (int j = 0; j < ls; ++j) {
			if (s[j] != '?' && str[j] != s[j]) {
				ok = false;
				break;
			}
		}
		if (!ok) {
			continue;
		}
		for (int j = 0; j < 1000; ++j) {
			std::string str2 = std::to_string(j);
			while (str2.length() < ls) {
				str2 = "0" + str2;
			}
			if (str2.length() > ls) {
				break;
			}
			bool ok = true;
			for (int k = 0; k < ls; ++k) {
				if (t[k] != '?' && str2[k] != t[k]) {
					ok = false;
					break;
				}
			}
			if (!ok) {
				continue;
			}
			if (umin(best, abs(i - j))) {
				ax = str;
				ay = str2;
			}
		}
	}
}

void check_brute(const std::string& s, const std::string& t) {
	if (ax != s || ay != t) {
		std::cerr << "ERROR!" << std::endl;
		std::cerr << "Expected: " << ax << " " << ay << std::endl;
		std::cerr << "Found: " << s << " " << t << std::endl;
		exit(0);
	}
}

void update_score(const char * s, const char * t, ll& ax, ll& ay) {
	ll best = abs(ax - ay);
	ll cx = atoi(s);
	ll cy = atoi(t);
	if (umin(best, abs(cx - cy)) || (best == abs(cx - cy) && ax > cx) || (best == abs(cx - cy) && ax == cx && ay > cy)) {
		ax = cx;
		ay = cy;
	}
}

std::string make(ll x, int ls) {
	std::string s = to_string(x);
	while (s.length() < ls) {
		s = "0" + s;
	}
	return s;
}

void solve(istream& ins, ostream& out) {
	io.assign_files_input_txt();
	io >> __;
	for (int _ = 1; _ <= __; ++_) {
		std::cerr << _ << std::endl;
		io << "Case #" << _ << ": ";
		io >> s >> t;
		brute();
		// io << ax << " " << ay << endl;
		// continue;
		int ls = strlen(s);
		int cur_ind = 0;
		while (cur_ind < ls) {
			if (s[cur_ind] != '?' && t[cur_ind] != '?' && s[cur_ind] != t[cur_ind]) {
				++cur_ind;
				break;
			}
			++cur_ind;
		}
		ll ax = 0, ay = LINF;
		for (int i = 0; i <= cur_ind; ++i) {
			if (i > 0) {
				if (s[i - 1] == '?' && t[i - 1] == '?') {
					s[i - 1] = t[i - 1] = '0';
				}
				else
				if (s[i - 1] == '?') {
					s[i - 1] = t[i - 1];
				}
				else
				if (t[i - 1] == '?') {
					t[i - 1] = s[i - 1];
				}
			}
			if (i == ls) {
				update_score(s, t, ax, ay);
				break;
			}
			char sx = '0', fx = '9';
			char sy = '0', fy = '9';
			if (s[i] != '?') {
				sx = fx = s[i];
			}
			if (t[i] != '?') {
				sy = fy = t[i];
			}
			for (char x = sx; x <= fx; ++x) {
				for (char y = sy; y <= fy; ++y) {
					if (x == y) {
						continue;
					}
					strcpy(as, s);
					strcpy(at, t);
					as[i] = x;
					at[i] = y;
					if (x < y) {
						for (int j = i + 1; j < ls; ++j) {
							if (as[j] == '?') {
								as[j] = '9';
							}
							if (at[j] == '?') {
								at[j] = '0';
							}
						}
					}
					else {
						for (int j = i + 1; j < ls; ++j) {
							if (as[j] == '?') {
								as[j] = '0';
							}
							if (at[j] == '?') {
								at[j] = '9';
							}
						}
					}

					update_score(as, at, ax, ay);
				}
			}
		}
		io << make(ax, ls) << ' ' << make(ay, ls) << endl;
		check_brute(make(ax, ls), make(ay, ls));
	}
}
