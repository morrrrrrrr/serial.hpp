
#include "serial.hpp"
#include <string>
#include <iostream>

const std::string PORT = "COM3";
const int BAUD_RATE = 9600;

int main(int argc, char** argv) {
    SerialPort port(PORT, BAUD_RATE);

    if (!port.open()) {
        // print error message:
        std::cerr << "Couldn't connect to port " << PORT << "\n";
        return -1;
    }

    port.writeString("Hello");

    std::string answer = port.readString(5);

    // print answer
    std::cout << answer << "\n";

    port.close();

    return 0;
}
