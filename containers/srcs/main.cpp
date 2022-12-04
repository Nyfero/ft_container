#include "../class/utils.hpp"

int main() {
	clock_t deb;
	clock_t end;

	std::cout << CHECK << std::endl;

	title("\e[96m*** VECTOR ***\e[39m");
	deb = clock();
	launch_vector();
	launch_vector_iterators();
	end = clock() - deb;
	std::cout << "vector timer: "<< end << std::endl;

	title("\e[96m*** STACK ***\e[39m");
	deb = clock();
	launch_stack();
	end = clock() - deb;
	std::cout << "stack timer: "<< end << std::endl;

	title("\e[96m*** MAP ***\e[39m");
	deb = clock();
	launch_map();
 	launch_map_iterators();
	end = clock() - deb;
	std::cout << "map timer: "<< end << std::endl;


	 return (0);
}
