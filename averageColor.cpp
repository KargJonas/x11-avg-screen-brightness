#include <iostream>
#include <X11/Xlib.h>
#include <cmath> // round()

// https://stackoverflow.com/a/59663458/1997354
inline __attribute__((always_inline)) \
unsigned long XGetPixel(XImage * ximage, const int & x, const int & y)
{
    return (*ximage->f.get_pixel)(ximage, x, y);
}

int main()
{
    Display * my_display = XOpenDisplay(NULL);
    XColor screen_pixel_color;

    XImage * screen_image = XGetImage(
        my_display,
        XRootWindow(my_display, XDefaultScreen(my_display)),
        800, 800,
        1, 1,
        AllPlanes,
        XYPixmap
    );

    screen_pixel_color.pixel = XGetPixel(screen_image, 0, 0);

    XFree(screen_image);

    XQueryColor(
        my_display,
        XDefaultColormap(my_display, XDefaultScreen(my_display)),
        & screen_pixel_color
    );

    XCloseDisplay(my_display);

    unsigned short r = screen_pixel_color.red;
    unsigned short g = screen_pixel_color.green;
    unsigned short b = screen_pixel_color.blue;

    // (r + g + b) / 3 / 256 <=> (r + g + b) / 768
    unsigned short brightness = (r + g + b) / 768;

    std::cout
        << "Brightness: " << brightness << std::endl;

}
