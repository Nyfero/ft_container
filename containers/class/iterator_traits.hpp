# pragma once

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include "utils.hpp"

/*
**	Iterator traits
**
**	std::iterator_traits is the type trait class that provides uniform interface
**	to the properties of LegacyIterator types. This makes it possible to implement
**	algorithms only in terms of iterators.
**	The template can be specialized for user-defined iterators so that the information
**	about the iterator can be retrieved even if the type does not provide the usual typedefs.
*/

namespace ft {

	template < class Iterator >
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type					value_type;
			typedef typename Iterator::pointer						pointer;
			typedef typename Iterator::reference					reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template < class T >
	class iterator_traits<T*>
	{
		public:
			typedef ptrdiff_t													difference_type;
			typedef T																	value_type;
			typedef T*																pointer;
			typedef T&																reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

	template < class T >
	class iterator_traits<const T*>
	{
		public:
			typedef ptrdiff_t													difference_type;
			typedef T																	value_type;
			typedef const T*													pointer;
			typedef const T&													reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

}; // namespace ft

#endif /* ITERATOR_TRAITS_HPP */
