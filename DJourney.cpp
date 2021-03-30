#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/decimal.hpp"
#include "geometry/point_vector.hpp"
#include "collections/queue/queue.hpp"

class DJourney {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

    using Pt = Point2D<int>;
    const int kMaxn = 1111;

	void solve(std::istream& in, std::ostream& out) {
        ll n, m;
        in >> n >> m;
        std::vector<std::string> field(n);
        in >> field;

        std::vector<ll> pref_sum(kMaxn);
        for (int i : range(1, kMaxn)) {
            pref_sum[i] = pref_sum[i - 1] + i;
        }

        Decimal<> sum = 0;
        std::vector<Pt> static_points;
        for (int i : range(n)) {
            for (int j : range(m)) {
                const ll cur_sum = (pref_sum[i] + pref_sum[n - i - 1]) * m + (pref_sum[j] + pref_sum[m - j - 1]) * n;
                if (field[i][j] == '.') {
                    sum += cur_sum;
                } else {
                    sum -= cur_sum;
                    static_points.emplace_back(i, j);
                }
            }
        }

        const int count_static = static_points.size();
        debug(sum, count_static);

        for (const auto& pt : static_points) {
            const ll sum_dist_to_static = std::accumulate(all(static_points), 0LL, [&pt](const ll acc, const Pt& value) {
                return acc + pt.manhattan_dist(value);
            });
            sum += sum_dist_to_static;
        }

        sort(static_points);
        for (int i : range(count_static)) {
            const auto &pt = static_points[i];
            const int count_left = pt.y;

            int cur_right = pt.y;
            int prev_x = pt.x;
            for (int j : inclusiveDownrange(i)) {
                const auto &cur = static_points[j];
                if (cur.y < cur_right || prev_x > cur.x + 1) {
                    break;
                }
                cur_right = cur.y;
                prev_x = cur.x;
                sum += (m - cur_right - 1) * count_left * 4;
            }

            cur_right = pt.y;
            prev_x = pt.x;
            for (int j : range(i + 1, count_static)) {
                const auto &cur = static_points[j];
                if (cur.y < cur_right || prev_x < cur.x - 1) {
                    break;
                }
                cur_right = cur.y;
                prev_x = cur.x;
                sum += (m - cur_right - 1) * count_left * 4;
            }
        }
        debug(sum);

        sort(static_points, LessByY<Pt>());
        debug(static_points);
        for (int i : range(count_static)) {
            const auto& pt = static_points[i];
            const int count_up = pt.x;

            int cur_down = pt.x;
            int prev_y = pt.y;
            for (int j : inclusiveDownrange(i)) {
                const auto& cur = static_points[j];
                if (cur.x < cur_down || prev_y > cur.y + 1) {
                    break;
                }
                cur_down = cur.x;
                prev_y = cur.y;
                sum += (n - cur_down - 1) * count_up * 4;
            }

            cur_down = pt.x;
            prev_y = pt.y;
            for (int j : range(i + 1, count_static)) {
                const auto& cur = static_points[j];
                debug(i, j, cur, prev_y, cur_down, count_up);
                if (cur.x < cur_down || prev_y < cur.y - 1) {
                    break;
                }
                cur_down = cur.x;
                prev_y = cur.y;
                sum += (n - cur_down - 1) * count_up * 4;
            }
        }
        debug(sum);

        const ll count = sqr<ll>(n * m - count_static);
        out << sum / count << std::endl;
	}


	DJourney() {}

    std::vector<std::vector<int>> bfs(const int x, const int y, const std::vector<std::string>& field, const bool ban_static = true) {
        const int n = field.size();
        const int m = field.front().size();

        static Queue<Pt> q(kMaxn * kMaxn);
        q.clear();

        auto dist = make_vector<int>(n, m, INF);
        auto add = [&dist, &field, &n, &m, &ban_static](const int x, const int y, const int len) {
            if (x < 0 || y < 0 || x >= n || y >= m || ban_static && field[x][y] == 'X') {
                return;
            }
            if (umin(dist[x][y], len)) {
                q.push({x, y});
            }
        };
        add(x, y, 0);
        while (!q.empty()) {
            const Pt cur = q.pop_front();
            const int len = dist[cur.x][cur.y];
            for (int dir : range(4)) {
                add(cur.x + DX[dir], cur.y + DY[dir], len + 1);
            }
        }
        return dist;
    }

    static constexpr bool kUseCustomChecker = true;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
	    int n, m;
	    in >> n >> m;
	    std::vector<std::string> field(n);
	    in >> field;

	    Decimal<> jans = 0;
	    int count_static = 0;
	    for (int x : range(n)) {
	        for (int y : range(m)) {
	            if (field[x][y] == 'X') {
	                ++count_static;
	                continue;
	            }
	            auto dist = bfs(x, y, field);

                ll cur_sum = 0;
                for (int i : range(n)) {
                    for (int j : range(m)) {
                        if (dist[i][j] < INF) {
                            cur_sum += dist[i][j];
                        }
                    }
                }

                // debug(x, y, cur_sum);
                jans += cur_sum;
	        }
	    }
	    // debug(jans);
	    jans /= sqr<ll>(n * m - count_static);

	    Decimal<> pans;
	    out >> pans;

	    if (pans != jans) {
	        debug(jans, pans);
	        return false;
	    }

		return true;
	}

	static constexpr size_t kGeneratedTestsCount = 100;
	static constexpr bool kStopAfterFirstFail = true;
	static void generate_test(std::ostream& test) {
	    const int kMaxn = 5;

	    const int n = Random::get(2, kMaxn);
	    const int m = Random::get(2, kMaxn);
	    std::vector<std::string> field(n, std::string(m, '.'));

	    std::set<Pt> points;
	    for (int i : range(n)) {
	        for (int j : range(m)) {
                points.emplace(i, j);
	        }
	    }

	    int static_count = Random::get(1, std::min(n, m));
	    while (static_count > 0 && !points.empty()) {
	        const int id = Random::get<int>(0, points.size() - 1);
	        int index = 0;
	        for (const auto& pt : points) {
	            if (index == id) {
	                field[pt.x][pt.y] = 'X';
	                --static_count;
	                for (int dir : range(4, 8)) {
                        const Pt neighbor{pt.x + DX[dir], pt.y + DY[dir]};
                        points.erase(neighbor);
	                }
	                for (int i : range(n)) {
                        points.erase({i, pt.y});
                    }
                    for (int j : range(m)) {
                        points.erase({pt.x, j});
                    }
	                break;
	            }
	            ++index;
	        }
	    }

	    test << n << " " << m << std::endl;
	    for (const auto& row : field) {
	        test << row << std::endl;
	    }
	}

};
