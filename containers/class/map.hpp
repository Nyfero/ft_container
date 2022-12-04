#pragma once

#ifndef MAP_HPP
# define MAP_HPP

# include "utils.hpp"

namespace ft {

	template< typename T >
	struct node
	{
		T				*_data;
		node		*_left;
		node		*_right;
		node		*_parent;
		node		*_end;
		int			_height;
	};

	template < typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{

			/**********************************/
			/*****      MEMBER TYPES      *****/
			/**********************************/

		public:

			typedef Key																													key_type;
			typedef T																														mapped_type;
			typedef typename ft::pair<const Key, T>															value_type;

			typedef std::size_t																									size_type;
			typedef std::ptrdiff_t																							difference_type;

			typedef Compare																											key_compare;
			typedef Allocator																										allocator_type;
			typedef value_type&																									reference;
			typedef const value_type&																						const_reference;

			typedef typename allocator_type::pointer														pointer;
			typedef typename allocator_type::const_pointer											const_pointer;
			typedef map_iterators<Compare, node<value_type>, value_type>				iterator;
			typedef map_iterators<Compare, node<value_type>, const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>															reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>												const_reverse_iterator;

		protected:

			typedef node<value_type>																						tnode;
			typedef typename allocator_type::template rebind<tnode>::other			node_alloc;


		public:

			/************************************/
			/*****      MEMBER CLASSES      *****/
			/************************************/

			/*
			**	Value_compare
			**
			**	std::map::value_compare is a function object that compares objects of type
			**	std::map::value_type (key-value pairs) by comparing of the first components of the pairs.
			*/

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				protected:

					Compare comp;

				public:

					value_compare( Compare c )
						: comp(c) {
					};

					bool operator()( const value_type& x, const value_type& y ) const {
						return comp(x.first, y.first);
					};
			};

		private:

			/***************************************/
			/*****      MEMBER ATTRIBUTES      *****/
			/***************************************/

			node_alloc			_allocNode;
			tnode						*_root;
			tnode						*_end;
			allocator_type	_alloc;
			size_type				_size;
			Compare					_comp;

		public:

			/**************************************/
			/*****      MEMBER FUNCTIONS      *****/
			/**************************************/



			/*
			**	Constructors
			**
			**	Constructs new container from a variety of data sources and optionally
			**	using user supplied allocator alloc or comparison function object comp.
			**		1) Constructs an empty container.
			**		2) Constructs the container with the contents of the range [first, last).
			**		 If multiple elements in the range have keys that compare equivalent,
			**		 it is unspecified which element is inserted (pending LWG2844).
			**		3) Copy constructor. Constructs the container with the copy of the contents of other.
			*/

			explicit map( const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
				: _allocNode(node_alloc()), _root(NULL), _end(NULL), _alloc(alloc), _size(0), _comp(comp) {
					initialize_end();
			};

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
				: _allocNode(node_alloc()), _root(NULL), _end(NULL), _alloc(alloc), _size(0), _comp(comp) {
				initialize_end();
				insert(first, last);
			};

			map( const map& other )
				: _allocNode(other._allocNode), _root(NULL), _end(NULL), _alloc(other._alloc), _size(0), _comp(other._comp) {
				initialize_end();
				insert(other.begin(), other.end());
			};


			/*
			**	Destructor
			**
			**	Destructs the map. The destructors of the elements are called and the used storage is deallocated.
			**	Note, that if the elements are pointers, the pointed-to objects are not destroyed.
			*/

			~map() {
				clear();
				_alloc.deallocate(_end->_data, 1);
				_allocNode.deallocate(_end, 1);
				_allocNode.destroy(_end);
			};


			/*
			**	Operator=
			**
			**	Replaces the contents of the container.
			**	Copy assignment operator. Replaces the contents with a copy of the contents of other.
			*/

			map& operator=( const map& other ) {
				clear();
				_allocNode = other._allocNode;
				_alloc = other._alloc;
				_comp = other._comp;
				insert(other.begin(), other.end());
				return *this;
			};


			/*
			**	Get_allocator
			**
			**	Returns the allocator associated with the container.
			*/

			allocator_type	get_allocator() const {
				return _alloc;
			};



			/************************************/
			/*****      ELEMENT ACCESS      *****/
			/************************************/



			/*
			**	At
			**
			**	Returns a reference to the mapped value of the element with key equivalent to key.
			**	If no such element exists, an exception of type std::out_of_range is thrown.
			*/

			T& at( const Key& key ) {
				iterator it = find(key);
				if (it != end() && it->first == key) {
					return it->second;
				}
				throw std::out_of_range("Key not found");
			};

			const T& at( const Key& key ) const {
				const_iterator it = find(key);
				if (it != end() && it->first == key) {
					return it->second;
				}
				throw std::out_of_range("Key not found");
			};

			/*
			**	Operator[]
			**
			**	Returns a reference to the value that is mapped to a key equivalent to key,
			**	performing an insertion if such key does not already exist.
			**	Inserts value_type(key, T()) if the key does not exist.
			**	This function is equivalent to return insert(std::make_pair(key, T())).first->second;
			**	- key_type must meet the requirements of CopyConstructible.
			**	- mapped_type must meet the requirements of CopyConstructible and DefaultConstructible.
			**	If an insertion is performed, the mapped value is value-initialized
			**	(default-constructed for class types, zero-initialized otherwise) and a reference to it is returned.
			*/

			T& operator[]( const Key& key ) {
				iterator it = find(key);
				if (it == end()) {
					value_type add(key, T());
					insert(add);
				}
				it = find(key);
				return it->second;
			};



			/******************************/
			/*****      ITERATOR      *****/
			/******************************/



			/*
			**	Begin
			**
			**	Returns an iterator to the first element of the map.
			**	If the map is empty, the returned iterator will be equal to end().
			*/

			iterator begin() {
				if (_size == 0) {
					return iterator(_end);
				}
				return iterator(node_value_min(_root));
			};

			const_iterator begin() const {
				if (_size == 0) {
					return const_iterator(_end);
				}
				return const_iterator(node_value_min(_root));
			};


			/*
			**	End
			**
			**	Returns an iterator to the element following the last element of the map.
			**	This element acts as a placeholder; attempting to access it results in undefined behavior.
			*/

			iterator end() {
				return iterator(_end);
			};

			const_iterator end() const {
				return const_iterator(_end);
			};


			/*
			**	Rbegin
			**
			**	Returns a reverse iterator to the first element of the reversed map.
			**	It corresponds to the last element of the non-reversed map.
			**	If the map is empty, the returned iterator is equal to rend().
			*/

			reverse_iterator rbegin() {
				return reverse_iterator(end());
			};

			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(end());
			};


			/*
			**	Rend
			**
			**	Returns a reverse iterator to the element following the last element of the reversed map.
			**	It corresponds to the element preceding the first element of the non-reversed map.
			**	This element acts as a placeholder, attempting to access it results in undefined behavior.
			*/

			reverse_iterator rend() {
				return reverse_iterator(begin());
			};

			const_reverse_iterator rend() const {
				return const_reverse_iterator(begin());
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

			size_type	size() const {
				return _size;
			};


			/*
			**	Max_size
			**
			**	Returns the maximum number of elements the container is able to hold
			**	due to system or library implementation limitations,
			**	i.e. std::distance(begin(), end()) for the largest container.
			*/

			size_type	max_size() const {
				return _alloc.max_size();
			};



			/*******************************/
			/*****      MODIFIERS      *****/
			/*******************************/



			/*
			**	Clear
			**
			**	Erases all elements from the container. After this call, size() returns zero.
			**	Invalidates any references, pointers, or iterators referring to contained elements.
			**	Any past-the-end iterator remains valid.
			*/

			void clear() {
				if (_size) {
					destroy_tree(_root);
				}
			};


			/*
			**	Insert
			**
			**	Inserts element(s) into the container, if the container doesn't already
			**	contain an element with an equivalent key.
			**		1) Inserts value. The overload (2) is equivalent to emplace(std::forward<P>(value)
			**		 and only participates in overload resolution if std::is_constructible<value_type, P&&>::value == true.
			**
			**		2) Inserts value in the position as close as possible, just prior(since C++11), to hint.
			**		 The overload (5) is equivalent to emplace_hint(hint, std::forward<P>(value))
			**		 and only participates in overload resolution if std::is_constructible<value_type, P&&>::value == true.
			**
			**		3) Inserts elements from range [first, last). If multiple elements in the range
			**		 have keys that compare equivalent, it is unspecified which element is inserted (pending LWG2844).
			*/

			pair<iterator, bool> insert( const value_type& value ) {
				size_type temp = _size;

				_root = insert_node(_root, value, NULL);
				if (_end->_parent == NULL) {
					_end->_parent = _root;
					_end->_left = _root;
				}
				else {
					tnode *new_max = node_value_max(_root);
					if (_comp(_end->_parent->_data->first, new_max->_data->first)) {
						_end->_parent = new_max;
						_end->_left = new_max;
					}
				}
				return pair<iterator, bool>(find(value.first), temp != size());
			};

			template< class InputIt >
			void insert( InputIt first, InputIt last ) {
				for (; first != last; ++first)
					insert(*first);
			};

			iterator	insert( iterator hint, const value_type& value ) {
				(void)hint;
				insert(value);
				return find(value.first);
			};


			/*
			**	Erase
			**
			**	Removes specified elements from the container.
			**		1) Removes the element at pos.
			**		2) Removes the elements in the range [first; last), which must be a valid range in *this.
			**		3) Removes the element (if one exists) with the key equivalent to key.
			**	References and iterators to the erased elements are invalidated.
			**	Other references and iterators are not affected.
			**	The iterator pos must be valid and dereferenceable.
			**	Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
			*/

			void erase( iterator pos ) {
				_root = deleteNode(_root, *pos.getnode()->_data);
				if (_root) {
					tnode *new_max = node_value_max(_root);
					_end->_parent = new_max;
					_end->_left = new_max;
				}
				else {
					_end->_parent = NULL;
					_end->_left = NULL;
				}
			};

			void erase( iterator first, iterator last ) {
				map tmp(first, last);
				iterator it = tmp.begin();
				iterator ite = tmp.end();
				ite--;
				for (; it != ite;) {
					erase(it);
					it++;
				}
				erase(it);
				if (!_size) {
						_end->_parent = NULL;
						_end->_left = NULL;
				}
			};

			size_type erase( const Key& key ) {
				iterator it = find(key);
				if (it == end()) {
					return 0;
				}
				erase(it);
				return 1;
			};


			/*
			**	Swap
			**
			**	Exchanges the contents of the container with those of other.
			**	Does not invoke any move, copy, or swap operations on individual elements.
			**	All iterators and references remain valid. The past-the-end iterator is invalidated.
			**	The Compare objects must be Swappable, and they are exchanged using unqualified call to non-member swap.
			*/

			void swap( map& other ) {
				node_alloc			tmp_allocNode = _allocNode;
				tnode						*tmp_root = _root;
				tnode						*tmp_end = _end;
				allocator_type	tmp_alloc = _alloc;
				size_type				tmp_size = _size;
				Compare					tmp_comp = _comp;

				_allocNode = other._allocNode;
				_root = other._root;
				_end = other._end;
				_alloc = other._alloc;
				_size = other._size;
				_comp = other._comp;
				other._allocNode = tmp_allocNode;
				other._root = tmp_root;
				other._end = tmp_end;
				other._alloc = tmp_alloc;
				other._size = tmp_size;
				other._comp = tmp_comp;
			};



			/****************************/
			/*****      LOOKUP      *****/
			/****************************/



			/*
			**	Count
			**
			**	Returns the number of elements with key that compares equivalent to the specified argument,
			**	which is either 1 or 0 since this container does not allow duplicates.
			**	Returns the number of elements with key key.
			*/

			size_type count( const Key& key ) const {
				return find(key) == end() ? 0 : 1;
			};


			/*
			**	Find
			**
			**	Finds an element with key equivalent to key.
			*/

			iterator find( const Key& key ) {
				return (find_in_tree(_root, key));
			};

			const_iterator find( const Key& key ) const {
				return (find_in_tree(_root, key));
			};


			/*
			**	Equal_range
			**
			**	Returns a range containing all elements with the given key in the container.
			**	The range is defined by two iterators, one pointing to the first element
			**	that is not less than key and another pointing to the first element greater than key.
			**	Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
			**	Compares the keys to key.
			*/

			ft::pair<iterator,iterator> equal_range( const Key& key ) {
				return ft::pair<iterator,iterator>(lower_bound(key), upper_bound(key));
			};

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
				return ft::pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key));
			};


			/*
			**	Lower_bound
			**
			**	Returns an iterator pointing to the first element that is not less than (i.e. greater or equal to) key.
			*/

			iterator lower_bound( const Key& key ) {
				iterator it = begin();
				while (it != end()) {
					if (it->first >= key) {
						return it;
					}
					++it;
				}
				return it;
			};

			const_iterator lower_bound( const Key& key ) const {
				const_iterator it = begin();
				while (it != end()) {
					if (it->first >= key) {
						return it;
					}
					++it;
				}
				return it;
			};


			/*
			**	Upper_bound
			**
			**	Returns an iterator pointing to the first element that is greater than key.
			*/

			iterator upper_bound( const Key& key ) {
				iterator it = begin();
				while (it != end()) {
					if (it->first > key)
						return it;
					++it;
				}
				return it;
			};

			const_iterator upper_bound( const Key& key ) const {
				const_iterator it = begin();
				while (it != end()) {
					if (it->first > key)
						return it;
					++it;
				}
				return it;
			};



			/*******************************/
			/*****      OBSERVERS      *****/
			/*******************************/



			/*
			**	Key_comp
			**
			**	Returns the function object that compares the keys,
			**	which is a copy of this container's constructor argument comp.
			*/

			key_compare key_comp() const {
				return _comp;
			};


			/*
			**	Value_comp
			**
			**	Returns a function object that compares objects of type std::map::value_type
			**	(key-value pairs) by using key_comp to compare the first components of the pairs.
			*/

			value_compare value_comp() const {
				return value_compare(Compare());
			};



			/*************************/
			/*****      AVL      *****/
			/*************************/

		private:

			int	max( int a, int b ) {
				return (a > b) ? a : b;
			};

			int height( tnode *nd ) {
				if (nd == NULL) {
					return 0;
				}
				return nd->_height;
			};

			void destroy_tree( tnode *nd ) {
				if (nd != NULL) {
					destroy_tree(nd->_left);
					destroy_tree(nd->_right);
					_size--;
					if (_size == 0) {
						_end->_parent = NULL;
						_end->_left = NULL;
					}
					free_node(nd);
				}
				_root = NULL;
			};

			iterator find_in_tree( tnode *nd, const Key& key ) {
				if (nd == NULL) {
					return end();
				}
				if (nd->_data->first == key) {
					return iterator(nd);
				}
				else if (_comp(key, nd->_data->first)) {
					return find_in_tree(nd->_left, key);
				}
				else {
					return find_in_tree(nd->_right, key);
				}
			};

			const_iterator find_in_tree( tnode *nd, const Key& key ) const {
				if (nd == NULL) {
					return end();
				}
				if (nd->_data->first == key) {
					return iterator(nd);
				}
				else if (_comp(key, nd->_data->first)) {
					return find_in_tree(nd->_left, key);
				}
				else {
					return find_in_tree(nd->_right, key);
				}
			};

			tnode	*new_node( const value_type& value, tnode *parent ) {
				tnode *nd = _allocNode.allocate(1);
				_allocNode.construct(nd, tnode());
				nd->_left = NULL;
				nd->_right = NULL;
				nd->_parent = parent;
				nd->_end = _end;
				nd->_height = 1;
				nd->_data = _alloc.allocate(1);
				_alloc.construct(nd->_data, value);
				return (nd);
			};

			void	free_node( tnode *nd ) {
				if (nd->_data) {
					_alloc.deallocate(nd->_data, 1);
					nd->_data = NULL;
				}
				_allocNode.deallocate(nd, 1);
				_allocNode.destroy(nd);
				nd = NULL;
			};

			tnode *rightRotate( tnode *y ) {
				tnode *x = y->_left;
				tnode *xr = x->_right;

				x->_parent = y->_parent;
				y->_parent = x;
				x->_right = y;
				y->_left = xr;
				if (xr) {
					xr->_parent = y;
				}
				y->_height = max(height(y->_left), height(y->_right)) + 1;
				x->_height = max(height(x->_left), height(x->_right)) + 1;
				return x;
			};

			tnode *leftRotate( tnode *x ) {
				tnode *y = x->_right;
				tnode *yl = y->_left;

				y->_parent = x->_parent;
				x->_parent = y;
				y->_left = x;
				x->_right = yl;
				if (yl) {
					yl->_parent = x;
				}
				x->_height = max(height(x->_left), height(x->_right)) + 1;
				y->_height = max(height(y->_left), height(y->_right)) + 1;
				return y;
			};

			int getBalanceFactor( tnode *nd ) {
				if (nd == NULL) {
					return 0;
				}
				return height(nd->_left) - height(nd->_right);
			};

			/* Insert a node in a recursive way
			/ 1- Find the correct position and Insert new node
			/ 2- Check the balance and rotate if necessary
			*/
			tnode *insert_node( tnode *root, const value_type value, tnode *parent ) {
				if (root == NULL) {
					_size++;
					return (new_node(value, parent));
				}
				if (_comp(value.first, root->_data->first)) {
					root->_left = insert_node(root->_left, value, root);
				}
				else {
					if (value.first == root->_data->first) {
						return root;
					}
					root->_right = insert_node(root->_right, value, root);
				}
				root->_height = 1 + max(height(root->_left), height(root->_right));
				int balanceFactor = getBalanceFactor(root);
				if (balanceFactor > 1) {
					if (_comp(value.first, root->_left->_data->first)) {
						return rightRotate(root);
					}
					else {
						root->_left = leftRotate(root->_left);
						return rightRotate(root);
					}
				}
				if (balanceFactor < -1) {
					if (!(_comp(value.first, root->_right->_data->first))) {
						return leftRotate(root);
					}
					else {
						root->_right = rightRotate(root->_right);
						return leftRotate(root);
					}
				}
				return root;
			};

			tnode *node_value_min( tnode *nd ) const {
				tnode *temp = nd;
				while (temp->_left != NULL) {
					temp = temp->_left;
				}
				return temp;
			};

			tnode *node_value_max( tnode *nd ) const {
				tnode *temp = nd;
				while (temp->_right != NULL) {
					temp = temp->_right;
				}
				return temp;
			};

			tnode *deleteNode( tnode *root, const value_type value ) {
				if (root == NULL) {
					return root;
				}
				if (_comp(value.first, root->_data->first)) {
					root->_left = deleteNode(root->_left, value);
				}
				else if (value.first != root->_data->first) {
					root->_right = deleteNode(root->_right, value);
				}
				else {
					if ((root->_left == NULL) || (root->_right == NULL)) {
						tnode *temp = root->_left ? root->_left : root->_right;
						if (temp == NULL) {
							temp = root;
							root = NULL;
						}
						else {
							tnode swap;
							swap._data = root->_data;
							root->_data = temp->_data;
							root->_left = temp->_left;
							root->_right = temp->_right;
							temp->_data = swap._data;
						}
						_size--;
						free_node(temp);
					}
					else {
						tnode swap;
						swap._data = root->_data;
						tnode *temp = node_value_min(root->_right);
						if (temp->_data->first == root->_right->_data->first) {
							root->_right = root->_right->_right;
						}
						else {
							temp->_parent->_left = NULL;
						}
						root->_data = temp->_data;
						temp->_data = swap._data;
						if (temp->_right) {
							temp->_right->_parent = root;
						}
						_size--;
						free_node(temp);
					}
				}
				if (root == NULL) {
					return root;
				}
				root->_height = 1 + max(height(root->_left), height(root->_right));
				int balanceFactor = getBalanceFactor(root);
				if (balanceFactor > 1) {
					if (getBalanceFactor(root->_left) >= 0) {
						return rightRotate(root);
					}
					else {
						root->_left = leftRotate(root->_left);
						return rightRotate(root);
					}
				}
				if (balanceFactor < -1)	{
					if (getBalanceFactor(root->_right) <= 0) {
						return leftRotate(root);
					}
					else {
						root->_right = rightRotate(root->_right);
						return leftRotate(root);
					}
				}
				return root;
			};

			void	initialize_end() {
				_end = new_node(value_type(key_type(), mapped_type()), NULL);
			};

			// Print the tree
			void printTree( tnode *root, std::string indent, bool last ) {
				if (root != NULL) {
					std::cout << indent;
					if (last) {
						std::cout << "R----";
						indent += "   ";
					}
					else {
						std::cout << "L----";
						indent += "|  ";
					}
					std::cout << root->_data->first << std::endl;
					printInfoNode(root);
					printTree(root->_left, indent, false);
					printTree(root->_right, indent, true);
				}
			};

			void printInfoNode( tnode *nd ) {
				std::cout << "ndODE " << nd->_data->first;
				//  std::cout << "ndODE " << nd->_data->first << " HEIGHT LEFT = " << height(nd->_left) << " HEIGHT RIGHT = " << height(nd->_right) << " HEIGHT = " << height(nd->_left) - height(nd->_right);
				if (nd->_left) {
					std::cout<< " Value nd->_left "<< nd->_left->_data->first;
				}
				if (nd->_right) {
					std::cout<< " Value nd->_right "<< nd->_right->_data->first;
				}
				if (nd->_parent) {
					std::cout << " DAD = " << nd->_parent->_data->first;
				}
				else {
					std::cout << " DAD = NULL ";
				}
				std::cout<< std::endl;
			};

	};

	/******************************************/
	/*****      NON-MEMBER FUNCTIONS      *****/
	/******************************************/



	/*
	**	Operators
	**
	**	Compares the contents of two maps.
	**		1-2) Checks if the contents of lhs and rhs are equal, that is,
	**		 they have the same number of elements and each element in lhs compares equal
	**		 with the element in rhs at the same position.
	**		3-6) Compares the contents of lhs and rhs lexicographically.
	**		 The comparison is performed by a function equivalent to std::lexicographical_compare.
	**		 This comparison ignores the map's ordering Compare.
	*/

	//	Operator==
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size()) {
			return false;
		}
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it1 = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end()) {
			if (it1->first != it2->first || it1->second != it2->second) {
				return false;
			}
			++it1;
			++it2;
		}
		return true;
	};

	//	Operator!=
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs == rhs);
	};

	//	Operator<
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it1 = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it2 = rhs.begin();
		while (it1 != lhs.end() && it2 != rhs.end()) {
			if (it1->first < it2->first) {
				return true;
			}
			else if (it1->first > it2->first) {
				return false;
			}
			else if (it1->second < it2->second) {
				return true;
			}
			else if (it1->second > it2->second) {
				return false;
			}
			++it1;
			++it2;
		}
		if (it1 == lhs.end() && it2 != rhs.end()) {
			return true;
		}
		return false;
	};

	//	Operator<=
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(rhs < lhs);
	};

	//	Operator>
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	};

	//	Operator>=
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	};

	/*
	**	Swap
	**
	**	Specializes the std::swap algorithm for std::map. Swaps the contents of lhs and rhs. Calls lhs.swap(rhs).
	*/

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	};

}; // namespace ft

#endif /*MAP_HPP*/
