#pragma GCC optimize("O3")
#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/prime.hpp"

class DDvaDelitelya {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {

		// check(out); return;

		auto a = input(in);
		const int n = a.size();

		std::vector<int> x(n, -1);
		std::vector<int> y(n, -1);

		std::vector<int> divs(30);
		for (int index : range(n)) {
			int divs_count = 0;
			const int value = a[index];
			int cur = value;
			for (const auto& prime : primes) {
				if (value % prime == 0) {
					divs[divs_count] = prime;
					++divs_count;
					while (cur % prime == 0) {
						cur /= prime;
					}
				}
			}
			if (cur > 1) {
				divs[divs_count] = cur;
				++divs_count;
			}
			bool good = false;
			for (int i : range(divs_count)) {
				for (int j : range(i + 1, divs_count)) {
					if (gcd(divs[i] + divs[j], value) == 1) {
						x[index] = divs[i];
						y[index] = divs[j];
						good = true;
						break;
					}
					for (int k : range(j + 1, divs_count)) {
						if (gcd(divs[i] + divs[j] * divs[k], value) == 1) {
							x[index] = divs[i];
							y[index] = divs[j] * divs[k];
							good = true;
							break;
						}
					}
					if (good) {
						break;
					}
				}
				if (good) {
					break;
				}
			}
		}

		output(out, x, y);
	}

	void check(std::ostream& out) {
		const int N = 10000000;
		bool any = false;
		for (int x : range(2, N)) {
			if (x % 10000 == 0) {
				std::cout << x << std::endl;
			}
			auto a = divisors_vector(x);
			auto b = get_prime_divisors_vector(x);
			bool valid = false;
			std::vector<pii> pairs;
			for (int i : range<int>(1, a.size())) {
				for (int j : range<int>(i + 1, a.size())) {
					if (gcd(a[i] + a[j], x) == 1) {
						valid = true;
						pairs.emplace_back(a[i], a[j]);
					}
				}
			}
			bool prime_pair = false;
			assert(b.size() <= 8);
			for (size_t i : range(b.size())) {
				for (size_t j : range(i + 1, b.size())) {
					if (gcd(b[i].first + b[j].first, x) == 1) {
						prime_pair = true;
						break;
					}
					for (size_t k : range(j + 1, b.size())) {
						if (gcd(b[i].first + b[j].first * b[k].first, x) == 1) {
							prime_pair = true;
							break;
						}
//						for (size_t l : range(k + 1, b.size())) {
//							if (gcd(b[i].first + b[j].first * b[k].first * b[l].first, x) == 1) {
//								prime_pair = true;
//								break;
//							}
//						}
//						if (prime_pair) {
//							break;
//						}
					}
					if (prime_pair) {
						break;
					}
				}
			}
			if (valid && !prime_pair) {
				any = true;
				std::cout << "FAIL " << x << " " << to_string(pairs) << std::endl;
			}
		}
		if (!any) {
			std::cout << "ALL OK" << std::endl;
		}
	}

	static std::vector<int> input(std::istream& in) {
#ifdef HOME
		int n;
		in >> n;
		std::vector<int> a(n);
		in >> a;
#else
		int n;
		scanf("%d", &n);
		std::vector<int> a(n);
		for (int& x : a) {
			scanf("%d", &x);
		}
#endif

		return a;
	}

	static void output(std::ostream& out, const std::vector<int>& x, const std::vector<int>& y) {
#ifdef HOME
		for (int i : x) {
			out << i << " ";
		}
		out << std::endl;
		for (int i : y) {
			out << i << " ";
		}
		out << std::endl;
#else
		for (int i : x) {
			printf("%d ", i);
		}
		printf("\n");
		for (int i : y) {
			printf("%d ", i);
		}
		printf("\n");
#endif
	}


	std::vector<int> primes;
	DDvaDelitelya() {
		const int N = sqrt(11111111);
		primes = primes_vector<int>(N);
	}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
