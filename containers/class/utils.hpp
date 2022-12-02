#pragma once

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <deque>
# include <stdlib.h>
# include <sstream>
# include <sys/time.h>
# include <unistd.h>
# include <cstddef>

# include "iterator_traits.hpp"
# include "reverse_iterators.hpp"
# include "enable_if.hpp"
# include "equal.hpp"
# include "is_integral.hpp"
# include "lexicographical_compare.hpp"
# include "vector_iterators.hpp"
# include "pair.hpp"
// # include "map_iterators.hpp"

// STD lib
# include <stack>
# include <vector>
# include <map>

// FT lib
# include "stack.hpp"
# include "vector.hpp"
# include "map.hpp"

void	title(std::string str);
void	annonce(std::string msg);
void	Test_failure();
void	Test_performance(long real_time, long mine_time);
void	Test_success();
void	Test_timeout();
long	get_time();

void	launch_stack();

void	launch_vector();
void	launch_vector_iterators();

void launch_map();
void launch_map_iterators();

#endif /* UTILS_HPP */
