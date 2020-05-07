#pragma comment(linker, "/STACK:66777216")

#include <cstdio>
#pragma warning(disable : 4996)
#include <algorithm>
#include <array>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <utility>
#include <functional>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cassert>
#include <queue>
#include <cmath>
#include <random>
#include <sstream>
#include <numeric>
#include <limits>
#include <chrono>
#include <type_traits>
#pragma hdrstop

#ifdef _MSC_VER
#include <intrin.h>

#else
#define LLD "%lld"
#define LLU "%llu"
#define popcount(a) __builtin_popcount(a)
#define clz(a) __builtin_clz(a)
#define ctz(a) __builtin_ctz(a)
#endif

#ifdef _MSC_VER

#endif

template<typename T>
class Stack {
public:
	using value_type = T;
	using size_type = size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using rvalue = value_type&&;
	using container = std::vector<value_type>;

	Stack(const size_type max_size) : data_(container(max_size)) {
		clear();
	}

	Stack() = delete;

	Stack(const Stack&) = default;
	Stack& operator =(const Stack&) = default;
	Stack(Stack&&) = default;
	Stack& operator =(Stack&&) = default;

	reference top() {
		return data_[top_index_ - 1];
	}

	constexpr bool empty() const {
		return top_index_ == 0;
	}

	void clear() {
		top_index_ = 0;
	}

	constexpr size_type size() const {
		return top_index_;
	}

	void push(const_reference value) {
		data_[top_index_++] = value;
	}

	void push(rvalue value) {
		data_[top_index_++] = std::move(value);
	}

	value_type pop() {
		return data_[--top_index_];
	}

private:
	container data_;
	size_type top_index_;

};

inline int dig(const char ch)
// get exact numeric value of the corresponding char
// REQUIRE: char from '0' to '9'
{
	return ch - '0';
}

template<typename T>
inline T gcd(T a, T b) {
	while (b != 0) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

template<typename T>
class Rational {
public:
	static_assert(std::is_integral<T>::value, "Base type of Rational must be an integral.");

	constexpr Rational() : Rational(0) {}
	constexpr Rational(const T a) : a_(a), b_(1) {}
	Rational(const T a, const T b) : a_(a), b_(b) {
		normalize();
	}

	void swap(Rational& rhs) {
		std::swap(a_, rhs.a_);
		std::swap(b_, rhs.b_);
	}

	std::string to_string() const {
		return std::to_string(a_) + "/" + std::to_string(b_);
	}

	constexpr Rational add(const Rational& rhs) const {
		return{ a_ * rhs.b_ + rhs.a_ * b_, b_ * rhs.b_ };
	}

	constexpr Rational multiply(const Rational& rhs) const {
		return{ a_ * rhs.a_, b_ * rhs.b_ };
	}

	constexpr Rational operator *(const Rational& rhs) const {
		return multiply(rhs);
	}

	Rational& operator +=(const Rational& rhs) {
		Rational res = add(rhs);
		swap(res);
		return *this;
	}

	Rational& operator *=(const Rational& rhs) {
		Rational res = multiply(rhs);
		swap(res);
		return *this;
	}

	constexpr friend bool operator ==(const Rational& lhs, const Rational& rhs) {
		return lhs.a_ == rhs.a_ && lhs.b_ == rhs.b_;
	}

	void normalize() {
		const T g = gcd(a_, b_);
		a_ /= g;
		b_ /= g;
		if (b_ < 0) {
			a_ = -a_;
			b_ = -b_;
		}
	}

	constexpr Rational abs() const {
		return a_ < 0 ? Rational(-a_, b_) : Rational(a_, b_);
	}

	constexpr int sign() const {
		return a_ < 0 ? -1 : static_cast<int>(a_ > 0);
	}

private:
	T a_;
	T b_;

};

namespace std {

template<typename T>
std::string to_string(const Rational<T>& arg) {
	return arg.to_string();
}

}

template<typename T>
class Polynom : public std::vector<T> {
public:
	using size_type = typename std::vector<T>::size_type;

	Polynom() : Polynom(0) {}

	explicit Polynom(const size_type degree) : std::vector<T>(degree + 1) {}

	constexpr size_type degree() const {
		return this->size() - 1;
	}

	Polynom add(const Polynom& rhs) const {
		Polynom res(std::max(rhs.degree(), degree()));
		std::copy(this->begin(), this->end(), res.begin());
		for (size_t i = 0; i < rhs.size(); ++i) {
			res[i] += rhs[i];
		}
		res.normalize();
		return res;
	}

	Polynom multiply(const Polynom& rhs) const {
		Polynom res(rhs.degree() + degree());
		for (size_t i = 0; i < this->size(); ++i) {
			for (size_t j = 0; j < rhs.size(); ++j) {
				res[i + j] += this->data()[i] * rhs[j];
			}
		}
		res.normalize();
		return res;
	}

	Polynom multiply(const T& rhs) const {
		Polynom res(*this);
		for (auto& it : res) {
			it *= rhs;
		}
		res.normalize();
		return res;
	}

	Polynom operator *(const T& rhs) const {
		return multiply(rhs);
	}

	Polynom& operator +=(const Polynom& rhs) {
		Polynom res = add(rhs);
		this->swap(res);
		return *this;
	}

	template<typename U>
	Polynom& operator *=(const U& rhs) {
		Polynom res = multiply(rhs);
		this->swap(res);
		return *this;
	}

	static Polynom one() {
		Polynom res;
		res.front() = 1;
		return res;
	}

	T operator()(const T& x) const {
		T result = 0;
		T deg = 1;
		for (const auto& it : *this) {
			result += it * deg;
			deg *= x;
		}
		return result;
	}

private:

	void normalize() {
		while (this->size() > 1 && this->back() == T(0)) {
			this->pop_back();
		}
	}

};

template<typename T, T MOD = BASE_MOD>
class ModInt {
public:

private:
	T value_;

};

namespace std {

template<typename T, T MOD>
struct is_integral<ModInt<T, MOD>> : std::true_type {};

}

using namespace std;

std::vector<std::string> get_input(istream& in) {
	std::vector<std::string> res;
	std::string s;
	while (std::getline(in, s)) {
		res.emplace_back(s);
	}
	return res;
}

std::unordered_map<char, size_t> wh;

inline size_t get_var(const char ch) {
	if (ch == 'n') {
		return 0;
	}
	const auto it = wh.find(ch);
	if (it != wh.end()) {
		return it->second;
	}
	const size_t ret = wh.size() + 1;
	return wh[ch] = ret;
}

struct Statement {
public:

	Statement() : is_loop_(false), loop_var_(0), range_val_(0), indent_(0) {}

	bool loop() const {
		return is_loop_;
	}

	int loop_var() const {
		return loop_var_;
	}

	int range_val() const {
		return range_val_;
	}

	size_t indent() const {
		return indent_;
	}

	bool is_loop_;
	int loop_var_;
	int range_val_;
	size_t indent_;

};

std::vector<Statement> parse_program(const std::vector<std::string>& input) {
	std::vector<Statement> program;
	for (const auto& line : input) {
		size_t indent = 0;
		size_t index = 0;
		Statement statement;
		while (index < line.length() && line[index] == ' ') {
			++indent;
			++index;
		}
		statement.indent_ = indent / 4;
		const std::string code = line.substr(index);
		if (code == "lag") {
			program.emplace_back(statement);
			continue;
		}
		statement.is_loop_ = true;
		const char variable = code[4];
		const char range_value = code[15];
		statement.loop_var_ = get_var(variable);
		statement.range_val_ = get_var(range_value);
		program.emplace_back(statement);
	}
	return program;
}

using Poly = Polynom<Rational<int>>;

using Operation = std::vector<Poly>;
using ResultLevel = std::vector<Operation>;

Poly process(const Poly& polynom) {
	Poly res(polynom.degree() + 1);
	res[1] += polynom[0];

	if (polynom.degree() < 1) {
		return res;
	}

	res[1] += Rational<int>(-1, 2) * polynom[1];
	res[2] += Rational<int>(1, 2) * polynom[1];

	if (polynom.degree() < 2) {
		return res;
	}

	res[1] += Rational<int>(1, 6) * polynom[2];
	res[2] += Rational<int>(-1, 2) * polynom[2];
	res[3] += Rational<int>(1, 3) * polynom[2];

	if (polynom.degree() < 3) {
		return res;
	}

	res[2] += Rational<int>(1, 4) * polynom[3];
	res[3] += Rational<int>(-1, 2) * polynom[3];
	res[4] += Rational<int>(1, 4) * polynom[3];

	if (polynom.degree() < 4) {
		return res;
	}

	res[1] += Rational<int>(-1, 30) * polynom[4];
	res[3] += Rational<int>(1, 3) * polynom[4];
	res[4] += Rational<int>(-1, 2) * polynom[4];
	res[5] += Rational<int>(1, 5) * polynom[4];

	if (polynom.degree() < 5) {
		return res;
	}

	res[2] += Rational<int>(-1, 12) * polynom[5];
	res[4] += Rational<int>(5, 12) * polynom[5];
	res[5] += Rational<int>(-1, 2) * polynom[5];
	res[6] += Rational<int>(1, 6) * polynom[5];

	return res;
}

void process(Operation& operation, int loop_var, int range_var) {
	operation[range_var] *= process(operation[loop_var]);
	operation[loop_var] = Poly::one();
}

void process(Stack<ResultLevel>& result_stack, Stack<Statement>& program_stack) {
	ResultLevel top_level = result_stack.pop();
	for (auto& it : top_level) {
		process(it, program_stack.top().loop_var(), program_stack.top().range_val());
	}
	ResultLevel& level = result_stack.top();
	level.insert(level.end(), top_level.begin(), top_level.end());
	program_stack.pop();
}

void solve(istream& in, ostream& out) {

	if (std::is_integral<ModInt<int>>::value) {
		std::cerr << "123" << std::endl;
		return;
	}

	wh.clear();
	std::vector<std::string> input = get_input(in);
	std::vector<Statement> program = parse_program(input);

	const size_t vars = wh.size() + 1;

	Stack<Statement> program_stack(32);
	Stack<ResultLevel> result_stack(32);

	result_stack.push(ResultLevel());

 	for (const auto& statement : program) {
		while (!program_stack.empty() && statement.indent() <= program_stack.top().indent()) {
			process(result_stack, program_stack);
		}
		if (!statement.loop()) {
			result_stack.top().emplace_back(vars, Poly::one());
			continue;
		}
		program_stack.push(statement);
		result_stack.push(ResultLevel());
	}

	while (result_stack.size() > 1) {
		process(result_stack, program_stack);
	}

	const ResultLevel top_level = result_stack.pop();
	Poly result;
	for (const auto& op : top_level) {
		Rational<int> multiplier = 1;
		for (const auto& it : wh) {
			if (isdigit(it.first)) {
				multiplier *= op[it.second](dig(it.first));
			}
		}
		result += op.front() * multiplier;
	}

	std::string ans;
	for (size_t i = 0; i < result.size(); ++i) {
		if (i > 0) {
			ans += (result[i].sign() == -1 ? '-' : '+');
		}
		ans += std::to_string(result[i].abs());
		for (size_t j = 0; j < i; ++j) {
			ans += "*n";
		}
	}
	out << ans << endl;
}

#include <fstream>

int main() {
    srand(time(NULL));
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;

    ostream& out = cout;

    out << fixed << setprecision(16);
    solve(in, out);
    return 0;
}

