#include "base/header.hpp"

using namespace std;

double sqr(double a) // квадрат числа
{
	return a * a;
}


bool doubleEqual(double a, double b) // сравниваем на равенство с eps, константой 1е-9 используется только здесь
{
	return fabs(a - b) < 1e-9;
}


bool doubleLessOrEqual(double a, double b) // <= с eps
{
	return a < b || doubleEqual(a, b);
}


bool doubleLess(double a, double b) // < с eps
{
	return a < b && !doubleEqual(a, b);
}


bool doubleGreaterOrEqual(double a, double b) // >= с eps
{
	return a > b || doubleEqual(a, b);
}


bool doubleGreater(double a, double b) // > с eps
{
	return a > b && !doubleEqual(a, b);
}


double mySqrt(double a) // mySqrt с проверкой, что корректен аргумент
{
	if(doubleLess(a, 0) ) //некорректный вызов
	{
		throw "sqrt(-1)";
	}
	if(a < 0) return 0; //отрицательное ввиду небольшой погрешности
	return sqrt(a);
}


struct Point{ // класс точки или вектора, далее мы эти понятия разделять не будем
	// но условимся (для удобного чтения) большими буквами обозначать точки (A, B, C, D, ...)
	// маленькими - вектора(v, u, w,...)
private: double x, y; // 2 приватных поля, других не будет
public:
	Point(): x(0), y(0) {} // конструктор по умолчанию

	Point(double x, double y): x(x), y(y) {} // намеренно сделаем два конструктора вместо Point(x = 0...)
	//Это избавит нас от ошибок вида Point A = 2;

	void scan() // читаем координаты точки
	{
		scanf("%lf %lf", &x, &y);
	}

	void print() const // выводим координаты точки
	{
		printf("%.10lf %.10lf\n", x, y);
	}

	Point operator+(const Point & p) const // сложение 2х векторов
	{
		return Point(x + p.x, y + p.y);
	}

	Point operator-(const Point & p) const // вычитание 2х векторов
	{
		return Point(x - p.x, y - p.y);
	}

	Point operator-() const // обратный вектор
	{
		return Point(-x, -y);
	}

	Point operator*(double k) const // умножение вектора на скаляр
	{
		return Point(x * k, y * k);
	}

	Point operator/(double k) const // деление вектора на скаляр
	{
		return Point(x / k, y / k);
	}

	double operator%(const Point & p) const // скалярное произведение
	{
		return x * p.x + y * p.y;
	}

	double operator*(const Point & p) const // векторное произведение
	{
		return x * p.y - y * p.x;
	}

	double length() const // длина вектора по определению из ан.гема (корень из скалярного квадрата)
	{
		return mySqrt(*this % *this);
	}

	double distTo(const Point & p) const //расстояние между 2мя точками - модуль вектора между ними
	{
		return (*this - p).length();
	}

	double distTo(const Point & A, const Point & B) const // расстояние от точки до прямой (всегда >= 0)
	{
		double d = A.distTo(B);
		if(doubleEqual(d, 0) ) // прямая должна задаваться двумя! точками
		{
			throw "A = B";
		}
		double s = (*this - A) * (*this - B); // удвоенная площадь треугольника
		return fabs(s) / d; // метод площадей
	}

	Point normalize(double k = 1) const // выставляет длину вектора в k
	{
		double len = length(); // Текущая длина
		if(doubleEqual(len, 0) ) // если длина ноль
		{
			if(doubleEqual(k, 0) )
			{
				return Point();
			}
			throw "zero-size vector"; //кроме нулевой никакую получить не можем
		}
		return *this * (k / len);
	}

	Point getH(const Point & A, const Point & B) const // опускаем высоту из точки на прямую (A, B)
	{
		Point C = *this;
		Point v = B - A; // направляющий вектор прямой
		Point u = C - A; // вектор, проекция которого нам нужна
		double k = v % u / v.length(); // нашли длину проекции
		v = v.normalize(k); // нашли проекцию u на v
		Point H = A + v; // подвинули точку A в проекцию конца вектора u, отложенного из A
		return H;
	}

	Point rotate() const // поворот на 90 градусов против часовой стрелки (положительное направление)
	{
		return Point(-y, x);
	}

	Point rotate(double alpha) const // поворот на угол alpha против часовой стрелки
	// (по часовой стрелке, если alpha < 0)
	{
		return rotate(cos(alpha), sin(alpha) ); // делегируем задачу другому экземпляру функции
	}

	Point rotate(double cosa, double sina) const // поворот с заданными косинусом и синусом
	{
		Point v = *this;
		Point u = v.rotate(); // вектор, перпендикулярный v, теперь (v, u) - базис, в котором мы знаем ответ
		Point w = v * cosa + u * sina; // зная координаты в базисе (v, u), нашли w
		return w;
	}

	bool isZero() const // проверка на то, что точка нулевая без сложных операций и погрешности
	{
		return doubleEqual(x, 0) && doubleEqual(y, 0);
	}

	bool isOnLine(const Point & A, const Point & B) const // точка на прямой?
	{
		return doubleEqual( (A - *this) * (B - *this), 0);
	}

	bool isInSegment(const Point & A, const Point & B) const // точка внутри отрезка?
	{
		return isOnLine(A, B) && doubleLessOrEqual( (A - *this) % (B - *this), 0 );
	}

	bool isInSegmentStrictly(const Point & A, const Point & B) const // точка внутри отрезка строго?
	{
		return isOnLine(A, B) && doubleLess( (A - *this) % (B - *this), 0 );
	}

	double getAngle() const
	{
		return atan2(y, x); // угол между вектором и осью ОХ
	}

	double getAngle(Point u) const
	{
		Point v = *this;
		return atan2(v * u, v % u); // ориентированный угол между векторами
	}

};


int getIntersection // ищем пересечение прямой (A, B) и прямой (C, D)
		(
				const Point & A,
				const Point & B,
				const Point & C,
				const Point & D,
				Point & O
		)
{
	Point v = B - A; // направляющий вектор прямой (A, B)
	double s1 = (C - A) * (D - A); // площадь треугольника A, C, D
	double s2 = (D - B) * (C - B); // площадь треугольника B, D, C
	double s = s1 + s2; // площадь четурёхугольника
	if(doubleEqual(s, 0) ) // прямые параллельны (или совпадают)
	{
		if(!A.isOnLine(C, D) ) // прямые параллельны
		{
			return 0; // пересечение пусто
		}
		return 2; // больше 1ой точки в пересечении
	}
	v = v / s;
	v = v * s1; // вектора AO и AB пропорциональны площадям s1 и s
	O = A + v; // нашли точку пересечения
	return 1; // 1 точка в пересечении
}


int getIntersection // ищем пересечение 2х окружностей с центрами в A, B, радиусами rA, rB
		(
				const Point & A,
				double rA,
				const Point & B,
				double rB,
				Point & M,
				Point & N
		)
{
	double d = A.distTo(B); // расстояние между точками
	if(doubleLess(rA + rB, d) || doubleLess(d, fabs(rA - rB)) ) // если окружности не касаются, то точек 0
	{
		return 0;
	}
	double a = (sqr(rA) - sqr(rB) + sqr(d) ) / 2 / d; // длину проекции отрезка (от A до пересечения окружностей) на прямую AB
	double h = mySqrt(sqr(rA) - sqr(a)); //расстояние о точки пересечения окружностей до прямой AB
	Point v = B - A; //направляющий вектор прямой AB
	Point u = v.rotate(); // нормальный вектор к прямой AB
	v = v.normalize(a);
	u = u.normalize(h); //нормируем до нужных длин оба вектора
	Point H = A + v;
	M = H + u;
	N = H - u;
	if(u.isZero() ) return 1; //если u = 0, то окружности касаются
	return 2;
}



int getIntersection // ищем пересечение прямой (A, B) и окружности (O, r)
		(
				const Point & A,
				const Point & B,
				const Point & O,
				double r,
				Point & M,
				Point & N
		)
{
	double h = O.distTo(A, B);
	if(doubleLess(r, h) ) //если окружность далеко от прямой
	{
		return 0;
	}
	Point H = O.getH(A, B); //уронили высоту на AB
	Point v = B - A; //взяли направляющий вектор прямой
	double k = mySqrt(sqr(r) - sqr(h) ); // величина, на которую надо подвинуть H до точки пересечения окружности и прямой
	v = v.normalize(k);
	M = H + v;
	N = H - v;
	if(v.isZero() ) return 1;
	return 2;
}


int getTangent  // получаем касательные из точки A к оркужности (O, r)
		(
				const Point & A,
				const Point & O,
				double r,
				Point & M,
				Point & N
		)
{
	Point v = O - A;
	double d = v.length();
	if(doubleLess(d, r) ) return 0; // точка внутри, не существует касательной
	double alpha = asin(r / d); // нашли угол между касательной и вектором v
	double L = mySqrt(sqr(d) - sqr(r)); // длина касательной
	v = v.normalize(L); // теперь v имеет длину касательной
	M = A + v.rotate(alpha);
	N = A - v.rotate(alpha); // повернули вектор v в обе стороны и нашли концы обоих касательных
	if(doubleEqual(r, d) ) return 1;
	return 2;
}

class WormholeInOne {
public:
	static constexpr bool kWriteCaseNumber = true;
	static constexpr bool kMultiTest = true;
	void solve(std::istream& in, std::ostream& out) {
		int n;
		in >> n;
		std::vector<Point> points;
		for (int i : range(n)) {
			double x, y;
			in >> x >> y;
			points.emplace_back(x, y);
		}

		std::vector<pii> edges;
		for (int i : range(n)) {
			for (int j : range(i + 1, n)) {
				edges.emplace_back(i, j);
			}
		}
		const int m = edges.size();
		debug(m);

		int ans = 1;
		for (int a : range(n)) {
			for (int b : range(n)) {
				if (a == b) {
					continue;
				}
				const Point from = points[a];
				const Point to = points[b];

				const Point vec = to - from;
				std::vector<int> going_to(n, -1);
				for (int c : range(n)) {
					const Point start = points[c];
					const Point to_vec = start + vec;
					for (int d : range(n)) {
						if (c == d) {
							continue;
						}
						const Point finish = points[d];
						if (!finish.isOnLine(start, to_vec)) {
							continue;
						}
						bool ok = true;
						for (int e : range(n)) {
							const Point current = points[e];
							if (current.isInSegmentStrictly(start, finish)) {
								ok = false;
							}
						}
						if (!ok) {
							continue;
						}
						going_to[c] = d;
					}
				}

				for (int mask : range(1 << m)) {
					std::vector<int> hole(n, -1);
					bool ok = true;
					for (int i : range(m)) {
						if ((1 << i) & mask) {
							int from = edges[i].first;
							int to = edges[i].second;

							if (hole[from] != -1 || hole[to] != -1) {
								ok = false;
							}
							hole[from] = to;
							hole[to] = from;
						}
					}
					if (!ok) {
						continue;
					}
					for(int start : range(n)) {
						std::vector<bool> used(n, false);
						int cur = start;
						int best = 0;
						while (!used[cur]) {
							++best;
							used[cur] = true;
							if (hole[cur] != -1) {
								cur = hole[cur];
							} else
							if (going_to[cur] != -1) {
								cur = going_to[cur];
							}
						}
						umax(ans, best);
					}
				}

			}
		}
		out << ans << std::endl;

	}


	WormholeInOne() {}


	static constexpr bool kUseCustomChecker = false;
	bool check(std::istringstream in, std::istringstream jury, std::istringstream out) {
		return true;
	}


	static constexpr size_t kGeneratedTestsCount = 0;
	static constexpr bool kStopAfterFirstFail = false;
	static void generate_test(std::ostream& test) {}

};
