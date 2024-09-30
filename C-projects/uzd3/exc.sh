#!/bin/bash

# Clear the results file if it exists, or create a new one
> results.txt

# Loop through the 12 C programs
for i in {1..12}; do
    # Compile each C file to an executable named queryN (e.g., query1, query2, ...)
    gcc -o query$i query$i.c
    
    # Check if compilation was successful
    if [ $? -eq 0 ]; then
        # Append a header line for the query number
        echo "QUERY$i" >> results.txt
        
        # Run the compiled program and append its output to results.txt
        ./query$i >> results.txt
        
        # Optional: Add a newline for readability between queries
        echo "" >> results.txt
    else
        echo "Compilation of query$i.c failed" >> results.txt
    fi
done

