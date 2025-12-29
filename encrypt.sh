#!/bin/bash

TARGET_DIR="Order"

read -s -p "Enter encryption password: " PASSWORD
echo
read -s -p "Confirm password: " CONFIRM
echo

if [[ ${#PASSWORD} -lt 8 ]]; then
    echo "Password must be at least 8 characters"
    exit 1
fi

if [[ "$PASSWORD" != "$CONFIRM" ]]; then
    echo "Password mismatch!"
    exit 1
fi

find "$TARGET_DIR" -type f \( -name "*.cpp" -o -name "*.h" \) | while read -r file; do
    tmp="${file}.enc"

    openssl enc -aes-256-cbc -pbkdf2 -salt \
        -in "$file" \
        -out "$tmp" \
        -pass pass:"$PASSWORD"

    if [[ $? -eq 0 ]]; then
        mv "$tmp" "$file"
        echo "Encrypted: $file"
    else
        echo "Failed: $file"
        rm -f "$tmp"
    fi
done
