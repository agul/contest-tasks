#include "base/header.hpp"
#include "maths/maths.hpp"
#include "maths/mod_int.hpp"

using namespace std;

int __;
const int MOD = 1000000007;
const int MAXN = 111111;

struct Date {
	int year;
	int month;
	int day;
	int weekday;

	Date() : year(1970), month(0), day(0), weekday(3) {}

	bool is_leap() const {
		return is_leap_year(year);
	}

	friend ostream& operator <<(ostream& out, const Date& rhs) {
		out << rhs.day + 1 << "." << rhs.month + 1 << "." << rhs.year << "(" << rhs.weekday + 1 << ")";
		return out;
	}
};

inline int get_days_in_month(const int month, const int year) {
	const int days = kDayMonth[month] + (month == 1 && is_leap_year(year) ? 1 : 0);
	return days;
}

struct Moment {
	Date date;
	int hour;
	int minute;
	int second;

	Moment() : date(), hour(0), minute(0), second(0) {}

	friend istream& operator >>(istream& in, Moment& rhs) {
		in >> rhs.second >> rhs.minute >> rhs.hour >> rhs.date.weekday >> rhs.date.day >> rhs.date.month;
		if (rhs.date.weekday != -1) {
			--rhs.date.weekday;
		}
		if (rhs.date.day != -1) {
			--rhs.date.day;
		}
		if (rhs.date.month != -1) {
			--rhs.date.month;
		}
		return in;
	}

	void next_month() {
		const int days_rem = get_days_in_month(date.month, date.year) - date.day;
		add_mod(date.weekday, days_rem % 7, 7);
		++date.month;
		if (date.month == 12) {
			date.month = 0;
			++date.year;
		}
		date.day = 0;
		hour = 0;
		minute = 0;
		second = 0;
	}

	void next_day() {
		const int days = get_days_in_month(date.month, date.year);
		++date.day;
		add_mod(date.weekday, 1, 7);
		hour = 0;
		minute = 0;
		second = 0;
		if (date.day == days) {
			next_month();
		}
	}

	void next_hour() {
		++hour;
		minute = 0;
		second = 0;
		if (hour == 24) {
			next_day();
		}
	}
	
	void next_minute() {
		++minute;
		second = 0;
		if (minute == 60) {
			next_hour();
		}
	}

	void next_second() {
		++second;
		if (second == 60) {
			next_minute();
		}
	}

	void set_month(const int month) {
		bool first = true;
		while (date.month != month || first) {
			first = false;
			next_month();
		}
	}

	void next_year() {
		set_month(0);
	}

	friend ostream& operator <<(ostream& out, const Moment& rhs) {
		out << rhs.hour << ":" << rhs.minute << ":" << rhs.second << " " << rhs.date;
		return out;
	}
};

namespace parser {

inline void parse_year(Date& date, ll& time_passed) {
	while (true) {
		const int days = 365 + (date.is_leap() ? 1 : 0);
		const int seconds = days * 86400;
		if (time_passed < seconds) {
			break;
		}
		time_passed -= seconds;
		++date.year;
		add_mod(date.weekday, days % 7, 7);
	}
}

inline void parse_month(Date& date, ll& time_passed) {
	for (size_t month = 0; month < 12; ++month) {
		const int days = get_days_in_month(month, date.year);// kDayMonth[i] + (i == 1 && date.is_leap() ? 1 : 0);
		const int seconds = days * 86400;
		if (time_passed < seconds) {
			break;
		}
		time_passed -= seconds;
		++date.month;
		add_mod(date.weekday, days % 7, 7);
	}
}

inline void parse_day(Date& date, ll& time_passed) {
	const int seconds = 86400;
	date.day = time_passed / seconds;
	add_mod(date.weekday, date.day % 7, 7);
	time_passed %= seconds;
}

inline Date parse_date(ll& time_passed) {
	Date date;
	parse_year(date, time_passed);
	parse_month(date, time_passed);
	parse_day(date, time_passed);
	return date;
}

inline int parse_hour(ll& time_passed) {
	const int seconds = 3600;
	const int hour = time_passed / seconds;
	time_passed %= seconds;
	return hour;
}

inline int parse_minute(ll& time_passed) {
	const int seconds = 60;
	const int minute = time_passed / seconds;
	time_passed %= seconds;
	return minute;
}

inline int parse_second(ll& time_passed) {
	const int second = time_passed;
	time_passed = 0;
	return second;
}

inline Moment parse_moment(ll time_passed) {
	Moment moment;
	moment.date = parse_date(time_passed);
	moment.hour = parse_hour(time_passed);
	moment.minute = parse_minute(time_passed);
	moment.second = parse_second(time_passed);
	return moment;
}

}  // namespace parser

namespace encoder {

inline ll encode_year(const Date& date) {
	ll time = 0;
	for (int year = 1970; year < date.year; ++year) {
		const int days = 365 + (is_leap_year(year) ? 1 : 0);
		const int seconds = days * 86400;
		time += seconds;
	}
	return time;
}

inline ll encode_month(const Date& date) {
	ll time = 0;
	for (int month = 0; month < date.month; ++month) {
		const int days = get_days_in_month(month, date.year); // kDayMonth[month] + (month == 1 && date.is_leap() ? 1 : 0);
		const int seconds = days * 86400;
		time += seconds;
	}
	return time;
}

inline ll encode_day(const Date& date) {
	const int seconds = 86400;
	return date.day * seconds;
}

inline ll encode_date(const Date& date) {
	ll time = 0;
	time += encode_year(date);
	time += encode_month(date);
	time += encode_day(date);
	return time;
}

inline ll encode_hour(const int hour) {
	const int seconds = 3600;
	return hour * seconds;
}

inline ll encode_minute(const int minute) {
	const int seconds = 60;
	return minute * seconds;
}

inline ll encode_second(const int second) {
	return second;
}

inline ll encode_moment(const Moment& moment) {
	ll time = 0;
	time += encode_date(moment.date);
	time += encode_hour(moment.hour);
	time += encode_minute(moment.minute);
	time += encode_second(moment.second);
	return time;
}

}  // namespace encoder

bool test_minute(Moment& good_moment, const Moment& config) {
	Moment cur = good_moment;
	for (int second = cur.second; second < 60; ++second) {
		bool ok = (config.second == -1 || config.second == cur.second);
		if (ok) {
			good_moment = cur;
			return true;
		}
		cur.next_second();
	}
	return false;
}

bool test_hour(Moment& good_moment, const Moment& config) {
	Moment cur = good_moment;
	for (int minute = cur.minute; minute < 60; ++minute) {
		bool ok = (config.minute == -1 || config.minute == cur.minute);
		if (ok && test_minute(cur, config)) {
			good_moment = cur;
			return true;
		}
		cur.next_minute();
	}
	return false;
}

bool test_day(Moment& good_moment, const Moment& config) {
	Moment cur = good_moment;
	for (int hour = cur.hour; hour < 24; ++hour) {
		bool ok = (config.hour == -1 || config.hour == cur.hour);
		if (ok && test_hour(cur, config)) {
			good_moment = cur;
			return true;
		}
		cur.next_hour();
	}
	return false;
}

bool test_month(Moment& good_moment, const Moment& config) {
	const int days = get_days_in_month(good_moment.date.month, good_moment.date.year);
	Moment cur = good_moment;
	for (int day = good_moment.date.day; day < days; ++day) {
		bool ok = false;
		if (config.date.day == -1) {
			ok |= (config.date.weekday == -1 || config.date.weekday == cur.date.weekday);
		} else {
			if (config.date.weekday != -1) {
				ok |= (config.date.day == cur.date.day || config.date.weekday == cur.date.weekday);
			} else {
				ok |= (config.date.day == cur.date.day);
			}			
		}
		if (ok && test_day(cur, config)) {
			good_moment = cur;
			return true;
		}
		cur.next_day();
	}
	return false;
}

void solve(std::istream& in, std::ostream& out) {
	Moment config;
	in >> config >> __;
	for (int _ : range(__)) {
		ll time_passed;
		in >> time_passed;
		const Moment current_moment = parser::parse_moment(time_passed);
		// const ll encoded = encoder::encode_moment(current_moment);
		// out << boolalpha << current_moment << " " << encoded << " " << (encoded == time_passed) << endl;
		Moment good_moment = current_moment;
		good_moment.next_second();
		
		if (config.date.month != -1 && config.date.month != good_moment.date.month) {
			good_moment.set_month(config.date.month);
		}

		while (!test_month(good_moment, config)) {
			if (config.date.month != -1) {
				good_moment.set_month(config.date.month);
			}
			else {
				good_moment.next_month();
			}
		}


		const ll ans = encoder::encode_moment(good_moment);
		out << ans << endl;
	}
}
