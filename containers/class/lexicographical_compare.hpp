#pragma once

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

# include "utils.hpp"

/*
**	Lexicographical_compare
**
**	Checks if the first range [first1, last1) is lexicographically less than the second range [first2, last2).
**	 1) Elements are compared using operator<.
**	 2) Elements are compared using the given binary comparison function comp.
**	Lexicographical comparison is an operation with the following properties:
**		Two ranges are compared element by element.
**		The first mismatching element defines which range is lexicographically less or greater than the other.
**		If one range is a prefix of another, the shorter range is lexicographically less than the other.
**		If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
**		An empty range is lexicographically less than any non-empty range.
**		Two empty ranges are lexicographically equal.
*/

namespace ft {

	template < class InputIterator1, class InputIterator2 >
	bool	lexicographical_compare( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2 ) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1) {
				return false;
			}
			else if (*first1 < *first2) {
				return true;
			}
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template < class InputIterator1, class InputIterator2, class Compare >
	bool	lexicographical_compare( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp ) {
		while (first1 != last1) {
			if (first2 == last2 || comp(*first2, *first1)) {
				return false;
			}
			else if (comp(*first1, *first2)) {
				return true;
			}
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

}; // namespace ft

#endif /* LEXICOGRAPHICAL_COMPARE_HPP */
