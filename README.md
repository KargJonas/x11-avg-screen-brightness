# x11-avg-screen-brightness

A simple tool for finding the average screen brightness within an area of the screen.

## Usage
`get_avg_brightness` takes a snapshot of the screen and calculates the average color of the pixels within this snapshot. If a precise value is needed, `sample_density` can be set to `1`. This will cause all pixels within the snapshot to be used in the average. If more performance is desired and an approximation is enough, the value can be set to something like `0.02` such that only `2%` of all pixels are used for the average.

If run in a terminal, `get_avg_brightness` will return a single integer value for the brightness.

There is also a bash script (`decide_theme.sh`) to demonstrate a use case.

```
./get_avg_brightness <pos_x> <pos_y> <width> <height> <sample_density>
```
e.g.:
```
$ ./get_avg_brightness 600 300 500 500 0.02
58
```
---

| pos_x, pos_y            | width, height       | sample_density |
| ----------------------- | ------------------- | -------------- |
| Position of sample area | Size of sample area | Sample density |
| uint | uint | float |

## Compilation
```
g++ -O2 -std=c++17 -Wall -Wextra -Werror -Wpedantic -pedantic-errors main.cpp -o get_avg_brightness $(pkg-config --cflags --libs x11)
```