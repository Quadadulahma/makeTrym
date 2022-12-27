#pragma once



struct Coord_Pos {
	double x;
	double y;

	void transform_to_openglcoord(const double& window_width, const double& window_height) {
		x = 2.0 * (x / window_width) - 1.0;
		y = 2.0 * (y / window_height) - 1.0;
	}
	void transform_to_screen_coord(const double& window_width, const double& window_height) {
		x = ((x + 1.0) / 2.0) * window_width;
		y = window_height - (((y + 1.0) / 2.0) * window_height);
	}
	void print() {
		std::cout << x << " " << y << std::endl;
	}
};