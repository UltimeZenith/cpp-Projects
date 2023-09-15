
#include <stdio.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
	int data = 0;
	char opcion;
	bool valor = true;
	FILE *file;
	while(valor){

		file = fopen("/dev/ttyUSB0","w");  //Opening device file
		cout << "Ingresa un valor: " << endl;
		cin >> data;
		fprintf(file,"%d",data); //Writing to the file
		sleep(2);
		fclose(file);

		while(1){
			cout << "Desea continuar?" << endl;
			cin >> opcion;
			if (opcion == 78 or opcion == 110){
				valor = false;
				break;
			}else if (opcion == 83 or opcion == 115){
				break;
			}else{
				cout << "Caracter incorrecto" << endl;
			}
		}
	}
	return 0;
}
