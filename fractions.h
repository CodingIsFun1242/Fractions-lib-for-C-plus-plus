/*fractions.h */
/*
 * Copyright ©2026 王家祺(Jacky Velarde Z.) <3594929067@qq.com>
 *
 * This file is released under the GPLv2 (or later, at your option).
 *
 * All Rights Reserved.
 *
 */

#ifndef FRACTIONS_H
#define FRACTIONS_H
using type = int; //Change int to whatever you need


#include <cstdlib>
#include<iostream>
#include <cmath>
#include <string>
#include <stdexcept>

template <typename T>
static inline T gcd(T a, T b)
{
	a = std::abs(a);
	b = std::abs(b);
	while (b != 0)
	{
		T temp = b;
		b = a % b;
		a = temp;

	}
	return a;
}
inline static int Decimal_count(double in) {
	std::string s = std::to_string(in);
	const size_t pos = s.find('.');
	if (pos == std::string::npos) return 0;
	const size_t end = s.find_last_not_of('0');
	if (end == std::string::npos || s[end] == '.') return 0;
	return static_cast<int>(end - pos);
}

namespace mfc { //mfc, aka.Math for C++.
	class fraction {
	private:
		type num = 0;//numerator
		type den = 1;//denominator
	public:
		template<typename TypesForSolve = float>
		TypesForSolve solve() const noexcept
		{
			if (den == 0)
			{
				throw std::invalid_argument("Denominator cannot be zero");
			}
			else
			{
				return static_cast<TypesForSolve>(num) / den;
			}
		}
		fraction(type n, type d) : num(n), den(d) {
			if (d == 0) {
				throw std::invalid_argument("Denominator cannot be zero");
			}
			if (den < 0) {
				num = -num;
				den = -den;
			}
		}
		fraction() : num(0), den(1) {}
		fraction(type n) : num(n), den(1) {}
		fraction(double n) : num(0), den(1)
		{
			fraction temp1(n * std::pow(10, Decimal_count(n)), std::pow(10, Decimal_count(n)));
			temp1 = temp1.simplify();
			num = temp1.num;
			den = temp1.den;
		}
		fraction pow_int(int a) const;
		fraction rec() const;//Basically makes the fraction upside down.
		fraction& abs(); //This modifys the fraction.
		fraction rtrn_abs() const; //This returns the result instead of modifying the fraction itself.
		fraction simplify() const
		{
			type g = gcd(std::abs(num), std::abs(den));
			return fraction(num / g, den / g);
		}
		void swap(fraction& other) noexcept
		{
			std::swap(num, other.num);
			std::swap(den, other.den);
		}
		fraction& operator = (fraction other) noexcept
		{
			swap(other);
			return *this;
		}
		fraction operator % (const fraction& other) const noexcept
		{
			type lcm = den / gcd(den, other.den) * other.den;
			if (this->num * lcm > other.num * lcm)
			{
				fraction Temp((this->num * lcm) % (other.num * lcm), lcm);
				return Temp.simplify();
			}
			else
			{
				fraction Temp((other.num * lcm) % (this->num * lcm), lcm);
				return Temp.simplify();
			}

		}
		fraction operator - () const noexcept
		{
			fraction Temp(-num, den);
			return Temp;
		}
		fraction operator + (const fraction& other) const noexcept
		{
			type lcm = den / gcd(den, other.den) * other.den;
			type new_num = num * (lcm / den) + other.num * (lcm / other.den);
			fraction result(new_num, lcm);
			return result.simplify();
		}
		fraction operator - (const fraction& other) const noexcept
		{
			type lcm = den / gcd(den, other.den) * other.den;
			type new_num = num * (lcm / den) - other.num * (lcm / other.den);
			fraction result(new_num, lcm);
			return result.simplify();
		}
		fraction operator * (const fraction& other) const
		{
			fraction result(num * other.num, den * other.den);
			return result.simplify();
		}
		fraction operator / (const fraction& other) const
		{
			fraction result(num * other.den, den * other.num);
			return result.simplify();
		}
		fraction operator / (const type& other) const
		{
			if (other == 0)
			{
				throw std::invalid_argument("It ain't a smart choice to use 0 as a divisor");
			}
			else {
				fraction result(num, den * other);
				return result.simplify();
			}
		}
		fraction& operator+=(const fraction& other) noexcept {
			*this = *this + other;
			return *this;
		}
		fraction& operator-=(const fraction& other) noexcept {
			*this = *this - other;
			return *this;
		}
		fraction& operator*=(const fraction& other) noexcept {
			*this = *this * other;
			return *this;
		}
		fraction& operator/=(const fraction& other) noexcept {
			*this = *this / other;
			return *this;
		}
		fraction& operator++() noexcept { num += den; return *this; }
		fraction& operator--() noexcept { num -= den; return *this; }
		fraction operator++(int) noexcept {
			fraction temp = *this;
			num += den;
			return temp;
		}
		fraction operator--(int) noexcept {
			fraction temp = *this;
			num -= den;
			return temp;
		}

		friend std::ostream& operator<<(std::ostream& os, const fraction& a) noexcept
		{
			os << a.num << "/" << a.den;
			return os;
		}
		friend std::istream& operator>>(std::istream& is, fraction& a) noexcept
		{
			std::cout << "Num.:";
			is >> a.num;
			std::cout << "Den.:";
			is >> a.den;
			return is;
		}
		bool operator < (const fraction& other) const noexcept
		{
			if (this->num / this->den != other.num / other.den)
			{
				return this->num / this->den < other.num / other.den;
			}
			else {
				return (this->num % this->den) * other.den < (other.num % other.den) * this->den;
			}
		}
		bool operator <= (const fraction& other) const noexcept
		{
			return *this < other or *this == other;
		}
		bool operator != (const fraction& other) const noexcept
		{
			if (this->num / this->den != other.num / other.den)
			{
				return true;
			}
			else {
				return (this->num % this->den) * other.den != (other.num % other.den) * this->den;
			}
		}
		bool operator > (const fraction& other) const noexcept
		{
			return other < *this;
		}
		bool operator >= (const fraction& other) const noexcept
		{
			return other < *this or other == *this;;
		}
		bool operator < (const double& other) const noexcept
		{
			if (this->num / this->den != static_cast<int>(other))
			{
				return this->num / this->den < static_cast<int>(other);
			}
			else {
				return this->num % this->den < (other - static_cast<int>(other)) * this->den;
			}
		}
		bool operator != (const double& other) const noexcept
		{
			if (this->num / this->den != static_cast<int>(other))
			{
				return true;
			}
			else {
				return this->num % this->den != (other - static_cast<int>(other)) * this->den;
			}
		}
		bool operator <= (const double& other) const noexcept
		{
			if (this->num / this->den != static_cast<int>(other))
			{
				return this->num / this->den <= static_cast<int>(other);
			}
			else {
				return this->num % this->den <= (other - static_cast<int>(other)) * this->den;
			}
		}
		bool operator > (const double& other) const noexcept
		{
			if (this->num / this->den != static_cast<int>(other))
			{
				return this->num / this->den > static_cast<int>(other);
			}
			else {
				return this->num % this->den > (other - static_cast<int>(other)) * this->den;
			};
		}
		bool operator >= (const double& other) const noexcept
		{
			if (this->num / this->den != static_cast<int>(other))
			{
				return this->num / this->den >= static_cast<int>(other);
			}
			else {
				return this->num % this->den >= (other - static_cast<int>(other)) * this->den;
			};
		}
		bool operator == (const fraction& other) const noexcept
		{
			if (this->num / this->den != other.num / other.den)
			{
				return this->num / this->den == other.num / other.den;
			}
			else {
				return (this->num % this->den) * other.den == (other.num % other.den) * this->den;
			}
		}
		bool operator == (const double& other) const noexcept
		{
			if (this->num / this->den != static_cast<int>(other))
			{
				return this->num / this->den == static_cast<int>(other);
			}
			else {
				return this->num % this->den == (other - static_cast<int>(other)) * this->den;
			};
		}
	};
	fraction fraction::rec() const
	{
		if (num == 0)
		{
			throw std::invalid_argument("Denominator cannot be zero");
		}
		else {
			fraction temp(den, num);
			return temp.simplify();
		}
	}
	fraction fraction::pow_int(int a) const
	{
		if (a > 0)
		{
			fraction temp(static_cast<int>(std::pow(num, a)), static_cast<int>(std::pow(den, a)));
			return temp.simplify();
		}
		if (a == 0)
		{
			fraction b(1, 1);
			return b;
		}
		else
		{
			fraction Ntemp = this->rec();
			return Ntemp.pow_int(-a);
		}
	}
	fraction& fraction::abs()
	{
		if (num < 0)
		{
			this->num = -num;
		}
		return *this;
	}
	fraction fraction::rtrn_abs() const
	{
		if (num < 0)
		{
			fraction temp(-num, den);
			return temp;
		}
		else
		{
			fraction temp2(num, den);
			return temp2;
		}
	}
	const inline  fraction f(type a, type b) noexcept//Easier Fraction Maker
	{
		return fraction(a, b);
	}
}
#endif


//===========================================================================
//I recommend using this library in C++ 11 or higher

//logs:
//8/20/2026, Added basic calculation
//8/21/2026, Added int and double compatibility
//8/22/2026，Added some stuff and fixed bugs
//8/23/2026，Addded useful functions like pow_int
//8/26/2026,Optimized the algorithm.
//8/31/2026 Added using type = int;
//9/4/2026 Added some functions and removed useless stuff(Compare function).
//9/7/2026 Changed Solve into templates to make it better
//9/8/2026 Optimized the compare thing.
//9/11/2026 Delated some useless stuff.

// Verision: 3.0.0
// Welcome to apply to Xiamen No.6 High School
// If there are any problems with my code, feel free to email me at: 3594929067@qq.com
// I will reply if im not in school
//============================================================================
