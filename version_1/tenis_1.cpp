#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

//constantes
const int ANCHO_PISTA = 7;

const int LIM_INF_HAB = 1;
const int LIM_SUP_HAB = 3;

const int LIM_INF_VEL = 1;
const int LIM_SUP_VEL = 5;

const bool MODO_DEBUG = true;
const bool JUEGO_ALEATORIO = true;

const int NEGRO_MUY_CLARO = 246;
const int NEGRO_CLARO = 241;
const int NEGRO_OSCURO = 238;

const int TIEMPO_DELAY_LARGO = 100000000;
const int TIEMPO_DELAY_CORTO = 10000000;

int introducir_dato(string dato, int min, int max);
string marcador(int puntuacion);
int corre_tenista(int posicion_tenista, int velocidad, int pos_bola);
int golpeo_bola(int posicion_tenista, int habilidad);

int main(){
    srand(time(NULL));
    int centro_pista = ANCHO_PISTA/2 + 1;

//Tenista 1
    string ini1;
    int hab1;
    int vel1;
    int pos1 = 4;
    int punt1 = 0;
//Tenista 2
    string ini2;
    int hab2;
    int vel2;
    int pos2 = 4;
    int punt2 = 0;
//Bola
    int pos_bola = centro_pista;
    bool tenista_que_golpea = false; //false si golpea el tenista 1 y true si golpea el tenista 2
    bool ganador_juego = false;
    bool ganador_punto = false;

    cout << endl << "\x1b[38;5;125m\x1b[1m\x1b[7m  ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ Bienvenido al simulador de partidos de tenis! ᕙ( ͡❛ ͜ʖ ͡❛)ᕗ  \x1b[0m"<< endl << endl;

//TENISTA 1
    cout << "  \x1b[38;5;125m\x1b[4m\x1b[1m(─‿‿─) Datos del tenista 1 (─‿‿─)\x1b[0m" << endl << endl;
    cout << "\x1b[38;5;125m> Introduce sus iniciales: \x1b[38;5;106m";
    getline(cin, ini1);
    hab1 = introducir_dato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);
    vel1 = introducir_dato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);

//TENISTA 2
    cout << endl << endl << "  \x1b[38;5;125m\x1b[4m(ㆆ_ㆆ) Datos del tenista 2 (ㆆ_ㆆ)\x1b[0m" << endl << endl;
    cout << "\x1b[38;5;125m> Introduce sus iniciales: \x1b[38;5;106m";
    cin.ignore();
    getline(cin, ini2);
    while(ini1 == ini2){
        cout << "\x1b[38;5;88mElija unas iniciales distintas a las del otro tenista: \x1b[38;5;106m";
        getline(cin, ini2);
    }
    hab2 = introducir_dato("habilidad", LIM_INF_HAB, LIM_SUP_HAB);
    vel2 = introducir_dato("velocidad", LIM_INF_VEL, LIM_SUP_VEL);
    cout << endl;

//Determinar aleatoriamente quien empiezaa
    if(rand()%2){
        cout << "\x1b[38;5;"<<NEGRO_MUY_CLARO<<"mServicio para " << ini1 << " (─‿‿─)\x1b[0m" << endl;
        tenista_que_golpea = false;}
    else{
        cout << "\x1b[38;5;"<<NEGRO_MUY_CLARO<<"mServicio para " << ini2 << " (ㆆ_ㆆ)\x1b[0m" << endl;
        tenista_que_golpea = true;}

    cout << endl << "\x1b[38;5;125m\x1b[1m" << ini1 << " " << marcador(punt1) << " - " << marcador(punt2) << " " << ini2 << "\x1b[0m" << endl << endl;
    
    if(JUEGO_ALEATORIO)
        cout << endl;
        cin.get();

//Bucle principal del juego
    while(!ganador_juego){
        pos1 = centro_pista, pos2 = centro_pista, pos_bola = centro_pista; //Centramos tenistas y bola
        ganador_punto = false;

//Jugar el punto
        while(!ganador_punto){
            if(tenista_que_golpea){
                cout << "\x1b[38;5;"<<NEGRO_CLARO<<"m(ㆆ_ㆆ) Golpea " << ini2 << "\x1b[38;5;106m ";
                pos_bola = golpeo_bola(pos2, hab2);}
            else{
                cout << "\x1b[38;5;"<<NEGRO_CLARO<<"m(─‿‿─) Golpea " << ini1 << "\x1b[38;5;106m ";
                pos_bola = golpeo_bola(pos1, hab1);}

    //Sale fuera la bola
            if(pos_bola < 1 || pos_bola > ANCHO_PISTA){
                if(tenista_que_golpea){
                    cout << "\x1b[38;5;"<<NEGRO_MUY_CLARO<<"mPunto para " << ini1 << " (─‿‿─)!!" << endl;
                    punt1++;
                    if(punt2 == 4) punt2--;}
                else{
                    cout << "\x1b[38;5;"<<NEGRO_MUY_CLARO<<"mPunto para " << ini2 << " (ㆆ_ㆆ)!!!" << endl;
                    punt2++;
                    if(punt1 == 4) punt1--;}
                ganador_punto = true;
            }
    //Acierta el disparo y el otro tenista corre
            else if(tenista_que_golpea){
                pos1 = corre_tenista(pos1, vel1, pos_bola);
                if(pos1 != pos_bola){ //falla
                    cout << "\x1b[38;5;"<<NEGRO_MUY_CLARO<<"mPunto para " << ini2 << " (ㆆ_ㆆ)!!!" << endl;
                    punt2++;
                    if(punt1 == 4) punt1--;
                    ganador_punto = true;
                }
            }
            else{
                pos2 = corre_tenista(pos2, vel2, pos_bola);
                if(pos2 != pos_bola){ //falla
                    cout << "\x1b[38;5;"<<NEGRO_MUY_CLARO<<"mPunto para " << ini1 << " (─‿‿─)!!!" << endl;
                    punt1++;
                    if(punt2 == 4) punt2--;
                    ganador_punto = true;
                }
            }
            tenista_que_golpea = !tenista_que_golpea;//Actualizamos el tenista que golpea
            sleep_for(nanoseconds(TIEMPO_DELAY_LARGO));//delay entre cada golpeo
        }
        cout << endl << "\x1b[38;5;125m\x1b[1m" << ini1 << " " << marcador(punt1) << " - " << marcador(punt2) << " " << ini2 << "\x1b[0m" << endl << endl;
        if(punt1 >= 4 && punt1 - punt2 > 1){
            cout << endl <<  "\x1b[38;5;125m\x1b[1m\x1b[7m  (─‿‿─) El ganador del juego es " << ini1 << " (─‿‿─)  \x1b[0m" << endl << endl;
            ganador_juego = true;}
        else if(punt2 >= 4 && punt2 - punt1 > 1){
            cout << endl << "\x1b[38;5;125m\x1b[1m\x1b[7m  (ㆆ_ㆆ) El ganador del juego es " << ini2 << " (ㆆ_ㆆ)  \x1b[0m" << endl << endl;
            ganador_juego = true;
        }
        if(JUEGO_ALEATORIO)
                cout << endl;
                cin.get();
        }
    return 0;
}

int introducir_dato(string dato, int min, int max){
    int dato_i;
    cout << "\x1b[38;5;125m> Introduzca su " << dato << " (valor entre " << min << " y " << max << "): \x1b[38;5;106m";
    cin >> dato_i;

    while(dato_i < min || dato_i > max || cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "\x1b[38;5;88mDato incorrecto o fuera de rango, vuelva a introducirlo (" << min << " y " << max << "): \x1b[38;5;106m";
        cin >> dato_i;
    }
    return dato_i;
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

int corre_tenista(int posicion_tenista, int velocidad, int pos_bola){
    int distancia = abs(posicion_tenista - pos_bola);
    int posicion_final;

    if(distancia <= velocidad){
        if(MODO_DEBUG)
            cout << "\x1b[38;5;"<<NEGRO_OSCURO<<"mEl tenista llega a la bola\x1b[0m" << endl << endl;
            sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));
        posicion_final = pos_bola;

    }else{
        if(MODO_DEBUG)
            cout << "\x1b[38;5;"<<NEGRO_OSCURO<<"mEl tenista no ha llegado a la bola\x1b[0m" << endl << endl;
            sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));

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
            cout << endl << "\x1b[38;5;"<<NEGRO_OSCURO<<"mEl jugador dispara hacia la calle \x1b[38;5;106m" << destino_bola << "\x1b[0m" << endl;
            sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));}
    else{
        cin >> destino_bola;
        while(destino_bola < 1 || destino_bola > ANCHO_PISTA || cin.fail()){
            cin.clear();
            cin.ignore();
            cout << "\x1b[38;5;88mCalle fuera de rango (1 - " << ANCHO_PISTA << "), vuelva introducir calle: \x1b[38;5;106m";
            cin >> destino_bola;
        }
    }

    distancia = abs(posicion_tenista - destino_bola);

    if(distancia < habilidad){
        if(MODO_DEBUG){
            cout << "\x1b[38;5;"<<NEGRO_OSCURO<<"mEse ha sido un tiro sencillo\x1b[0m" << endl;
            sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));}
    }else{
        int probabilidad_extito = 100 - ((distancia-habilidad)*100 / ((ANCHO_PISTA-1)-LIM_INF_HAB));
        int random = rand()%100;

        if(random < probabilidad_extito){
            if(MODO_DEBUG){
                cout<<"\x1b[38;5;"<<NEGRO_OSCURO<<"mTiro complicado que... (propab_exito = "<<probabilidad_extito<<" y resultado = "<<random<<") Llega a su destino!"<<endl;
                sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));
                cout << "La bola llega a la calle " << destino_bola << endl;
                sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));}
        }else{
            int random_fuera = rand()%2;
            if(random_fuera) destino_bola++; 
            else destino_bola--;

            if(MODO_DEBUG){
                cout<<"\x1b[38;5;"<<NEGRO_OSCURO<<"mTiro complicado que... (propab_exito = "<<probabilidad_extito<<" y resultado = "<<random<<") No ha sido preciso!"<<endl;
                sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));
                if(destino_bola < 1 || destino_bola > ANCHO_PISTA){
                    cout << "La bola se sale fuera\x1b[0m" << endl << endl;
                    sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));}
                else{
                    cout << "La bola llega a la calle " << destino_bola << "\x1b[38;5;238m" << endl;
                    sleep_for(nanoseconds(TIEMPO_DELAY_CORTO));}
            }
        }
    }
    return destino_bola;
}

/*
CODIGOS PARA ESTABLECER COLORES

    Versión de 8 colores

    >Color fuente => \x1b[30m
    >Color fondo => \x1b[40m
    >Color fuente y fondo => \x1b[30;40m
    >Reiniciador de colores => "\x1b[0m"

    Versión de 256 colores (la version que yo he usado juas juas juas) (perdon por dejar los string feos con tantos codigos de colores :V)

    >Son de la fomra => \x1b[38;5;${ID}m

PALETA DE COLORES

    +---------+------------+------------+
    |  color  | foreground | background |
    |         |    code    |    code    |
    +---------+------------+------------+
    | black   |     30     |     40     |
    | red     |     31     |     41     |
    | green   |     32     |     42     |
    | yellow  |     33     |     43     |
    | blue    |     34     |     44     |
    | magenta |     35     |     45     |
    | cyan    |     36     |     46     |
    | white   |     37     |     47     |
    +---------+------------+------------+
*/