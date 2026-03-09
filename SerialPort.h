#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>

class SerialPort {
private:
    int serialFd;
    bool connected;

public:
    SerialPort();
    ~SerialPort();

    bool connectPort(const std::string& portName, int baudRate = 9600);
    void disconnectPort();
    bool isConnected() const;
    int readByte();

    bool sendData(const std::string& data);
};

#endif