#include "../class/utils.hpp"

int main() {
	title("\e[96m*** STACK ***\e[39m");
	launch_stack();

	title("\e[96m*** VECTOR ***\e[39m");
	launch_vector();
	launch_vector_iterators();

	title("\e[96m*** MAP ***\e[39m");
	launch_map();
	launch_map_iterators();

	return (0);
}
