#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

using namespace std;

// Deinir funciones
int *crearArreglo();
void *promediarArreglo(void *arg);

// Tipo de dato pasado por parámetro a la función que manejan los hilos
typedef struct {
    int rango[2]; //Rango asignado
    int hilo_actual;
} hilo_info;

// Definr variables
int *arreglo = crearArreglo();
int promd_h1 = 0;
int promd_h2 = 0;
int promd_h3 = 0;
int promd_h4 = 0;

// main
int main() {
    // Definir hilos
    pthread_t hilo1;
    pthread_t hilo2;
    pthread_t hilo3;
    pthread_t hilo4;

    // Definir parámetros para la función que maneja el hilo 1
    hilo_info ph1;
    ph1.rango[0] = 0;
    ph1.rango[1] = 24;
    ph1.hilo_actual = 1;

    // Definir parámetros para la función que maneja el hilo 2
    hilo_info ph2;
    ph2.rango[0] = 25;
    ph2.rango[1] = 50;
    ph2.hilo_actual = 2;

    // Definir parámetros para la función que maneja el hilo 3
    hilo_info ph3;
    ph3.rango[0] = 51;
    ph3.rango[1] = 74;
    ph3.hilo_actual = 3;

    // Definir parámetros para la función que maneja el hilo 4
    hilo_info ph4;
    ph4.rango[0] = 75;
    ph4.rango[1] = 99;
    ph4.hilo_actual = 4;

    // Crear los hilos
    pthread_create(&hilo1,NULL,promediarArreglo,(void *)&ph1);
    pthread_create(&hilo2,NULL,promediarArreglo,(void *)&ph2);
    pthread_create(&hilo3,NULL,promediarArreglo,(void *)&ph3);
    pthread_create(&hilo4,NULL,promediarArreglo,(void *)&ph4);

    // Ejecutar los hilos
    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);
    pthread_join(hilo3,NULL);
    pthread_join(hilo4,NULL);

    // Mostrar promedios
    cout << "Promedio hilo 1: " << promd_h1 / 25 << endl;
    cout << "Promedio hilo 2: " << promd_h2 / 25 << endl;
    cout << "Promedio hilo 3: " << promd_h3 / 25 << endl;
    cout << "Promedio hilo 4: " << promd_h4 / 25 << endl;
    cout << "Promedio total: " << (promd_h1 + promd_h2 + promd_h3 + promd_h4 ) / 100 << endl;

    return 0;
}

// Crea un arreglo
int *crearArreglo() {
    int *arreglo = new int[100];
    srand(time(NULL));
    for(int i = 0; i < 100; i++) {
        arreglo[i] = rand() % 1001;
    }

    return arreglo;
}

// Crear promedio del rango asignado
void *promediarArreglo(void *arg) {
    hilo_info *p = (hilo_info *) arg;
    for(int i = p->rango[0]; i <= p->rango[1]; i++) {
        switch(p->hilo_actual) {
            case 1:
                promd_h1 += arreglo[i];
            break;
            case 2:
                promd_h2 += arreglo[i];
            break;
            case 3:
                promd_h3 += arreglo[i];
            break;
            case 4:
                promd_h4 += arreglo[i];
            break;
        }
    }
}