#pragma once

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft {

	template < class T, class Container = std::vector<T> >
	class stack
	{
		public:

			/**********************************/
			/*****      MEMBER TYPES      *****/
			/**********************************/

			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::size_type			size_type;

			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;

		protected:
			Container	c;

		public:

			/**************************************/
			/*****      MEMBER FUNCTIONS      *****/
			/**************************************/



			/*
			**	Constructors
			**
			**	Constructs new underlying container of the container adaptor from a variety of data sources.
			**	Copy-constructs the underlying container c with the contents of cont.
			**	This is also the default constructor.
			*/

			explicit stack( const container_type& cont = container_type() )
				: c( cont ) {
			};


			/*
			**	Destructor
			**
			**	Destructs the stack. The destructors of the elements are called and the used storage is deallocated.
			**	Note, that if the elements are pointers, the pointed-to objects are not destroyed.
			*/

			virtual ~stack() {
			};


			/*
			**	Operator=
			**
			**	Replaces the contents of the container adaptor with those of other.
			**	Copy assignment operator. Replaces the contents with a copy of the contents of other.
			**	Effectively calls c = other.c;.
			*/

			stack& operator=( const stack& other ) {
				c = other.c;
				return *this;
			};



			/*******************************/
			/*****      Operators      *****/
			/*******************************/



			/*
			**	Operators
			**
			**	Compares the contents of the underlying containers of two container adaptors.
			**	The comparison is done by applying the corresponding operator to the underlying containers.
			*/

			//	Operator==
			friend bool operator==( const ft::stack<value_type, container_type>& lhs, const ft::stack<value_type, container_type>& rhs ) {
				return lhs.c == rhs.c;
			};

			//	Operator!=
			friend bool operator!=( const ft::stack<value_type, container_type>& lhs, const ft::stack<value_type, container_type>& rhs ) {
				return lhs.c != rhs.c;
			};

			//	Operator<
			friend bool operator<( const ft::stack<value_type, container_type>& lhs, const ft::stack<value_type, container_type>& rhs ) {
				return lhs.c < rhs.c;
			};

			//	Operator<=
			friend bool operator<=( const ft::stack<value_type, container_type>& lhs, const ft::stack<value_type, container_type>& rhs ) {
				return lhs.c <= rhs.c;
			};

			//	Operator>
			friend bool operator>( const ft::stack<value_type, container_type>& lhs, const ft::stack<value_type, container_type>& rhs ) {
				return lhs.c > rhs.c;
			};

			//	Operator>=
			friend bool operator>=( const ft::stack<value_type, container_type>& lhs, const ft::stack<value_type, container_type>& rhs ) {
				return lhs.c >= rhs.c;
			};



			/************************************/
			/*****      ELEMENT ACCESS      *****/
			/************************************/



			/*
			**	Top
			**
			**	Returns reference to the top element in the stack.
			**	This is the most recently pushed element. This element will be removed on a call to pop().
			**	Effectively calls c.back().
			*/

			reference top() {
				return c.back();
			};

			const_reference top() const {
				return c.back();
			};



			/******************************/
			/*****      CAPACITY      *****/
			/******************************/



			/*
			**	Empty
			**
			**	Checks if the underlying container has no elements, i.e. whether c.empty().
			*/

			bool empty() const {
				return c.empty();
			};


			/*
			**	Size
			**
			**	Returns the number of elements in the underlying container, that is, c.size().
			*/

			size_type size() const {
				return c.size();
			};



			/*******************************/
			/*****      MODIFIERS      *****/
			/*******************************/



			/*
			**	Push
			**
			**	Pushes the given element value to the top of the stack.
			**	Effectively calls c.push_back(value).
			*/

			void push( const value_type& value ) {
				c.push_back( value );
			};


			/*
			**	Pop
			**
			**	Removes the top element from the stack. Effectively calls c.pop_back().
			*/

			void pop() {
				c.pop_back();
			};
	};

}	// namespace ft

#endif /*STACK_HPP*/
