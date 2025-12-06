#!/data/data/com.termux/files/usr/bin/bash
set -euo pipefail

termux-wake-lock

cleanup() {
  termux-wake-unlock || true
}
trap cleanup EXIT SIGINT SIGTERM

while true; do
  OUTPUT=$(./SellInterface/SellInterface)
  if [ -n "$OUTPUT" ]; then
    termux-notification --title "Process output" --content "$OUTPUT"
  fi
done
