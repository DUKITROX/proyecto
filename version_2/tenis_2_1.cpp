#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const bool DEBUG_MODE = true, JUEGO_ALEATORIO = false;;
const int ANCHO_PISTA = 7, MIN_HABILIDAD = 1, MAX_HABILIDAD = 3, MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;
const int LARGO_PISTA = 3, JUEGOS_SET = 3;


typedef enum {nadie, tenista1, tenista2} t_tenista;
typedef enum {nada , quince, treinta, cuarenta, ventaja, aux} t_puntos_juego;

string marcador(int puntuacion);
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int juegos1, int juegos2, t_tenista serivico_para);
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista);
int correTenista(int posicion_tenista, int velocidad, int posicion_bola);
int introducirDato(string dato, int min_dato, int max_dato);
int golpeoBola(int posicion_tenista, int habilidad);
t_tenista saqueInicial();
void punto(t_puntos_juego &puntos);
t_tenista juego(string nombre1, string nombre2, int velocidad1, int velocidad2, int habilidad1, int habilidad2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, t_tenista turno);



int main(){

    srand(time(NULL));
    string nombre1, nombre2, ganador_punto;
    t_puntos_juego puntos1 = nada, puntos2 = nada;
    int habilidad1, habilidad2, velocidad1, velocidad2, juegos1 = 0, juegos2 = 0;
    t_tenista ganador = nadie, turno;
    t_tenista jugador1 = tenista1;
    t_tenista jugador2 = tenista2;


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
    //ganador = juego(nombre1, nombre2, velocidad1, velocidad2, habilidad1, habilidad2, puntos1, puntos2);
    //cout << ganador << endl;
    turno = saqueInicial();
    while(ganador == nadie){
        pintar_marcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, turno);
        if(puntos1 > cuarenta && puntos2 < cuarenta){
            cout << "El ganador del juego es " << nombre1 << "!!" << endl;
            ganador = tenista1;
        }else if(puntos2 > cuarenta && puntos1 < cuarenta){
            cout << "El ganador del juego es " << nombre2 << "!!" << endl;
            ganador = tenista2;
        }else if(puntos1 == cuarenta && puntos2 == aux ){
            cout << "El ganador del juego es " << nombre2 << "!!" << endl;
            ganador = tenista2;
        } else if ( puntos2 == cuarenta && puntos1 == aux ){
            cout << "El ganador del juego es " << nombre1 << "!!" << endl;
            ganador = tenista1;
        } else {
            if(juego(nombre1, nombre2, velocidad1, velocidad2, habilidad1, habilidad2, puntos1, puntos2, turno) == tenista1){
                punto(puntos1);
            }else{
                punto(puntos2);
            }
        }
        if(puntos1 == puntos2 && puntos1 == ventaja){
                puntos1 = cuarenta;
                puntos2 = cuarenta;
        }
    }
    cout << ganador << endl;

    return 0;
}

t_tenista juego(string nombre1, string nombre2, int velocidad1, int velocidad2, int habilidad1, int habilidad2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, t_tenista turno){
    t_tenista ganador_punto = nadie;
    int pos1 = 4, pos2 = 4, pos_bola = 4;
    t_puntos_juego punt1 = nada, punt2 = nada;

        while(ganador_punto == nadie){
            pintar_peloteo(nombre1, nombre2, pos1, pos2, turno, pos_bola);
            if(turno == tenista1){
                cout << "Turno para " << nombre1 << endl;
                if(pos1 != pos_bola || pos_bola < 1 || pos_bola > 7){
                    cout << "Punto para " << nombre2 << "\n"<< endl;
                    ganador_punto = tenista2;
                } else {
                    pos_bola = golpeoBola(pos1, habilidad1);
                    pos2 = correTenista(pos2, velocidad2, pos_bola);
                    turno = tenista2;
                }
            } else {
                cout << "Turno para " << nombre2 << endl;
                if(pos2 != pos_bola || pos_bola < 1 || pos_bola > 7){
                    cout << "Punto para " << nombre1 << "\n" << endl;
                    ganador_punto = tenista1;
                } else {
                    pos_bola = golpeoBola(pos2, habilidad2);
                    pos1 = correTenista(pos1, velocidad1, pos_bola);
                    turno = tenista1;
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

void cambioTurno(t_tenista &turno){
    if(turno == tenista1)
        turno = tenista2;
    else
        turno = tenista1;
}

string marcador(int puntuacion)
{
    string punt;
    switch(puntuacion)
    {
    case 0:
        punt = "00";
    break;
    case 1:
        punt = "15";
    break;
    case 2:
        punt = "30";
    break;
    case 3:
        punt = "40";
    break;
    case 4:
        punt = "Ad";
    break;
    }
    return punt;
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

void pintar_inciales(string iniciales, int pos_tenista){
    cout << " ";
    for(int i = 1; i < pos_tenista; i++) {
        cout << "  ";
    }
    cout << iniciales << endl;
}

void pintar_fila_fondo(int ancho_pista){
    cout << " ";
    for(int i = 0; i < ANCHO_PISTA; i++){
        cout << " -";
    }
    cout << endl;
}

void pintar_fila_medio(int ancho_pista){
    cout << "-";
    for(int i = 1; i <= ancho_pista; i++) {
        cout << "-" << i;
        }
    cout << "--" << endl;
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

int correTenista(int posicion_tenista, int velocidad, int posicion_bola)
{
    if( abs(posicion_bola - posicion_tenista) <= velocidad){
        posicion_tenista = posicion_bola;
        if(DEBUG_MODE){
            cout << "Su rival llega a la bola." << endl;
        }
    }else{
        if(DEBUG_MODE){
            cout << "Su rival no llega a la bola." << endl;
        }
        if(posicion_bola < posicion_tenista){
            posicion_tenista = posicion_tenista - velocidad;
        } else {
            posicion_tenista = posicion_tenista + velocidad;
        }
    }
    return posicion_tenista;
}

int introducirDato(string dato, int min_dato, int max_dato){
    int dato_int;
    bool apto = false;
    cout << "Introduce la " << dato << " del jugador:" << endl;
    while(!apto){
        cin >> dato_int;
        if(dato_int > max_dato || dato_int < min_dato)
            cout << "El número debe estar entre " << min_dato << " y " << max_dato << endl;
        else
            apto = true;
    }
    return dato_int;
}

int golpeoBola(int posicion_tenista, int habilidad){
    int destino, distancia, prob_acierto, aux, desicion;

    if(JUEGO_ALEATORIO){
        destino = rand() % 7 + 1;
    } else {
        cout << "Introduce una calle de  destino: " << endl;
        cin >> destino;
    }
    if(DEBUG_MODE)
        cout << "El jugador dispara hacia la calle " << destino << endl;
    distancia = abs(posicion_tenista - destino);

    if(distancia > habilidad){
        double d1, d2, d3;
        d1 = distancia - habilidad;
        d2 = (ANCHO_PISTA - 1) - MIN_HABILIDAD;
        d3 = d1/d2;
        prob_acierto = 100 - ((d1/d2)*100);
        aux = rand() % 100;
        if(DEBUG_MODE)
            cout << "Tiro complicado que... (probab_exito = " << prob_acierto << " y resultado = " << aux << " )" << endl;
        if(aux >= prob_acierto){
            if(DEBUG_MODE)
                cout << "No llega a su destino!" << endl;
            desicion = rand() % 2;
            if(desicion == 1){
                destino = destino + 1;
            } else {
                destino = destino - 1;
            }
        } else {
            if(DEBUG_MODE)
                cout << "Llega a su destino!" << endl;
        }
    }
    if(DEBUG_MODE)
        cout << "La pelota cae en la calle " << destino << endl;
    return destino;
}

t_tenista saqueInicial(){
    int i;
    t_tenista saque;

    i = rand()%2;

    if(i == 0)
        saque = tenista1;
    else
        saque = tenista2;

    return saque;
}

