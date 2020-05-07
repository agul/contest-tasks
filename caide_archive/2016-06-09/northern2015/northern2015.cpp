#include "Head.h"

#include "stack.hpp"
#include "string_utils.hpp"
#include "rational.hpp"
#include "polynom.hpp"
#include "mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 55555;

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

	bool lag() const {
		return !is_loop_;
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

Operation operator +(const Operation& lhs, const Operation& rhs) {
	const size_t n = lhs.size();
	Operation result(n);
	for (size_t i = 0; i < n; ++i) {
		result[i] = lhs[i] + rhs[i];
	}
	return result;
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
