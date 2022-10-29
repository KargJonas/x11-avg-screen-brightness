#include <X11/Xlib.h>
#include <cmath>
#include <iostream>

ushort* getAverageColor(uint x, uint y, uint width, uint height, float sample_density)
{
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

    const ulong total_n_pixels = width * height;
    const ulong step = floor(1 / sample_density);
    ulong r = 0, g = 0, b = 0;
    ulong n_pixels = 0;

    for (ulong i = 0; i < total_n_pixels; i += step) {
        pixel_color.pixel = 
            screen_image->f.get_pixel(
                screen_image, i % width, floor(i / width));

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

    const ulong factor = n_pixels * 255;

    r /= factor;
    g /= factor;
    b /= factor;

    XFree(screen_image);

    XCloseDisplay(display);

    static ushort avg_color[3] = {
        (ushort)r,
        (ushort)g,
        (ushort)b
    };

    return avg_color;
}
