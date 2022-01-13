#!/bin/bash

#make clean && make sincos   # Rebuild the sincos executable.
#./sincos > /tmp/sin.dat     # Place the data points into a file.


rm -f /tmp/max.dat
rm -f /tmp/length.dat

for n in {2...10000}; do

	echo -n $n >> /tmp/max.dat
	echo " " >> /tmp/max.dat 
	./collatz -n $n | sort -n | tail -n 1 >> /tmp/max.dat	

        ./collatz -n $n | wc -l >> /tmp/length.dat

done

# This is the heredoc that is sent to gnuplot.

gnuplot <<END
    set terminal pdf
    set output "max.pdf"
    set title "Maximum Collatz Sequence Value"
    set xlabel "n"
    set ylabel "value"
    set yrange [0:10000]
    set xrange [0:10000]
    plot "/tmp/max.dat" with dots title ""
END


gnuplot <<END
    set terminal pdf
    set output "length.pdf"
    set title "Sequence Lengths"
    set xlabel "x"
    set ylabel "y"
    plot "/tmp/length.dat" with dots title ""
END


