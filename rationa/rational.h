#pragma once

class Rational {
private:
	void simplify();
	static int gcd(int a, int b);
public:
	int num;
	int den;
	Rational();
	Rational(int n);
	Rational(int n, int d);
	Rational& operator +=(const Rational& r);
	Rational operator +(const Rational& r) const;
	Rational& operator-=(const Rational& r);
	Rational operator-(const Rational& r) const;
	Rational& operator *=(const Rational& r);
	Rational operator *(const Rational& r) const;
	Rational& operator /=(const Rational& r);
	Rational operator /(const Rational& r) const;
	double toDouble() const;  // ïðåîáðàçîâàíèå â double
	bool operator==(const Rational& r) const;
	bool operator!=(const Rational& r) const;
	bool operator<(const Rational& r) const;
	bool operator<=(const Rational& r) const;
	bool operator>(const Rational& r) const;
	bool operator>=(const Rational& r) const;

};
void KvUrav(const Rational& a, const Rational& b, const Rational& c);