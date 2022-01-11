#!/bin/bash

#make clean && make sincos   # Rebuild the sincos executable.
#./sincos > /tmp/sin.dat     # Place the data points into a file.


rm -f /tmp/max.dat

for n in {1..1000}; do
       ./collatz | sort -nr | head -n 1 >> /tmp/max.dat	
done

# This is the heredoc that is sent to gnuplot.

gnuplot <<END
    set terminal pdf
    set output "max.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    plot "/tmp/max.dat" with points title ""
END

