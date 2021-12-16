#pragma once

#include "F7/Math/Math.hpp"
#include "F7/Vec/Vec.hpp"
#include "F7/Common/Log.hpp"

namespace F7
{
 	template <typename T, int row, int col>
 	class MatMxN_T
 	{
 	public:
 		using value_type = T;
		using VecRow = Vec_T<value_type, col>;
		using VecCol = Vec_T<value_type, row>;
		MatMxN_T() {}
		MatMxN_T(value_type e) {
 			for (int i = 0; i < row && i<col; ++i)
 					_m[i][i] = e;
 		}

		inline void set(value_type e) {
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					_m[i][j] = e;
		}

		inline VecRow getRow(int iRow) const {
			VecRow res;
			for (int i = 0; i < col; ++i)
				res[i] = _m[iRow][i];
			return res;
		}
		inline void getRow(int iRow, VecRow& v) const {
			for (int i = 0; i < col; ++i)
				v[i] = _m[iRow][i];
		}
		inline void setRow(int iRow, const VecRow& v) {
			for (int i = 0; i < col; ++i)
				_m[iRow][i] = v[i];
		}

		inline VecCol getCol(int iCol) const {
			VecCol res;
			for (int i = 0; i < row; ++i)
				res[i] = _m[i][iCol];
			return res;
		}
		inline void getCol(int iCol, VecCol& v) const {
			for (int i = 0; i < row; ++i)
				v[i] = _m[i][iCol];
		}
		inline void setCol(int iCol, const VecCol& v) {
			for (int i = 0; i < row; ++i)
				_m[i][iCol] = v[i];
		}

		inline value_type* ptr() { return (value_type*)_m; }
		inline const value_type* ptr() const { return (value_type*)_m; }
		inline value_type** begin() { return &_m[0][0]; }
		inline value_type** end() { return begin() + row*col; }
		inline const value_type** begin() const { return &_m[0][0]; }
		inline const value_type** end() const { return begin() + row*col; }

		inline MatMxN_T<T, col, row> getTranspose() const {
			MatMxN_T<T, col, row> res;
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					res[j][i] = _m[i][j];
			return res;
		}

		inline value_type& operator ()(int i, int j) { return _m[i][j]; }
		inline value_type operator ()(int i, int j) const { return _m[i][j]; }
		friend std::ostream& operator << (std::ostream& os, const MatMxN_T& m) {
			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j)
					os << m(i, j)<< " ";
				os << "\n";
			} 
			return os; 
		}


		inline MatMxN_T operator + (const MatMxN_T& mR) const {
			MatMxN_T res;
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					res(i, j) = _m[i][j] + mR[i][j];
			return res;
		}
		inline MatMxN_T& operator += (const MatMxN_T& mR) {
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					_m[i][j] += mR[i][j];
			return *this;
		}

		inline MatMxN_T operator - (const MatMxN_T& mR) const {
			MatMxN_T res;
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					res(i, j) = _m[i][j] - mR[i][j];
			return res;
		}
		inline MatMxN_T& operator -= (const MatMxN_T& mR) {
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					_m[i][j] -= mR(i,j);
			return *this;
		}
		inline MatMxN_T operator - () const {
			MatMxN_T res;
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					res(i, j) = -_m[i][j];
			return res;
		}

		inline MatMxN_T<T, row, row> operator * (const MatMxN_T<T, col, row>& mR) const {
			MatMxN_T<T, row, row> res;
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					for (int k = 0; k < col; ++k)
						res(i, j) += _m[i][k] * mR(k,j);
			return res;
		}
		inline Vec_T<value_type, col> operator * (const Vec_T<value_type, col>& v) const {
			Vec_T<value_type, col> res;
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					res[i] += _m[i][j] * v[j];
			return res;
		}
		friend Vec_T<value_type, col> operator * (const Vec_T<value_type, row>& vL, const MatMxN_T& mR) {
			Vec_T<value_type, col> res;
			for (int i = 0; i < col; ++i)
				for (int j = 0; j < row; ++j)
					res[i] += _m[j][i] * vL[j];
			return res;
		}
 
		inline bool operator == (const MatMxN_T& mR) const {
			for (int i = 0; i < row; ++i)
				for (int j = 0; j < col; ++j)
					if (_m[i][j] != mR[i][j])
						return false;
			return true;
		}
		inline bool operator != (const MatMxN_T& mR) const {
			return !(*this == mR);
		}

 	protected:
 		value_type _m[row][col]{};// TODO: test every value is 0
 	};

	template <typename T, int N>
	class MatN_T: public MatMxN_T<T, N, N>
	{
	public: 
		using value_type = T;
		using base_type = MatMxN_T<T, N, N>;
		using VecN = Vec_T<value_type, N>;
		using base_type::_m;
		//static void Invert(MatN_T& m);
		//static MatN_T GetInverse(MatN_T& m);
	public:
		MatN_T() {}
		MatN_T(value_type e) {
			for (int i = 0; i < N; ++i)
				_m[i][i] = e;
		}

		//void invert();
		//void getInverse() const;

		MatN_T& transpose() {
			value_type tem;
			for (int i = 1; i < N; ++i)
				for (int j = 0; j < i; ++j) {
					tem = _m[i][j];
					_m[i][j] = _m[j][i];
					_m[j][i] = tem;
				}
			return *this;
		}

		MatN_T operator *= (const MatN_T& mR) {
			value_type tem;
			Vec_T<value_type, N> vTem;
			for (int i = 0; i < N; ++i) {
				vTem.set(0);
				for (int j = 0; j < N; ++j) {
					tem = 0;
					for (int k = 0; k < N; ++k) {
						tem += _m[i][k] * mR(k,j);
					}
					vTem[j] = tem;
				}
				for (int j = 0; j < N; ++j) {
					_m[i][j] = vTem[j];
				}
			}
			return *this;
		}

		operator base_type() { return static_cast<MatN_T>(*this); }

	};

	template <typename T> class Quat_T;

	template <typename T>
	class Mat4_T : public MatN_T<T, 4>
	{
	public:
		using value_type = T;
		using base_type = MatN_T<T, 4>;
		using Vec3 = Vec3_T<value_type>;
		using Vec4 = Vec4_T<value_type>;
		using base_type::_m;
		static const int N = 4;
		static Mat4_T Scale(const Vec3& v3) {
			Mat4_T res;
			res._m[0][0] = v3[0];
			res._m[1][1] = v3[1];
			res._m[2][2] = v3[2];
			res._m[3][3] = 1;
			return res;
		}
		static Mat4_T Scale(value_type e) {
			Mat4_T res;
			res._m[0][0] = e;
			res._m[1][1] = e;
			res._m[2][2] = e;
			res._m[3][3] = 1;
			return res;
		}
		static Mat4_T Scale(value_type e0, value_type e1, value_type e2) {
			Mat4_T res;
			res._m[0][0] = e0;
			res._m[1][1] = e1;
			res._m[2][2] = e2;
			res._m[3][3] = 1;
			return res;
		}
		static Mat4_T RotateX(value_type angle) {
			Mat4_T res;
			res(3, 3) = res(0, 0) = 1;
			res(1, 1) = res(2, 2) = Math::cos(angle);
			res(2, 1) = Math::sin(angle);
			res(1, 2) = -res(2, 1);
			return res;
		}
		static Mat4_T RotateY(value_type angle) {
			Mat4_T res;
			res(3, 3) = res(1, 1) = 1;
			res(0, 0) = res(2, 2) = Math::cos(angle);
			res(0, 2) = Math::sin(angle);
			res(2, 0) = -res(0, 2);
			return res;
		}
		static Mat4_T RotateZ(value_type angle) {
			Mat4_T res;
			res(3, 3) = res(2, 2) = 1;
			res(0, 0) = res(1, 1) = Math::cos(angle);
			res(1, 0) = Math::sin(angle);
			res(0, 1) = -res(1, 0);
			return res;
		}
		static Mat4_T Rotate(const Vec3& angleXYZ) {
			Mat4_T res{ 1 };
			res *= RotateX(angleXYZ.x());
			res *= RotateY(angleXYZ.y());
			res *= RotateZ(angleXYZ.z());
			return res;
		}
		//static Mat4_T Rotate(value_type angleX, value_type angleY, value_type angleZ);
		//static Mat4_T Rotate(value_type angle, const Vec3& axis);
		//static Mat4_T Rotate(const Vec3& from, const Vec3& to);
		// TODO: quat 
		static Mat4_T Translate(const Vec3& site) {
			Mat4_T res(1);
			res(0, 3) = site[0];
			res(1, 3) = site[1];
			res(2, 3) = site[2];
			return res;
		}
		static Mat4_T Translate(value_type e0, value_type e1, value_type e2) {
			Mat4_T res(1);
			res(0, 3) = e0;
			res(1, 3) = e1;
			res(2, 3) = e2;
			return res;
		}
		static Mat4_T LookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
			Vec3 f(center - eye);
			f.normalize();
			Vec3 r(f ^ up);
			r.normalize();
			Vec3 u(r ^ f);
			u.normalize();
			Mat4_T res;
			res.set(
				r[0], r[1], r[2], -r * eye,
				u[0], u[1], u[2], -u * eye,
				-f[0], -f[1], -f[2], f * eye,
				0, 0, 0, 1
			);
			return res;
		}
		static Mat4_T Ortho(
			value_type left, value_type right,
			value_type bottom, value_type top,
			value_type zNear, value_type zFar) 
		{// TODO: need check
			Mat4_T res;
			value_type tx = 1.f/(right - left);
			value_type ty = 1.f/(top - bottom);
			value_type tz = 1.f/(zFar - zNear);
			res(0, 0) = 2.f * tx;
			res(1, 1) = 2.f * ty;
			res(2, 2) = 1.f * tz;
			res(0, 3) = -(right + left) * tx;
			res(1, 3) = -(top + bottom) * ty;
			res(2, 3) = -(zNear) * tz;
			res(3, 3) = 1;
			return res;
		}
// 		static Mat4_T Frustum(
// 			value_type left, value_type right,
// 			value_type bottom, value_type top,
// 			value_type near, value_type far);

		static Mat4_T Perspective(
			value_type fovy, value_type aspect,
			value_type near, value_type far)
		{
			Mat4_T res;
			res(1, 1) = 1.f / Math::tan(fovy * 0.5f);
			res(0, 0) = res(1, 1) / aspect;
			value_type tx = 1.f / (near - far);
			res(2, 2) = (near + far) * tx;
			res(2, 3) = 2 * near * far * tx;
			res(3, 2) = -1;
			return res;
		}

	public:
		Mat4_T() {}
		Mat4_T(value_type e) : base_type(e) {}

		inline bool invert()
		{
			unsigned int indxc[4], indxr[4], ipiv[4];
			unsigned int i, j, k, l, ll;
			unsigned int icol = 0;
			unsigned int irow = 0;
			value_type temp, pivinv, dum, big;

			for (j = 0; j < 4; j++) ipiv[j] = 0;

			for (i = 0; i < 4; i++)
			{
				big = 0.0;
				for (j = 0; j < 4; j++)
					if (ipiv[j] != 1)
						for (k = 0; k < 4; k++)
						{
							if (ipiv[k] == 0)
							{
								if (Math::abs(_m[j][k]) >= big)
								{
									big = Math::abs(_m[j][k]);
									irow = j;
									icol = k;
								}
							}
							else if (ipiv[k] > 1)
								return false;
						}
				++(ipiv[icol]);
				if (irow != icol)
					for (l = 0; l < 4; l++)
						Math::swap(_m[irow][l], _m[icol][l]);

				indxr[i] = irow;
				indxc[i] = icol;
				if (_m[icol][icol] == 0)
					return false;

				pivinv = 1.0 / _m[icol][icol];
				_m[icol][icol] = 1;
				for (l = 0; l < 4; l++) _m[icol][l] *= pivinv;
				for (ll = 0; ll < 4; ll++)
					if (ll != icol)
					{
						dum = _m[ll][icol];
						_m[ll][icol] = 0;
						for (l = 0; l < 4; l++) _m[ll][l] -= _m[icol][l] * dum;
					}
			}
			for (int lx = 4; lx > 0; --lx)
			{
				if (indxr[lx - 1] != indxc[lx - 1])
					for (k = 0; k < 4; k++) 
						Math::swap(_m[k][indxr[lx - 1]], _m[k][indxc[lx - 1]]);
			}

			return true;
		}

		inline void set(value_type e00, value_type e01, value_type e02, value_type e03,
			value_type e10, value_type e11, value_type e12, value_type e13,
			value_type e20, value_type e21, value_type e22, value_type e23,
			value_type e30, value_type e31, value_type e32, value_type e33) 
		{
			_m[0][0] = e00; _m[0][1] = e01; _m[0][2] = e02; _m[0][3] = e03;
			_m[1][0] = e10; _m[1][1] = e11; _m[1][2] = e12; _m[1][3] = e13;
			_m[2][0] = e20; _m[2][1] = e21; _m[2][2] = e22; _m[2][3] = e23;
			_m[3][0] = e30; _m[3][1] = e31; _m[3][2] = e32; _m[3][3] = e33;
		}

		void setTrans(const Vec3& site) {
			base_type::set(1);
			_m[0][3] = site[0];
			_m[1][3] = site[1];
			_m[2][3] = site[2];
		}
		void setTrans(value_type e0, value_type e1, value_type e2) {
			base_type::set(1);
			_m[0][3] = e0;
			_m[1][3] = e1;
			_m[2][3] = e2;
		}

		Quat_T<value_type> getRotate() const;

		//F7::Vec3_T<value_type> operator * (const F7::Vec3_T<value_type>& v3) {
		//	F7::Vec4_T<value_type> res(v3, 1);
		//	res = (*this) * res;
		//	return res.xyz();
		//}
		//F7::Vec4_T<value_type> operator * (const F7::Vec4_T<value_type>& v4) {
		//	F7::Vec4_T<value_type> res(v4);
		//	res = (*(base_type*)(this)) * res;
		//	return res;
		//}

		// TODO: setR... setS....
		Mat4_T& operator = (const base_type::base_type& m) {
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j)
					_m[i][j] = m(i, j);
			return *this;
		}
		operator base_type() { return static_cast<Mat4_T> (*this); }
		//friend Mat4_T& operator = ()
	};


	template <typename T>
	class Quat_T
	{
	public:
		using value_type = T;
		static const int N = 4;

		Quat_T() {}
		Quat_T(value_type e0, value_type e1, value_type e2, value_type e3) 
		{
			_v[0] = e0;
			_v[1] = e1;
			_v[2] = e2;
			_v[3] = e3;
		}
		Quat_T(const Vec4_T<value_type>& v)
		{
			_v[0] = v[0];
			_v[1] = v[1];
			_v[2] = v[2];
			_v[3] = v[3];
		}
		Quat_T(value_type angle, Vec3_T<value_type> axis) { makeRotate(angle, axis); }

		Quat_T(value_type angle1, Vec3_T<value_type> axis1,
			value_type angle2, Vec3_T<value_type> axis2,
			value_type angle3, Vec3_T<value_type> axis3)
		{
			
		}

		void set(value_type e0, value_type e1, value_type e2, value_type e3)
		{
			_v[0] = e0;
			_v[1] = e1;
			_v[2] = e2;
			_v[3] = e3;
		}
		void set(const Vec4_T<value_type>& v)
		{
			_v[0] = v[0];
			_v[1] = v[1];
			_v[2] = v[2];
			_v[3] = v[3];
		}
		void set(Mat4_T<value_type> m) { *this = m.getRotate(); }

		Vec4_T<value_type> asVec4() const { return Vec4_T<value_type>(_v[0], _v[1], _v[2], _v[3]); }
		Vec3_T<value_type> asVec3() const { return Vec3_T<value_type>(_v[0], _v[1], _v[2]); }
		value_type length() const { return Math::sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3]); }
		value_type length2() const { return _v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2] + _v[3] * _v[3]; }
		Quat_T conj() const { return Quat_T(-_v[0], -_v[1], -_v[2], _v[3]); }
		Quat_T inverse() const { return conj() / length2(); }
		bool zeroRotation() const { return _v[0] == 0.0 && _v[1] == 0.0 && _v[2] == 0.0 && _v[3] == 1.0; }
		
		void slerp(const Quat_T& from, const Quat_T& to, value_type t);

		void makeRotate(value_type angle, Vec3_T<value_type> axis)
		{
			const value_type eps = value_type(0.0000001);//epsilon
			value_type len = axis.length();
			if (len < eps) {
				*this = Quat_T();
				return;
			}
			_v[3] = Math::cos((value_type)(0.5 * angle));
			value_type t1 = Math::sin((value_type)(0.5 * angle)) / len;
			_v[0] = axis[0] * t1;
			_v[1] = axis[1] * t1;
			_v[2] = axis[2] * t1;
		}
		void makeRotate(value_type angle1, Vec3_T<value_type> axis1,
			value_type angle2, Vec3_T<value_type> axis2,
			value_type angle3, Vec3_T<value_type> axis3)
		{
			Quat_T q1(angle1, axis1);
			Quat_T q2(angle1, axis1);
			Quat_T q3(angle1, axis1);
			*this = q1 * q2 * q3;
		}
		// from 和 to 必须是单位向量
		void makeRotate(const Vec3_T<value_type>& from, const Vec3_T<value_type>& to);
		void makeRotate_original(const Vec3_T<value_type>& from, const Vec3_T<value_type>& to);

		void getRotate(value_type& angle, Vec3_T<value_type>& axis) const
		{
			value_type sinhalfangle = sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);

			angle = 2.0 * Math::atan2(sinhalfangle, _v[3]);
			if (sinhalfangle)
			{
				axis[0] = _v[0] / sinhalfangle;
				axis[1] = _v[1] / sinhalfangle;
				axis[2] = _v[2] / sinhalfangle;
			}
			else
			{
				axis[0] = 0.0;
				axis[1] = 0.0;
				axis[2] = 1.0;
			}
		}

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

		value_type& operator [] (int id) { return _v[id]; }
		value_type operator [] (int id) const { return _v[id]; }
		/** Rotate a vector by this quaternion.*/
		Vec3_T<value_type> operator* (const Vec3_T<value_type>& v) const
		{
			Vec3_T<value_type> uv, uuv;
			Vec3_T<value_type> qvec(_v[0], _v[1], _v[2]);
			uv = qvec ^ v;
			uuv = qvec ^ uv;
			uv *= (2.0f * _v[3]);
			uuv *= 2.0f;
			return v + uv + uuv;
		}
		Quat_T operator * (const Quat_T& q) const
		{
			return Quat_T(q[3] * _v[0] - q[0] * _v[3] + q[1] * _v[2] + q[2] * _v[1],
				q[3] * _v[1] - q[0] * _v[2] + q[1] * _v[3] + q[2] * _v[0],
				q[3] * _v[2] - q[0] * _v[1] + q[1] * _v[0] + q[2] * _v[3],
				q[3] * _v[3] - q[0] * _v[0] + q[1] * _v[1] + q[2] * _v[2]);
		}
		Quat_T& operator *= (const Quat_T& q)
		{
			value_type t0 = q[3] * _v[0] - q[0] * _v[3] + q[1] * _v[2] + q[2] * _v[1];
			value_type t1 = q[3] * _v[1] - q[0] * _v[2] + q[1] * _v[3] + q[2] * _v[0];
			value_type t2 = q[3] * _v[2] - q[0] * _v[1] + q[1] * _v[0] + q[2] * _v[3];
			_v[3] = q[3] * _v[3] - q[0] * _v[0] + q[1] * _v[1] + q[2] * _v[2];
			_v[2] = t2;
			_v[1] = t1;
			_v[0] = t0;
			return *this;
		}
		Quat_T operator * (value_type e) const
		{
			return Quat_T(_v[0] * e, _v[1] * e, _v[2] * e, _v[3] * e);
		}
		Quat_T& operator *= (value_type e)
		{
			_v[0] *= e;
			_v[1] *= e;
			_v[2] *= e;
			_v[3] *= e;
			return *this;
		}
		Quat_T operator / (value_type e) const
		{
			value_type div = (value_type)(1.0 / e);
			return Quat_T(_v[0] * div, _v[1] * div, _v[2] * div, _v[3] * div);
		}
		Quat_T& operator /= (value_type e)
		{
			value_type div = value_type(1.0 / e);
			_v[0] *= div;
			_v[1] *= div;
			_v[2] *= div;
			_v[3] *= div;
			return *this;
		}
		Quat_T operator/(const Quat_T& q) const { return ((*this) * q.inverse()); }
		Quat_T& operator/=(const Quat_T& q) { return (*this) *= q.inverse(); }
		Quat_T operator + (const Quat_T& q) const 
		{ 
			return Quat_T(
				_v[0] + q[0],
				_v[1] + q[1],
				_v[2] + q[2],
				_v[3] + q[3]);
		}
		Quat_T operator += (const Quat_T& q)
		{
			_v[0] += q[0];
			_v[1] += q[1];
			_v[2] += q[2];
			_v[3] += q[3];
			return *this;
		}
		Quat_T operator - (const Quat_T& q) const
		{
			return Quat_T(_v[0] - q[0],
				_v[1] - q[1],
				_v[2] - q[2],
				_v[3] - q[3]);
		}
		Quat_T& operator -= (const Quat_T& e)
		{
			_v[0] -= e[0];
			_v[1] -= e[1];
			_v[2] -= e[2];
			_v[3] -= e[3];
			return *this;
		}
		Quat_T operator - () const
		{
			return Quat_T(-_v[0], -_v[1], -_v[2], -_v[3]);
		}

	private:
		value_type _v[N]{0,0,0,1};
	};

	template <typename T>
	void F7::Quat_T<T>::makeRotate_original(const Vec3_T<value_type>& from, const Vec3_T<value_type>& to)
	{
		const value_type epsilon = 0.0000001;

		value_type cosangle = from * to;

		if (Math::fabs(cosangle - 1) < epsilon)
		{
			Log() << "Quat::makeRotate_original(from,to) with near co-linear vectors, epsilon= " << fabs(cosangle - 1) << Log::ENDL;
			makeRotate(0.0, 0.0, 0.0, 1.0);
		}
		else if (Math::fabs(cosangle + 1.0) < epsilon)
		{
			// vectors are close to being opposite, so will need to find a
			// vector orthongonal to from to rotate about.
			Vec3_T<value_type> tmp;
			if (Math::fabs(from.x()) < Math::fabs(from.y()))
				if (Math::fabs(from.x()) < Math::fabs(from.z())) tmp.set(1.0, 0.0, 0.0); // use x axis.
				else tmp.set(0.0, 0.0, 1.0);
			else if (Math::fabs(from.y()) < Math::fabs(from.z())) tmp.set(0.0, 1.0, 0.0);
			else tmp.set(0.0, 0.0, 1.0);

			Vec3_T<value_type> fromd(from.x(), from.y(), from.z());

			// find orthogonal axis.
			Vec3_T<value_type> axis(fromd ^ tmp);
			axis.normalize();

			_v[0] = axis[0]; // sin of half angle of PI is 1.0.
			_v[1] = axis[1]; // sin of half angle of PI is 1.0.
			_v[2] = axis[2]; // sin of half angle of PI is 1.0.
			_v[3] = 0; // cos of half angle of PI is zero.

		}
		else
		{
			// This is the usual situation - take a cross-product of vec1 and vec2
			// and that is the axis around which to rotate.
			Vec3_T<value_type> axis(from ^ to);
			value_type angle = acos(cosangle);
			makeRotate(angle, axis);
		}
	}

	/// Spherical Linear Interpolation
	/// As t goes from 0 to 1, the Quat object goes from "from" to "to"
	/// Reference: Shoemake at SIGGRAPH 89
	/// See also
	/// http://www.gamasutra.com/features/programming/19980703/quaternions_01.htm
	template <typename T>
	void F7::Quat_T<T>::slerp(const Quat_T& from, const Quat_T& to, value_type t)
	{
		const value_type epsilon = 0.00001;
		value_type omega, cosomega, sinomega, scale_from, scale_to;

		Quat_T quatTo(to);
		// this is a dot product

		cosomega = from.asVec4() * to.asVec4();

		if (cosomega < 0.0)
		{
			cosomega = -cosomega;
			quatTo = -to;
		}

		if ((1.0 - cosomega) > epsilon)
		{
			omega = Math::acos(cosomega);  // 0 <= omega <= Pi (see man acos)
			sinomega = Math::sin(omega);  // this sinomega should always be +ve so
			// could try sinomega=sqrt(1-cosomega*cosomega) to avoid a sin()?
			scale_from = Math::sin((1.0 - t) * omega) / sinomega;
			scale_to = Math::sin(t * omega) / sinomega;
		}
		else
		{
			/* --------------------------------------------------
				The ends of the vectors are very close
				we can use simple linear interpolation - no need
				to worry about the "spherical" interpolation
				-------------------------------------------------- */
			scale_from = 1.0 - t;
			scale_to = t;
		}

		*this = (from * scale_from) + (quatTo * scale_to);

		// so that we get a Vec4
	}

	template<typename T>
	inline void Quat_T<T>::makeRotate(const Vec3_T<value_type>& from, const Vec3_T<value_type>& to)
	{
		value_type dotProdPlus1 = 1.0 + from * to;
		if (dotProdPlus1 < 1e-7) {
			if (Math::fabs(from.x()) < 0.6) {
				const double norm = Math::sqrt(1.0 - from.x() * from.x());
				_v[0] = 0.0;
				_v[1] = from.z() / norm;
				_v[2] = -from.y() / norm;
				_v[3] = 0.0;
			}
			else if (Math::fabs(from.y()) < 0.6) {
				const double norm = Math::sqrt(1.0 - from.y() * from.y());
				_v[0] = -from.z() / norm;
				_v[1] = 0.0;
				_v[2] = from.x() / norm;
				_v[3] = 0.0;
			}
			else {
				const double norm = Math::sqrt(1.0 - from.z() * from.z());
				_v[0] = from.y() / norm;
				_v[1] = -from.x() / norm;
				_v[2] = 0.0;
				_v[3] = 0.0;
			}
		}
		else {
			const double s = Math::sqrt(0.5 * dotProdPlus1);
			const Vec3_T<value_type> tmp = from ^ to / (2.0 * s);
			_v[0] = tmp.x();
			_v[1] = tmp.y();
			_v[2] = tmp.z();
			_v[3] = s;
		}
	}


	template <typename T>
	F7::Quat_T<T> F7::Mat4_T<T>::getRotate() const
	{
		Quat_T<value_type> q;

		value_type s;
		value_type tq[4];
		int    i, j;

		// Use tq to store the largest trace
		tq[0] = 1 + _m[0][0] + _m[1][1] + _m[2][2];
		tq[1] = 1 + _m[0][0] - _m[1][1] - _m[2][2];
		tq[2] = 1 - _m[0][0] + _m[1][1] - _m[2][2];
		tq[3] = 1 - _m[0][0] - _m[1][1] + _m[2][2];

		// Find the maximum (could also use stacked if's later)
		j = 0;
		for (i = 1; i < 4; i++) j = (tq[i] > tq[j]) ? i : j;

		// check the diagonal
		if (j == 0)
		{
			/* perform instant calculation */
			q.w() = tq[0];
			q.x() = _m[1][2] - _m[2][1];
			q.y() = _m[2][0] - _m[0][2];
			q.z() = _m[0][1] - _m[1][0];
		}
		else if (j == 1)
		{
			q.w() = _m[1][2] - _m[2][1];
			q.x() = tq[1];
			q.y() = _m[0][1] + _m[1][0];
			q.z() = _m[2][0] + _m[0][2];
		}
		else if (j == 2)
		{
			q.w() = _m[2][0] - _m[0][2];
			q.x() = _m[0][1] + _m[1][0];
			q.y() = tq[2];
			q.z() = _m[1][2] + _m[2][1];
		}
		else /* if (j==3) */
		{
			q.w() = _m[0][1] - _m[1][0];
			q.x() = _m[2][0] + _m[0][2];
			q.y() = _m[1][2] + _m[2][1];
			q.z() = tq[3];
		}

		s = sqrt(0.25f / tq[j]);
		q.w() *= s;
		q.x() *= s;
		q.y() *= s;
		q.z() *= s;

		return q;
	}

}