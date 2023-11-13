# C++ Windows Serial Port Header-Only Library

## Overview

The C++ Windows Serial Port Header-Only Library provides a convenient and encapsulated solution for working with serial ports in Windows environments. It abstracts the complexities of the WinApi, offering a clean interface for reading and writing operations. The library is designed to operate seamlessly with C++17 and has been tested on Windows 10.

## Features

- **Simplified Interface**: The library wraps the WinApi in a C++-friendly manner, allowing users to work with serial ports more intuitively.

- **Multithreading Support**: Reading operations are handled on a separate thread, ensuring that the main program can execute without interruptions.

- **Tested Environment**: The library has been tested extensively on Windows 10, providing a reliable solution for serial port communication.

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
    
    // all commands are 3 chars long
    std::string command = mySerialPort.readString(3);
    ```

## Example

```cpp
#include "serial.hpp"

int main() {
    SerialPort mySerialPort("COM1", 9600);

    if (mySerialPort.open()) {
        // Perform operations...

        mySerialPort.close();
    }

    return 0;
}
```

## License

This library is provided under the [MIT License](LICENSE), allowing for flexibility in usage and modification.

## Contribution

Contributions are welcome! If you encounter issues or have suggestions for improvements, please open an [issue](https://github.com/morrrrrrrr/serial.hpp/issues) or submit a [pull request](https://github.com/morrrrrrrr/serial.hpp/pulls).

---

Feel free to customize this README to suit the specifics of your project and provide additional information as needed.