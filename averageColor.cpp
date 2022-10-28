#include <iostream>
#include <X11/Xlib.h>
#include <cmath>

/**
 * Compile with:
 * g++ -O2 -std=c++17 -Wall -Wextra -Werror -Wpedantic -pedantic-errors averageColor.cpp -o averageColor $(pkg-config --cflags --libs x11)
 * if g++ does not work, use g++-7
*/

int main(int argc, char* argv[])
{
    if (argc != 6) {
        std::cerr << "Invalid number of arguments.\nExpected: <pos_x> <pos_y> <width> <height> <sample_rate>" << std::endl;
        return 1;
    }

    const float n_samples = strtod(argv[5], nullptr);

    if (n_samples < 0 || n_samples > 1) {
        std::cerr << "Invalid argument parameter 5 (sample_rate) should be a float from 0 to 1." << std::endl;
        return 1;
    }


    const uint x = strtol(argv[1], nullptr, 0),
        y = strtol(argv[2], nullptr, 0),
        width = strtol(argv[3], nullptr, 0),
        height = strtol(argv[4], nullptr, 0);


    XColor pixel_color;

    Display * display = XOpenDisplay(NULL);

    XImage * screen_image = XGetImage(
        display,
        XRootWindow(display, XDefaultScreen(display)),
        x, y,
        width, height,
        AllPlanes,
        XYPixmap
    );

    uint r = 0, g = 0, b = 0;

    const uint step = floor(1 / n_samples);
    uint n_pixels = 0;

    for (uint _y = 0; _y < height; _y++) {
        for (uint _x = 0; _x < width; _x += step) {
            pixel_color.pixel = 
                screen_image->f.get_pixel(screen_image, _x, _y);


            XQueryColor(
                display,
                XDefaultColormap(display, XDefaultScreen(display)),
                &pixel_color
            );

            r += pixel_color.red;
            g += pixel_color.green;
            b += pixel_color.blue;

            n_pixels++;
        }
    }

    const uint factor = n_pixels * 256;

    r /= factor;
    g /= factor;
    b /= factor;

    std::cout << "r: " << r << std::endl;
    std::cout << "g: " << g << std::endl;
    std::cout << "b: " << b << std::endl;

    XFree(screen_image);

    XCloseDisplay(display);
}
