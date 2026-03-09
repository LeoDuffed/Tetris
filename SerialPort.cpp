#include "SerialPort.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

using namespace std;

SerialPort::SerialPort() {
    serialFd = -1;
    cout<<"Serial port llamando"<<endl;
    connected = false;
}

SerialPort::~SerialPort() {
    disconnectPort();
}

bool SerialPort::connectPort(const std::string& portName, int baudRate) {
    serialFd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

    if (serialFd < 0) {
        cerr << "Error al abrir el puerto serial: " << portName << endl;
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(serialFd, &tty) != 0) {
        cerr << "Error en tcgetattr()" << endl;
        close(serialFd);
        serialFd = -1;
        return false;
    }

    speed_t speed;
    switch (baudRate) {
        case 9600:   speed = B9600; break;
        case 19200:  speed = B19200; break;
        case 38400:  speed = B38400; break;
        case 57600:  speed = B57600; break;
        case 115200: speed = B115200; break;
        default:
            cerr << "Baud rate no soportado, usando 9600" << endl;
            speed = B9600;
            break;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 5;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(serialFd, TCSANOW, &tty) != 0) {
        cerr << "Error en tcsetattr()" << endl;
        close(serialFd);
        serialFd = -1;
        return false;
    }

    connected = true;
    return true;
}

void SerialPort::disconnectPort() {
    if (serialFd >= 0) {
        close(serialFd);
        serialFd = -1;
    }
    connected = false;
}

bool SerialPort::isConnected() const {
    return connected;
}

bool SerialPort::sendData(const std::string& data) {
    if (!connected || serialFd < 0) {
        return false;
    }

    ssize_t bytesWritten = write(serialFd, data.c_str(), data.length());
    return (bytesWritten == (ssize_t)data.length());
}