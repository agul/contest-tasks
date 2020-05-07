#include "Head.h"
#include "IO/IO.h"
#include "Graph/Graph.h"

using namespace std;

int __;
IO io;
const int MOD = 1000000007;
const int MAXN = 32;

const size_t REV[] = { 5, 3, 4, 1, 2, 0 };

const size_t INDICES[3][4] = {
	{1, 2, 3, 4},
	{0, 4, 5, 2},
	{0, 1, 5, 3}
};

std::string normalize(const std::string& ans, const bool first) {
	std::vector<std::string> rotates;
	for (size_t i = 0; i < 6; ++i) {
		std::string tmp(6, '$');
		std::vector<bool> used(6, false);
		tmp.front() = ans[i];
		tmp.back() = ans[REV[i]];
		used[i] = used[REV[i]] = true;
		size_t core_index = std::min(i, REV[i]);
		for (size_t j = 0; j < 4; ++j) {
			tmp[j + 1] = ans[INDICES[core_index][j]];
		}
		for (size_t j = 0; j < 4; ++j) {
			rotates.emplace_back(tmp);
			std::rotate(tmp.begin() + 1, tmp.begin() + 2, tmp.begin() + 5);
		}
	}
	std::sort(rotates.begin(), rotates.end());
	if (first) {
		return normalize(rotates.front(), false);
	}
	return rotates.front();
}

void solve(istream& ins, ostream& out) {
	std::set<std::string> ans;
	std::vector<std::string> input(6);
	std::string permutation;
	for (auto& it : input) {
		ins >> it;
		std::sort(it.begin() + 1, it.end());
		permutation += it.front();
	}
	std::sort(input.begin(), input.end());
	std::sort(permutation.begin(), permutation.end());

	do {
		std::vector<std::string> vision(6);
		for (int i = 0; i < 6; ++i) {
			auto& cur = vision[i];
			cur += permutation[i];
			for (int j = 0; j < 6; ++j) {
				if (j != REV[i] && j != i) {
					cur += permutation[j];
				}
			}
			std::sort(cur.begin() + 1, cur.end());
		}
		std::sort(vision.begin(), vision.end());
		if (vision == input) {
			ans.insert(normalize(permutation, true));
		}
	} while (std::next_permutation(permutation.begin(), permutation.end()));

	if (ans.empty()) {
		io << "Impossible" << endl;
		return;
	}
	io << *ans.cbegin() << endl;
	if (ans.size() > 1) {
		io << *ans.crbegin() << endl;
	}
}
