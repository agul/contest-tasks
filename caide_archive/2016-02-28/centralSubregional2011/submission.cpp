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


#define ll int64_t
#define pli std::pair<ll, int>


namespace std {

	template<typename T, typename U>
	struct hash<std::pair<T, U>> {
		std::size_t operator()(const std::pair<T, U>& lhs) const {
			return lhs.first * 877117 + lhs.second;
		}
	};

}

#ifdef _MSC_VER

#endif


namespace Random {


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


	inline void flush();
	inline void new_line();

	inline void print_int(const int32_t x);
	inline void print_long(const int64_t x);
	//inline void print_string(const std::string& s);
	//inline void print_line(const std::string& s);

	IO& operator <<(const int32_t x);
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


	template<typename T>
	void print_number(const T& value);

};

extern bool useFastIO;
extern std::istream * pin;
extern std::ostream * pout;
extern IO io;


inline void new_line();

inline void print_int(const int32_t x);
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
const int MAXN = 128;

enum Commands {
	ADD,
	SUB,
	NEG,
	NOT,
	CALL,
	RET
};

const char* COMS[] = { "ADD", "SUB", "NEG", "NOT", "CALL", "RET" };


ll val[MAXN];
int com[MAXN];
char s[8];

const ll MOD = 1LL << 60;

int st[1111111], stack_top;
oaht::hash_map<pli, ll> used;


ll run(ll acc, int addr) {
	if (used.count({ acc, addr })) {
		return used[{acc, addr}];
	}
	ll& cur = used[{acc, addr}];
	if (com[addr] == ADD) {
		return cur = run((acc + val[addr]) % MOD, addr + 1);
	}
	if (com[addr] == SUB) {
		ll x = val[addr];
		return cur = run((x - acc) % MOD, addr + 1);
	}
	if (com[addr] == NEG) {
		return cur = run(-acc, addr + 1);
	}
	if (com[addr] == NOT) {
		return cur = run(~acc, addr + 1);
	}
	if (com[addr] == CALL) {
		st[++stack_top] = addr;
		return cur = run(acc, val[addr]);
	}
	if (com[addr] == RET) {
		if (stack_top == -1) {
			return cur = acc;
		}
		return cur = run(acc, st[stack_top--] + 1);
	}
	assert(false);
	return -1;
}

void solve(istream& ins, ostream& out) {
	int n;
	ins >> n >> __;
	for (int i = 0; i < n; ++i) {
		
		int x;
		ins >> x >> s;
		for (int j = 0; j < 6; ++j) {
			if (strcmp(s, COMS[j]) == 0) {
				com[i] = j;
			}
		}
		if (com[i] == ADD || com[i] == SUB || com[i] == CALL) {
			ins >> val[i];
		}
	}
	io << __ << endl;
	for (int _ = 0; _ < __; ++_) {
		long long x;
		ins >> x;
		stack_top = -1;
		io << run(x, 0) << endl;
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

inline void IO::print_int(const int32_t x) {
	print_number(x);
}


inline void IO::print_long(const int64_t x) {
	print_number(x);
}


IO& IO::operator <<(const int32_t x) {
	::print_int(x);
	return *this;
}


IO& IO::operator <<(const int64_t x) {
	::print_long(x);
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

inline void print_int(const int32_t x) {
	if (useFastIO) {
		io.print_int(x);
		return;
	}
	*pout << x;
}


inline void print_long(const int64_t x) {
	if (useFastIO) {
		io.print_long(x);
		return;
	}
	*pout << x;
}
