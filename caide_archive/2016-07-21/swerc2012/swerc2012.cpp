#include "base/header.hpp"
#include "maths/decimal.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111;



void solve(std::istream& in, std::ostream& out) {
	string s;
	while (getline(in, s)) {
		stringstream ss;
		ss << s;
		int d, p;
		ss >> d >> p;
		int x;
		vector<Decimal> a;
		while (ss >> x) {
			a.emplace_back(x);
		}
		{
			Decimal x = *max_element(a);
			if (x == 0) {
				out << "The spider may fall!" << endl;
				continue;
			}
		}
		if (a.size() <= d) {
			std::vector<std::vector<Decimal>> matrix(2);
			matrix[0] = { a[0], a[1], a[2] };
			matrix[1] = { a[1], a[2], a[3] };
			int cur = 0;
			for (int col : range(3)) {
				bool found = false;
				for (int row : range(cur, 2)) {
					if (matrix[row][col] != 0) {
						found = true;
						matrix[row].swap(matrix[cur]);
						break;
					}
				}
				if (!found) {
					continue;
				}
				for (int row : range(cur + 1, 2)) {
					const Decimal mul = matrix[row][col] / matrix[cur][col];
					for (int c : range(col, 3)) {
						matrix[row][c] -= mul * matrix[cur][c];
					}
				}

				++cur;
			}
			Decimal x1, x2;
			if (matrix[1][1] == 0) {
				x1 = 0;
				x2 = matrix[0][2] / matrix[0][1];
			}
			else {
				x2 = matrix[1][2] / matrix[1][1];
				x1 = (matrix[0][2] - matrix[0][1] * x2) / matrix[0][0];
			}
			for (int i : range((int)a.size(), d + 1)) {
				a.emplace_back(a[i - 2] * x1 + a[i - 1] * x2);
			}
		}
		int ans = -1;
		for (int i = 0; i < a.size(); ++i) {
			if (a[i] > p) {
				break;
			}
			ans = i;
		}
		if (ans == -1) {
			out << "The spider is going to fall!" << endl;
			continue;
		}
		if (ans == d) {
			out << "The spider may fall!" << endl;
			continue;
		}
		out << d - ans << endl;
	}
}
