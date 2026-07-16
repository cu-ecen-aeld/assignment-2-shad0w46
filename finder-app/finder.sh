#!/bin/bash

# Check number of arguments
if [ $# -ne 2 ]; then
    echo "Error: Two arguments required."
    echo "Usage: $0 <filesdir> <searchstr>"
    exit 1
fi

filesdir=$1
searchstr=$2

# Check if directory exists
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a valid directory."
    exit 1
fi

# Count number of files (recursive)
file_count=$(find "$filesdir" -type f | wc -l)

# Count matching lines (recursive)
match_count=$(grep -r "$searchstr" "$filesdir" 2>/dev/null | wc -l)

# Print result
echo "The number of files are $file_count and the number of matching lines are $match_count"