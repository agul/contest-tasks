#include "base/header.hpp"
#include "collections/value_compressor.hpp"
#include "data_structures/fenwick_tree.hpp"

class DVikaIOtrezki {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using coord_type = ll;
	using Point = std::pair<coord_type, coord_type>;

	struct Segment {
		Point a;
		Point b;

		Segment() : Segment(Point(0, 0), Point(0, 0)) {}
		Segment(const Point& a, const Point& b) : a(a), b(b) {}

		bool is_vertical() const {
			return a.X == b.X;
		}

		bool is_horizontal() const {
			return a.Y == b.Y;
		}

		coord_type x() const {
			return a.X;
		}

		coord_type y() const {
			return a.Y;
		}

		coord_type length() const {
			return (b.X - a.X + 1) * std::abs(b.Y - a.Y + 1);
		}

		void normalize() {
			if (b.X < a.X || b.Y < a.Y) {
				std::swap(a, b);
			}
		}

		std::pair<Point, Point> to_pair() const {
			return {a, b};
		}

		bool operator <(const Segment& rhs) const {
			return to_pair() < rhs.to_pair();
		}
	};

	static coord_type get_x(const Segment& segment) {
		return segment.x();
	}

	static coord_type get_y(const Segment& segment) {
		return segment.y();
	}

	friend std::istream& operator >>(std::istream& in, Segment& segment) {
		in >> segment.a >> segment.b;
		segment.normalize();
		return in;
	}

	using SegmentPoint = std::pair<coord_type, bool>;
	using SweepLineVector = std::vector<SegmentPoint>;
	using SweepLineMap = std::map<coord_type, SweepLineVector>;

	using CoordinatesVector = std::vector<coord_type>;

	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;

		std::vector<Segment> input_segments(n);
		in >> input_segments;

		SweepLineMap horizontal_lines;
		SweepLineMap vertical_lines;

		for (const auto& segment : input_segments) {
			if (segment.is_vertical()) {
				const coord_type x = segment.x();
				vertical_lines[x].emplace_back(segment.a.Y, false);
				vertical_lines[x].emplace_back(segment.b.Y, true);
			} else {
				// horizontal
				const coord_type y = segment.y();
				horizontal_lines[y].emplace_back(segment.a.X, false);
				horizontal_lines[y].emplace_back(segment.b.X, true);
			}
		}

		// debug(horizontal_lines);
		// debug(vertical_lines);

		auto unite_segments = [](SweepLineMap& map, const bool is_vertical) {
			std::vector<Segment> result;
			for (auto& kv : map) {
				const coord_type key = kv.first;
				auto& vec = kv.second;
				sort(vec);
				int balance = 0;
				coord_type prev_start = -LINF;
				for (const auto& point : vec) {
					const coord_type coordinate = point.first;
					if (balance == 0) {
						prev_start = coordinate;
					}
					if (point.second) {
						--balance;
					} else {
						++balance;
					}
					if (balance == 0) {
						if (is_vertical) {
							result.emplace_back(Point(key, prev_start), Point(key, coordinate));
						} else {
							result.emplace_back(Point(prev_start, key), Point(coordinate, key));
						}
					}
				}
			}
			return result;
		};

		auto sum_lengths = [](const std::vector<Segment>& segments) {
			return std::accumulate(all(segments), coord_type{0}, [](const coord_type acc, const Segment& segment) {
				return acc + segment.length();
			});
		};
		const std::vector<Segment> horizontal_segments = sorted(unite_segments(horizontal_lines, false), [](const Segment& lhs, const Segment& rhs) {
			return lhs.y() < rhs.y() || (lhs.y() == rhs.y() && lhs.a < rhs.a);
		});
		const std::vector<Segment> vertical_segments = sorted(unite_segments(vertical_lines, true));
		const coord_type total_segment_length = sum_lengths(vertical_segments) + sum_lengths(horizontal_segments);

//		debug(total_segment_length);
//		debug(input_segments);
//		debug(horizontal_segments);
//		debug(vertical_segments);

		auto get_coordinates = [](const std::vector<Segment>& segments, const std::function<coord_type(const Segment&)>& func) {
			CoordinatesVector coordinates;
			coordinates.reserve(segments.size());
			for (const auto& segment : segments) {
				coordinates.emplace_back(func(segment));
			}
			dedup(coordinates);
			return coordinates;
		};

		const CoordinatesVector horizontal_coordinates = get_coordinates(horizontal_segments, get_y);
		const CoordinatesVector vertical_coordinates = get_coordinates(vertical_segments, get_x);
		IntegralValueCompressor<coord_type> minimized_vertical_coordinates(vertical_coordinates);

		std::vector<CoordinatesVector> intersection_start(horizontal_coordinates.size());
		std::vector<CoordinatesVector> intersection_end(horizontal_coordinates.size());

		for (const auto& segment : vertical_segments) {
			const coord_type x = minimized_vertical_coordinates[segment.x()];
			const coord_type lower = segment.a.Y;
			const coord_type upper = segment.b.Y;

			const auto lower_it = lower_bound(horizontal_coordinates, lower);
			const auto upper_it = upper_bound(horizontal_coordinates, upper);
			if (upper_it == lower_it) {
				continue;
			}

			const int lower_index = lower_it - horizontal_coordinates.cbegin();
			const int upper_index = upper_it - 1 - horizontal_coordinates.cbegin();

			intersection_start[lower_index].emplace_back(x);
			intersection_end[upper_index].emplace_back(x);
		}

		debug(horizontal_coordinates);
		debug(intersection_start);
		debug(intersection_end);

		FenwickTreeSum<int> fenwick_tree(vertical_coordinates.size());

		auto add_vertical_coordinates = [&fenwick_tree](const CoordinatesVector& coordinates) {
			for (const auto& coordinate : coordinates) {
				fenwick_tree.inc(coordinate, 1);
			}
		};

		auto remove_vertical_coordinates = [&fenwick_tree](const CoordinatesVector& coordinates) {
			for (const auto& coordinate : coordinates) {
				fenwick_tree.inc(coordinate, -1);
			}
		};

		coord_type intersections_count = 0;
		int index = 0;
		for (const auto& segment : horizontal_segments) {
			while (index < horizontal_coordinates.size() && horizontal_coordinates[index] <= segment.y()) {
				if (index > 0) {
					remove_vertical_coordinates(intersection_end[index - 1]);
				}
				add_vertical_coordinates(intersection_start[index]);
				++index;
			}
			const coord_type lower = segment.a.X;
			const coord_type upper = segment.b.X;

			const auto lower_it = lower_bound(vertical_coordinates, lower);
			const auto upper_it = upper_bound(vertical_coordinates, upper);
			if (upper_it == lower_it) {
				continue;
			}

			const int lower_index = lower_it - vertical_coordinates.cbegin();
			const int upper_index = upper_it - 1 - vertical_coordinates.cbegin();

			intersections_count += fenwick_tree.query(lower_index, upper_index);
			debug(lower_index, upper_index);
		}

		debug(total_segment_length);
		debug(intersections_count);
		out << total_segment_length - intersections_count << std::endl;
	}


	DVikaIOtrezki() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};

std::string to_string(const DVikaIOtrezki::Segment& segment) {
	return to_string(segment.to_pair());
}

std::ostream& operator <<(std::ostream& out, const DVikaIOtrezki::Segment& segment) {
	return out << to_string(segment);
}
