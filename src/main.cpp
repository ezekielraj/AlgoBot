#include <iostream>
#include <cstdlib>
#include <unistd.h>


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << CHILD_PATH << std::endl;


    std::cout << "Launching Stocks program..." << std::endl;
    // Use fork + exec to start child process (Linux/macOS only)
    pid_t pid = fork();
    if (pid == 0) {
    // Child
        execl(CHILD_PATH, "", (char*)nullptr);
        std::cerr << "exec failed" << std::endl;
        exit(1);
    } else if (pid > 0) {
        std::cout << "Child process started with PID: " << pid << std::endl;
    } else {
        std::cerr << "fork failed" << std::endl;
    }

    return 0;
}