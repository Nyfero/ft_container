#pragma once

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

/*
** Reversed iterator
**
** std::reverse_iterators is an iterator adaptor that reverses the direction of a given iterator,
** which must be at least a LegacyBidirectionalIterator. In other words,
** when provided with a bidirectional iterator, std::reverse_iterators produces a new iterator
** that moves from the end to the beginning of the sequence defined by the underlying bidirectional iterator.
** For a reverse iterator r constructed from an iterator i, the relationship &*r == &*(i-1)
** is always true (as long as r is dereferenceable); thus a reverse iterator constructed
** from a one-past-the-end iterator dereferences to the last element in a sequence.
** This is the iterator returned by member functions rbegin() and rend() of the standard library containers.
*/

namespace ft {

	template < class Iterator >
	class reverse_iterators
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

		protected:
			Iterator	_current;

		public:

			/**************************************/
			/*****      MEMBER FUNCTIONS      *****/
			/**************************************/



			/*
			**	Constructors
			**
			**	Constructs a new iterator adaptor.
			**	 1) Default constructor. The underlying iterator is value-initialized.
			**		Operations on the resulting iterator have defined behavior if and only if
			**		the corresponding operations on a value-initialized Iterator also have defined behavior.
			**	 2) The underlying iterator is initialized with x.
			**	 3) The underlying iterator is initialized with that of other.
			*/

			reverse_iterators()
				: _current() {
			}

			explicit reverse_iterators( iterator_type it )
				: _current(it) {
			}

			template < class It >
			reverse_iterators( const reverse_iterators<It>& rev_it )
				: _current(rev_it.base()) {
			}


			/*
			**	Destructor
			*/

			~reverse_iterators() {
			}


			/*
			**	Operator=
			**
			**	The underlying iterator is assigned the value of the underlying
			**	iterator of other, i.e. other.base().
			*/

			template< class It >
			reverse_iterators& operator=( const reverse_iterators<It>& rev_it ) {
				_current = rev_it.base();
				return *this;
			}


			/*
			**	Base
			**
			**	Returns the underlying base iterator. That is std::reverse_iterators(it).base() == it.
			**	The base iterator refers to the element that is next (from the std::reverse_iterators::iterator_type perspective)
			**	to the element the reverse_iterators is currently pointing to. That is &*(rit.base() - 1) == &*rit.
			*/

			iterator_type	base() const {
				return _current;
			}


			/*
			**	Operators(*, ->)
			**
			**	Returns a reference or pointer to the element previous to current.
			**	 1) Equivalent to Iter tmp = current; return *--tmp;
			**	 2) Equivalent to return std::addressof(operator*());.
			*/

			reference		operator*() const {
				Iterator tmp = _current;
				return *--tmp;
			}

			pointer			operator->() const {
				return &(operator*());
			}


			/*
			**	Operator[]
			**
			**	Returns a reference to the element at specified relative location.
			*/

			reference			operator[]( difference_type n ) const {
				return *(*this + n);
			}


			/*
			**	Maths operators
			**
			**	Increments or decrements the iterator. Inverse operations are applied
			**	to the underlying operator because of the reverse order.
			**	 1-2) Pre-increments or pre-decrements by one respectively.
			**	 3-4) Post-increments or post-decrements by one respectively.
			**	 5-6) Returns an iterator which is advanced by n or -n positions respectively.
			**	 7-8) Advances the iterator by n or -n positions respectively.
			*/

			reverse_iterators&	operator++() {
				--_current;
				return *this;
			}

			reverse_iterators&	operator--() {
				++_current;
				return *this;
			}

			reverse_iterators	operator++(int) {
				reverse_iterators tmp = *this;
				--_current;
				return tmp;
			}

			reverse_iterators	operator--(int) {
				reverse_iterators tmp = *this;
				++_current;
				return tmp;
			}

			reverse_iterators	operator+( difference_type n ) const {
				return reverse_iterators(_current - n);
			}

			reverse_iterators	operator-( difference_type n ) const {
				return reverse_iterators(_current + n);
			}

			reverse_iterators&	operator+=( difference_type n ) {
				_current -= n;
				return *this;
			}

			reverse_iterators&	operator-=( difference_type n ) {
				_current += n;
				return *this;
			}

	};

	/******************************************/
	/*****      NON-MEMBER FUNCTIONS      *****/
	/******************************************/



	/*
	**	Operators
	**
	**	Compares the underlying iterators. Inverse comparisons are applied in order
	**	to take into account that the iterator order is reversed.
	*/

	template < class It >
	bool	operator==( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template < class It >
	bool	operator!=( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template < class It >
	bool	operator<( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template < class It >
	bool	operator<=( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template < class It >
	bool	operator>( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template < class It >
	bool	operator>=( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return lhs.base() <= rhs.base();
	}


	/*
	**	Operator+
	**
	**	Returns the iterator it incremented by n.
	*/

	template < class It >
	reverse_iterators<It>	operator+( typename reverse_iterators<It>::difference_type n, const reverse_iterators<It>& rev_it ) {
		return reverse_iterators<It>(rev_it.base() - n);
	}


	/*
	**	Operator-
	**
	**	Returns the distance between two iterator adaptors.
	*/
	template < class It >
	typename reverse_iterators<It>::difference_type	operator-( const reverse_iterators<It>& lhs, const reverse_iterators<It>& rhs ) {
		return rhs.base() - lhs.base();
	}

} // namespace ft

#endif // REVERSE_ITERATOR_HPP
