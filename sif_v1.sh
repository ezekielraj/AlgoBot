#!/data/data/com.termux/files/usr/bin/bash
set -u  # KEEP undefined variable check but REMOVE -e to avoid exiting loop

termux-wake-lock

# Cleanup only for Ctrl+C
cleanup() {
  termux-wake-unlock || true
  echo "Unlocked due to Ctrl-C"
}

# Only trap SIGINT (Ctrl+C)
trap cleanup SIGINT

while true; do
  # Run the program and capture errors WITHOUT exiting script
  OUTPUT=$(./SellInterface/SellInterface 2>&1)  
  STATUS=$?   # capture exit code manually
  if [ $STATUS -eq 130 ]; then
    break
  fi
  if [ $STATUS -ne 0 ]; then
    echo "Error occurred (exit $STATUS). Restarting loop..."
    # DO NOT unlock, DO NOT exit. Continue loop.
    continue
  fi

  # Notify only when valid output exists
  if [ -n "$OUTPUT" ]; then
    termux-notification --title "Process output" --content "$OUTPUT"
  fi
done
