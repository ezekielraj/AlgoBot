while true; do
	OUTPUT=$(./SellInterface/SellInterface)
  if [ -n "$OUTPUT" ]; then
    termux-notification --title "Process output" --content "$OUTPUT"
  fi
done
