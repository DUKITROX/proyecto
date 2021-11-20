#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const bool DEBUG_MODE = true, JUEGO_ALEATORIO = true;
const int ANCHO_PISTA = 7, MIN_HABILIDAD = 1, MAX_HABILIDAD = 3, MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;
const int LARGO_PISTA = 3, JUEGOS_SET = 3;
;

typedef enum {nadie, tenista1, tenista2} t_tenista;
typedef enum {nada , quince, treinta, cuarenta, ventaja} t_puntos_juego;

string marcador(int puntuacion);
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int juegos1, int juegos2, t_tenista serivico_para);
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista);
int correTenista(int posicion_tenista, int velocidad, int posicion_bola);
int introducirDato(string dato, int min_dato, int max_dato);
int golpeoBola(int posicion_tenista, int habilidad);
t_tenista saqueInicial();
void punto(t_puntos_juego &puntos);
string juego(int habilidad1, int habilidad2, int velocidad1, int velocidad2, string nombre1, string nombre2);

int main(){

    srand(time(NULL));
    string nombre1, nombre2, ganador_punto;
    t_puntos_juego puntos1 = nada, puntos2 = nada;
    int habilidad1, habilidad2, velocidad1, velocidad2, juegos1 = 0, juegos2 = 0;;
    bool ganador;

    cout << "BIENVENIDO/S AL MEJOR TENIS JAMAS PROGRAMADO" << endl;
    cout << endl;

    //Datos tenista 1
    cout << endl << "Datos del tenista 1" << endl;
    cout << "- Iniciales del tenista1: ";
    cin >> nombre1;
    habilidad1 = introducirDato("habilidad", MIN_HABILIDAD, MAX_HABILIDAD);
    velocidad1 = introducirDato("velocidad", MIN_VELOCIDAD, MAX_VELOCIDAD);

    //Datos tenista 2
    cout << endl << "Datos del tenista 2" << endl;
    cout << "- Iniciales del tenista2: ";
    cin >> nombre2;
    habilidad2 = introducirDato("habilidad", MIN_HABILIDAD, MAX_HABILIDAD);
    velocidad2 = introducirDato("velocidad", MIN_VELOCIDAD, MAX_VELOCIDAD);

    //Juego
    ganador = false;

    while(!ganador){
        pintar_marcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, saqueInicial());
        if(puntos1 > 3 && puntos2 < 3){
            cout << "El ganador del juego es " << nombre1 << "!!" << endl;
            ganador = true;
        }else if(puntos2 > 3 && puntos1 < 3){
            cout << "El ganador del juego es " << nombre2 << "!!" << endl;
            ganador = true;
        }else if(puntos1 == 3 && puntos2 == 5 ){
            cout << "El ganador del juego es " << nombre2 << "!!" << endl;
            ganador = true;
        } else if ( puntos2 == 3 && puntos1 == 5 ){
            cout << "El ganador del juego es " << nombre1 << "!!" << endl;
            ganador = true;
        } else {
            if(juego(habilidad1, habilidad2, velocidad1, velocidad2, nombre1, nombre2) == nombre1){
                punto(puntos1);
            }else{
                punto(puntos2);
            }
        }
        if(puntos1 == puntos2 && int(puntos1) == 4){
                puntos1 = t_puntos_juego(3);
                puntos2 = t_puntos_juego(3);
        }
    }
    return 0;
}

string juego(int habilidad1, int habilidad2, int velocidad1, int velocidad2, string nombre1, string nombre2, t_tenista tenista1, t_tenista tenista2){
    bool _ganador_punto = false, saque1, turno1;
    string ganador_punto;
    int pos1 = 4, pos2 = 4, pos_bola = 4;

    if(saqueInicial() == tenista1)
        saque1 = true;
    else
        saque1 = false;

    if(saque1){
        pos_bola = golpeoBola(pos1, habilidad1);
        pos2 = correTenista(pos2, velocidad2, pos_bola);
        turno1 = false;
    }else{
        pos_bola = golpeoBola(pos2, habilidad2);
        pos1 = correTenista(pos1, velocidad1, pos_bola);
        turno1 = true;
    }

    while (!_ganador_punto)
    {
        if(turno1){
            cout << "Turno para " << nombre1 << endl;
            if(pos1 != pos_bola || pos_bola < 1 || pos_bola > 7){
                cout << "Punto para " << nombre2 << "\n"<< endl;
                ganador_punto = nombre2;
                _ganador_punto = true;
            } else {
                pos_bola = golpeoBola(pos1, habilidad1);
                pos2 = correTenista(pos2, velocidad2, pos_bola);
                turno1 = false;
            }
        } else {
            cout << "Turno para " << nombre2 << endl;
            if(pos2 != pos_bola || pos_bola < 1 || pos_bola > 7){
                cout << "Punto para " << nombre1 << "\n" << endl;
                ganador_punto = nombre1;
                _ganador_punto = true;
            } else {
                pos_bola = golpeoBola(pos2, habilidad2);
                pos1 = correTenista(pos1, velocidad1, pos_bola);
                turno1 = true;
            }
        }

    }
    return ganador_punto;
}

void punto(t_puntos_juego &puntos){
    int i = int(puntos);
    i++;
    puntos = t_puntos_juego(i);
}

t_tenista saqueInicial(){
    int i = rand()%2;
    t_tenista saque;
    if(i == 0)
        saque = tenista1;
    else
        saque = tenista2;
    return saque;
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