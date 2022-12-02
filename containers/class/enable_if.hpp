#pragma once

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

/*
**	Enable if
**
**	If B is true, std::enable_if has a public member typedef type, equal to T;
**	otherwise, there is no member typedef.
**	This metafunction is a convenient way to leverage SFINAE prior to C++20's concepts,
**	in particular for conditionally removing functions from the candidate set based on type traits,
**	allowing separate function overloads or specializations based on those different type traits.
**	std::enable_if can be used in many forms, including:
**		as an additional function argument (not applicable to operator overloads)
**		as a return type (not applicable to constructors and destructors)
**		as a class template or function template parameter
**	The behavior of a program that adds specializations for enable_if is undefined.
*/

namespace ft {

	template < bool B, class T = void >
	struct enable_if {
	};

	template < class T >
	struct enable_if<true, T> {
		typedef T type;
	};

} // namespace ft

#endif /* ENABLE_IF_HPP */
