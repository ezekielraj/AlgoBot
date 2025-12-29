clang++ -std=c++17 \
    *.cpp \
    -Iinclude \
    -lcurl \
    -lsqlite3 \
    -luuid \
    -o OrderApp