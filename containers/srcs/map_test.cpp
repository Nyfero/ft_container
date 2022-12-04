#include "../class/utils.hpp"

void	map_test_constructors() {
	title("\e[95m-Constructors-\e[39m");

	annonce("Default constructor");

	long time = get_time();
	std::map<char, int> real;
	real['a'] = 44;
	real['b'] = -34;
	real['c'] = 112;
	long real_time = get_time() - time;

	time = get_time();
	PRE::map<char, int>		mine;
	mine['a'] = 44;
	mine['b'] = -34;
	mine['c'] = 112;
	long mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Range constructor");

	time = get_time();
	std::map<char, int>		real2(real.begin(), real.end());
	real_time = get_time() - time;

	time = get_time();
	PRE::map<char, int>	mine2(mine.begin(), mine.end());
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), mine2.begin()) || mine2.size() != real2.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Copy constructor");

	time = get_time();
	std::map<char, int>		real3(real2);
	real_time = get_time() - time;

	time = get_time();
	PRE::map<char, int> mine3(mine);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), mine3.begin()) || mine3.size() != real3.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Operator =");

	time = get_time();
	std::map<char, int>		real4 = real3;
	real_time = get_time() - time;

	time = get_time();
	PRE::map<char, int> mine4 = mine;
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), mine4.begin()) || mine4.size() != real4.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	map_test_at() {
	title("\e[95m-At-\e[39m");

	std::map<int, int> real;
	for (int i = 0; i < 10; i++) {
			real.insert(std::pair<int, int>(i, i));
	}
	PRE::map<int, int>		mine;
	for (int i = 0; i < 10; i++) {
			mine.insert(PRE::pair<int, int>(i, i));
	}

	annonce("At in range");
	try {
		for (int k = 0; k < 10; k++) {
			if (real.at(k) != mine.at(k)) {
				std::cout << "Real map: " << real.at(k) << std::endl;
				std::cout << "Mine map: " << mine.at(k) << std::endl;
				return Test_failure();
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("At negative");
	try {
		int must_fail = mine.at(-1);
		std::cout << "At(-1) ? " << must_fail << std::endl;
		return Test_failure();
	}
	catch (const std::exception& e) {
		;
	}
	Test_success();

	annonce("At out of range");
	try {
		int must_fail = mine.at(10);
		std::cout << "At(10) ? " << must_fail << std::endl;
		return Test_failure();
	}
	catch (const std::exception& e) {
		;
	}
	Test_success();
};

void	map_test_bracket() {
		title("\e[95m-Brackets []-\e[39m");

	std::map<int, int> real;
	for (int i = 0; i < 10; i++) {
			real.insert(std::pair<int, int>(i, i));
	}
	PRE::map<int, int>		mine;
	for (int i = 0; i < 10; i++) {
			mine.insert(PRE::pair<int, int>(i, i));
	}

	annonce("Brackets in range");
	for (int k = 0; k < 10; k++) {
		if (real[k] != mine[k]) {
			std::cout << "Real map: " << real[k] << std::endl;
			std::cout << "Mine map: " << mine[k] << std::endl;
			return Test_failure();
		}
	}
	Test_success();

	// Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior

	annonce("Brackets negative");
	if (real[-1] != mine[-1]) {
		std::cout << "Real map: " << real[-1] << std::endl;
		std::cout << "Mine map: " << mine[-1] << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Brackets out of range");
	if (real[10] != mine[10]) {
		std::cout << "Real map: " << real[10] << std::endl;
		std::cout << "Mine map: " << mine[10] << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	map_test_empty() {
	title("\e[95m-Empty-\e[39m");

	std::map<int, int>	real;
	PRE::map<int, int>		mine;

	annonce("Empty with no element");
	if (real.empty() != mine.empty()) {
		std::cout << "Real map: " << real.empty() << std::endl;
		std::cout << "Mine map: " << mine.empty() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Empty with one element");
	real.insert(std::pair<int, int>(1, 1));
	mine.insert(PRE::pair<int, int>(1, 1));
	if (real.empty() != mine.empty()) {
		std::cout << "Real map: " << real.empty() << std::endl;
		std::cout << "Mine map: " << mine.empty() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	map_test_size() {
	title("\e[95m-Size-\e[39m");
	srand(time(NULL));

	std::map<int, int>	real;
	PRE::map<int, int>		mine;

	annonce("Size with no element");
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Size with one element");
	real.insert(std::pair<int, int>(1, 1));
	mine.insert(PRE::pair<int, int>(1, 1));
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Size beetwen 1 and 1000");
	int n = (rand() % 1000) + 1;
	for (int i = 0; i < n; i++) {
		real.insert(std::pair<int, int>(i, i));
		mine.insert(PRE::pair<int, int>(i, i));
	}
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	map_test_clear() {
	title("\e[95m-Clear-\e[39m");
	srand(time(NULL));

	std::map<int, int>	real;
	PRE::map<int, int>		mine;

	annonce("Clear with 0");

	long time = get_time();
	real.clear();
	long real_time = get_time() - time;

	time = get_time();
	mine.clear();
	long mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Clear with 1");

	real.insert(std::pair<int, int>(1, 1));
	mine.insert(PRE::pair<int, int>(1, 1));

	time = get_time();
	real.clear();
	real_time = get_time() - time;

	time = get_time();
	mine.clear();
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Clear with 1000");
	for (int i = 0; i < 1000; i++) {
		real.insert(std::pair<int, int>(i, i));
		mine.insert(PRE::pair<int, int>(i, i));
	}

	time = get_time();
	real.clear();
	real_time = get_time() - time;

	time = get_time();
	mine.clear();
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	map_test_insert() {
	title("\e[95m-Insert-\e[39m");
	srand(time(NULL));

	annonce("Insert with pair");
	std::map<int, int> real;

	std::pair<int, int> radd(100, 42);
	std::pair<int, int> radd2(50, 42);
	std::pair<int, int> radd3(4, 42);
	std::pair<int, int> radd4(2, 42);
	std::pair<int, int> radd5(999, 48);
	std::pair<int, int> radd6(7, 42);
	std::pair<int, int> radd7(12, 42);
	std::pair<int, int> radd8(-56, 42);
	std::pair<int, int> radd9(1, 42);

	long time = get_time();
	real.insert(radd);
	real.insert(radd2);
	real.insert(radd3);
	real.insert(radd4);
	real.insert(radd5);
	real.insert(radd6);
	real.insert(radd7);
	real.insert(radd8);
	real.insert(radd9);
	long real_time = get_time() - time;

	PRE::map<int, int> mine;

	PRE::pair<int, int> madd(100, 42);
	PRE::pair<int, int> madd2(50, 42);
	PRE::pair<int, int> madd3(4, 42);
	PRE::pair<int, int> madd4(2, 42);
	PRE::pair<int, int> madd5(999, 48);
	PRE::pair<int, int> madd6(7, 42);
	PRE::pair<int, int> madd7(12, 42);
	PRE::pair<int, int> madd8(-56, 42);
	PRE::pair<int, int> madd9(1, 42);

	time = get_time();
	mine.insert(madd);
	mine.insert(madd2);
	mine.insert(madd3);
	mine.insert(madd4);
	mine.insert(madd5);
	mine.insert(madd6);
	mine.insert(madd7);
	mine.insert(madd8);
	mine.insert(madd9);
	long mine_time = get_time() - time;

	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Insert with range");

	std::map<int, int> real2;
	PRE::map<int, int> mine2;

	time = get_time();
	real2.insert(real.begin(), real.end());
	real_time = get_time() - time;

	time = get_time();
	mine2.insert(mine.begin(), mine.end());
	mine_time = get_time() - time;

	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Insert with value");

	std::map<int, int> real3;
	PRE::map<int, int> mine3;

	time = get_time();
	real2.insert(real.begin(), radd);
	real_time = get_time() - time;

	time = get_time();
	mine2.insert(mine.begin(), madd);
	mine_time = get_time() - time;

	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);


	// PRE::map<int, int>::iterator it_real = real.begin();
	//
	// for (PRE::map<int, int>::iterator it = mine.begin(); it != mine.end();)
	// {
	// 	// std::cout << it->first << std::endl;
	// 	EXPECT_EQ(it->first, it_real->first);
	// 	it++;
	// 	it_real++;
	// }
};

void	map_test_erase() {
	title("\e[95m-Erase-\e[39m");
	srand(time(NULL));

	annonce("Erase with iterator"); {
			std::map<std::string, int>	real;
			real["bonjour"] = 42;
			real["je"] = 43;
			real["suis"] = 44;
			real["un"] = 45;
			real["dinosaure"] = 46;
			real["lol"] = 47;
			real["."] = 48;

			PRE::map<std::string, int>		mine;
			mine["bonjour"] = 42;
			mine["je"] = 43;
			mine["suis"] = 44;
			mine["un"] = 45;
			mine["dinosaure"] = 46;
			mine["lol"] = 47;
			mine["."] = 48;

			std::map<std::string, int>::iterator it_real = real.begin();
			it_real++;
			it_real++;
			long time = get_time();
			real.erase(real.begin());
			real.erase(it_real);
			long real_time = get_time() - time;

			PRE::map<std::string, int>::iterator it = mine.begin();
			it++;
			it++;
			time = get_time();
			mine.erase(mine.begin());
			mine.erase(it);
			long mine_time = get_time() - time;

			if (real.size() != mine.size()) {
				std::cout << "Real map: " << real.size() << std::endl;
				std::cout << "Mine map: " << mine.size() << std::endl;
				return Test_failure();
			}
			Test_performance(real_time, mine_time);
	}

	annonce("Erase with range"); {
		std::map<std::string, int>	real;
		real["bonjour"] = 42;
		real["je"] = 43;
		real["suis"] = 44;
		real["un"] = 45;
		real["dinosaure"] = 46;
		real["lol"] = 47;
		real["."] = 48;

		PRE::map<std::string, int>		mine;
		mine["bonjour"] = 42;
		mine["je"] = 43;
		mine["suis"] = 44;
		mine["un"] = 45;
		mine["dinosaure"] = 46;
		mine["lol"] = 47;
		mine["."] = 48;

		long time = get_time();
		real.erase(real.begin(), real.end());
		long real_time = get_time() - time;

		time = get_time();
		mine.erase(mine.begin(), mine.end());
		long mine_time = get_time() - time;

		if (real.size() != mine.size()) {
			std::cout << "Real map: " << real.size() << std::endl;
			std::cout << "Mine map: " << mine.size() << std::endl;
			return Test_failure();
		}
		Test_performance(real_time, mine_time);
	}

	annonce("Erase with key"); {
		std::map<std::string, int>	real;
		real["bonjour"] = 42;
		real["je"] = 43;
		real["suis"] = 44;
		real["un"] = 45;
		real["dinosaure"] = 46;
		real["lol"] = 47;
		real["."] = 48;

		PRE::map<std::string, int>		mine;
		mine["bonjour"] = 42;
		mine["je"] = 43;
		mine["suis"] = 44;
		mine["un"] = 45;
		mine["dinosaure"] = 46;
		mine["lol"] = 47;
		mine["."] = 48;

		long time = get_time();
		real.erase("lol");
		real.erase("suis");
		long real_time = get_time() - time;

		time = get_time();
		mine.erase("lol");
		mine.erase("suis");
		long mine_time = get_time() - time;

		if (real.size() != mine.size()) {
			std::cout << "Real map: " << real.size() << std::endl;
			std::cout << "Mine map: " << mine.size() << std::endl;
			return Test_failure();
		}
		Test_performance(real_time, mine_time);
	}
};

void	map_test_swap() {
	title("\e[95m-Swap-\e[39m");
	srand(time(NULL));

	std::map<int, int>	real;
	PRE::map<int, int>		mine;

	annonce("Swap 1 element");
	real.insert(std::pair<int, int>(1, 1));
	mine.insert(PRE::pair<int, int>(1, 1));

	long time = get_time();
	real.swap(real);
	long real_time = get_time() - time;

	time = get_time();
	mine.swap(mine);
	long mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Swap 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.insert(std::pair<int, int>(i, i));
		mine.insert(PRE::pair<int, int>(i, i));
	}

	time = get_time();
	real.swap(real);
	real_time = get_time() - time;

	time = get_time();
	mine.swap(mine);
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real map: " << real.size() << std::endl;
		std::cout << "Mine map: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void map_test_count() {
	title("\e[95m-Count-\e[39m");

	std::map<std::string, int>	real;
	real["bonjour"] = 42;
	real["je"] = 43;
	real["suis"] = 44;
	real["un"] = 45;
	real["dinosaure"] = 46;
	real["lol"] = 47;
	real["."] = 48;

	PRE::map<std::string, int>		mine;
	mine["bonjour"] = 42;
	mine["je"] = 43;
	mine["suis"] = 44;
	mine["un"] = 45;
	mine["dinosaure"] = 46;
	mine["lol"] = 47;
	mine["."] = 48;

	annonce("Count");
	if (real.count("un") != mine.count("un")) {
		std::cout << "Real map: " << real.count("un") << std::endl;
		std::cout << "Mine map: " << mine.count("un") << std::endl;
		return Test_failure();
	}
	if (real.count("salut") != mine.count("salut")) {
		std::cout << "Real map: " << real.count("salut") << std::endl;
		std::cout << "Mine map: " << mine.count("salut") << std::endl;
		return Test_failure();
	}
	Test_success();
};

void launch_map() {
	title("\e[93m Functions: \e[39m");
  map_test_constructors();
	map_test_at();
	map_test_bracket();
	map_test_empty();
	map_test_size();
	map_test_clear();
	map_test_insert();
	map_test_erase();
	map_test_swap();
	map_test_count();
};

void map_test_begin() {
	title("\e[95m-Begin-\e[39m");
	srand(time(NULL));

	PRE::map<int, int>		mine;
	PRE::map<int, int>		mine2;

	annonce("Begin 1 element");
	mine.insert(PRE::pair<int, int>(1, 1));
	mine2.insert(PRE::pair<int, int>(1, 1));
	if (*mine.begin() != *mine2.begin()) {
		return Test_failure();
	}
	Test_success();

	annonce("Begin 1000 elements");
	for (int i = 0; i < 1000; i++) {
		mine.insert(PRE::pair<int, int>(i, i));
		mine2.insert(PRE::pair<int, int>(i, i));
	}
	if (*mine.begin() != *mine2.begin()) {
		return Test_failure();
	}
	Test_success();
};

void map_test_end() {
	title("\e[95m-End-\e[39m");
	srand(time(NULL));

	PRE::map<int, int>		mine;
	PRE::map<int, int>		mine2;

	annonce("End 1 element");
	mine.insert(PRE::pair<int, int>(1, 1));
	mine2.insert(PRE::pair<int, int>(1, 1));
	if (*mine.end() != *mine2.end()) {
		return Test_failure();
	}
	Test_success();

	annonce("End 1000 elements");
	for (int i = 0; i < 1000; i++) {
		mine.insert(PRE::pair<int, int>(i, i));
		mine2.insert(PRE::pair<int, int>(i, i));
	}
	if (*mine.end() != *mine2.end()) {
		return Test_failure();
	}
	Test_success();
};

void map_test_rbegin() {
	title("\e[95m-Rbegin-\e[39m");
	srand(time(NULL));

	PRE::map<int, int>		mine;
	PRE::map<int, int>		mine2;

	annonce("Rbegin 1 element");
	mine.insert(PRE::pair<int, int>(1, 1));
	mine2.insert(PRE::pair<int, int>(1, 1));
	if (*mine.rbegin() != *mine2.rbegin()) {
		return Test_failure();
	}
	Test_success();

	annonce("Rbegin 1000 elements");
	for (int i = 0; i < 1000; i++) {
		mine.insert(PRE::pair<int, int>(i, i));
		mine2.insert(PRE::pair<int, int>(i, i));
	}
	if (*mine.rbegin() != *mine2.rbegin()) {
		return Test_failure();
	}
	Test_success();
};

void map_test_rend() {
	title("\e[95m-Rend-\e[39m");
	srand(time(NULL));

	PRE::map<int, int>		mine;
	PRE::map<int, int>		mine2;

	annonce("Rend 1 element");
	mine.insert(PRE::pair<int, int>(1, 1));
	mine2.insert(PRE::pair<int, int>(1, 1));
	if (*mine.rend() != *mine2.rend()) {
		return Test_failure();
	}
	Test_success();

	annonce("Rend 1000 elements");
	for (int i = 0; i < 1000; i++) {
		mine.insert(PRE::pair<int, int>(i, i));
		mine2.insert(PRE::pair<int, int>(i, i));
	}
	if (*mine.rend() != *mine2.rend()) {
		return Test_failure();
	}
	Test_success();
};

void map_test_lower() {
	title("\e[95m-Lower_bound-\e[39m");
	srand(time(NULL));

	PRE::map<int, int>		mine;
	PRE::map<int, int>		mine2;

	annonce("Lower_bound 1 element");
	mine.insert(PRE::pair<int, int>(1, 1));
	mine2.insert(PRE::pair<int, int>(1, 1));
	if (*mine.lower_bound(1) != *mine2.lower_bound(1)) {
		return Test_failure();
	}
	Test_success();

	annonce("Lower_bound 1000 elements");
	for (int i = 0; i < 1000; i++) {
		mine.insert(PRE::pair<int, int>(i, i));
		mine2.insert(PRE::pair<int, int>(i, i));
	}
	if (*mine.lower_bound(54) != *mine2.lower_bound(54)) {
		return Test_failure();
	}
	Test_success();

	annonce("Lower_bound out of bounds");
	if (*mine.lower_bound(1001) != *mine2.lower_bound(1001)) {
		return Test_failure();
	}
	Test_success();
};

void map_test_upper() {
	title("\e[95m-Upper_bound-\e[39m");
	srand(time(NULL));

	PRE::map<int, int>		mine;
	PRE::map<int, int>		mine2;

	annonce("Upper_bound 1 element");
	mine.insert(PRE::pair<int, int>(1, 1));
	mine2.insert(PRE::pair<int, int>(1, 1));
	if (*mine.upper_bound(1) != *mine2.upper_bound(1)) {
		return Test_failure();
	}
	Test_success();

	annonce("Upper_bound 1000 elements");
	for (int i = 0; i < 1000; i++) {
		mine.insert(PRE::pair<int, int>(i, i));
		mine2.insert(PRE::pair<int, int>(i, i));
	}
	if (*mine.upper_bound(54) != *mine2.upper_bound(54)) {
		return Test_failure();
	}
	Test_success();

	annonce("Upper_bound out of bounds");
	if (*mine.upper_bound(1001) != *mine2.upper_bound(1001)) {
		return Test_failure();
	}
	Test_success();
};

void launch_map_iterators() {
	title("\e[93m Iterators: \e[39m");
	map_test_begin();
	map_test_end();
	map_test_rbegin();
	map_test_rend();
	map_test_lower();
	map_test_upper();
};
