#pragma once

#ifndef EQUAL_HPP
# define EQUAL_HPP

# include "utils.hpp"

/*
**	Equal
**
**	Returns true if the range [first1, last1) is equal to
**	the range [first2, first2 + (last1 - first1)), and false otherwise.
**	Two ranges are considered equal if they have the same number of elements and,
**	for every iterator i in the range [first1,last1), *i equals *(first2 + (i - first1)).
**	This use operator== to determine if two elements are equal.
*/


namespace  ft {

	template < class  InputIterator1,  class  InputIterator2 >
	bool  equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 ) {
		while  (first1 != last1) {
			if  (!(*first1 == *first2)) {
				return  false;
			}
			++first1;
			++first2;
		}
		return  true;
	};

	template < class  InputIterator1,  class  InputIterator2,  class  BinaryPredicate >
	bool  equal( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred ) {
		while  (first1 != last1) {
			if  (!pred(*first1, *first2)) {
				return  false;
			}
			++first1;
			++first2;
		}
		return  true ;
	};

};  // namespace ft

#endif  /* EQUAL_HPP */
