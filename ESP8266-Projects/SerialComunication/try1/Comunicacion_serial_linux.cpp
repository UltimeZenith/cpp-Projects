#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <cstdio>

using namespace std;


// Constants for keyboard input
#define ARRIBA  65
#define ABAJO   66
#define DERECHA 67
#define IZQUIERDA 68
#define ESC     27

int opcion;     // Global variables
bool valor = true;
int serialPort; // File descriptor for the serial port

// Function to set up the serial port
void Configurar_Puerto() {
    serialPort = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (serialPort == -1) {
        cerr << "Error: Unable to open the serial port." << endl;
        exit(1);
    }

    struct termios serialParams;
    tcgetattr(serialPort, &serialParams);

    // Set the baud rate, data bits, stop bits, and parity
    cfsetispeed(&serialParams, B9600);
    cfsetospeed(&serialParams, B9600);
    serialParams.c_cflag &= ~PARENB;
    serialParams.c_cflag &= ~CSTOPB;
    serialParams.c_cflag &= ~CSIZE;
    serialParams.c_cflag |= CS8;

    tcsetattr(serialPort, TCSANOW, &serialParams);
}

// Function to write and send data to the connected device through the serial port
void Escribir_Puerto(const char* x) {
    ssize_t bytes_written = write(serialPort, x, strlen(x));
    if (bytes_written == -1) {
        cerr << "Error writing to the serial port: " << strerror(errno) << endl;
        close(serialPort);
        exit(1);
    }
}

// Function to get a single character from the keyboard without waiting for Enter
int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int Tecla() {
    int T;
    while (true) {
        int key = getch();
        if (key == 27) {  // Escape key
            T = 5;
            break;
        } else if (key == 119 or key == ARRIBA) {  // 'w' key
            T = 1;
            break;
        } else if (key == 115 or key == ABAJO) {  // 's' key
            T = 2;
            break;
        } else if (key == 100 or key == DERECHA) {  // 'd' key
            T = 3;
            break;
        } else if (key == 97 or key == IZQUIERDA) {   // 'a' key
            T = 4;
            break;
        }
    }
    return T;
}

int main() {
    system("clear");  // Clear the terminal

    Configurar_Puerto();

    while (valor) {
        opcion = Tecla();

        switch (opcion) {
            case 1:
                system("clear");  // Clear the terminal
                Escribir_Puerto("1");
                break;
            case 2:
                system("clear");  // Clear the terminal
                Escribir_Puerto("0");
                break;
            case 3:
                system("clear");  // Clear the terminal
                Escribir_Puerto("2");
                break;
            case 4:
                system("clear");  // Clear the terminal
                Escribir_Puerto("3");
                break;
            case 5:
                valor = false;
                break;
        }
    }

    close(serialPort);
    return 0;
}
