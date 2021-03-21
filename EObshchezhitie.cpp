#include "base/header.hpp"

class EObshchezhitie {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	struct Event {
	    int time;
	    int type;
	    int id;
	    int food;

	    std::tuple<int, int, int, int> as_tuple() const {
	        return std::make_tuple(time, type, id, food);
	    }

	    pii food_id_pair() const {
	        return pii{food, id};
	    }

	    bool operator<(const Event& rhs) const {
	        return as_tuple() < rhs.as_tuple();
	    }
	};

	void solve(std::istream& in, std::ostream& out) {
#ifndef HOME
        assign_files_input_txt();
#endif
        int days, vasya_consumption;
        in >> days >> vasya_consumption;
        std::vector<int> food_income(days);
        in >> food_income;

        food_income.insert(food_income.begin(), 0);

        int friends_count;
        in >> friends_count;
        std::vector<int> friends_consumption;
        std::vector<Event> events;
        for (int i : range(friends_count)) {
            int start, end, food;
            in >> start >> end >> food;
            events.emplace_back(Event{start, 1, i, food});
            events.emplace_back(Event{end + 1, 0, i, food});
        }
        sort(events);

        auto food_for_friends = make_vector<int>(days + 1, 1, 0);
        auto best_friends_ids = make_vector<int>(days + 1, 0, 0);
        std::set<pii> best_friends;
        int index = 0;
        for (int day : inclusiveRange(1, days)) {
            while (index < events.size() && events[index].time == day) {
                if (events[index].type == 0) {
                    best_friends.erase(events[index].food_id_pair());
                } else {
                    best_friends.emplace(events[index].food_id_pair());
                }
                ++index;
            }

            auto& friends_id_vec = best_friends_ids[day];
            int sum = 0;
            for (const auto& my_friend : best_friends) {
                sum += my_friend.first;
                friends_id_vec.emplace_back(my_friend.second);
                food_for_friends[day].emplace_back(sum);
            }
        }

        auto dp = make_vector<int>(days + 1, 888, -1);
        auto path = make_vector<pii>(days + 1, 888, pii{-1, -1});
        dp[0][0] = 0;
        for (int day : range(days)) {
            for (int food : range(888)) {
                const int cur_rating = dp[day][food];
                if (cur_rating == -1) {
                    continue;
                }
                const int max_food_left = std::min(food, food_income[day]);
                const int next_day_food = max_food_left + food_income[day + 1] - vasya_consumption;
                if (next_day_food < 0) {
                    continue;
                }
                const auto& feeder = food_for_friends[day + 1];
                for (int i : range(feeder.size())) {
                    if (feeder[i] > next_day_food) {
                        break;
                    }
                    const int food_left = next_day_food - feeder[i];
                    const int new_rating = cur_rating + i;
                    if (umax(dp[day + 1][food_left], new_rating)) {
                        path[day + 1][food_left] = pii{i, food};
                    }
                }
            }
        }

        const auto it = max_element(dp[days]);

        const int ans = *it;
        out << ans << std::endl;

        int food_left = it - dp[days].begin();
        std::vector<int> result(days + 1);
        for (int day : inclusiveDownrange(days, 1)) {
            const auto& node = path[day][food_left];
            const int friends_cnt = node.first;
            result[day] = friends_cnt;
            food_left = node.second;
        }

        for (int day : inclusiveRange(1, days)) {
            const int friends_cnt = result[day];

            const auto& vec = best_friends_ids[day];
            out << friends_cnt;
            for (int i : range(friends_cnt)) {
                out << " " << vec[i] + 1;
            }
            out << std::endl;
        }
	}


	EObshchezhitie() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
