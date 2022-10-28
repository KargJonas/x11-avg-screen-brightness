#include <iostream>
#include <X11/Xlib.h>
#include <cmath> // round()

// https://stackoverflow.com/a/59663458/1997354
inline __attribute__((always_inline)) \
unsigned long XGetPixel(XImage * ximage, const int & x, const int & y)
{
    return (*ximage->f.get_pixel)(ximage, x, y);
}

int main(int argc, char* argv[])
{
    if (argc != 6) {
        std::cerr << "Invalid number of arguments.\nExpected: <pos_x> <pos_y> <width> <height> <n_samples>" << std::endl;
        return 1;
    }

    const uint x = strtol(argv[1], nullptr, 0);
    const uint y = strtol(argv[2], nullptr, 0);
    const uint width = strtol(argv[3], nullptr, 0);
    const uint height = strtol(argv[4], nullptr, 0);
    const uint n_samples = strtol(argv[5], nullptr, 0);

    std::cout << x << std::endl;
    std::cout << x << std::endl;
    std::cout << width << std::endl;
    std::cout << height << std::endl;
    std::cout << n_samples << std::endl;

    Display * my_display = XOpenDisplay(NULL);
    XColor pixel_color;

    XImage * screen_image = XGetImage(
        my_display,
        XRootWindow(my_display, XDefaultScreen(my_display)),
        x, y,
        width, height,
        AllPlanes,
        XYPixmap
    );

    pixel_color.pixel = XGetPixel(screen_image, 0, 0);

    XFree(screen_image);

    XQueryColor(
        my_display,
        XDefaultColormap(my_display, XDefaultScreen(my_display)),
        & pixel_color
    );

    XCloseDisplay(my_display);

    unsigned short r = pixel_color.red;
    unsigned short g = pixel_color.green;
    unsigned short b = pixel_color.blue;

    // (r + g + b) / 3 / 256 <=> (r + g + b) / 768
    unsigned short brightness = (r + g + b) / 768;

    std::cout
        << "Brightness: " << brightness << std::endl;

}
