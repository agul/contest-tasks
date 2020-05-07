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

#define X first
#define Y second
#define all(a) a.begin(), a.end()

#define ll int64_t
#define pii std::pair<int, int>


namespace std {


}

#ifdef _MSC_VER

#endif


namespace Random {


}


inline bool is_digit(const char ch) {
	return (ch >= '0' && ch <= '9');
}


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


	inline void shift_char();

	inline int32_t next_int();

	IO& operator >>(int32_t& x);

	inline void flush();
	inline void new_line();

	inline void print_long(const int64_t x);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int64_t x);

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

	inline void update_buffer();

	template<typename T>
	T read_number();

	template<typename T>
	void print_number(const T& value);

};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;

inline int32_t next_int();


inline void new_line();

inline void print_long(const int64_t x);
//inline void print_string(const std::string& s);
//inline void print_line(const std::string& s);


namespace oaht
{

	using std::size_t;

	enum class node_state {
		FREE,
		IN_USE,
		ERASED
	};

	template<typename _Key, typename _Value>
	struct node {
		_Key key;
		_Value value;
		node_state state = node_state::FREE;
	};

	template<typename _Key, typename _Value, typename _Hash = std::hash<_Key>>
	class hash_map {
	public:		
		const node<_Key, _Value> UNDEFINED;

		hash_map(size_t capacity) : capacity(capacity), size(0), UNDEFINED(node<_Key, _Value>()) {
			nodes = new node<_Key, _Value>[capacity];

			for (size_t i = 0; i < capacity; i++)
				nodes[i] = node<_Key, _Value>();
		}

		hash_map() : hash_map(3) {
		}

		size_t count(const _Key& key) const {
			size_t index = get_index(key, capacity);

			for (size_t d = 0; d < capacity; d++) {
				if (nodes[index].state == node_state::FREE)
					return false;
				if (nodes[index].state == node_state::IN_USE
					&& nodes[index].key == key)
					return true;
				index++;
				if (index == capacity)
					index = 0;
			}

			return false;
		}


		_Value& operator[](const _Key& key) {
			if ((size << 1) > capacity)
				rehash();

			size_t index;
			bool result = put(key, index, nodes, capacity);
			if (result)
				size++;

			return nodes[index].value;
		}

		void clear() {
			for (size_t d = 0; d < capacity; d++) {
				nodes[d].state = node_state::FREE;
			}
			size = 0;
		}

		~hash_map() {
			delete[] nodes;
		}

		size_t capacity;
		size_t size;

		node<_Key, _Value>* nodes;
		
	private:
		size_t get_index(const _Key& key, size_t size) const {
			return (h(key) * 22543) % size;
		}

		void rehash() {
			size_t n_capacity = (capacity << 1);

			node<_Key, _Value>* n_nodes = new node<_Key, _Value>[n_capacity];
			for (size_t i = 0; i < n_capacity; i++)
				n_nodes[i] = node<_Key, _Value>();

			for (size_t i = 0; i < capacity; i++)
			if (nodes[i].state == node_state::IN_USE) {
				size_t index;
				put(nodes[i].key, index, n_nodes, n_capacity);
				n_nodes[index].value = nodes[i].value;
			}

			delete[] nodes;

			nodes = n_nodes;
			capacity = n_capacity;
		}

		bool put(const _Key& key, size_t& index, node<_Key, _Value>* nodes, size_t nodes_length) {
			index = get_index(key, nodes_length);

			for (size_t i = 0; i < nodes_length; i++) {
				if (nodes[index].state == node_state::FREE
					|| nodes[index].state == node_state::ERASED) {
					nodes[index].key = key;
					nodes[index].state = node_state::IN_USE;
					nodes[index].value = 0;
					return true;
				}

				if (nodes[index].key == key)
					return false;

				index++;
				if (index == nodes_length)
					index = 0;
			}

			return false;
			// throw std::logic_error("Unexpected case.");
		}

		_Hash h;
	};

}


using namespace std;

int __;
IO io;
const int MAXN = 1111111;

int compressed[MAXN];
oaht::hash_map<int, int> rows;
vector<pii> events[MAXN];
vector<pii> colored[MAXN];
vector<pair<int, pii>> input;

int get_row(const int row) {
	if (rows.count(row)) {
		return rows[row];
	}
	int sz = rows.size;
	compressed[sz] = row;
	rows[row] = sz;
	return sz;
}

void solve(istream& ins, ostream& out) {
	io >> __;
	for (int _ = 0; _ < __; ++_) {
		int m, n, k, p;
		io >> m >> n >> k >> p;
		rows.clear();
		input.clear();
		for (int i = 0; i < p; ++i) {
			int b, e, row;
			io >> b >> e >> row;
			input.emplace_back(row, pii(b, e));
		}
		sort(all(input));
		for (const auto& it : input) {
			int row = get_row(it.X);
			events[row].emplace_back(it.Y.X, 0);
			events[row].emplace_back(it.Y.Y + 1, 1);
		}
		int rows_cnt = rows.size;
		for (int i = 0; i < rows_cnt; ++i) {
			auto& cur_vector = events[i];
			sort(all(cur_vector));
			int balance = 0;
			int events_cnt = cur_vector.size();
			int cur_index = 0;
			for (int j = 0; j < events_cnt; ++j) {
				pii& e = cur_vector[j];
				if (e.Y) {
					--balance;
					if (balance == 0) {
						cur_vector[cur_index++] = e;
					}
				}
				else {
					++balance;
					if (balance == 1) {
						cur_vector[cur_index++] = e;
					}
				}
			}
			cur_vector.resize(cur_index);
		}
		for (int i = 1; i < rows_cnt - 1; ++i) {
			if (compressed[i - 1] != compressed[i] - 1 || compressed[i + 1] != compressed[i] + 1) {
				continue;
			}
			vector<pii> tmp = events[i];
			std::copy(all(events[i - 1]), back_inserter(tmp));
			std::copy(all(events[i + 1]), back_inserter(tmp));
			sort(all(tmp));
			int balance = 0;
			int last = 0;
			for (const auto& it : tmp) {
				if (it.Y) {
					if (balance == 3 && it.X - last >= k) {
						colored[i - 1].emplace_back(last, 0);
						colored[i - 1].emplace_back(it.X - 1, 1);
						colored[i].emplace_back(last, 0);
						colored[i].emplace_back(it.X - 1, 1);
						colored[i + 1].emplace_back(last, 0);
						colored[i + 1].emplace_back(it.X - 1, 1);
					}
					--balance;
				}
				else {
					++balance;
					if (balance == 3) {
						last = it.X;
					}
				}
			}
		}
		ll ans = 0;
		for (int i = 0; i < rows_cnt; ++i) {
			auto& cur_vector = colored[i];
			sort(all(cur_vector));
			int balance = 0;
			int last = 0;
			for (const auto& it : cur_vector) {
				if (it.Y) {
					--balance;
					if (balance == 0) {
						ans += it.X - last + 1;
					}
				}
				else {
					++balance;
					if (balance == 1) {
						last = it.X;
					}
				}
			}
			events[i].clear();
			colored[i].clear();
		}
		io << ans << endl;
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


template<typename T>
T IO::read_number() {
	bool is_negative = false;
	while (!eof_ && !is_digit(current_char_) && (std::is_unsigned<T>() || current_char_ != '-')) {
		shift_char();
	}
	if (std::is_signed<T>() && current_char_ == '-') {
		is_negative = true;
		shift_char();
	}
	T result = 0;
	while (!eof_ && is_digit(current_char_)) {
		result = (result << 3) + (result << 1) + current_char_ - '0';
		shift_char();
	}
	return (is_negative ? result * -1 : result);
}

template<typename T>
void IO::print_number(const T& value) {
	T current_value = value;
	if (write_buffer_offset_ + 32 > kBufferSize) {
		flush();
	}
	if (current_value < 0) {
		write_buffer_[write_buffer_offset_++] = '-';
		current_value = abs(current_value);
	} else
	if (current_value == 0) {
		write_buffer_[write_buffer_offset_++] = '0';
		return;
	}
	std::size_t start_index = write_buffer_offset_;
	while (current_value != 0) {
		write_buffer_[write_buffer_offset_++] = current_value % 10 + '0';
		current_value /= 10;
	}
	std::reverse(write_buffer_.begin() + start_index, write_buffer_.begin() + write_buffer_offset_);
}


inline void IO::update_buffer() {
	if (read_buffer_offset_ == read_bytes_count_) {
		read_bytes_count_ = fread(&read_buffer_[0], sizeof(read_buffer_[0]), read_buffer_.size(), stdin);
		if (read_bytes_count_ == 0) {
			eof_ = true;
			return;
		}
		read_buffer_offset_ = 0;
	}
}

inline void IO::shift_char() {
	update_buffer();
	current_char_ = read_buffer_[read_buffer_offset_++];
}

inline int32_t IO::next_int() {
	return read_number<int32_t>();
}


IO& IO::operator >>(int32_t& x) {
	x = ::next_int();
	return *this;
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


inline void IO::print_long(const int64_t x) {
	print_number(x);
}


IO& IO::operator <<(const int64_t x) {
	::print_long(x);
	return *this;
}


IO& IO::operator <<(std::ostream& (*)(std::ostream&)) {
	::new_line();
	return *this;
}

inline int32_t next_int() {
	if (useFastIO) {
		return io.next_int();
	}
	int32_t ret;
	*pin >> ret;
	return ret;
}


inline void new_line() {
	if (useFastIO) {
		io.new_line();
		return;
	}
	*pout << std::endl;
}


inline void print_long(const int64_t x) {
	if (useFastIO) {
		io.print_long(x);
		return;
	}
	*pout << x;
}
