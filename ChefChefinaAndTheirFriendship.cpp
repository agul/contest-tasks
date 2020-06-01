#include "base/header.hpp"
#include "hash/hasher.hpp"
#include "string/z_function.hpp"

class ChefChefinaAndTheirFriendship {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = true;

	int solve_hash(const std::string& s) {
		Hasher<DoubleHasher<ll>> hasher(s);
		int ans = 0;
		for (int len : range<int>(1, s.length())) {
			const int rem_len = (s.length() - len * 2) / 2;
			if (s.length() <= len * 2) {
				break;
			}
			if (hasher.get_hash(0, len - 1) == hasher.get_hash(len, 2 * len - 1) && hasher.get_hash(2 * len, 2 * len + rem_len - 1) == hasher.get_hash(2 * len + rem_len, 2 * len + 2 * rem_len - 1)) {
				++ans;
			}
		}
		return ans;
	}

	int solve_z(const std::string& s) {
		auto z = z_function(s);
		std::string t = s;
		reverse(t);
		auto z_rev = z_function(t);

		int ans = 0;
		for (int len : range<int>(1, s.length())) {
			const int rem_len = (s.length() - len * 2) / 2;
			if (s.length() <= len * 2) {
				break;
			}
			if (z[len] >= len && z_rev[rem_len] >= rem_len) {
				++ans;
			}
		}
		return ans;
	}

	void solve(std::istream& in, std::ostream& out) {
		std::string s;
		in >> s;
		out << solve_z(s) << std::endl;
	}


	ChefChefinaAndTheirFriendship() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
