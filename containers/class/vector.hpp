#pragma once

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

			/**********************************/
			/*****      MEMBER TYPES      *****/
			/**********************************/

			typedef T																						value_type;
			typedef Allocator																		allocator_type;

			typedef T*																					iterator;
			typedef const T*																		const_iterator;

			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference		const_reference;

			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer			const_pointer;

			typedef std::size_t																	size_type;
			typedef std::ptrdiff_t															difference_type;



		private:

			/**************************************/
			/*****      MEMBER ATTRIBUTES     *****/
			/**************************************/

			allocator_type	_alloc;
			pointer					_data;
			size_type				_size;
			size_type				_capacity;

		public:

			/**************************************/
			/*****      MEMBER FUNCTIONS      *****/
			/**************************************/



			/*
			**	Constructors
			**
			**	Constructs a new container from a variety of data sources,
			**	optionally using a user supplied allocator alloc.
			**		1) Default constructor. Constructs an empty container with a default-constructed allocator.
			**		2) Constructs an empty container with the given allocator alloc.
			**		3) Constructs the container with count copies of elements with value value.
			**		4) Constructs the container with the contents of the range [first, last).
			**		5) Copy constructor. Constructs the container with the copy of the contents of other.
			*/

			// 1
			vector()
				: _alloc(Allocator()), _data(NULL), _size(0), _capacity(0) {
					_data = _alloc.allocate(0);
			};

 			// 2
			explicit vector( const allocator_type& alloc )
				: _alloc(alloc), _data(NULL), _size(0), _capacity(0) {
					_data = _alloc.allocate(0);
			};

			// 3
			explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type() )
				: _alloc(alloc), _size(count), _capacity(count) {
				_data = _alloc.allocate(count);
				for (size_type i = 0; i < count; i++) {
					_alloc.construct(_data + i, value);
				}
			};

			// 4
			template< class InputIt >
			vector( InputIt first, InputIt last, const allocator_type& alloc = allocator_type() )
				: _alloc(alloc) {
				_data = _alloc.allocate(0);
				_capacity = 0;
				_size = 0;
				assign(first, last);
			};

			// 5
			vector( const vector& other ) {
				_alloc = other._alloc;
				_capacity = other._capacity;
				_size = other._size;
				_data = _alloc.allocate(_capacity);
				for (size_type i = 0; i < _size; i++) {
					_alloc.construct(_data + i, other._data[i]);
				}
			};


			/*
			**	Destructor
			**
			**	Destructs the vector. The destructors of the elements are called
			**	and the used storage is deallocated. Note, that if the elements are pointers,
			**	the pointed-to objects are not destroyed.
			*/

			~vector() {
				clear();
				_alloc.deallocate(_data, _capacity);
			};


			/*
			**	Operator=
			**
			**	Replaces the contents of the container.
			**	Copy assignment operator. Replaces the contents with a copy of the contents of other.
			*/

			vector& operator=( const vector& other ) {
				if (this != &other) {
					clear();
					_alloc = other._alloc;
					if (_capacity < other._size) {
						reserve(other._capacity);
					}
					_size = other._size;
					for (size_type i = 0; i < _size; i++) {
						_alloc.construct(_data + i, other._data[i]);
					}
				}
				return *this;
			};


			/*
			**	Assign
			**
			**	Replaces the contents of the container.
			**		1) Replaces the contents with count copies of value value
			**		2) Replaces the contents with copies of those in the range [first, last).
			**	The behavior is undefined if either argument is an iterator into *this.
			**	This overload has the same effect as overload (1) if InputIt is an integral type.
			**	All iterators, pointers and references to the elements of the container are invalidated.
			**	The past-the-end iterator is also invalidated.
			*/

			// 1
			void assign( size_type count, const T& value ) {
				reserve(count);
				for (size_type i = 0; i < count; i++) {
					_alloc.destroy(_data + i);
					_alloc.construct(_data + i, value);
				}
				_size = count;
			};

			// 2
			template< class InputIt >
			void assign( InputIt first, InputIt last , typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL ) {
				size_type count = std::distance(first, last);
				reserve(count);
				for (size_type i = 0; i < count; i++) {
					_alloc.destroy(_data + i);
					_alloc.construct(_data + i, *first++);
				}
				_size = count;
			};


			/*
			**	Get_allocator
			**
			**	Returns the allocator associated with the container.
			*/

			allocator_type get_allocator() const {
				return _alloc;
			};



			/************************************/
			/*****      ELEMENT ACCESS      *****/
			/************************************/



			/*
			**	At
			**
			**	Returns a reference to the element at specified location pos, with bounds checking.
			**	If pos is not within the range of the container, an exception of type std::out_of_range is thrown.
			*/

			reference at( size_type pos ) {
				range_check(pos);
				return _data[pos];
			};

			const_reference at( size_type pos ) const {
				range_check(pos);
				return _data[pos];
			};


			/*
			**	Operator []
			**
			**	Returns a reference to the element at specified location pos.
			**	No bounds checking is performed.
			*/

			reference operator[]( size_type pos ) {
				return _data[pos];
			};

			const_reference operator[]( size_type pos ) const {
				return _data[pos];
			};


			/*
			**	Front
			**
			**	Returns a reference to the first element in the container.
			**	Calling front on an empty container is undefined.
			*/

			reference front() {
				return _data[0];
			};

			const_reference front() const {
				return _data[0];
			};


			/*
			**	Back
			**
			**	Returns a reference to the last element in the container.
			**	Calling back on an empty container causes undefined behavior.
			*/

			reference back() {
				return _data[_size - 1];
			};

			const_reference back() const {
				return _data[_size - 1];
			};


			/*
			**	Data
			**
			**	Returns pointer to the underlying array serving as element storage.
			**	The pointer is such that range [data(); data()+size()) is always
			**	a valid range, even if the container is empty (data() is not
			**	dereferenceable in that case).
			*/

			T* data() {
				return _data;
			};

			const T* data() const {
				return _data;
			};



			/******************************/
			/*****      ITERATOR      *****/
			/******************************/



			/*
			**	Begin
			**
			**	Returns an iterator to the first element of the vector.
			**	If the vector is empty, the returned iterator will be equal to end().
			*/

			iterator begin() {
				return _data;
			};

			const_iterator begin() const {
				return _data;
			};


			/*
			**	End
			**
			**	Returns an iterator to the element following the last element of the vector.
			**	This element acts as a placeholder; attempting to access it results in undefined behavior.
			*/

			iterator end() {
				return _data + _size;
			};

			const_iterator end() const {
				return _data + _size;
			};


			/*
			**	Rbegin
			**
			**	Returns a reverse iterator to the first element of the reversed vector.
			**	It corresponds to the last element of the non-reversed vector.
			**	If the vector is empty, the returned iterator is equal to rend().
			*/

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			};

			const_reverse_iterator rbegin() const {
				return reverse_const_iterator(end());
			};


			/*
			**	Rend
			**
			**	Returns a reverse iterator to the element following the last element of the reversed vector.
			**	It corresponds to the element preceding the first element of the non-reversed vector.
			**	This element acts as a placeholder, attempting to access it results in undefined behavior.
			*/

			reverse_iterator rend() {
				return reverse_iterator(begin());
			};

			const_reverse_iterator rend() const {
				return reverse_const_iterator(begin());
			};



			/******************************/
			/*****      CAPACITY      *****/
			/******************************/



			/*
			**	Empty
			**
			**	Checks if the container has no elements, i.e. whether begin() == end().
			*/

			bool empty() const {
				return _size == 0;
			};


			/*
			**	Size
			**
			**	Returns the number of elements in the container, i.e. std::distance(begin(), end()).
			*/

			size_type size() const {
				return _size;
			};


			/*
			**	Max_size
			**
			**	Returns the maximum number of elements the container is able to hold
			**	due to system or library implementation limitations,
			**	i.e. std::distance(begin(), end()) for the largest container.
			*/

			size_type max_size() const {
				return _alloc.max_size();
			};


			/*
			**	Reserve
			**
			**	Increase the capacity of the vector (the total number of elements
			**	that the vector can hold without requiring reallocation) to a value
			**	that's greater or equal to new_cap. If new_cap is greater than
			**	the current capacity(), new storage is allocated, otherwise the function does nothing.
			**	reserve() does not change the size of the vector.
			**	If new_cap is greater than capacity(), all iterators,
			**	including the past-the-end iterator, and all references to the
			**	elements are invalidated. Otherwise, no iterators or references are invalidated.
			*/

			void reserve( size_type new_cap ) {
				if (new_cap > max_size()) {
					throw std::length_error("vector::reserve");
				}
				if (new_cap > _capacity) {
					pointer tmp = _alloc.allocate(new_cap);
					for (size_type i = 0; i < _size; i++) {
						_alloc.construct(tmp + i, _data[i]);
						_alloc.destroy(_data + i);
					}
					_alloc.deallocate(_data, _capacity);
					_data = tmp;
					_capacity = new_cap;
				}
			};


			/*
			**	Capacity
			**
			**	Returns the number of elements that the container has currently allocated space for.
			*/

			size_type capacity() const {
				return _capacity;
			};



			/*******************************/
			/*****      MODIFIERS      *****/
			/*******************************/



			/*
			**	Clear
			**
			**	Erases all elements from the container. After this call, size() returns zero.
			**	Invalidates any references, pointers, or iterators referring to contained elements.
			**	Any past-the-end iterators are also invalidated.
			**	Leaves the capacity() of the vector unchanged (note: the standard's
			**	restriction on the changes to capacity is in the specification of vector::reserve).
			*/

			void clear() {
				for (size_type i = 0; i < _size; i++) {
					_alloc.destroy(_data + i);
				}
				_size = 0;
			};


			/*
			**	Insert
			**
			**	Inserts elements at the specified location in the container.
			**	Causes reallocation if the new size() is greater than the old capacity().
			**	If the new size() is greater than capacity(), all iterators and references are invalidated.
			**	Otherwise, only the iterators and references before the insertion point remain valid.
			**	The past-the-end iterator is also invalidated.
			*/

			iterator insert( const_iterator pos, const T& value ) {
				size_type index = pos - begin();
				if (_size + 1 > _capacity) {
					reserve(_size + 1);
				}
				if (index > 0) {
					shift_right(index , 1);
				}
				_alloc.construct(_data + index, value);
				_size++;
				return begin() + index;
			};

			void insert( const_iterator pos, size_type count, const T& value ) {
				size_type index = pos - begin();
				if (!count) {
					return;
				}
				if (_size + count > _capacity) {
					reserve(_size + count);
				}
				shift_right(index, count);
				for (size_type i = 0; i < count; i++) {
					_alloc.construct(_data + index + i, value);
					_size++;
				}
			};

			template< class InputIt >
			void insert( const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = NULL ) {
				size_type count = std::distance(first, last);
				if (!count) {
					return;
				}
				size_type index = pos - begin();
				if (_size + count > _capacity) {
					reserve(_size + count);
				}
				shift_right(index, count);
				for (size_type i = 0; i < count; i++) {
					_alloc.construct(_data + index + i, *first++);
					_size++;
				}
			};


			/*
			**	Erase
			**
			**	Erases the specified elements from the container.
			**		1) Removes the element at pos.
			**		2) Removes the elements in the range [first, last).
			**	Invalidates iterators and references at or after the point of the erase, including the end() iterator.
			**	The iterator pos must be valid and dereferenceable.
			**	Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
			**	The iterator first does not need to be dereferenceable if first == last: erasing an empty range is a no-op.
			*/

			// 1
			iterator erase( iterator pos ) {
				size_type index = pos - begin();
				_alloc.destroy(_data + index);
				if (index < _size - 1) {
					shift_left(index, 1);
				}
				_size--;
				return begin() + index;
			};

			// 2
			iterator erase( iterator first, iterator last ) {
				size_type count = last - first;
				size_type index = first - begin();
				size_type it_last = last - begin();
				for ( size_type i = index; i < it_last; ++i ) {
					_alloc.destroy(_data + i);
				}
				if (index < _size - count) {
					shift_left(index, count);
				}
				_size -= count;
				return begin() + index;
			};


			/*
			**	Push_back
			**
			**	Appends the given element value to the end of the container.
			**	The new element is initialized as a copy of value.
			**	If the new size() is greater than capacity() then all iterators
			**	and references (including the past-the-end iterator) are invalidated.
			**	Otherwise only the past-the-end iterator is invalidated.
			*/

			void push_back( const T& value ) {
				if (_size + 1 > _capacity) {
					reserve(size_check());
				}
				_alloc.construct(_data + _size, value);
				_size++;
			};


			/*
			**	Pop_back
			**
			**	Removes the last element of the container.
			**	Calling pop_back on an empty container results in undefined behavior.
			**	Iterators and references to the last element, as well as the end() iterator, are invalidated.
			*/

			void pop_back() {
				_alloc.destroy(_data + _size - 1);
				_size--;
			};


			/*
			**	Resize
			**
			**	Resizes the container to contain count elements.
			**	If the current size is greater than count, the container is reduced to its first count elements.
			**	If the current size is less than count,
			**	Additional default-inserted elements are appended
			*/

			void resize( size_type count, T value = T() ) {
				if (count > _size) {
					reserve(count);
					for (size_type i = _size; i < count; i++) {
						_alloc.construct(_data + i, value);
					}
				}
				else {
					for (size_type i = count; i < _size; i++) {
						_alloc.destroy(_data + i);
					}
				}
				_size = count;
			};


			/*
			**	Swap
			**
			**	Exchanges the contents of the container with those of other.
			**	Does not invoke any move, copy, or swap operations on individual elements.
			**	All iterators and references remain valid. The past-the-end iterator is invalidated.
			*/

			void swap( vector& other ) {
				std::swap( _alloc, other._alloc);
				std::swap( _data, other._data);
				std::swap( _size, other._size);
				std::swap( _capacity, other._capacity);
			};



			/****************************************/
			/*****      PRIVATES FUNCTIONS      *****/
			/****************************************/



		private:

			// Return 1 if the vector's size is 0, otherwise double the vector's size
			size_type	size_check() {
				if ( _size == 0 ) {
					return 1;
				}
				return _size * 2;
			};

			// Shift all my vector elements from pos to the right n times
			void	shift_right( size_type pos, size_type n ) {
				for (size_type i = _size - 1; i >= pos && _size; i--) {
					_alloc.construct(_data + i + n, _data[i]);
					_alloc.destroy(_data + i);
					if (i == 0) {
						break;
					}
				}
			};

			// Shift all my vector elements from pos to the left n times
			void	shift_left( size_type pos, size_type n ) {
				for (; pos < _size && pos + n < _capacity; pos++) {
					_alloc.construct(_data + pos, _data[pos + n]);
					_alloc.destroy(_data + pos + n);
					}
				};

			// Throw an error if the element is out of range for the vector
			void	range_check( size_type pos ) const {
				std::ostringstream c_n;
				std::ostringstream c_size;

				c_n << pos;
				c_size << _size;
				if (pos >= _size) {
					throw std::out_of_range(
						std::string("vector::_M_range_check: __n ") + \
						std::string("(which is ") + c_n.str() + \
						std::string(") >= this->size() (which is ") + \
						c_size.str() + std::string(")"));
				}
			};
	};

	/******************************************/
	/*****      NON-MEMBER FUNCTIONS      *****/
	/******************************************/



	/*
	**	Operators
	**
	**	Compares the contents of two vectors.
	**		1-2) Checks if the contents of lhs and rhs are equal, that is,
	**		 they have the same number of elements and each element in lhs compares equal
	**		 with the element in rhs at the same position.
	**		3-6) Compares the contents of lhs and rhs lexicographically.
	**		 The comparison is performed by a function equivalent to std::lexicographical_compare.
	*/

	// 1	Operator==
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	};

	// 2	Operator!=
	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return !(lhs == rhs);
	};

	// 3	Operator<
	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	// 4	Operator<=
	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs == rhs) {
			return true;
		}
		return lhs < rhs;
	};

	// 5	Operator>
	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs == rhs) {
			return false;
		}
		return !(lhs < rhs);
	};

	// 6	Operator>=
	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		if (lhs == rhs) {
			return true;
		}
		return !(lhs < rhs);
	};

	/*
	**	Swap
	**
	**	Specializes the std::swap algorithm for std::vector. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
	*/

	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	};

}; // namespace ft

#endif /* VECTOR_HPP */
