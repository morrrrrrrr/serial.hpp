# serial.hpp - README

C++ Windows Serial Port Header-Only Library

## Overview

The C++ Windows Serial Port Header-Only Library provides a convenient and encapsulated solution for working with serial ports in Windows environments. It abstracts the complexities of the WinApi, offering a clean interface for reading and writing operations. The library is designed to operate seamlessly with C++17 and has been tested on Windows 10.

## Table of Contents

 - [Features](#features)
 - [Usage](#usage)
 - [Examples](#examples)
 - [Building](#building)
 - [Lisence](#license)
 - [Contribution](#contribution)

## Features

### Opening and Closing the SerialPort

```cpp
bool SerialPort::open()
void SerialPort::close()
```

### Checking if SerialPort is open

```cpp
bool SerialPort::isOpen()
```

### Getting the size of the input read buffer 
similar to Arduino's Serial.available()

```cpp
std::size_t SerialPort::available()
```

Reading and Writing from and to SerialPort using

 - read and write Functions
 - stream operators _(*<<* | *>>*)_

---
### Write Functions:
```cpp
void SerialPort::writeString(const std::string& str)
SerialPort& operator<<(SerialPort& port, const std::string& str)
```
---
### Read Functions:

#### Reading Char
```cpp
char SerialPort::readChar()
char& operator>>(SerialPort& port, char& c)
```

#### Reading String

```cpp
std::string SerialPort::readString()
std::string SerialPort::readString(int length)
std::string& operator>>(SerialPort& port, std::string& str)
```

when defining the length of a string to read in, the current thread waits until the required length is met, then the string is returned.

## Usage

1. **Include Header File**: Add the "serial.hpp" header file to your C++ project.

    ```cpp
    #include "serial.hpp"
    ```

2. **Instantiate SerialPort Object**: Create a `SerialPort` object by specifying the port name and baud rate.

    ```cpp
    SerialPort mySerialPort("COM1", 9600);
    ```

3. **Open and Close Port**: Utilize the `open()` and `close()` methods to establish and terminate the serial port connection.

    ```cpp
    mySerialPort.open();
    // Perform operations...
    mySerialPort.close();
    ```

4. **Read and Write Data**: Use the `readChar()` / `readString()` and `writeString()` methods to perform data communication.

    ```cpp
    std::string str = "Hello, Serial!";
    mySerialPort.writeString(str);
    
    // all commands are for example 3 chars long
    std::string command = mySerialPort.readString(3);
    ```

## Examples

```cpp
#include "serial.hpp"

int main() {
    SerialPort mySerialPort("COM3", 9600);

    if (mySerialPort.open()) {
        // Perform operations...

        mySerialPort.close();
    }

    return 0;
}
```
---
from [tests](test.cpp):
```cpp
SerialPort port(PORT, BAUD_RATE);

std::cout << "Opening port (" << PORT << ")...\n";
if (!port.open()) {
    // print error message:
    std::cerr << "Couldn't connect to port " << PORT << "\n";
    return -1;
}

std::cout << "Is port Open? " << port.isOpen() << "\n";

std::cout << "Writing \"Hello\" to port\n";
port.writeString("Hello");

std::cout << "Waiting for full answer to return...\n";
std::this_thread::sleep_for(std::chrono::milliseconds(500));

std::cout << "Reading in Answer...\n";
std::string answer;
port >> answer;

std::cout << "Printing Answer...\n";
std::cout << answer << "\n";

std::cout << "Closing Port...\n";
port.close();

std::cout << "Done with Test1.\n";
return 0;
```

## Building



## License

This library is provided under the [MIT License](LICENSE), allowing for flexibility in usage and modification.

## Contribution

Contributions are welcome! If you encounter issues or have suggestions for improvements, please open an [issue](https://github.com/morrrrrrrr/serial.hpp/issues) or submit a [pull request](https://github.com/morrrrrrrr/serial.hpp/pulls).
