#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h> //Solo windows dah XD
using namespace std;

#define BLACK   "\x1B[30m"		//Colores
#define RED     "\x1b[31m"

//se asigna un n�mero a cada palabra. El programa lee del teclado numeros en tipo char, en este caso la tecla arriba se lee como 72, mismo caso con el resto de teclas.
#define ARRIBA 72
#define ABAJO 80
#define DERECHA 77
#define IZQUIERDA 75
#define ESC 27

int opcion;     //Variables globales
bool valor = true;
HANDLE serialPort; //Variable del puerto en serie, se puede colocar otros nombres pero habria que modificar otras cosas en el c�digo.

//Obtener la informaci�n del buffer del teclado.
int Tecla (){
    // usando la funci�n getch() se obtiene el valor en char de la �ltima tecla presionada en el teclado.
    int T;
    while(true){
        if(kbhit()){
            char key = getch();
            if (key == ARRIBA or key == 'w'){T = 1; break;}
            if (key == ABAJO or key == 's'){T = 2; break;}
            if (key == DERECHA or key == 'd'){T = 3; break;}
            if (key == IZQUIERDA or key == 'a'){T = 4; break;}
            if (key == ESC){T = 5; break;}
        }
    }
    return T;
}

//Todo lo relacionado para abrir y configurar los parametros del puerto en serie.
void Configurar_Puerto(){
    serialPort = CreateFile("COM8",                             //Aqu� se asigna el puerto al que esta conectado el microcontrolador.
                            GENERIC_READ | GENERIC_WRITE, 0, 0, //Se asigna la lectura y escritura para el puerto en cuesti�n.
                            OPEN_EXISTING,                      //...
                            FILE_ATTRIBUTE_NORMAL, 0
                            );

    //Se comprueba si se puede abrir el puerto, de lo contrario envia error.
    if(serialPort == INVALID_HANDLE_VALUE){
        cout << "�ERROR! , no se pudo abrir el puerto. " << endl;
        system("pause");
        exit(1);
    }

    // Se crea una nueva variable para modificar los parametros del puerto en cuestion.
    DCB serialParams = {0};
    serialParams.DCBlength = sizeof(serialParams);

    //Se comprueba si es posible abrir los parametros para el puerto en serie, de lo contrario, se cierra el puerto y envia error.
    if (!GetCommState(serialPort, &serialParams)){
        cout << "�ERROR! , no se pudo obtener la configuraci�n del puerto serie. " << endl;
        system("pause");
        CloseHandle(serialPort);
        exit(1);
    }

    //Establecer la cantidad de baudios, el ancho de bits de entrada que puede recibir, el bit de parada y la paridad.
    serialParams.BaudRate = CBR_9600;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;

    //Comprobar si hay problemas para configurar el puerto en serie.
    if (!SetCommState(serialPort, &serialParams)){
        cout << "�ERROR! , problemas al configurar el puerto serie. " << endl;
        system("pause");
        CloseHandle(serialPort);
        exit(1);
    }
}

//Escribir y enviar informaci�n al dispositivo conectado atraves del puerto en serie.
void Escribir_Puerto(const char* x){
    DWORD escribir;
    if (!WriteFile(serialPort, x, strlen(x), &escribir, NULL)){
        cout << "ERROR al escribir en el puerto serie" << endl;
        system("pause");
        CloseHandle(serialPort);
        exit(1);
    }
}


int main(){
    system("Color F0");

    Configurar_Puerto();

	while(valor){

        opcion = Tecla();

        switch (opcion){
        case 1:
            system("cls");
            Escribir_Puerto("1");
            system("cls");
            break;
        case 2:
            system("cls");
            Escribir_Puerto("0");
            break;
        case 3:
            system("cls");
            Escribir_Puerto("2");
            break;
        case 4:
            system("cls");
            Escribir_Puerto("3");
            break;
        case 5:
            valor = false;
            break;
        }
	}
	CloseHandle(serialPort);
	return 0;
}