#pragma once

#include <cmath>

namespace F7
{
	enum class EBaseType
	{
		BOOL,
		CHAR,
		UNSIGNED_CHAR,
		SHORT,
		UNSIGNED_SHORT,
		INT,
		UNSIGNED_INT,
		LONG_INT,
		UNSIGNED_LONG_INT,
		LONG_LONG_INT,
		UNSIGNED_LONG_LONG_INT,
		FLOAT,
		DOUBLE,
		LONG_DOUBLE,
		LONG_LONG_DOUBLE
	};

	const double PI = 3.14159265358979323846;
	const double PI_2 = 1.57079632679489661923;
	const double PI_4 = 0.78539816339744830962;
	const double LN_2 = 0.69314718055994530942;
	const double INVLN_2 = 1.0 / LN_2;

	class Math
	{
	public:
		static inline float Degree2Radian(float angle) { return angle * (float)PI / 180.0f; }
		static inline double Degree2Radian(double angle) { return angle * PI / 180.0; }
		static inline float RadiansToDegrees(float angle) { return angle * 180.0f / (float)PI; }
		static inline double RadiansToDegrees(double angle) { return angle * 180.0 / PI; }

		static inline float sqrt(int value) { return (float)std::sqrtf((float)value); }
		static inline float sqrt(float value) { return std::sqrtf(value); }
		static inline double sqrt(double value) { return std::sqrt(value); }
		static inline long double sqrt(long double value) { return std::sqrtl(value); }

		static inline float sin(float angle) { return std::sin(angle); }
		static inline double sin(double angle) { return std::sin(angle); }
		static inline long double sin(long double angle) { return std::sin(angle); }

		static inline float cos(float angle) { return std::cos(angle); }
		static inline double cos(double angle) { return std::cos(angle); }
		static inline long double cos(long double angle) { return std::cos(angle); }

		static inline float tan(float angle) { return std::tan(angle); }
		static inline double tan(double angle) { return std::tan(angle); }
		static inline long double tan(long double angle) { return std::tan(angle); }

		static inline float asin(float value) { return std::asin(value); }
		static inline double asin(double value) { return std::asin(value); }
		static inline long double asin(long double value) { return std::asin(value); }

		static inline float acos(float value) { return std::acos(value); }
		static inline double acos(double value) { return std::acos(value); }
		static inline long double acos(long double value) { return std::acos(value); }

		static inline float atan(float value) { return std::atan(value); }
		static inline double atan(double value) { return std::atan(value); }
		static inline long double atan(long double value) { return std::atan(value); }

		/** @brief: get angel with x axis, angle in [-Pi, +Pi] */
		static inline float atan2(float y, float x) { return std::atan2(y, x); }
		static inline double atan2(double y, double x) { return std::atan2(y, x); }
		static inline long double atan2(long double y, long double x) { return std::atan2(y, x); }

		

	private:
		Math() {}
		~Math() {}
	};
}