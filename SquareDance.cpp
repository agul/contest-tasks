#include "../algolib/cpplib/base/header.hpp"

class SquareDance;
SquareDance * solution;

class SquareDance {
public:
	class Contestant;
	using DanceFloor = std::vector<std::vector<Contestant>>;

	class Contestant {
	public:
		Contestant() {}

		Contestant(const ll skill, const size_t x = 0, const size_t y = 0) :
			indices_(x, y),
			skill_(skill),
			left_(nullptr),
			right_(nullptr),
			up_(nullptr),
			down_(nullptr)
		{}

		Contestant(const ll skill, const size_t x, const size_t y, DanceFloor& floor) : Contestant(skill, x, y) {
			if (x > 0) {
				up_ = &floor[x - 1][y];
			}
			if (x + 1 < floor.size()) {
				down_ = &floor[x + 1][y];
			}
			if (y > 0) {
				left_ = &floor[x][y - 1];
			}
			if (y + 1 < floor.front().size()) {
				right_ = &floor[x][y + 1];
			}
		}

		bool is_loser() const {
			return diff() < 0;
		}

		ll diff() const {
			return skill() * 4 - neighbors_sum();
		}

		ll neighbors_sum() const {
			return skill(left_) + skill(right_) + skill(up_) + skill(down_);
		}

		ll skill() const {
			return skill_;
		}

		ll skill(const Contestant* rhs) const {
			return (rhs == nullptr ? skill_ : rhs->skill());
		}

		const pii& indices() const {
			return indices_;
		}

		std::vector<pii> eliminate(const bool dry_run = true) const {
			std::vector<pii> updates;
			if (left_ != nullptr) {
				if (!dry_run) {
					left_->right_ = this->right_;
				}
				updates.emplace_back(left_->indices());
			}
			if (right_ != nullptr) {
				if (!dry_run) {
					right_->left_ = this->left_;
				}
				updates.emplace_back(right_->indices());
			}
			if (up_ != nullptr) {
				if (!dry_run) {
					up_->down_ = this->down_;
				}
				updates.emplace_back(up_->indices());
			}
			if (down_ != nullptr) {
				if (!dry_run) {
					down_->up_ = this->up_;
				}
				updates.emplace_back(down_->indices());
			}
			return updates;
		}

	private:
		pii indices_;
		ll skill_;
		Contestant* left_;
		Contestant* right_;
		Contestant* up_;
		Contestant* down_;
	};

	void add_contestant(const size_t x, const size_t y, const ll skill) {
		interest_level_ += skill;
		floor_[x][y] = Contestant(skill, x, y, floor_);
	}

	std::vector<pii> eliminate(const Contestant& contestant, const bool dry_run = true) {
		if (!dry_run) {
			interest_level_ -= contestant.skill();
		}
		return contestant.eliminate(dry_run);
	}

	struct ContestantComparator {
		bool operator() (const pii& lhs, const pii& rhs) const {
			const Contestant& left = solution->get_contestant(lhs);
			const Contestant& right = solution->get_contestant(rhs);
			const ll left_diff = left.diff();
			const ll right_diff = right.diff();
			return left_diff < right_diff || (left_diff == right_diff && lhs < rhs);
		}
	};


	void solve(std::istream& in, std::ostream& out) {
		out << "Case #" << ++test_id_ << ": ";
		int n, m;
		in >> n >> m;
		floor_ = make_vector<Contestant>(n, m, 0LL);
		interest_level_ = 0;
		for (int i : range(n)) {
			for (int j : range(m)) {
				ll skill;
				in >> skill;
				add_contestant(i, j, skill);
			}
		}

		std::set<pii, SquareDance::ContestantComparator> contestants;
		for (int i : range(n)) {
			for (int j : range(m)) {
				contestants.emplace(i, j);
			}
		}

		ll ans = 0;
		while (true) {
			ans += interest_level_;
			std::vector<pii> to_eliminate;
			for (const auto& indices : contestants) {
				const auto& contestant = get_contestant(indices);
				if (contestant.is_loser()) {
					to_eliminate.emplace_back(indices);
				} else {
					break;
				}
			}
			if (to_eliminate.empty()) {
				break;
			}
			
			std::unordered_set<pii> to_modify;
			for (const auto& indices : to_eliminate) {
				const auto &contestant = get_contestant(indices);
				std::vector<pii> updates = eliminate(contestant, true);
				for (auto&& update : updates) {
					to_modify.emplace(std::move(update));
				}
			}

			for (const auto& indices : to_eliminate) {
				const auto &contestant = get_contestant(indices);
				contestants.erase(indices);
			}

			std::vector<pii> modifications;
			for (const auto& update : to_modify) {
				const auto &it = contestants.find(update);
				if (it == contestants.cend()) {
					continue;
				}
				contestants.erase(it);
				modifications.emplace_back(update);
			}

			for (const auto& indices : to_eliminate) {
				const auto &contestant = get_contestant(indices);
				eliminate(contestant, false);
			}

			for (const auto& update : modifications) {
				contestants.emplace(update);
			}
		}

		out << ans << std::endl;
	}

	const Contestant& get_contestant(const pii& indices) const {
		return floor_[indices.first][indices.second];
	}

	bool check(std::string input, std::string expected_output, std::string actual_output) {
		return true;
	}

	SquareDance() {
		solution = this;
	}

	static constexpr size_t kGeneratedTestsCount = 0;
	static void generate_test(std::ostream& test) {
		const int MAXN = 100;
		const int MAXNxM = 100000;

		const int N = rand() % MAXN + 1;
		const int M = rand() % (MAXNxM / N) % MAXN + 1;

		test << 1 << std::endl;
		test << N << " " << M << std::endl;
		for (int i : range(N)) {
			for (int j : range(M)) {
				test << rand() % 100 + 1 << " ";
			}
			test << std::endl;
		}
	}

private:
	DanceFloor floor_;
	ll interest_level_;
	size_t test_id_ = 0;
};
