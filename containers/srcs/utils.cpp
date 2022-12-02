#include "../class/utils.hpp"

void	title(std::string str) {
	std::cout << std::endl << str << std::endl;
}

void	annonce(std::string msg) {
	std::cout << msg << std::endl;
}

void	Test_failure() {
	std::cout << "\e[31m[KO]\e[39m" << std::endl;
}

void	Test_performance(long real_time, long mine_time) {
	if (mine_time <= real_time * 20) {
		Test_success();
	}
	else {
		Test_timeout();
		std::cout << "Real time: " << real_time << std::endl;
		std::cout << "Mine time: " << mine_time << std::endl;
	}
}

void	Test_success() {
	std::cout << "\e[92m[OK]\e[39m" << std::endl;
}

void	Test_timeout() {
	std::cout << "\e[93m[TIMEOUT]\e[39m" << std::endl;
}

long	get_time() {
	struct timeval tv;
	long time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
