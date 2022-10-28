#include <X11/Xlib.h>
#include <cmath>

uint* getAverageColor(uint x, uint y, uint width, uint height, float sample_density)
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

    uint r = 0, g = 0, b = 0;

    const uint step = floor(1 / sample_density);
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

    XFree(screen_image);

    XCloseDisplay(display);

    static uint avg_color[3] = {
        r / factor,
        g / factor,
        b / factor
    };

    return avg_color;
}
