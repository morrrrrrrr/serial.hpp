
#include "serial.hpp"

int main() {
    SerialPort port("COM7", 9600);

    if (port.open()) {
        
        // do something with the shitter
        
        port.close();
    }
}
