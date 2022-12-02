#pragma once

#ifndef MAP_ITERATORS_HPP
# define MAP_ITERATORS_HPP

namespace ft {

	template < typename Compare, typename node, typename T >
		class map_iterators {

			public:

				/**********************************/
				/*****      MEMBER TYPES      *****/
				/**********************************/

				typedef T                               value_type;
				typedef T*                              pointer;
				typedef T&                              reference;
				typedef std::ptrdiff_t                  difference_type;
				typedef std::size_t                     size_type;
				typedef std::bidirectional_iterator_tag iterator_category;

			private:

				/**************************************/
				/*****      MEMBER ATTRIBUTES     *****/
				/**************************************/

				node    *_current;
				Compare _comp;

			public:

				/**************************************/
				/*****      MEMBER FUNCTIONS      *****/
				/**************************************/

				map_iterators()
					: _current(NULL) {
					};

				map_iterators( node *ptr )
					: _current(ptr), _comp(Compare()) {
					};

				map_iterators( const map_iterators &other ) {
					_current = other._current;
					_comp = other._comp;
				};

				virtual ~map_iterators() {
				};

				map_iterators &operator=( const map_iterators &other ) {
					if ( this != &other ) {
						this->_current = other._current;
					}
					return *this;
				};

				map_iterators &operator+=( difference_type n ) {
					for ( difference_type i = 0; i < n; ++i ) {
						_current++;
					}
					return *this;
				};

				map_iterators &operator-=( difference_type n ) {
					for ( difference_type i = 0; i < n; ++i) {
						_current--;
					}
					return *this;
				};



				/************************************/
				/*****      ELEMENT ACCESS      *****/
				/************************************/



				operator map_iterators<Compare, node, T const>() const {
					return map_iterators<Compare, node, T const>(_current);
				};

				reference operator*() const {
					return *(_current->_data);
				};

				pointer operator->() const {
					return _current->_data;
				};



				/*******************************/
				/*****      OPERATORS      *****/
				/*******************************/



				map_iterators& operator++() {
					if (_current->_right) {
						_current = _current->_right;
						while (_current->_left != NULL) {
						  _current = _current->_left;
						}
					}
					else if (_current->_right == NULL) {
						node *temp = _current;
						if (_current->_parent) {
							if (_comp(_current->_data->first, _current->_parent->_data->first)) {
                _current = _current->_parent;
              }
							else {
								while (_current->_parent && (!(_comp(_current->_data->first, _current->_parent->_data->first)))) {
                  _current = _current->_parent;
                }
								if (_current->_parent && _comp(_current->_data->first, _current->_parent->_data->first)) {
                  _current = _current->_parent;
                }
								if (_comp(_current->_data->first, temp->_data->first)) {
                  _current = _current->_end;
                }
							}
						}
						else {
              _current = _current->_end;
            }
					}
					return *this;
				};

				map_iterators operator++(int) {
					node *temp = _current;
					++(*this);
					return (map_iterators(temp));
				};

				map_iterators& operator--() {
					if (_current->_left) {
						_current = _current->_left;
						while (_current->_right) {
              _current = _current->_right;
            }
					}
					else {
						while (_current->_parent && (_comp(_current->_data->first, _current->_parent->_data->first))) {
              _current = _current->_parent;
            }
						if (_current->_parent && (!_comp(_current->_data->first, _current->_parent->_data->first))) {
              _current = _current->_parent;
            }
					}
					return *this;
				};

				map_iterators operator--(int) {
					node *temp = _current;
					--(*this);
					return (map_iterators(temp));
				};

				node *find_end( node *N ) {
					node *temp = N;
					while (temp->_parent) {
            temp = temp->_parent;
          }
					while (temp->_right) {
            temp = temp->_right;
          }
					return temp->_end;
				};

				node *find_last( node *N ) {
          node *temp = N;
					while (temp->_parent) {
            temp = temp->_parent;
          }
					while (temp->_right) {
            temp = temp->_right;
          }
					return temp;
				};

				node	*getnode() {
          return _current;
        };

				friend bool operator==( const map_iterators& lhs, const map_iterators& rhs ) {
					return lhs._current == rhs._current;
				};

				friend bool operator!=( const map_iterators& lhs, const map_iterators& rhs ) {
					return lhs._current != rhs._current;
				};

		}; // map_iterators

}; // namespace ft


#endif /* MAP_ITERATORS_HPP */
