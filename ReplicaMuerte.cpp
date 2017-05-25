#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>

using namespace std;

class ReplicaMuerte {
    private:
        pid_t proceso_inicial;
        pid_t hijo_principal;

        bool sigueVivo(pid_t proceso) {
            return 0 == kill(proceso,0);
        }

        void cicloDeVida(pid_t padre) {
            // Esperar 5 segundos
            sleep(5);
            // Verificar vida del padre
            if(this->sigueVivo(padre)) {
                // Replicar al hijo y si es el hijo se repite el ciclo de vida
                //if(0 == fork() && this->sigueVivo(this->hijo_principal)) {
                if(0 == fork()) {
                    cout << "Nuevo hijo " << getpid() << " de padre " << getppid() << endl;
                    this->cicloDeVida(getppid());
                } 
                // Si es el padre, es porque sigue vivo 
                else {
                   cout << "Proceso padre " << getpid() << " sigue vivo." << endl;
                   // Volvemos a continuar con el ciclo de vida
                   this->cicloDeVida(padre);
                }
            }

            cout << "El proceso hijo " << getpid() << " se suicida." << endl;
            kill(getpid(),SIGKILL);
        }

    public:

        ReplicaMuerte() {
            this->proceso_inicial = fork();
            string option;

            switch((int) this->proceso_inicial) {
                // Hijo
                case 0:
                    this->hijo_principal = getpid();
                    this->cicloDeVida(getppid());
                break;
                // Error
                case -1:
                    cout << "No se pudo arrancar el programa." << endl;
                break;
                // Padre
                default:
                    cin >> option;
                    cout << "El primer hijo " << this->proceso_inicial << " muere y se detiene el padre." << endl;
                    // Matar al hijo
                    kill(this->proceso_inicial,SIGKILL);
                    // Detener al padre
                    kill(getpid(),SIGTERM);
                break;
            }
        }
};

// Main
int main() {
    system("clear");

    ReplicaMuerte *rep = new ReplicaMuerte();

    return 0;
}