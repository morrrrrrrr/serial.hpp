
#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <windows.h>
#include <thread>
#include <string>
#include <functional>

namespace serial {
    class SerialPort {
        
    public:
        #pragma region Constructors
        SerialPort(const std::string& port, int bRate) {

        }

        #pragma endregion

        #pragma region open / close
        void open() {

        }

        void close() {

        }
        #pragma endregion
    }; // class port
}; // namespace serial

#endif