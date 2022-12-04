#pragma once

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

/*
** Reversed iterator
**
** std::reverse_iterator is an iterator adaptor that reverses the direction of a given iterator,
** which must be at least a LegacyBidirectionalIterator. In other words,
** when provided with a bidirectional iterator, std::reverse_iterator produces a new iterator
** that moves from the end to the beginning of the sequence defined by the underlying bidirectional iterator.
** For a reverse iterator r constructed from an iterator i, the relationship &*r == &*(i-1)
** is always true (as long as r is dereferenceable); thus a reverse iterator constructed
** from a one-past-the-end iterator dereferences to the last element in a sequence.
** This is the iterator returned by member functions rbegin() and rend() of the standard library containers.
*/

namespace ft {

	template < class Iterator >
	class reverse_iterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category		iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type					value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type			difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer							pointer;
			typedef typename ft::iterator_traits<Iterator>::reference						reference;

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

			reverse_iterator()
				: _current() {
			};

			explicit reverse_iterator( iterator_type it )
				: _current(it) {
			};

			template < class It >
			reverse_iterator( const reverse_iterator<It>& rev_it )
				: _current(rev_it.base()) {
			};


			/*
			**	Destructor
			*/

			~reverse_iterator() {
			};


			/*
			**	Operator=
			**
			**	The underlying iterator is assigned the value of the underlying
			**	iterator of other, i.e. other.base().
			*/

			template< class It >
			reverse_iterator& operator=( const reverse_iterator<It>& rev_it ) {
				_current = rev_it.base();
				return *this;
			};


			/*
			**	Base
			**
			**	Returns the underlying base iterator. That is std::reverse_iterator(it).base() == it.
			**	The base iterator refers to the element that is next (from the std::reverse_iterator::iterator_type perspective)
			**	to the element the reverse_iterator is currently pointing to. That is &*(rit.base() - 1) == &*rit.
			*/

			iterator_type	base() const {
				return _current;
			};


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
			};

			pointer			operator->() const {
				return &(operator*());
			};


			/*
			**	Operator[]
			**
			**	Returns a reference to the element at specified relative location.
			*/

			reference			operator[]( difference_type n ) const {
				return *(*this + n);
			};


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

			reverse_iterator&	operator++() {
				--_current;
				return *this;
			};

			reverse_iterator&	operator--() {
				++_current;
				return *this;
			};

			reverse_iterator	operator++(int) {
				reverse_iterator tmp = *this;
				--_current;
				return tmp;
			};

			reverse_iterator	operator--(int) {
				reverse_iterator tmp = *this;
				++_current;
				return tmp;
			};

			reverse_iterator	operator+( difference_type n ) const {
				return reverse_iterator(_current - n);
			};

			reverse_iterator	operator-( difference_type n ) const {
				return reverse_iterator(_current + n);
			};

			difference_type	operator+( const reverse_iterator & x ) {
				return base() + x.base();
			};

			difference_type	operator-( const reverse_iterator & x ) {
				return x.base() - base();
			};

			reverse_iterator&	operator+=( difference_type n ) {
				_current -= n;
				return *this;
			};

			reverse_iterator&	operator-=( difference_type n ) {
				_current += n;
				return *this;
			};

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

	template < class It1, class It2 >
	bool	operator==( const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return lhs.base() == rhs.base();
	};

	template < class It1, class It2 >
	bool	operator!=( const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return lhs.base() != rhs.base();
	};

	template < class It1, class It2 >
	bool	operator<( const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return lhs.base() > rhs.base();
	};

	template < class It1, class It2 >
	bool	operator<=( const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return lhs.base() >= rhs.base();
	};

	template < class It1, class It2 >
	bool	operator>( const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return lhs.base() < rhs.base();
	};

	template < class It1, class It2 >
	bool	operator>=( const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs ) {
		return lhs.base() <= rhs.base();
	};


	/*
	**	Operator+
	**
	**	Returns the iterator it incremented by n.
	*/

	template < class It >
	reverse_iterator<It>	operator+( typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& rev_it ) {
		return reverse_iterator<It>(rev_it + n);
	};


	/*
	**	Operator-
	**
	**	Returns the distance between two iterator adaptors.
	*/
	template < class It >
	typename reverse_iterator<It>::difference_type	operator-( const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs ) {
		return rhs.base() - lhs.base();
	};

}; // namespace ft

#endif // REVERSE_ITERATOR_HPP
