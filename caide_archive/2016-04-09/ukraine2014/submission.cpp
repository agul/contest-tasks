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

#define all(a) a.begin(), a.end()


namespace std {


}

#ifdef _MSC_VER

#endif


namespace Random {


}


extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;


//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


using namespace std;


string tmp;
char temp[11111];

struct Pupil {
	string first_name, last_name;
	int grade;
	char grade_letter;
	int birth_day, birth_month, birth_year;

	Pupil() {}

	friend istream& operator >> (istream& io, Pupil& pupil) {
		getline(io, pupil.last_name);
		getline(io, pupil.first_name);
		getline(io, tmp);
		sscanf(tmp.c_str(), "%d%c", &pupil.grade, &pupil.grade_letter);
		getline(io, tmp);
		sscanf(tmp.c_str(), "%d.%d.%d", &pupil.birth_day, &pupil.birth_month, &pupil.birth_year);
		if (pupil.birth_year < 100) {
			pupil.birth_year += 2000;
		} else {
			pupil.birth_year += 1900;
		}
		return io;
	}

	friend ostream& operator << (ostream& io, const Pupil& pupil) {
		sprintf(temp, "%02d.%02d.%02d", pupil.birth_day, pupil.birth_month, pupil.birth_year % 1000);
		io << pupil.grade << pupil.grade_letter << ", " << pupil.last_name << ", " << pupil.first_name << ", " << temp;
		return io;
	}

};

bool surname_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.last_name < rhs.last_name;
}

bool fullname_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.last_name < rhs.last_name
		|| (lhs.last_name == rhs.last_name && lhs.first_name < rhs.first_name);
}

bool birthyear_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.birth_year < rhs.birth_year;
}

bool birthday_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.birth_month < rhs.birth_month 
		|| (lhs.birth_month == rhs.birth_month && lhs.birth_day < rhs.birth_day);
}

bool birthdate_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.birth_year < rhs.birth_year
		|| (lhs.birth_year == rhs.birth_year && birthday_cmp(lhs, rhs));
}

bool grade_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.grade < rhs.grade;
}

bool class_cmp(const Pupil& lhs, const Pupil& rhs) {
	return lhs.grade < rhs.grade
		|| (lhs.grade == rhs.grade && lhs.grade_letter < rhs.grade_letter);
}

void solve(istream& ins, ostream& out) {
	string sorts;
	getline(ins, sorts);
	int n;
	ins >> n;
	vector<Pupil> a(n);
	for (auto& it : a) {
		ins >> it;
	}

	stringstream ss;
	ss << sorts << endl;
	string sort;
	while (ss >> sort) {
		auto cmp = surname_cmp;
		if (sort == "fullname") {
			cmp = fullname_cmp;
		}
		if (sort == "birthyear") {
			cmp = birthyear_cmp;
		}
		if (sort == "birthdate") {
			cmp = birthdate_cmp;
		}
		if (sort == "birthday") {
			cmp = birthday_cmp;
		}
		if (sort == "grade") {
			cmp = grade_cmp;
		}
		if (sort == "class") {
			cmp = class_cmp;
		}
		stable_sort(all(a), cmp);
	}

	for (const auto& it : a) {
		out << it << endl;
	}
}
#include <fstream>


bool useFastIO = false;
istream * pin;
ostream * pout;

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    istream& in = cin;
    useFastIO = true;

    ostream& out = cout;
    out << fixed << setprecision(16);
    pin = &in; pout = &out;
    solve(in, out);
    return 0;
}
