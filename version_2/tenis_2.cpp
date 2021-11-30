#include <iostream>
#include <string>
#include <ctime>
#include <iomanip> 

using namespace std;

const bool MODO_DEBUG = true, JUEGO_ALEATORIO = true;

const int MIN_HABILIDAD = 1, MAX_HABILIDAD = 3;
const int MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;
const int ANCHO_PISTA = 7, LARGO_PISTA = 3, JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;

typedef enum {NADIE, TENISTA1, TENISTA2} t_tenista;
typedef enum {NADA , QUINCE, TREINTA, CUARENTA, VENTAJA} t_puntos_juego;
typedef int t_conteo_golpes[ANCHO_PISTA + 2];

int introducirDato(string dato, int min_dato, int max_dato);
void introducir_tenista(string &iniciales, int &habilidad, int &velocidad);
t_tenista saqueInicial();

string puntos_a_string(t_puntos_juego puntuacion);
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int juegos1, int juegos2, t_tenista serivico_para);
void sumar_punto(t_puntos_juego &puntos);
void actualizar_marcador(t_tenista ganador_punto, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int &juegos1, int &juegos2, t_tenista &ganador_juego);
void mostrar_estadistica(t_tenista tenista, t_conteo_golpes &golpes1, t_conteo_golpes &golpes2, int golpes_ganadores);

void lance(t_tenista tenista_que_golpea, string nombre, int habilidad, t_conteo_golpes golpes, int &golpes_ganados, int velocidad, int &pos_recibe, int &pos_bola, t_tenista &ganador_lance);
void jugar_punto(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, t_conteo_golpes golpes2, int &golopes_ganados2, t_tenista &ganador_punto);
void jugar_juego(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, int &juegos1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int &juegos2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_punto);

void pintar_iniciales(string iniciales, int pos_tenista);
void pintar_fila_fondo(int ancho_pista);
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista);
void pintar_fila_medio(int ancho_pista);
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);

int correTenista(int posicion_tenista, int velocidad, int posicion_bola);
int golpeoBola(int posicion_tenista, int habilidad);

void punto(t_puntos_juego &puntos);
string juego(int habilidad1, int habilidad2, int velocidad1, int velocidad2, string nombre1, string nombre2);

int main(){
    srand(time(NULL));
    string ini1, ini2;
    int habilidad1, habilidad2;
    int velocidad1, velocidad2;
    t_puntos_juego puntos1, puntos2;
    int juegos1, juegos2;

    t_conteo_golpes golpes1, golpes2;
    int golpes_ganadores1, golpes_ganadores2;
}

int main(){

    srand(time(NULL));
    string nombre1, nombre2, ganador_punto;
    t_puntos_juego puntos1 = NADA, puntos2 = NADA;
    int habilidad1, habilidad2, velocidad1, velocidad2, juegos1 = 0, juegos2 = 0;;
    bool ganador;

    cout << "Bienvenidos al simulador de partidos de tenis" << endl;
    cout << endl;

    //Datos tenista 1
    cout << endl << "Datos del tenista 1" << endl;
    introducir_tenista(nombre1, habilidad1, velocidad1);

    //Datos tenista 2
    cout << endl << "Datos del tenista 2" << endl;
    introducir_tenista(nombre2, habilidad2, velocidad2);

    //Juego
    
    return 0;
}

void mostrar_estadistica(t_tenista tenista, string nombre_tenista, t_conteo_golpes &golpes_tenista, int golpes_ganadores){
    string space = "       ";
    int golpes_totales = 0;
    for(int i = 0; i <= sizeof(golpes_tenista) ; i++){
      golpes_totales += golpes_tenista[i];
    }
    cout << "Estadisticas de " << nombre_tenista << ":" << endl;
    cout << setw(10) << "Golpes totales: "<< golpes_tenista << endl;
    cout << setw(10) << "Golpes ganadores: " << golpes_ganadores << endl;
    cout << setw(10) << "Errores no forzados: " << golpes_tenista[0] + golpes_tenista[8] << endl;
    cout << setw(10) << "Distribucion de los golpes en la pista: " << endl;
    cout << setw(15) << " Calle";
    for(int i = 0; i <= ANCHO_PISTA; i++){
        cout << i << space;
    }
    cout << endl << setw(15) << "   %";
    for(int i = 0; i <= ANCHO_PISTA; i++){
        cout << space << golpes_tenista[i]/golpes_totales;
    }
}

int introducir_dato(string dato, int min, int max){
    int dato_i;
    cout << "> Introduzca su " << dato << " (valor entre " << min << " y " << max << "): ";
    cin >> dato_i;

    while(dato_i < min || dato_i > max || cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "Dato incorrecto o fuera de rango, vuelva a introducirlo (" << min << " y " << max << "): ";
        cin >> dato_i;
    }
    return dato_i;
}
void introducir_tenista(string &iniciales, int &habilidad, int &velocidad){
    cout << "   >Introduce sus iniciales (3 letras): ";
    cin >> iniciales;
    habilidad = introducir_dato("habilidad", MIN_HABILIDAD, MAX_HABILIDAD);
    velocidad = introducir_dato("velocidad", MIN_VELOCIDAD, MAX_VELOCIDAD);
}
t_tenista saqueInicial(){
    int random = rand()%2;
    t_tenista saque;
    if(random == 0)
        saque = TENISTA1;
    else
        saque = TENISTA2;

    return saque;
}

string puntos_a_string(t_puntos_juego puntuacion){
    string puntuacion_s;
    switch(puntuacion){
        case NADA:
            puntuacion_s = "00";
            break;
        case QUINCE:
            puntuacion_s = "15";
            break;
        case TREINTA:
            puntuacion_s = "30";
            break;
        case CUARENTA:
            puntuacion_s = "40";
            break;
        case VENTAJA:
            puntuacion_s = "Ad";
            break;
    }
    return puntuacion_s;
}
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego puntos1, t_puntos_juego puntos2, int juegos1, int juegos2, t_tenista serivico_para){

    string marcador1 = puntos_a_string(puntos1);
    string marcador2 = puntos_a_string(puntos2);

    cout << endl << "   " << nombre1 << "  " << juegos1 << " : " << marcador1 << " ";
    if(serivico_para == TENISTA1) cout << '*';

    cout << endl << "   " << nombre2 << "  " << juegos2 << " : " << marcador2 << " ";
    if(serivico_para == TENISTA2) cout << '*';
    cout << endl << endl;
}
void sumar_punto(t_puntos_juego &puntos){
    int i = int(puntos);
    i++;
    puntos = t_puntos_juego(i);
}
void actualizar_marcador(t_tenista ganador_punto, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int &juegos1, int &juegos2, t_tenista &ganador_juego){
    if(ganador_punto == TENISTA1)
        sumar_punto(puntos1);
    else
        sumar_punto(puntos2);

    if(puntos1 == VENTAJA && int(puntos2) < int(CUARENTA)){
        ganador_juego = TENISTA1;
        juegos1++;
        puntos1 = NADA;
        puntos2 = NADA;
    } else if(puntos2 == VENTAJA && int(puntos1) < int(CUARENTA)){
        ganador_juego = TENISTA2;
        juegos2++;
        puntos1 = NADA;
        puntos2 = NADA;
    } else
        ganador_juego = NADIE;


    if(puntos1 == VENTAJA && puntos2 == VENTAJA){
        puntos1 = CUARENTA;
        puntos2 = CUARENTA;
    }
}

void lance(t_tenista tenista_que_golpea, string nombre, int habilidad, t_conteo_golpes golpes, int &golpes_ganados, int velocidad, int &pos_recibe, int &pos_bola, t_tenista &ganador_lance){
    ganador_lance = NADIE;
    pos_bola = golpeo_bola(pos_bola, habilidad);
    golpes[pos_bola]++;
    if(pos_bola <= ANCHO_PISTA && pos_bola > 0){
        golpes_ganados++;
        pos_recibe = corre_tenista(pos_recibe, velocidad, pos_bola);
        if(pos_recibe != pos_bola){
            ganador_lance = tenista_que_golpea;
        }
    }else{
        if(tenista_que_golpea == TENISTA1) ganador_lance = TENISTA2;
        else ganador_lance = TENISTA1;
    }
}
void jugar_punto(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, t_conteo_golpes golpes2, int &golopes_ganados2, t_tenista &ganador_punto){
    ganador_punto = NADIE;
    int habilidad_ataca, velocidad_defiende, golpes_ganados_ataca;
    t_conteo_golpes golpes_ataca;
    t_tenista tenista_ataca = servicio, tenista_defiende;

    int medio_campo = ANCHO_PISTA / 2 + 1;
    int pos1 = medio_campo, pos2 = medio_campo, pos_bola = medio_campo;
    int pos_ataca, pos_defiende;
    while(ganador_punto == NADIE){
        if(tenista_ataca == TENISTA1){
            habilidad_ataca = habilidad1;
            velocidad_defiende = velocidad2;

            pos_ataca = pos1;
            pos_defiende = pos2;

            for(int i = 0; i < ANCHO_PISTA + 2; i++){
                golpes_ataca[i] = golpes1[i];
            }
            golpes_ganados_ataca = golpes_ganados1;

            tenista_defiende = TENISTA2;
        }else{
            habilidad_ataca = habilidad2;
            velocidad_defiende = velocidad1;

            pos_ataca = pos2;
            pos_defiende = pos1;

            tenista_defiende = TENISTA1;
        }
        lance(tenista_ataca, nombre1, habilidad_ataca, golpes_ataca, golpes_ganados_ataca, velocidad_defiende, pos_defiende, pos_bola, ganador_punto);
        pintar_peloteo(nombre1, nombre2, pos1, pos2, tenista_defiende, pos_bola);

        if(tenista_ataca == TENISTA1){

        }else{

        }
    }
    //actualizar_marcador();
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
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista){
    char bola;
    int extremo_pista;

    switch(tenista){
        case TENISTA1:
            extremo_pista = 1;
            break;
        case TENISTA2:
            extremo_pista = largo_pista;
            break;
        case NADIE:
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
    //TODO: el "ancho pista" la pides por parametros o la uedes usar por const. globasl?
    cout << "-";
    for(int i = 1; i <= ancho_pista; i++) {
        cout << "-" << i;
        }
    cout << "--" << endl;
}
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola){
    t_tenista tenista1 = tenista1, tenista2 = tenista2;
    if(bola_jugador == tenista1) tenista2 = NADIE;
    else if(bola_jugador == tenista2) tenista1 = NADIE;

    pintar_inciales(nombre1, pos_t1);
    pintar_fila_fondo(ANCHO_PISTA);
    pintar_campo(ANCHO_PISTA, LARGO_PISTA, pos_bola, tenista1);
    pintar_fila_medio(ANCHO_PISTA);
    pintar_campo(ANCHO_PISTA, LARGO_PISTA, pos_bola, tenista2);
    pintar_fila_fondo(ANCHO_PISTA);
    pintar_inciales(nombre2, pos_t2);
}

int corre_tenista(int posicion_tenista, int velocidad, int pos_bola){
    int distancia = abs(posicion_tenista - pos_bola);
    int posicion_final;

    if(distancia <= velocidad){
        if(MODO_DEBUG)
            cout << "El tenista llega a la bola" << endl << endl;
        posicion_final = pos_bola;

    }else{
        if(MODO_DEBUG)
            cout << "El tenista no ha llegado a la bola" << endl << endl;

        if(posicion_tenista < pos_bola){
            posicion_final = posicion_tenista + velocidad;
        }else{
            posicion_final = posicion_tenista - velocidad;
        }
    }
    return posicion_final;
}

int golpeo_bola(int posicion_tenista, int habilidad){
    int destino_bola, distancia;

    if(JUEGO_ALEATORIO){
        destino_bola = rand()%ANCHO_PISTA + 1;
        cout << endl;
        if(MODO_DEBUG)
            cout << endl << "El jugador dispara hacia la calle" << destino_bola << endl;
    }else{
        cin >> destino_bola;
        while(destino_bola < 1 || destino_bola > ANCHO_PISTA || cin.fail()){
            cin.clear();
            cin.ignore();
            cout << "Calle fuera de rango (1 - " << ANCHO_PISTA << "), vuelva introducir calle: ";
            cin >> destino_bola;
        }
    }

    distancia = abs(posicion_tenista - destino_bola);

    if(distancia <= habilidad){
        if(MODO_DEBUG)cout << "Ese ha sido un tiro sencillo" << endl;
    }else{
        int probabilidad_extito = 100 - ((distancia-habilidad)*100 / ((ANCHO_PISTA-1)-MIN_HABILIDAD));
        int random = rand()%100;

        if(random < probabilidad_extito){
            if(MODO_DEBUG){
                cout << "Tiro complicado que... (propab_exito = "<<probabilidad_extito<<" y resultado = "<<random<<") Llega a su destino!"<<endl;
                cout << "La bola llega a la calle " << destino_bola << endl;}
        }else{
            int random2 = rand()%2;
            if(random2 == 0) destino_bola++; 
            else destino_bola--;

            if(MODO_DEBUG){
                cout << "Tiro complicado que... (propab_exito = "<<probabilidad_extito<<" y resultado = "<<random<<") No ha sido preciso!"<<endl;
                if(destino_bola < 1 || destino_bola > ANCHO_PISTA){
                    cout << "La bola se sale fuera" << endl << endl;}
                else{
                    cout << "La bola llega a la calle " << destino_bola << endl;}
            }
        }
    }
    return destino_bola;
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