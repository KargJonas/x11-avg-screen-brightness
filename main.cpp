#include <iostream>

#include "./averageColor.h"

/**
 * Compile with:
 * g++ -O2 -std=c++17 -Wall -Wextra -Werror -Wpedantic -pedantic-errors main.cpp -o get_avg_brightness $(pkg-config --cflags --libs x11)
 * if g++ does not work, use g++-7
*/

int main(int argc, char* argv[])
{
    if (argc != 6) {
        std::cerr << "Invalid number of arguments.\nExpected: <pos_x> <pos_y> <width> <height> <sample_density>" << std::endl;
        return 1;
    }

    const float n_samples = strtod(argv[5], nullptr);

    if (n_samples < 0 || n_samples > 1) {
        std::cerr << "Invalid argument parameter 5 (sample_density) should be a float from 0 to 1." << std::endl;
        return 1;
    }

    const uint x = strtol(argv[1], nullptr, 0),
        y = strtol(argv[2], nullptr, 0),
        width = strtol(argv[3], nullptr, 0),
        height = strtol(argv[4], nullptr, 0);

    uint* averageColor = getAverageColor(x, y, width, height, n_samples);
    uint brightness = (averageColor[0] + averageColor[1] + averageColor[2]) / 3;

    std::cout << brightness << std::endl;

    return 0;
}