#include "base/header.hpp"

class CPsevdonimiServerov {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	pii parse_query(const std::string& s) {
		std::string address = s.substr(7);
		const auto pos = address.find('/');
		std::string host = address.substr(0, pos);
		std::string page;
		if (pos != std::string::npos) {
			page = address.substr(pos);
		}
		return {get_host(host), get_page(page)};
	}

	static int get_str_id(std::unordered_map<std::string, int>& values, const std::string& str, std::vector<std::string>* by_id = nullptr) {
		const auto it = values.find(str);
		if (it == values.cend()) {
			const int res = values.size();
			values[str] = res;
			if (by_id != nullptr) {
				by_id->emplace_back(str);
			}
			return res;
		}
		return it->second;
	}

	int get_host(const std::string& host) {
		return get_str_id(hosts, host, &host_by_id);
	}

	int get_page(const std::string& page) {
		return get_str_id(pages, page);
	}

	std::unordered_map<std::string, int> hosts;
	std::vector<std::string> host_by_id;

	std::unordered_map<std::string, int> pages;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<std::string> input(n);
		in >> input;

		std::vector<pii> queries;
		queries.reserve(n);
		for (const auto& query : input) {
			queries.emplace_back(parse_query(query));
		}

		std::vector<std::vector<int>> queries_by_host(hosts.size());
		for (const auto& query : queries) {
			queries_by_host[query.first].emplace_back(query.second);
		}

		debug(queries_by_host);

		std::map<std::vector<int>, std::vector<int>> groups_by_queries;
		for (int i : range(queries_by_host.size())) {
			auto& host = queries_by_host[i];
			dedup(host);
			groups_by_queries[host].emplace_back(i);
		}

		debug(groups_by_queries);
		debug(host_by_id);

		int ans = 0;
		for (const auto& it : groups_by_queries) {
			if (it.second.size() > 1) {
				++ans;
			}
		}
		out << ans << std::endl;
		for (const auto& it : groups_by_queries) {
			if (it.second.size() == 1) {
				continue;
			}
			for (const auto& host : it.second) {
				out << "http://" + host_by_id[host] << " ";
			}
			out << std::endl;
		}
	}


	CPsevdonimiServerov() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
