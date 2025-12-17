clang++ -std=c++17 \
    *.cpp \
    ../core/*.cpp \
    -Iinclude \
    -I../core/include \
    -I../engine/include \
    -lcurl \
    -lsqlite3 \
    -o BInterface
