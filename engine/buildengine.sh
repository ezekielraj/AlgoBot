clang++ -std=c++17 \
    *.cpp \
    ../core/*.cpp \
    -Iinclude \
    -I../core/include \
    -lcurl \
    -lsqlite3 \
    -o stocks
