#include "../algolib/cpplib/base/header.hpp"

class Pattern {
public:
	Pattern() {}

	Pattern(const std::string& pattern) {
		int n = pattern.size();
		int l = 0;
		while (l < n && pattern[l] != '*') {
			start_ += pattern[l];
			++l;
		}

		int r = n - 1;
		while (l < r && pattern[r] != '*') {
			end_ += pattern[r];
			--r;
		}
		std::reverse(all(end_));

		while (l < r) {
			if (pattern[l] != '*') {
				mid_ += pattern[l];
			}
			++l;
		}
	}

	std::string start_;
	std::string mid_;
	std::string end_;
};

class PatternMatching {
public:
	bool starts_with(const std::string& s, const std::string& prefix) const {
		return s.substr(0, prefix.size()) == prefix;
	}

	bool ends_with(const std::string& s, const std::string& suffix) const {
		return s.substr(s.size() - suffix.size()) == suffix;
	}

	void solve(std::istream& in, std::ostream& out) {
		out << "Case #" << ++test_id_ << ": ";
		int n;
		in >> n;
		std::vector<Pattern> a;
		int max_start = 0;
		int max_end = 0;
		for (int i : range(n)) {
			std::string s;
			in >> s;
			a.emplace_back(s);
			if (a[i].start_.size() > a[max_start].start_.size()) {
				max_start = i;
			}
			if (a[i].end_.size() > a[max_end].end_.size()) {
				max_end = i;
			}
		}
		const std::string& prefix = a[max_start].start_;
		const std::string& suffix = a[max_end].end_;
		bool ok = true;
		for (const auto& x : a) {
			ok &= starts_with(prefix, x.start_) && ends_with(suffix, x.end_);
		}
		if (!ok) {
			out << "*" << std::endl;
		} else {
			std::string mids;
			for (const auto& x : a) {
				mids += x.mid_;
			}
			out << prefix << mids << suffix << std::endl;
		}
	}

private:
	size_t test_id_ = 0;
};
