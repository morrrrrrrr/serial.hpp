
#include "serial.hpp"
#include <string>
#include <iostream>

const std::string PORT = "COM3";
const int BAUD_RATE = 9600;

// standart use test
int test1(SerialPort& port) {
    std::cout << "Opening port (" << PORT << ")...\n";
    if (!port.open()) {
        // print error message:
        std::cerr << "Couldn't connect to port " << PORT << "\n";
        return -1;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Writing \"Hello\" to port\n";
    port.writeString("Hello World");

    std::cout << "Waiting for full answer to return...\n";
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Reading in Answer...\n";
    std::string answer = port.readString(strlen("Hello World"));

    std::cout << "Printing Answer...\n";
    std::cout << answer << "\n";

    std::cout << "Closing Port...\n";
    port.close();

    std::cout << "Done with Test1.\n";
    return 0;
}

// opening and closing the port multiple times
int test2() {
    SerialPort port(PORT, BAUD_RATE);

    for (int i = 0; i < 4; i++) {
        std::cout << "Opening Port in loop " << i << "...\n";
        if (!port.open()) {
            std::cerr << "Failed to open Port in loop " << i << "\n";
            return -1;
        }

        std::cout << "Closing Port in loop " << i << "...\n";
        port.close();

        // little sleep timer to not damage hardwares
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Done with Test2.\n";
    return 0;
}

static SerialPort* pPort = nullptr;

void closepPort() {
    if (pPort != nullptr)
        pPort->close();
}

int main(int argc, char** argv) {
    SerialPort port(PORT, BAUD_RATE);
    pPort = &port;
    std::atexit(closepPort);

    test1(port);

    //test2();
}
