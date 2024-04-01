#!/bin/bash

# Compile the sorting programs
gcc -Wall -o qsort qsort.c -lpthread -std=gnu99
gcc -Wall -o hsort hsort.c
gcc -Wall -o isort isort.c -lpthread

# Set the number of elements
NUM_ELEMENTS=(10000 50000 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000 2000000 5000000 10000000 100000000)

# Output files for timing data
ISORT_OUTPUT="isort_timing_data.txt"
HSORT_OUTPUT="hsort_timing_data.txt"
QSORT_OUTPUT="qsort_timing_data.txt"
COMBINED_OUTPUT="sorting_time_plot_combined.png"
COMBINED_LOG_OUTPUT="sorting_time_log_plot_combined.png"

# Function to run sorting program with given number of elements and record timing data
run_sorting() {
    local sorting_program=$1
    local num_elements=$2
    local output_file=$3
    local result=$(./$sorting_program -n $num_elements -t | tail -n 1)
    echo "$num_elements $result" >> $output_file
}

# Run sorting programs for different number of elements and record timing data
echo "Running sorting programs..."
echo "Number of elements Time (seconds)" > $ISORT_OUTPUT
echo "Number of elements Time (seconds)" > $HSORT_OUTPUT
echo "Number of elements Time (seconds)" > $QSORT_OUTPUT

for element in "${NUM_ELEMENTS[@]}"; do
    run_sorting "isort" $element $ISORT_OUTPUT
    run_sorting "hsort" $element $HSORT_OUTPUT
    run_sorting "qsort" $element $QSORT_OUTPUT
done

# Plotting with gnuplot
echo "Plotting with gnuplot..."
gnuplot <<- EOF
    set terminal pngcairo enhanced font 'Verdana,12'
    set output '$COMBINED_OUTPUT'
    set title "Sorting Time Comparison"
    set xlabel "Number of Elements"
    set ylabel "Time (seconds)"
    set grid
    plot "$ISORT_OUTPUT" using 1:2 with lines title "isort", \
         "$HSORT_OUTPUT" using 1:2 with lines title "hsort", \
         "$QSORT_OUTPUT" using 1:2 with lines title "qsort"
EOF

echo "Plotting with gnuplot..."
gnuplot <<- EOF
    set terminal pngcairo enhanced font 'Verdana,12'
    set output '$COMBINED_LOG_OUTPUT'
    set title "Sorting Time Comparison (Log Scale)"
    set xlabel "Number of Elements"
    set ylabel "Time (seconds)"
    set grid
    set logscale xy
    plot "$ISORT_OUTPUT" using 1:2 with lines title "isort", \
         "$HSORT_OUTPUT" using 1:2 with lines title "hsort", \
         "$QSORT_OUTPUT" using 1:2 with lines title "qsort"
EOF

echo "Plot saved as $COMBINED_OUTPUT"
