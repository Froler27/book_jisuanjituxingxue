#pragma once

#include "../Math/Math.hpp"
#include "../Vec/Vec.hpp"

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
		static void invert(MatN_T& m);
		static MatN_T getInverse(MatN_T& m);
	public:
		MatN_T() {}
		MatN_T(value_type e) {
			for (int i = 0; i < N; ++i)
				_m[i][i] = e;
		}

		void invert();
		void getInverse() const;

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
		static Mat4_T Rotate(value_type angleX, value_type angleY, value_type angleZ);
		static Mat4_T Rotate(value_type angle, const Vec3& axis);
		static Mat4_T Rotate(const Vec3& from, const Vec3& to);
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
		static Mat4_T Frustum(
			value_type left, value_type right,
			value_type bottom, value_type top,
			value_type near, value_type far);

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



}