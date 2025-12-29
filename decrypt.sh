#!/bin/bash

TARGET_DIR="Order"

read -s -p "Enter decryption password: " PASSWORD
echo

if [[ ${#PASSWORD} -lt 8 ]]; then
    echo "Password must be at least 8 characters"
    exit 1
fi

find "$TARGET_DIR" -type f \( -name "*.cpp" -o -name "*.h" \) | while read -r file; do
    tmp="${file}.dec"

    openssl enc -d -aes-256-cbc -pbkdf2 \
        -in "$file" \
        -out "$tmp" \
        -pass pass:"$PASSWORD"

    if [[ $? -eq 0 ]]; then
        mv "$tmp" "$file"
        echo "Decrypted: $file"
    else
        echo "Failed: $file"
        rm -f "$tmp"
    fi
done
