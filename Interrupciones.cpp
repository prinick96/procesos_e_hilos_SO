#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctime>
#include <pthread.h>
#include <fstream>

using namespace std;

// Variables globales
bool CPURunning = true;

// CPU controlado por el hilo del CPU
void *CPU(void *args) {
   cout << "CPU en ejecución..." << endl;

   time_t current_time;
   struct tm * time_info;
   char timeString[9];

   // Escribir en el archivo
   ofstream fs("file/log.txt");
   while(CPURunning) {
        time(&current_time);
        time_info = localtime(&current_time); 
        strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
        cout << timeString << endl;
        fs << timeString << endl;
        sleep(5);
        while(!CPURunning);
   }
   
   fs.close();
   return NULL;
}

// Interruptor controlador por el hiloINT
void *Interruptor(void *arg) {
    cout << "Interruptor arrancado, el CPU se detendrá por 30 segundos.\n" << endl;
    CPURunning = false;
    sleep(30);
    CPURunning = true;

    return NULL;
}

// main
int main() {
    // Variable que controla el mensaje de inicio del driver
    int i = 0;
    // Definir hilos
    pthread_t hiloCPU;
    pthread_t hiloINT;

    // Crear hilo de CPU
    pthread_create(&hiloCPU,NULL,CPU,NULL);

    // Creamos otro proceso
    pid_t child = fork();
    switch((int) child) {
        case 0:
            // Ejecutar hilo de CPU
            pthread_join(hiloCPU,NULL);
        break;
        case -1:
            cout << "\nNo pudo iniciar el programa.";
        break;
        // El proceso principal actúa como DRIVER
        default:
            while(true) {
                if(0 == i) {
                    cout << "\nDriver encendido..." << endl;
                    cout << "\nPara encender la interrupción presionar enter." << endl;
                }
                // Esperar por el ENTER
                getchar(); 
                // Para evitar mostar el mensaje dos veces
                i++;
                // Crear hilo de Interrupción
                pthread_create(&hiloINT,NULL,Interruptor,NULL);
                // Arrancar el simulador de interrupciones
                pthread_join(hiloINT,NULL);
            }
        break;
    }

    return 1;
}