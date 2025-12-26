#!/bin/bash

TODAY=$(date +"%Y-%m-%d")
DB="${TODAY}.db"
BOUGHT_DB="bought.db"

QUERY="
ATTACH DATABASE '${BOUGHT_DB}' AS bought;

SELECT
    s.symbol as symbol,
    s.week_change_per as wcp,
    b.cnt AS bcount
FROM stocks s
JOIN (
    SELECT
        symbol,
        COUNT(*) AS cnt
    FROM bought.boughtStocks
    GROUP BY symbol
    HAVING COUNT(*) < 5
) b
ON s.symbol = b.symbol
WHERE s.p_e > 20
  AND s.p_e < 30
  AND s.week_change_per < -5;
"

echo "Querying DB: $DB"
echo "Using bought DB: $BOUGHT_DB"
echo "--------------------------------------"

sqlite3 -header -column "$DB" "$QUERY"
