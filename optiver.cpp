#include "base/header.hpp"

class Shape {
public:
	virtual int GetArea() const = 0;
};

class Rectangle : public Shape {
public:
	Rectangle(const int height, const int width) : height_(height), width_(width) {}

	virtual int GetArea() const override {
		return height_ * width_;
	}

private:
	int height_;
	int width_;
};

class Circle : public Shape {
public:
	static constexpr double kPi = 3.14;

	explicit Circle(const int radius) : radius_(radius) {}

	virtual int GetArea() const override {
		return std::lround(kPi * radius_ * radius_);
	}

private:
	int radius_;
};

class Cabinet {
public:
	int size;
	using Map = std::unordered_map<int, int>;

	Map time;

	std::priority_queue<int, std::vector<int>, bool(*)(const int, const int)> lru;

	explicit Cabinet(const int size) : size(size) {
		auto comp = [&](const int lhs, const int rhs) {
			return time[lhs] < time[rhs];
		};
		auto x = std::priority_queue<int, std::vector<int>, decltype(comp)>(comp);
		lru = x;
	}
};

class optiver {
public:
	static constexpr bool kWriteCaseNumber = false;
	static constexpr bool kMultiTest = false;
	void solve(std::istream& in, std::ostream& out) {
		Rectangle rec(3, 4);
		out << rec.GetArea() << std::endl;

		Circle circle(5);
		out << circle.GetArea() << std::endl;
	}


	optiver() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
