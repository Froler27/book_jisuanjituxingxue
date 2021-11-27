#pragma once

#include <ostream>
#include "../Math/Math.hpp"

namespace F7
{
	template <typename T, int N>
	class Vec_T
	{
	public:
		using value_type = T;
		Vec_T() {}
		Vec_T(value_type e) { for (int i = 0; i < N; ++i) _v[i] = e; }
		Vec_T(const Vec_T& v) { for (int i = 0; i < N; ++i) _v[i] = v[i]; }

		inline value_type length2() const {
			value_type res{0};
			for (int i = 0; i < N; ++i) res += _v[i] * _v[i];
			return res;
		}
#pragma warning(push) // when value_type is int, this will have warning 4244
#pragma warning(disable:4244) 
		inline value_type length() const { return F7::Math::sqrt(length2()); }
#pragma warning(pop)

		inline Vec_T& normalize() {
			value_type len = length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i=0; i<N; ++i)
					_v[i] *= inv;
#pragma warning(pop) 
			}
			return *this;
		}
		inline Vec_T getNormalize() const 
		{
			Vec_T res = *this;
			value_type len = length();
			if (len > 0) {
				auto inv = 1.f / len;
#pragma warning(push) 
#pragma warning(disable:4244) 
				for (int i = 0; i < N; ++i)
					res[i] *= inv;
#pragma warning(pop) 
			}
			return res;
		}

		inline value_type* ptr() { return _v; }
		inline const value_type* ptr() const { return _v; }
		inline value_type* begin() { return _v; }
		inline value_type* end() { return _v + N; }
		inline const value_type* begin() const { return _v; }
		inline const value_type* end() const { return _v + N; }
		inline int size() const { return N; }

		void set(value_type e) { for (int i = 0; i < N; ++i) _v[i] = e; }

		inline value_type& operator [](int id) { return _v[id]; }
		inline value_type operator [](int id) const { return _v[id]; }
		friend std::ostream& operator <<(std::ostream& os, const Vec_T& v) { for (int i = 0; i < N; ++i) { os << v[i] << " "; } return os; }
		
		inline Vec_T operator +(const Vec_T& v) const { Vec_T res; for (int i = 0; i < N; ++i) { res[i] = _v[i] + v[i]; } return res; }
		inline Vec_T& operator +=(const Vec_T& v) { for (int i = 0; i < N; ++i) { _v[i] += v[i]; } return *this; }

		inline Vec_T operator -(const Vec_T& v) const { Vec_T res; for (int i = 0; i < N; ++i) { res[i] = _v[i] - v[i]; } return res; }
		inline Vec_T& operator -=(const Vec_T& v) { for (int i = 0; i < N; ++i) { _v[i] -= v[i]; } return *this; }
		inline Vec_T operator -() const { Vec_T res; for (int i = 0; i < N; ++i) { res[i] = -_v[i]; } return res; }

		inline Vec_T operator * (value_type e) const { Vec_T res; for (int i = 0; i < N; ++i) { res[i] = _v[i] * e; } return res; }
		inline Vec_T& operator *= (value_type e) { for (int i = 0; i < N; ++i) { _v[i] += e; } return *this;  }
		inline value_type operator * (const Vec_T& v) const { T res{0}; for (int i = 0; i < N; ++i) { res += _v[i] * v[i]; } return res; }

		inline Vec_T operator / (value_type e) const { Vec_T res; for (int i = 0; i < N; ++i) { res[i] = _v[i] / e; } return res; }
		inline Vec_T& operator /= (value_type e) { for (int i = 0; i < N; ++i) { _v[i] /= e; } return *this; }

		inline bool operator == (const Vec_T& v) const { for (int i = 0; i < N; ++i) { if (_v[i] != v[i]) return false; } return true; }
		inline bool operator != (const Vec_T& v) const { return !(_v == v); }

	protected:
		T _v[N]{};
	};

	template <typename T>
	class Vec2_T: public Vec_T<T, 2>
	{
	public:
		using value_type = T;
		using base_type = Vec_T<T, 2>;
		static const int N = 2;
		using base_type::_v;

		Vec2_T() {}
		Vec2_T(value_type e): base_type(e){}
		Vec2_T(value_type e0, value_type e1) { _v[0] = e0, _v[1] = e1; }
		~Vec2_T() {}

		void set(value_type e0, value_type e1) { _v[0] = e0, _v[1] = e1; }

		value_type& x() { return _v[0]; }
		value_type& y() { return _v[1]; }
		value_type x() const { return _v[0]; }
		value_type y() const { return _v[1]; }
		void x(value_type e) { _v[0] = e; }
		void y(value_type e) { _v[1] = e; }
		Vec2_T xy() const { return *this; }
		void xy(value_type e0, value_type e1) { x(e0), y(e1); }

		value_type& s() { return _v[0]; }
		value_type& t() { return _v[1]; }
		value_type s() const { return _v[0]; }
		value_type t() const { return _v[1]; }
		void s(value_type e) { _v[0] = e; }
		void t(value_type e) { _v[1] = e; }
		Vec2_T st() const { return *this; }
		void st(value_type e0, value_type e1) { s(e0), t(e1); }
	};


	template <typename T>
	class Vec3_T : public Vec_T<T, 3>
	{
	public:
		using value_type = T;
		using base_type = Vec_T<T, 3>;
		static const int N = 3;
		using base_type::_v;

		Vec3_T() {}
		Vec3_T(value_type e) : base_type(e) {}
		Vec3_T(const Vec3_T& v) : base_type(v) {}
		Vec3_T(const base_type& v) : base_type(v) {}
		Vec3_T(value_type e0, value_type e1, value_type e2) { _v[0] = e0, _v[1] = e1, _v[2] = e2; }
		Vec3_T(Vec2_T<value_type> v, value_type e = 0) { _v[0] = v[0], _v[1] = v[1], _v[2] = e; }
		Vec3_T(value_type e, Vec2_T<value_type> v) { _v[0] = e, _v[1] = v[0], _v[2] = v[1]; }
		~Vec3_T() {}

		inline void set(value_type e0, value_type e1, value_type e2) { _v[0] = e0, _v[1] = e1, _v[2] = e2; }
	
		inline value_type& x() { return _v[0]; }
		inline value_type& y() { return _v[1]; }
		inline value_type& z() { return _v[2]; }
		inline value_type x() const { return _v[0]; }
		inline value_type y() const { return _v[1]; }
		inline value_type z() const { return _v[2]; }
		inline void x(value_type e) { _v[0] = e; }
		inline void y(value_type e) { _v[1] = e; }
		inline void z(value_type e) { _v[2] = e; }

		inline Vec2_T<value_type> xy() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> xyz() { return *this; }

		//Vec2_T<T> xy() const { return Vec2_T<T>(x(), y()); }
		//void xy(T v0, T v1) { x() }
		//Vec2_T<T> yx() const { return Vec2_T<T>(y(), x()); }
		//Vec2_T<T> yz() const { return Vec2_T<T>(y(), z()); }
		//Vec2_T<T> zy() const { return Vec2_T<T>(z(), y()); }
		//Vec2_T<T> xz() const { return Vec2_T<T>(x(), z()); }
		//Vec2_T<T> zx() const { return Vec2_T<T>(z(), x()); }
		//Vec3_T<T> xyz() const { return *this; }
		//Vec3_T<T> xzy() const { return Vec3_T<T>(xz(), y()); }
		//Vec3_T<T> yxz() const { return Vec3_T<T>(yx(), z()); }
		//Vec3_T<T> yzx() const { return Vec3_T<T>(yz(), x()); }
		//Vec3_T<T> zxy() const { return Vec3_T<T>(zx(), y()); }
		//Vec3_T<T> zyx() const { return Vec3_T<T>(zy(), x()); }

		inline value_type s() const { return _v[0]; }
		inline value_type t() const { return _v[1]; }
		inline value_type p() const { return _v[2]; }
		inline value_type& s() { return _v[0]; }
		inline value_type& t() { return _v[1]; }
		inline value_type& p() { return _v[2]; }
		inline void s(value_type e) { _v[0] = e; }
		inline void t(value_type e) { _v[1] = e; }
		inline void p(value_type e) { _v[2] = e; }
		inline Vec2_T<value_type> st() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> stp() { return *this; }

		inline Vec3_T operator ^ (const Vec3_T& v) const { return Vec3_T(_v[1] * v[2] - _v[2] * v[1], _v[2] * v[0] - _v[0] * v[2], _v[0] * v[1] - _v[1] * v[0]); }

		inline operator Vec2_T<value_type>() { return xy(); }
	};

	template <typename T>
	class Vec4_T : public Vec_T<T, 4>
	{
	public:
		using value_type = T;
		using base_type = Vec_T<T, 4>;
		static const int N = 4;
		using base_type::_v;

		Vec4_T() {}
		Vec4_T(value_type e) : base_type(e) {}
		Vec4_T(value_type e0, value_type e1, value_type e2, value_type e3) { _v[0] = e0, _v[1] = e1, _v[2] = e2, _v[3] = e3; }
		Vec4_T(Vec3_T<value_type> vt3, value_type e3 = 0) { _v[0] = vt3[0], _v[1] = vt3[1], _v[2] = vt3[2], _v[3] = e3; }
		Vec4_T(value_type e0, Vec3_T<value_type> vt3) { _v[0] = e0, _v[1] = vt3[0], _v[2] = vt3[1], _v[3] = vt3[2]; }
		Vec4_T(Vec2_T<value_type> v0, Vec2_T<value_type> v1) { _v[0] = v0[0], _v[1] = v0[1], _v[2] = v1[0], _v[3] = v1[1]; }
		~Vec4_T() {}

		inline void set(value_type e0, value_type e1, value_type e2, value_type e3) { _v[0] = e0, _v[1] = e1, _v[2] = e2, _v[3] = e3; }

		inline value_type& x() { return _v[0]; }
		inline value_type& y() { return _v[1]; }
		inline value_type& z() { return _v[2]; }
		inline value_type& w() { return _v[3]; }
		inline value_type x() const { return _v[0]; }
		inline value_type y() const { return _v[1]; }
		inline value_type z() const { return _v[2]; }
		inline value_type w() const { return _v[3]; }
		inline void x(value_type e) { _v[0] = e; }
		inline void y(value_type e) { _v[1] = e; }
		inline void z(value_type e) { _v[2] = e; }
		inline void w(value_type e) { _v[3] = e; }
		inline Vec2_T<value_type> xy() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> xyz() { return Vec3_T<value_type>(_v[0], _v[1], _v[2]); }
		inline Vec4_T<value_type> xyzw() { return *this; }


		inline value_type& s() { return _v[0]; }
		inline value_type& t() { return _v[1]; }
		inline value_type& p() { return _v[2]; }
		inline value_type& q() { return _v[3]; }
		inline value_type s() const { return _v[0]; }
		inline value_type t() const { return _v[1]; }
		inline value_type p() const { return _v[2]; }
		inline value_type q() const { return _v[3]; }
		inline void s(value_type e) { _v[0] = e; }
		inline void t(value_type e) { _v[1] = e; }
		inline void p(value_type e) { _v[2] = e; }
		inline void q(value_type e) { _v[3] = e; }
		inline Vec2_T<value_type> st() { return Vec2_T<value_type>(_v[0], _v[1]); }
		inline Vec3_T<value_type> stp() { return Vec3_T<value_type>(_v[0], _v[1], _v[2]); }
		inline Vec4_T<value_type> stpq() { return *this; }

		inline operator Vec2_T<value_type>() { return xy(); }
		inline operator Vec3_T<value_type>() { return xyz(); }

	};

	class Color255;

 	template <typename T>
 	class Color_T: public Vec4_T<T>
 	{
 	public:
		using value_type = T;
		using base_type = Vec4_T<T>;
		static const int N = 4;
		using base_type::_v;

		Color_T(): Vec4_T<value_type>(Vec3_T<value_type>(0), 1) {}
		Color_T(value_type e0, value_type e1, value_type e2, value_type e3): Vec4_T<value_type>(e0, e1, e2, e3) {}
		Color_T(value_type e, value_type alpha = 1): Vec4_T<value_type>(Vec3_T<value_type>(e), alpha) {}
		Color_T(Vec3_T<value_type> v, value_type alpha = 1) : Vec4_T<value_type>(v, alpha) {}
		Color_T(Vec4_T<value_type> v) : Vec4_T<value_type>(v) {}
 		~Color_T() {}
		/** @brief: make value in [0,1] */
		inline Color_T& normalize() {
			for (auto& e : Vec4_T<value_type>::_v) if (e > 1) e = 1; else if (e < 0) e = 0;
			return *this;
		}
		inline Color255 to255();

 
 		inline value_type& r() { return Vec4_T<value_type>::_v[0]; }
 		inline value_type& g() { return Vec4_T<value_type>::_v[1]; }
 		inline value_type& b() { return Vec4_T<value_type>::_v[2]; }
 		inline value_type& a() { return Vec4_T<value_type>::_v[3]; }
 		inline value_type r() const { return Vec4_T<value_type>::_v[0]; }
 		inline value_type g() const { return Vec4_T<value_type>::_v[1]; }
 		inline value_type b() const { return Vec4_T<value_type>::_v[2]; }
 		inline value_type a() const { return Vec4_T<value_type>::_v[3]; }
 		inline void r(value_type e) { Vec4_T<value_type>::_v[0] = e; }
 		inline void g(value_type e) { Vec4_T<value_type>::_v[1] = e; }
 		inline void b(value_type e) { Vec4_T<value_type>::_v[2] = e; }
 		inline void a(value_type e) { Vec4_T<value_type>::_v[3] = e; }
		
		inline Vec3_T<value_type> rgb() { return Vec3_T<value_type>(Vec4_T<value_type>::_v[0], Vec4_T<value_type>::_v[1], Vec4_T<value_type>::_v[2]); }
		inline Color_T rgba() { return *this; }
		inline void rgb(value_type e0, value_type e1, value_type e2) { Vec4_T<value_type>::_v[0] = e0, Vec4_T<value_type>::_v[1] = e1, Vec4_T<value_type>::_v[2] = e2; }
		inline void rgba(value_type e0, value_type e1, value_type e2, value_type e3) { 
			Vec4_T<value_type>::_v[0] = e0, Vec4_T<value_type>::_v[1] = e1, Vec4_T<value_type>::_v[2] = e2, Vec4_T<value_type>::_v[3] = e3; 
		}
 	};

 	class Color255 : public Vec4_T<int>
 	{
 	public:
		Color255() : Vec4_T<value_type>(Vec3_T<value_type>(0), 255) {}
		Color255(value_type e0, value_type e1, value_type e2, value_type e3) : Vec4_T(e0, e1, e2, e3) {}
		Color255(value_type e, value_type alpha = 255) : Vec4_T<value_type>(Vec3_T<value_type>(e), alpha) {}
		Color255(Vec3_T<value_type> v, value_type alpha = 255) : Vec4_T<value_type>(v, alpha) {}
		Color255(Vec4_T<value_type> v) : Vec4_T<value_type>(v) {}
		~Color255() {}
		inline Color255& normalize255() {
			for (auto& e : Vec4_T<value_type>::_v) if (e > 255) e = 255; else if (e < 0) e = 0;
			return *this;
		}
		inline Color_T<float> normalize() {
			return Color_T<float>(_v[0] / 255.f, _v[1] / 255.f, _v[2] / 255.f, _v[3] / 255.f);
		}
 		
 
 		inline value_type& r() { return _v[0]; }
 		inline value_type& g() { return _v[1]; }
 		inline value_type& b() { return _v[2]; }
 		inline value_type& a() { return _v[3]; }
 		inline value_type r() const { return _v[0]; }
 		inline value_type g() const { return _v[1]; }
 		inline value_type b() const { return _v[2]; }
 		inline value_type a() const { return _v[3]; }
 		inline void r(value_type e) { _v[0] = e; }
 		inline void g(value_type e) { _v[1] = e; }
 		inline void b(value_type e) { _v[2] = e; }
 		inline void a(value_type e) { _v[3] = e; }
		inline Color255 rgba() { return *this; }
		inline void rgb(value_type e0, value_type e1, value_type e2) { _v[0] = e0, _v[1] = e1, _v[2] = e2; }
		inline void rgba(value_type e0, value_type e1, value_type e2, value_type e3) { _v[0] = e0, _v[1] = e1, _v[2] = e2, _v[3] = e3; }
 	};

	template <typename T>
	Color255 F7::Color_T<T>::to255()
	{
		return Color255(
			int(Vec4_T<value_type>::_v[0] * 255),
			int(Vec4_T<value_type>::_v[1] * 255),
			int(Vec4_T<value_type>::_v[2] * 255),
			int(Vec4_T<value_type>::_v[3] * 255));
	}
}