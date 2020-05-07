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


class IO {
public:
	
	constexpr static const std::size_t kBufferSize = 1 << 18;

	IO() : read_bytes_count_(0), read_buffer_offset_(0), current_char_(0), eof_(false) {
		static_assert(kBufferSize > 32, "Size of a buffer must be greater than 32 due to comparison in IO::flush() method.");
	}

	~IO() {
		flush();
	}

	IO(const IO&) = delete;
	IO& operator=(const IO&) = delete;
	IO(const IO&&) = delete;
	IO& operator=(const IO&&) = delete;

	
	inline void flush();
	inline void new_line();

	
	inline void print_string(const char* s);
	//inline void print_string(const std::string& s);
	
	//inline void print_line(const std::string& s);

	
	IO& operator <<(const char* s);
	IO& operator <<(const std::string& s);

	// Intended to use with std::endl.
	IO& operator <<(std::ostream& (*)(std::ostream&));

	
private:
	using Buffer = std::array<char, kBufferSize>;
	Buffer read_buffer_;
	Buffer write_buffer_;
	std::size_t read_bytes_count_;
	std::size_t read_buffer_offset_;
	std::size_t write_buffer_offset_;
	bool eof_;
	char current_char_;

	
};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;


inline void new_line();


inline void print_string(const char* s);
//inline void print_string(const std::string& s);

//inline void print_line(const std::string& s);


using namespace std;


IO io;


const size_t REV[] = { 5, 3, 4, 1, 2, 0 };

const size_t INDICES[3][4] = {
	{1, 2, 3, 4},
	{0, 4, 5, 2},
	{0, 1, 5, 3}
};

std::string normalize(const std::string& ans, const bool first) {
	std::vector<std::string> rotates;
	for (size_t i = 0; i < 6; ++i) {
		std::string tmp(6, '$');
		std::vector<bool> used(6, false);
		tmp.front() = ans[i];
		tmp.back() = ans[REV[i]];
		used[i] = used[REV[i]] = true;
		size_t core_index = std::min(i, REV[i]);
		for (size_t j = 0; j < 4; ++j) {
			tmp[j + 1] = ans[INDICES[core_index][j]];
		}
		for (size_t j = 0; j < 4; ++j) {
			rotates.emplace_back(tmp);
			std::rotate(tmp.begin() + 1, tmp.begin() + 2, tmp.begin() + 5);
		}
	}
	std::sort(rotates.begin(), rotates.end());
	if (first) {
		return normalize(rotates.front(), false);
	}
	return rotates.front();
}

void solve(istream& ins, ostream& out) {
	std::set<std::string> ans;
	std::vector<std::string> input(6);
	std::string permutation;
	for (auto& it : input) {
		ins >> it;
		std::sort(it.begin() + 1, it.end());
		permutation += it.front();
	}
	std::sort(input.begin(), input.end());
	std::sort(permutation.begin(), permutation.end());

	do {
		std::vector<std::string> vision(6);
		for (int i = 0; i < 6; ++i) {
			auto& cur = vision[i];
			cur += permutation[i];
			for (int j = 0; j < 6; ++j) {
				if (j != REV[i] && j != i) {
					cur += permutation[j];
				}
			}
			std::sort(cur.begin() + 1, cur.end());
		}
		std::sort(vision.begin(), vision.end());
		if (vision == input) {
			ans.insert(normalize(permutation, true));
		}
	} while (std::next_permutation(permutation.begin(), permutation.end()));

	if (ans.empty()) {
		io << "Impossible" << endl;
		return;
	}
	io << *ans.cbegin() << endl;
	if (ans.size() > 1) {
		io << *ans.crbegin() << endl;
	}
}


#include <fstream>


extern class IO io;
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


inline void IO::flush() {
	fwrite(&write_buffer_[0], sizeof(write_buffer_[0]), write_buffer_offset_, stdout);
	write_buffer_offset_ = 0;
}

inline void IO::new_line() {
	if (write_buffer_offset_ == kBufferSize) {
		flush();
	}
	write_buffer_[write_buffer_offset_++] = '\n';
}


inline void IO::print_string(const char* s) {
	for (std::size_t i = 0; s[i] != '\0'; ++i) {
		if (write_buffer_offset_ == kBufferSize) {
			flush();
		}
		write_buffer_[write_buffer_offset_++] = s[i];
	}
}


IO& IO::operator <<(const char* s) {
	::print_string(s);
	return *this;
}

IO& IO::operator <<(const std::string& s) {
	::print_string(s.c_str());
	return *this;
}

IO& IO::operator <<(std::ostream& (*)(std::ostream&)) {
	::new_line();
	return *this;
}


inline void new_line() {
	if (useFastIO) {
		io.new_line();
		return;
	}
	*pout << std::endl;
}


inline void print_string(const char* s) {
	if (useFastIO) {
		io.print_string(s);
		return;
	}
	*pout << s;
}


