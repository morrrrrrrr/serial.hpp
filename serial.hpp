
#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <windows.h>
#include <thread>
#include <string>
#include <sstream>
#include <stdexcept>
#include <functional>
#include <locale>
#include <codecvt>

#pragma region exceptions
class SerialException : public std::exception {
private:
    std::string errorMessage;

public:
    SerialException(const std::string& message) : errorMessage("Serial Error: " + message) {}

    // Override the what() function to provide a custom error message
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};
#pragma endregion

class SerialPort {
    HANDLE hSerial;
    std::stringstream read;
public:
    #pragma region Constructors
    SerialPort(const std::string& port, int bRate) {

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::wstring wPort = converter.from_bytes(port);

        const WCHAR* com = wPort.c_str();
        HANDLE hSerial = CreateFile(
            com,
            GENERIC_READ | GENERIC_WRITE,
            0,
            0,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            0
        );

        if (hSerial == INVALID_HANDLE_VALUE) {
            throw SerialException("Error opening serial port.");
        }

        DCB dcbSerialParams = { 0 };
        dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

        if (!GetCommState(hSerial, &dcbSerialParams)) {
            CloseHandle(hSerial);
            throw SerialException("Error getting serial port state.");
        }

        dcbSerialParams.BaudRate = CBR_9600;  // Set to match Arduino baud rate
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity   = NOPARITY;

        if (!SetCommState(hSerial, &dcbSerialParams)) {
            CloseHandle(hSerial);
            throw SerialException("Error setting serial port state.");
        }

        //hSerial is now set up
    }
    #pragma endregion

    #pragma region open / close
    void open() {

    }

    void close() {

    }
    #pragma endregion
}; // class port

#endif