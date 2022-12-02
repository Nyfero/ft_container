#pragma once

#ifndef VECTOR_ITERATORS_HPP
# define VECTOR_ITERATORS_HPP

namespace ft {

	template < class T >
	class vector_iterators
	{
		public:

			/**********************************/
			/*****      MEMBER TYPES      *****/
			/**********************************/

			typedef T				value_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef std::ptrdiff_t	difference_type;
			typedef std::size_t		size_type;



		private:

			/**************************************/
			/*****      MEMBER ATTRIBUTES     *****/
			/**************************************/

				pointer _ptr;



		public:

			/**************************************/
			/*****      MEMBER FUNCTIONS      *****/
			/**************************************/

			vector_iterators()
				: _ptr(NULL) {
			};

			vector_iterators( pointer ptr )
				: _ptr(ptr) {
			};

			vector_iterators( const vector_iterators<T>& other )
				: _ptr(other._ptr) {
			};

			virtual ~vector_iterators() {
			};

			vector_iterators & operator=( const vector_iterators & other ) {
				_ptr = other._ptr;
				return *this;
			};

			vector_iterators & operator+=( difference_type n ) {
				_ptr += n;
				return *this;
			};

			vector_iterators & operator-=( difference_type n ) {
				_ptr -= n;
				return *this;
			};



			/************************************/
			/*****      ELEMENT ACCESS      *****/
			/************************************/



			operator vector_iterators<T const>() const {
					return vector_iterators<T const>(_ptr);
			};

			reference operator*() const {
					return *_ptr;
			};

			pointer  operator->() const {
					return _ptr;
			};

			reference  operator[]( difference_type n ) const {
					return _ptr + n;
			};



			/*******************************/
			/*****      OPERATORS      *****/
			/*******************************/



			vector_iterators& operator++() {
					_ptr++;
					return *this;
			};

			vector_iterators& operator--() {
					_ptr--;
					return *this;
			};

			vector_iterators operator++(int) {
					_ptr++;
					return vector_iterators(_ptr - 1);
			};

			vector_iterators operator--(int) {
					_ptr--;
					return vector_iterators(_ptr + 1);
			};

			vector_iterators operator+( difference_type n ) const {
					vector_iterators tmp(*this);
					return tmp += n;
			};

			vector_iterators operator-( difference_type n ) const {
					vector_iterators tmp(*this);
					return tmp -= n;
			};

			difference_type operator+( const vector_iterators & other ) const{
					return _ptr + other._ptr;
			};

			difference_type operator-( const vector_iterators & other ) const {
					return _ptr - other._ptr;
			};

			bool operator==( const vector_iterators<T> & other ) const {
					return _ptr == other._ptr;
			};

			bool operator!=( const vector_iterators<T> & other) const {
					return _ptr != other._ptr;
			};

			bool operator<( const vector_iterators<T> & other ) const {
					return _ptr < other._ptr;
			};

			bool operator>( const vector_iterators<T> & other ) const {
					return _ptr > other._ptr;
			};

			bool operator<=( const vector_iterators<T> & other ) const {
					return _ptr <= other._ptr;
			};

			bool operator>= ( const vector_iterators<T> & other ) const {
					return _ptr >= other._ptr;
			};
	}; // vector_iterators

}; // namespace ft

#endif /* VECTOR_ITERATORS_HPP */
