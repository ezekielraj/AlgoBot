#!/bin/bash

# Get today's date (YYYY-MM-DD)
TODAY=$(date +"%Y-%m-%d")

DB="${TODAY}.db"

QUERY="SELECT * FROM stocks WHERE p_e > 20 and p_e < 30 AND week_change_per < -5;"

echo "Querying DB: $DB"
echo "Running: $QUERY"
echo "--------------------------------------"

sqlite3 -header -column "$DB" "$QUERY"
