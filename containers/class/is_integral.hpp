#pragma once

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "enable_if.hpp"

/*
**	Is_integral
**
**	Checks whether T is an integral type. Provides the member constant value which is equal to true,
**	if T is the type bool, char, wchar_t, short, int, long, long long
**	or any implementation-defined extended integer types, including any signed, unsigned
**	and cv-qualified variants. Otherwise, value is equal to false.
**	The behavior of a program that adds specializations for is_integral is undefined.
*/

namespace ft {

	template <class T>
	struct is_integral {
		static const bool value = false;
	};

	template <>
	struct is_integral<bool> {
		static const bool value = true;
	};

	template <>
	struct is_integral<char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<wchar_t> {
		static const bool value = true;
	};

	template <>
	struct is_integral<short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<int> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<long long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned char> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned short> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned int> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long> {
		static const bool value = true;
	};

	template <>
	struct is_integral<unsigned long long> {
		static const bool value = true;
	};

} // namespace ft

#endif /* IS_INTEGRAL_HPP */
