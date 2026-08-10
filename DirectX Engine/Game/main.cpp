#include <DX3D/All.h>

int main() {

	try {
		dx3d::Game game{};

		game.run();
	}
	catch (std::runtime_error&) {
		return EXIT_FAILURE;
	}
	catch (std::exception&) {
		return EXIT_FAILURE;
	}
	catch (...) { // catches all exceptions
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}