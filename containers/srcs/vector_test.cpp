#include "../class/utils.hpp"

void	vector_test_constructors() {
	title("\e[95m-Constructors-\e[39m");

	annonce("Default constructor");

	long time = get_time();
	std::vector<int> real;
	real.push_back(44);
	real.push_back(-34);
	real.push_back(112);
	long real_time = get_time() - time;

	time = get_time();
	PRE::vector<int>		mine;
	mine.push_back(44);
	mine.push_back(-34);
	mine.push_back(112);
	long mine_time = get_time() - time;
	Test_performance(real_time, mine_time);

	annonce("Fill constructor");

	time = get_time();
	std::vector<int>		real1(3, 42);
	real_time = get_time() - time;

	time = get_time();
	PRE::vector<int>		mine1(3, 42);
	mine_time = get_time() - time;
	if (!ft::equal(real1.begin(), real1.end(), mine1.begin())) {
		std::cout << "Mine vector: " << mine1.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Range constructor");

	time = get_time();
	std::vector<int>		real2(real1.begin(), real1.end());
	real_time = get_time() - time;

	time = get_time();
	PRE::vector<int>	mine2(mine.begin(), mine.end());
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), mine2.begin())) {
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Copy constructor");

	time = get_time();
	std::vector<int>		real3(real2);
	real_time = get_time() - time;

	time = get_time();
	PRE::vector<int> mine3(mine);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), mine3.begin())) {
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Operator =");

	time = get_time();
	std::vector<int>		real4 = real3;
	real_time = get_time() - time;

	time = get_time();
	PRE::vector<int> mine4 = mine;
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), mine4.begin())) {
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void vector_test_assign() {
	title("\e[95m-Assign-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Assign 1000 value");
	int i = rand() % 2147483647;

	long time = get_time();
	real.assign(1000,i);
	long real_time = get_time() - time;

	time = get_time();
	mine.assign(1000,i);
	long mine_time = get_time() - time;
	if (!ft::equal(real.begin(), real.end(), mine.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Assign 1000000 value");
	i = rand() % 2147483647;

	time = get_time();
	real.assign(1000000,i);
	real_time = get_time() - time;

	time = get_time();
	mine.assign(1000000,i);
	mine_time = get_time() - time;
	if (!ft::equal(real.begin(), real.end(), mine.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	std::vector<int>	real2;
	PRE::vector<int>		mine2;

	annonce("Assign range");

	time = get_time();
	real2.assign(real.begin(), real.end());
	real_time = get_time() - time;

	time = get_time();
	mine2.assign(mine.begin(), mine.end());
	mine_time = get_time() - time;
	if (!ft::equal(real2.begin(), real2.end(), mine2.begin())) {
		std::cout << "Real vector: " << real2.size() << std::endl;
		std::cout << "Mine vector: " << mine2.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_at() {
	title("\e[95m-At-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	for (int i = 0; i < 10; i++) {
		real.push_back(i);
		mine.push_back(i);
	}
	if (!ft::equal(real.begin(), real.end(), mine.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}

	annonce("At in range");
	try {
		for (int k = 0; k < 3; k++) {
			int i = rand() % 10;
			if (real.at(i) != mine.at(i)) {
				std::cout << "Real vector: " << real.at(i) << std::endl;
				std::cout << "Mine vector: " << mine.at(i) << std::endl;
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

void	vector_test_brackets() {
	title("\e[95m-Brackets []-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	for (int i = 0; i < 10; i++) {
		real.push_back(i);
		mine.push_back(i);
	}
	if (!ft::equal(real.begin(), real.end(), mine.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}

	annonce("Brackets in range");
	for (int k = 0; k < 3; k++) {
		int i = rand() % 10;
		if (real[i] != mine[i]) {
			std::cout << "Real vector: " << real[i] << std::endl;
			std::cout << "Mine vector: " << mine[i] << std::endl;
			return Test_failure();
		}
	}
	Test_success();

	// Portable programs should never call this function with an argument n that is out of range, since this causes undefined behavior

	// annonce("Brackets negative");
	// if (real[-1] != mine[-1]) {
	// 	std::cout << "Real vector: " << real[-1] << std::endl;
	// 	std::cout << "Mine vector: " << mine[-1] << std::endl;
	// 	return Test_failure();
	// }
	// Test_success();

	// annonce("Brackets out of range");
	// if (real[10] != mine[10]) {
	// 	std::cout << "Real vector: " << real[10] << std::endl;
	// 	std::cout << "Mine vector: " << mine[10] << std::endl;
	// 	return Test_failure();
	// }
	// Test_success();
};

void	vector_test_front() {
	title("\e[95m-Front-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;
	int n = rand() % 2147483647;

	annonce("Front with one element");
	real.push_back(n);
	mine.push_back(n);
	if (real.front() != mine.front()) {
		std::cout << "Real vector: " << real.front() << std::endl;
		std::cout << "Mine vector: " << mine.front() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Front with 11 elements");
	for (int i = 0; i < 10; i++) {
		n = rand() % 2147483647;
		real.push_back(n);
		mine.push_back(n);
	}
	if (real.front() != mine.front()) {
		std::cout << "Real vector: " << real.front() << std::endl;
		std::cout << "Mine vector: " << mine.front() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_back() {
	title("\e[95m-Back-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;
	int n = rand() % 2147483647;

	annonce("Back with one element");
	real.push_back(n);
	mine.push_back(n);
	if (real.back() != mine.back()) {
		std::cout << "Real vector: " << real.back() << std::endl;
		std::cout << "Mine vector: " << mine.back() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Back with 11 elements");
	for (int i = 0; i < 10; i++) {
		n = rand() % 2147483647;
		real.push_back(n);
		mine.push_back(n);
	}
	if (real.back() != mine.back()) {
		std::cout << "Real vector: " << real.back() << std::endl;
		std::cout << "Mine vector: " << mine.back() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_data() {
	title("\e[95m-Data-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;
	int n = rand() % 2147483647;

	annonce("Data with one element");
	real.push_back(n);
	mine.push_back(n);
	if (*(real.data()) != *(mine.data())) {
		std::cout << "Real vector: " << real.data() << std::endl;
		std::cout << "Mine vector: " << mine.data() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Data with 11 elements");
	for (int i = 0; i < 10; i++) {
		n = rand() % 2147483647;
		real.push_back(n);
		mine.push_back(n);
	}
	if (*(real.data()) != *(mine.data())) {
		std::cout << "Real vector: " << real.data() << std::endl;
		std::cout << "Mine vector: " << mine.data() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_empty() {
	title("\e[95m-Empty-\e[39m");

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Empty with no element");
	if (real.empty() != mine.empty()) {
		std::cout << "Real vector: " << real.empty() << std::endl;
		std::cout << "Mine vector: " << mine.empty() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Empty with one element");
	real.push_back(1);
	mine.push_back(1);
	if (real.empty() != mine.empty()) {
		std::cout << "Real vector: " << real.empty() << std::endl;
		std::cout << "Mine vector: " << mine.empty() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_size() {
	title("\e[95m-Size-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Size with no element");
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Size with one element");
	real.push_back(1);
	mine.push_back(1);
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Size beetwen 1 and 1000");
	int n = (rand() % 1000) + 1;
	for (int i = 0; i < n; i++) {
		real.push_back(1);
		mine.push_back(1);
	}
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_max_size() {
	title("\e[95m-Max_size-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Max_size");
	if (real.max_size() != mine.max_size()) {
		std::cout << "Real vector: " << real.max_size() << std::endl;
		std::cout << "Mine vector: " << mine.max_size() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_reserve() {
	title("\e[95m-Reserve-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Reserve with 0");

	long time = get_time();
	real.reserve(0);
	long real_time = get_time() - time;

	time = get_time();
	mine.reserve(0);
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Reserve with 1");

	time = get_time();
	real.reserve(1);
	real_time = get_time() - time;

	time = get_time();
	mine.reserve(1);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Reserve with 1000");

	time = get_time();
	real.reserve(1000);
	real_time = get_time() - time;

	time = get_time();
	mine.reserve(1000);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Reserve with 1000000");

	time = get_time();
	real.reserve(1000000);
	real_time = get_time() - time;

	time = get_time();
	mine.reserve(1000000);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_capacity() {
	title("\e[95m-Capacity-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Capacity with 0");
	if (real.capacity() != mine.capacity()) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Capacity with 1");
	real.push_back(1);
	mine.push_back(1);
	if (real.capacity() != mine.capacity()) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Capacity with 1000");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}
	if (real.capacity() != mine.capacity()) {
		std::cout << "Real vector: " << real.capacity() << std::endl;
		std::cout << "Mine vector: " << mine.capacity() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_test_clear() {
	title("\e[95m-Clear-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Clear with 0");

	long time = get_time();
	real.clear();
	long real_time = get_time() - time;

	time = get_time();
	mine.clear();
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Clear with 1");

	real.push_back(1);
	mine.push_back(1);

	time = get_time();
	real.clear();
	real_time = get_time() - time;

	time = get_time();
	mine.clear();
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Clear with 1000");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}

	time = get_time();
	real.clear();
	real_time = get_time() - time;

	time = get_time();
	mine.clear();
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_insert() {
	title("\e[95m-Insert-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Insert 2 element at begin");

	long time = get_time();
	real.insert(real.begin(), 2);
	long real_time = get_time() - time;

	time = get_time();
	mine.insert(mine.begin(), 2);
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Insert 1 element");

	time = get_time();
	real.insert(real.begin() + 1, 1);
	real_time = get_time() - time;

	time = get_time();
	mine.insert(mine.begin() + 1, 1);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Insert 100 elements at the begin");

	time = get_time();
	real.insert(real.begin(), 100, 1);
	real_time = get_time() - time;

	time = get_time();
	mine.insert(mine.begin(), 100, 1);
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Insert 4 elements");

	time = get_time();
	real.insert(real.end() - 42, 4, 1);
	real_time = get_time() - time;

	time = get_time();
	mine.insert(mine.end() - 42, 4, 1);
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	std::vector<int>	real2;
	PRE::vector<int>		mine2;

	annonce("Insert with range at begin");

	time = get_time();
	real2.insert(real2.begin(), real.begin(), real.end());
	real_time = get_time() - time;

	time = get_time();
	mine2.insert(mine2.begin(), mine.begin(), mine.end());
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real2.size() << std::endl;
		std::cout << "Mine vector: " << mine2.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Insert with range");

	time = get_time();
	real2.insert(real2.begin() + 42, real.begin(), real.end());
	real_time = get_time() - time;

	time = get_time();
	mine2.insert(mine2.begin() + 42, mine.begin(), mine.end());
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real2.size() << std::endl;
		std::cout << "Mine vector: " << mine2.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_erase() {
	title("\e[95m-Erase-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Erase 1 element from the begin");
	real.push_back(1);
	mine.push_back(1);

	long time = get_time();
	real.erase(real.begin());
	long real_time = get_time() - time;

	time = get_time();
	mine.erase(mine.begin());
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Erase 1 element");
	for (int i = 0; i < 100; i++) {
		real.push_back(1);
		mine.push_back(1);
	}

	time = get_time();
	real.erase(real.end() - 42);
	real_time = get_time() - time;

	time = get_time();
	mine.erase(mine.end() - 42);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Erase 15 elements with range");

	time = get_time();
	real.erase(real.begin() + 42, real.begin() + 57);
	real_time = get_time() - time;

	time = get_time();
	mine.erase(mine.begin() + 42, mine.begin() + 57);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Erase all with range");

	time = get_time();
	real.erase(real.begin(), real.end());
	real_time = get_time() - time;

	time = get_time();
	mine.erase(mine.begin(), mine.end());
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_push_back() {
	title("\e[95m-Push_back-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Push 1 element");

	long time = get_time();
	real.push_back(1);
	long real_time = get_time() - time;

	time = get_time();
	mine.push_back(1);
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.back() << std::endl;
		std::cout << "Mine vector: " << mine.back() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Push 1000 elements");

	time = get_time();
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
	}
	real_time = get_time() - time;

	time = get_time();
	for (int i = 0; i < 1000; i++) {
		mine.push_back(1);
	}
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.back() << std::endl;
		std::cout << "Mine vector: " << mine.back() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_pop_back() {
	title("\e[95m-Pop_back-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Pop 1 element");
	real.push_back(1);
	mine.push_back(1);

	long time = get_time();
	real.pop_back();
	long real_time = get_time() - time;

	time = get_time();
	mine.pop_back();
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.back() << std::endl;
		std::cout << "Mine vector: " << mine.back() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Pop 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}

	time = get_time();
	for (int i = 0; i < 1000; i++) {
		real.pop_back();
	}
	real_time = get_time() - time;

	time = get_time();
	for (int i = 0; i < 1000; i++) {
		mine.pop_back();
	}
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.back() << std::endl;
		std::cout << "Mine vector: " << mine.back() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_resize() {
	title("\e[95m-Resize-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Resize from 0 to 1 element");

	long time = get_time();
	real.resize(1);
	long real_time = get_time() - time;

	time = get_time();
	mine.resize(1);
	long mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Resize from 1 to 1000 elements");

	time = get_time();
	real.resize(1000);
	real_time = get_time() - time;

	time = get_time();
	mine.resize(1000);
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Resize 1000 to 50 elements");

	time = get_time();
	real.resize(50);
	real_time = get_time() - time;

	time = get_time();
	mine.resize(50);
	mine_time = get_time() - time;
	if (real.size() != mine.size()) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void	vector_test_swap() {
	title("\e[95m-Swap-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Swap 1 element");
	real.push_back(1);
	mine.push_back(1);

	long time = get_time();
	real.swap(real);
	long real_time = get_time() - time;

	time = get_time();
	mine.swap(mine);
	long mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);

	annonce("Swap 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}

	time = get_time();
	real.swap(real);
	real_time = get_time() - time;

	time = get_time();
	mine.swap(mine);
	mine_time = get_time() - time;
	if (!ft::equal(mine.begin(), mine.end(), real.begin())) {
		std::cout << "Real vector: " << real.size() << std::endl;
		std::cout << "Mine vector: " << mine.size() << std::endl;
		return Test_failure();
	}
	Test_performance(real_time, mine_time);
};

void launch_vector() {
	title("\e[93m Functions: \e[39m");
	vector_test_constructors();
	vector_test_assign();
	vector_test_at();
	vector_test_brackets();
	vector_test_front();
	vector_test_back();
	vector_test_data();
	vector_test_empty();
	vector_test_size();
	vector_test_max_size();
	vector_test_reserve();
	vector_test_capacity();
	vector_test_clear();
	vector_test_insert();
	vector_test_erase();
	vector_test_push_back();
	vector_test_pop_back();
	vector_test_resize();
	vector_test_swap();
};



	/*******************************/
	/*****      ITERATORS      *****/
	/*******************************/



void	vector_iterators_test_begin() {
	title("\e[95m-Begin-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Begin 1 element");
	real.push_back(1);
	mine.push_back(1);
	if (*mine.begin() != *real.begin()) {
		std::cout << "Real vector: " << *real.begin() << std::endl;
		std::cout << "Mine vector: " << *mine.begin() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Begin 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}
	if (*mine.begin() != *real.begin()) {
		std::cout << "Real vector: " << *real.begin() << std::endl;
		std::cout << "Mine vector: " << *mine.begin() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_iterators_test_end() {
	title("\e[95m-End-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("End 1 element");
	real.push_back(1);
	mine.push_back(1);
	if (*(mine.end() - 1) != *(real.end() - 1)) {
		std::cout << "Real vector: " << *real.end() << std::endl;
		std::cout << "Mine vector: " << *mine.end() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("End 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}
	if (*(mine.end() - 1) != *(real.end() - 1)) {
		std::cout << "Real vector: " << *real.end() << std::endl;
		std::cout << "Mine vector: " << *mine.end() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_iterators_test_rbegin() {
	title("\e[95m-Rbegin-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Rbegin 1 element");
	real.push_back(1);
	mine.push_back(1);
	if (*mine.rbegin() != *real.rbegin()) {
		std::cout << "Real vector: " << *real.rbegin() << std::endl;
		std::cout << "Mine vector: " << *mine.rbegin() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Rbegin 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}
	if (*mine.rbegin() != *real.rbegin()) {
		std::cout << "Real vector: " << *real.rbegin() << std::endl;
		std::cout << "Mine vector: " << *mine.rbegin() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void	vector_iterators_test_rend() {
	title("\e[95m-Rend-\e[39m");
	srand(time(NULL));

	std::vector<int>	real;
	PRE::vector<int>		mine;

	annonce("Rend 1 element");
	real.push_back(1);
	mine.push_back(1);
	if (*(mine.rend() - 1) != *(real.rend() - 1)) {
		std::cout << "Real vector: " << *real.rend() << std::endl;
		std::cout << "Mine vector: " << *mine.rend() << std::endl;
		return Test_failure();
	}
	Test_success();

	annonce("Rend 1000 elements");
	for (int i = 0; i < 1000; i++) {
		real.push_back(1);
		mine.push_back(1);
	}
	if (*(mine.rend() - 1) != *(real.rend() - 1)) {
		std::cout << "Real vector: " << *real.rend() << std::endl;
		std::cout << "Mine vector: " << *mine.rend() << std::endl;
		return Test_failure();
	}
	Test_success();
};

void 	launch_vector_iterators() {
	title("\e[93m Iterators: \e[39m");
	vector_iterators_test_begin();
	vector_iterators_test_end();
	vector_iterators_test_rbegin();
	vector_iterators_test_rend();
};
