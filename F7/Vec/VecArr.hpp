#pragma once

#include "Vec.hpp"
#include <vector>

namespace F7
{

	template <typename T1, typename T2 = Vec3_T<T1> >
	class VecArr_T
	{
	public:
		using value_type = T1;
		using vec_type = T2;
		VecArr_T() {}
		VecArr_T(const std::vector<vec_type>& arr): _arr(arr) {}
		~VecArr_T() { delete[] _ptr; }

		inline void* ptr() { return (void*)&_arr[0]; }
		inline void push_back(const vec_type& v) { _arr.push_back(v); }
		inline VecArr_T& operator <<(const vec_type& v) { _arr.push_back(v); return *this; }

	protected:
		std::vector<vec_type> _arr;
		value_type* _ptr{nullptr};
	};

	template <typename T>
	class ColorArr_T: public VecArr_T<T, Vec4_T<T>>
	{
	public:
		using base_type = VecArr_T<T, Vec4_T<T>>;
		ColorArr_T() {}
		ColorArr_T(const std::vector<base_type::vec_type>& arr) : base_type(arr) {}
		~ColorArr_T() {}

		void normalize() {
			for (auto& color : base_type::_arr) { color.normalize(); }
		}
	};
}

