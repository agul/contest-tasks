#include "base/header.hpp"
#include "graph/directed_graph.hpp"

#include <fstream>

class hashcode2021 {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;

	using CityNetwork = DirectedGraph<int, GraphType::Weighted>;
	using StreetNameMap = std::unordered_map<std::string, int>;

	using ScheduleRow = std::pair<int, int>;
	using Schedule = std::vector<ScheduleRow>;
	using ScheduleList = std::vector<Schedule>;

	struct Car {
        std::vector<int> route;
        int id;

        Car(const int id) : id(id) {}

        void read(std::ifstream& input, const StreetNameMap& street_name_to_id) {
            int route_size;
            input >> route_size;
            route.reserve(route_size);
            for (int i : range(route_size)) {
                std::string street_name;
                input >> street_name;

                const int street_id = street_name_to_id.at(street_name);
                route.emplace_back(street_id);
            }
        }
	};

	class Simulation {
	public:
	    Simulation(
	            const CityNetwork& city,
	            const std::vector<Car>& cars,
	            const ScheduleList& schedules,
	            const int bonus_points) :
            city_(city),
	        timer_(0),
	        bonus_points_(bonus_points)
        {
	        streets_.reserve(city.edges_count());
	        for (int i : range(city.edges_count())) {
	            streets_.emplace_back(i);
	        }

	        vehicles_.reserve(cars.size());
            for (int i : range(cars.size())) {
                vehicles_.emplace_back(cars[i]);

                const auto& vehicle = vehicles_.back();
                streets_[vehicle.current_street()].add_car_to_queue(vehicle);
            }

            intersections_.reserve(schedules.size());
            for (const auto& schedule : schedules) {
                intersections_.emplace_back(schedule);
            }
        }

        struct MovingVehicle;

        struct Street {
            std::queue<int> queue;
            bool is_green;
            int id;

            Street(const int id) : is_green(false), id(id) {}

            bool car_can_go(const int car_id) const {
                return !queue.empty() && is_green && queue.front() == car_id;
            }

            void add_car_to_queue(const MovingVehicle& vehicle) {
                queue.emplace(vehicle.id());
            }

            void pop_car() {
                if (!is_green || queue.empty()) {
                    return;
                }
                queue.pop();
            }

            void switch_light(const bool new_light) {
                is_green = new_light;
                if (is_green) {
                    // debug("Traffic light is on", id);
                }
            }
        };

        struct MovingVehicle {
            const Car &car;
            int remaining_dist_on_street;
            int last_update_time;

            MovingVehicle(const Car &car) :
                car(car),
                remaining_dist_on_street(0),
                cursor_in_route(0),
                last_update_time(0)
            {}

            int current_street() const {
                return car.route[cursor_in_route];
            }

            int id() const {
                return car.id;
            }

            bool finished() const {
                return cursor_in_route == car.route.size() - 1 && remaining_dist_on_street == 0;
            }

            int score(const int bonus_points, const int duration) const {
                if (!finished()) {
                    return 0;
                }
                // debug(id(), last_update_time);
                return bonus_points + duration - last_update_time;
            }

            bool move(const int time, const std::vector<Street>& streets, const CityNetwork& city) {
                if (finished()) {
                    return false;
                }
                if (remaining_dist_on_street == 0) {
                    const int street_id = current_street();
                    if (streets[street_id].car_can_go(id())) {
                        move_cursor(city);
                        last_update_time = time;
                        return true;
                    }
                    return false;
                }
                --remaining_dist_on_street;
                last_update_time = time;
                return true;
            }

            int cursor_pos() const {
                return cursor_in_route;
            }

            int dist_remaining() const {
                return remaining_dist_on_street;
            }

        private:
            int cursor_in_route;

            void move_cursor(const CityNetwork &city) {
                cursor_in_route += 1;
                const int street_id = current_street();
                remaining_dist_on_street = city.weight(street_id) - 1;
            }
        };

        struct Intersection {
            const Schedule& schedule;
            int cursor_in_schedule;
            int last_update_time;

            Intersection(const Schedule& schedule) :
                schedule(schedule),
                cursor_in_schedule(schedule.size() - 1),
                last_update_time(0) {}

            int current_street() const {
                if (schedule.empty()) {
                    return -1;
                }
                return schedule[cursor_in_schedule].first;
            }

            bool update(const int time, std::vector<Street>& streets) {
                const int time_diff = time - last_update_time;
                if (!schedule.empty() && time_diff == schedule[cursor_in_schedule].second) {
                    last_update_time = time;
                    streets[current_street()].switch_light(false);
                    move_cursor();
                    streets[current_street()].switch_light(true);
                    return true;
                }
                return false;
            }

        private:
            void move_cursor() {
                cursor_in_schedule = (cursor_in_schedule + 1) % schedule.size();
            }
        };

        int run(const int duration) {
            // debug("Run for", duration);
            while (timer_ < duration) {
                ++timer_;
                // debug(timer_);
                update_lights();
                move_cars();
                pop_cars();
                push_cars();
            }
            return get_score(duration);
        }

        int get_score(const int duration) const {
            int score = 0;
            int cnt = 0;
            for (const auto& vehicle : vehicles_) {
                score += vehicle.score(bonus_points_, duration);
                if (vehicle.finished()) {
                    cnt += 1;
                }
            }
            // debug(cnt);
            return score;
        }

	private:
	    const CityNetwork& city_;
	    int timer_;
	    int bonus_points_;

	    std::vector<MovingVehicle> vehicles_;
	    std::vector<Intersection> intersections_;
	    std::vector<Street> streets_;

	    void pop_cars() {
	        for (auto& street : streets_) {
	            street.pop_car();
	        }
	    }

	    void push_cars() {
	        for (const auto& vehicle : vehicles_) {
                if (vehicle.finished()) {
                    continue;
                }
                if (vehicle.last_update_time == timer_ && vehicle.dist_remaining() == 0) {
                    const int street_id = vehicle.current_street();
                    streets_[street_id].add_car_to_queue(vehicle);
                }
	        }
	    }

	    void move_cars() {
	        int index = 0;
	        std::vector<int> vehicles_to_push;
	        for (auto& vehicle : vehicles_) {
	            bool ok = vehicle.move(timer_, streets_, city_);
	            if (ok) {
	                const int current_street = vehicle.cursor_pos();
	                const int total_streets = vehicle.car.route.size();
	                const int dist = vehicle.dist_remaining();
	                // debug("Car moved", index, vehicle.current_street(), current_street, dist, total_streets);
	            }
	            ++index;
	        }
	    }

	    void update_lights() {
	        int index = 0;
	        for (auto& intersection : intersections_) {
	            bool ok = intersection.update(timer_, streets_);
	            if (ok) {
	                // // debug("Traffic light switched on intersection", index);
	            }
                ++index;
	        }
	    }
	};

	void analyze(const CityNetwork& graph) {
	    const int vertices_count = graph.vertices_count();
	    std::vector<int> out_degree(vertices_count, 0);
        std::vector<int> in_degree(vertices_count, 0);
	    for (const auto& edge : graph.edges()) {
	        out_degree[edge.from()]++;
	        in_degree[edge.to()]++;
	    }

	    auto compress_vector = [](const std::vector<int>& degree) {
	        std::vector<pii> counts;
	        for (int i : range(degree.size())) {
	            counts.emplace_back(degree[i], i);
	        }
	        sort(counts, std::greater<>());
	        return counts;
	    };

	    auto out_compressed = compress_vector(out_degree);
	    for (int i : range(std::min(20ULL, out_compressed.size()))) {
            // debug(i, out_compressed[i].first, out_compressed[i].second);
	    }
	    auto in_compressed = compress_vector(in_degree);
        for (int i : range(std::min(20ULL, in_compressed.size()))) {
            // debug(i, in_compressed[i].first, in_compressed[i].second);
        }

	}

	void solve(std::istream& in, std::ostream& out) {
	    std::cerr << "Enter filename with input:" << std::endl;
	    std::string filename;
	    in >> filename;

	    std::ifstream input(filename);

        int duration;
        int intersections_count;
        int streets_count;
        int cars_count;
        int bonus_points;
        input >> duration >> intersections_count >> streets_count >> cars_count >> bonus_points;

        CityNetwork city(intersections_count);

        StreetNameMap street_name_to_id;
        street_name_to_id.reserve(streets_count);

        for (int street_id : range(streets_count)) {
            int from;
            int to;
            std::string name;
            int length;
            input >> from >> to >> name >> length;

            city.add_directed_edge(from, to, length);
            street_name_to_id[name] = street_id;
        }

        std::vector<Car> cars;
        cars.reserve(cars_count);
        for (int car_id : range(cars_count)) {
            cars.emplace_back(Car(car_id));
            cars.back().read(input, street_name_to_id);
        }

        input.close();

        // analyze(city);
        std::cerr << "Enter output file (for simulation):" << std::endl;
        in >> filename;
        input = std::ifstream(filename);
        int schedules_count;
        input >> schedules_count;

        ScheduleList schedules(intersections_count);
        for (int schedule_id : range(schedules_count)) {
            int intersection_id;
            int schedule_rows_count;
            input >> intersection_id >> schedule_rows_count;

            Schedule& schedule = schedules[intersection_id];
            schedule.reserve(schedule_rows_count);
            for (int schedule_row_id : range(schedule_rows_count)) {
                std::string street_name;
                int green_light_duration;
                input >> street_name >> green_light_duration;

                const int street_id = street_name_to_id.at(street_name);
                schedule.emplace_back(street_id, green_light_duration);
            }
        }
        input.close();

        Simulation simulation(city, cars, schedules, bonus_points);
        const int ans = simulation.run(duration);
        out << ans << std::endl;

        /*
            int cnt = 0;
            for (const auto& car : cars) {
                cnt += (car.route.size() == 2 ? 1 : 0);
            }
            out << cnt << " / " << cars_count << std::endl;
        */
	}


	hashcode2021() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
