#include "base/header.hpp"
#include "collections/value_compressor.hpp"
#include "cpplib/data_structures/fenwick_tree/fenwick_tree.hpp"

class DVlozhennieOtrezki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Event {
		int pos;
		int type;
		int id;

		bool operator < (const Event& rhs) const {
			return pos < rhs.pos;
		}
	};

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<pii> a(n);
		in >> a;

		std::vector<int> coordinates;
		coordinates.reserve(n * 2);
		for (const auto& it : a) {
			coordinates.emplace_back(it.first);
			coordinates.emplace_back(it.second);
		}
		sort(coordinates);

		IntegralValueCompressor<int> compressor(coordinates);

		FenwickTreeSum<int> tree(compressor.size());

		for (auto& it : a) {
			it.first = compressor[it.first];
			it.second = compressor[it.second];
		}

		std::vector<pii> events;
		for (int i : range(n)) {
			events.emplace_back(a[i].first, i);
		}
		sort(events, std::greater<>());

		std::vector<int> ans(n);
		for (const auto& event : events) {
			int pos, id;
			std::tie(pos, id) = event;

			const int right = a[id].second;
			ans[id] = tree.query(pos, right);
			tree.inc(right, 1);
		}

		for (const auto x : ans) {
			out << x << std::endl;
		}
	}


	DVlozhennieOtrezki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
