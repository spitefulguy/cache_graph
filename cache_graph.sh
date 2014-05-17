#!/bin/sh

./cache > output_linear;
./cache -r > output_random;
gnuplot "gnuplot.p";
epstopdf graph.ps;
xdg-open graph.pdf;
