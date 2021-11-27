#include <iostream>
#include <ctime>

using namespace std;

const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;

const int TIEMPO_DELAY_LARGO = 10000000;
const int TIEMPO_DELAY_CORTO = 10000000;

typedef enum {nadie, tenista1, tenista2} t_tenista;
typedef enum {nada , quince, treinta, cuarenta, ventaja} t_puntos_juego;

string marcador(int puntuacion);
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int juegos1, int juegos2, t_tenista serivico_para);

void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista);

int main(){
    int n = 1;
    int c = 2;
    pintar_peloteo("ASD", "FNG", 1, 7, tenista1, 3);
    return 0;
}

string marcador(int puntuacion){
    string puntuacion_s;
    switch(puntuacion){
        case 0:
            puntuacion_s = "00";
            break;
        case 1:
            puntuacion_s = "15";
            break;
        case 2:
            puntuacion_s = "30";
            break;
        case 3:
            puntuacion_s = "40";
            break;
        default:
            puntuacion_s = "Ad";
            break;
    }
    return puntuacion_s;
}

void pintar_marcador(string nombre1, string nombre2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int juegos1, int juegos2, t_tenista serivico_para){

    string marcador1 = marcador(puntos1);
    string marcador2 = marcador(puntos2);

    cout << endl << "   " << nombre1 << "  " << juegos1 << " : " << marcador1 << " ";
    if(serivico_para == tenista1) cout << '*';

    cout << endl << "   " << nombre2 << "  " << juegos2 << " : " << marcador2 << " ";
    if(serivico_para == tenista2) cout << '*';
    cout << endl << endl;
}

void pintar_fila_fondo(int ancho_pista){
    cout << " ";
    for(int i = 0; i < ANCHO_PISTA; i++){
        cout << " -";
    }
    cout << endl;
}
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista){
    char bola;
    int extremo_pista;

    switch(tenista){
        case tenista1:
            extremo_pista = 1;
            break;
        case tenista2:
            extremo_pista = largo_pista;
            break;
        case nadie:
            extremo_pista = 0;
            break;
    }
        
    for(int i = 1; i <= largo_pista; i++){
        bola = 0 < pos_bola < ancho_pista+1 && i == extremo_pista ? bola = 'o' : bola = ' ';
        cout << " ";
        for(int j = 1; j <= ancho_pista; j++){
            cout << "| ";
            if(pos_bola == j) cout << "\b" << bola;
        }
        cout << "|" << endl;
    }
}
void pintar_fila_medio(int ancho_pista){
    cout << "-";
    for(int i = 1; i <= ancho_pista; i++) {
        cout << "-" << i;
        }
    cout << "--" << endl;
}
void pintar_inciales(string iniciales, int pos_tenista){
    cout << " ";
    for(int i = 1; i < pos_tenista; i++) {
        cout << "  ";
        }
    cout << iniciales << endl;
}

void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola){
    t_tenista tenista1 = tenista1, tenista2 = tenista2;
    if(bola_jugador == tenista1) tenista2 = nadie;
    else if(bola_jugador == tenista2) tenista1 = nadie;

    pintar_inciales(nombre1, pos_t1);
    pintar_fila_fondo(ANCHO_PISTA);
    pintar_campo(ANCHO_PISTA, LARGO_PISTA, pos_bola, tenista1);
    pintar_fila_medio(ANCHO_PISTA);
    pintar_campo(ANCHO_PISTA, LARGO_PISTA, pos_bola, tenista2);
    pintar_fila_fondo(ANCHO_PISTA);
    pintar_inciales(nombre2, pos_t2);
}