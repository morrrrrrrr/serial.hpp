
#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <windows.h>
#include <thread>
#include <chrono>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

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

class SerialPort {
    std::string _port;
    int _bRate;
    bool _isOpen, _pauseReadThread;

    std::stringstream _readBuffer;
    std::thread _readThread;

    DCB _dcbSerialParams;
    HANDLE _hSerial;
public:
    SerialPort(const std::string& port, int bRate = 9600) : _port(port), _bRate(bRate) {
        _dcbSerialParams = { 0 };
        _dcbSerialParams.DCBlength = sizeof(_dcbSerialParams);
        _dcbSerialParams.BaudRate = bRate;
        _dcbSerialParams.ByteSize = 8;
        _dcbSerialParams.StopBits = ONESTOPBIT;
        _dcbSerialParams.Parity   = NOPARITY;
        // Serial Parameters are set up

        _isOpen = false;
        _readBuffer.clear();
    }

    // Deconstructor: cleanup
    ~SerialPort() {
        if (_isOpen)
            close();
    }

    SerialPort(const SerialPort&) = delete;  // Deleted copy constructor
    SerialPort& operator=(const SerialPort&) = delete;  // Deleted copy assignment operator

    void readFunctionThread(bool& open, bool& pause) {
        while (open) {
            while (pause) { } // pause the thread while bigger read operations are happening
            DWORD pos;
            char c;
            
            if (ReadFile(_hSerial, &c, 1, &pos, nullptr)) {
                if (pos) { // read a byte
                    // this resets the stringstream, so that when the buffer was empty before, now you can read from it
                    std::string str = _readBuffer.str();
                    _readBuffer.clear();
                    _readBuffer.str(c + str);
                }
                else { // read empty
                    
                }
            }
        }
    }

    bool open() {
        try {
            if (_isOpen) {
                throw SerialException("Tried to open Port that was already open");
            }

            HANDLE hSerial = CreateFileA(
                _port.c_str(),
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
            if (!GetCommState(hSerial, &_dcbSerialParams)) {
                CloseHandle(hSerial);
                throw SerialException("Error getting serial port state.");
            }
            if (!SetCommState(hSerial, &_dcbSerialParams)) {
                CloseHandle(hSerial);
                throw SerialException("Error setting serial port state.");
            }

            _isOpen = true;
            _pauseReadThread = false;

            // initialize read thread
            _readBuffer.clear();

            _readThread = std::thread(readFunctionThread, this, std::ref(this->_isOpen), std::ref(this->_pauseReadThread));
        }
        catch (const std::exception& exception) {
            std::cerr << "Failed to open SerialPort: " << exception.what() << "\n";
            return false;
        }
        return true;
    }

    void close() {
        if (!_isOpen) {
            std::cerr << "Tried to close Port that was already closed\n";
            return;
        }

        _isOpen = false;
        
        _readThread.join();

        CloseHandle(_hSerial);
    }
    
    int available() {
        if (!_isOpen) {
            std::cerr << "Accessed SerialPort.available() while the port was closed\n";
            return 0;
        } 

        return _readBuffer.str().size();
    }

    char readChar() {
        if (available()) {
            char c;
            _readBuffer >> c;
            return c;
        }
        return '0';
    }

    std::string readString(int length) {
        while (available() < length) {
            // wait for the read buffer to fill up until it is at least `length` long
        }
        char c;
        int len;
        std::string output;
        while (c = readChar() && len < length) {
            len++;
            output = output + c;
        }
        return output;
    }

    void writeString(const std::string& str) {
        if (!_isOpen)
            return;
        
        DWORD pos;
        if (!WriteFile(_hSerial, str.c_str(), str.size(), &pos, nullptr)) {
            close();
            throw SerialException("Error writing to serial port.");
        }
    }

    bool isOpen() {
        return _isOpen;
    }

    const SerialPort& operator<<(const std::string& str) {
        writeString(str);
        return *this;
    }
}; // class port

#endif