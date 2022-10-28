#!/bin/bash

brightness=$(./get_avg_brightness 200 200 100 100 .02)

echo $brightness

if [[ $(($brightness)) -gt 128 ]]; then
    echo "Use light theme"
else
    echo "Use dark theme"
fi
