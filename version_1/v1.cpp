#include <cmath>
#include <iostream>
#include <ctime>
using namespace std;

const string CYN = "\e[0;36m";
const string NC = "\e[0m";
const string green = "\u001b[32;1m";
const string BRed = "\u001b[41m";
const string BBlack = "\u001b[40m";
const string BWhite = "\u001b[47m";
const string underline = "\033[4m";
const string normal = "\033[0m";

const bool DEBUG_MODE = true, JUEGO_ALEATORIO = true;
const int ANCHO_PISTA = 7, MIN_HABILIDAD = 1, MAX_HABILIDAD = 3, MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;

string marcador(int puntuacion);
int corre_tenista(int posicion_tenista, int velocidad, int posicion_bola);
int introducirDato(string dato, int min_dato, int max_dato);
int golpeo_bola(int posicion_tenista, int habilidad);
string saqueInicial(string nombre1, string nombre2);
string juego(int habilidad1, int habilidad2, int velocidad1, int velocidad2, string nombre1, string nombre2);


int main()
{
    srand(time(NULL));
    string nombre1, nombre2, ganador_punto;
    int habilidad1, habilidad2, velocidad1, velocidad2, punt1 = 0, punt2 = 0;
    bool ganador;

    cout << underline << BRed << "BIENVENIDO/S AL MEJOR TENIS JAMAS PROGRAMADO" << BBlack << normal << endl;
    cout << " " << endl;
    cout << green << R"(
    ,odOO"bo,
  ,dOOOP'dOOOb,
 ,O3OP'dOO3OO33,
 P",ad33O333O3Ob
 ?833O338333P",d
 `88383838P,d38'
  `Y8888P,d88P'
    `"?8,8P"'
    )" << NC << '\n';
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
        cout << CYN << marcador(punt1) << " " << nombre1 << " - " << nombre2 << " " << marcador(punt2) << NC << endl;
        if(punt1 > 3 && punt2 < 3){
            cout << "El ganador del juego es " << nombre1 << "!!" << endl;
            ganador = true;
        }else if(punt2 > 3 && punt1 < 3){
            cout << "El ganador del juego es " << nombre2 << "!!" << endl;
            ganador = true;
        }else if(punt1 == 3 && punt2 == 5 ){
            cout << "El ganador del juego es " << nombre2 << "!!" << endl;
            ganador = true;
        } else if ( punt2 == 3 && punt1 == 5 ){
            cout << "El ganador del juego es " << nombre1 << "!!" << endl;
            ganador = true;
        } else {
            if(juego(habilidad1, habilidad2, velocidad1, velocidad2, nombre1, nombre2) == nombre1){
                punt1++;
            }else{
                punt2++;
            }
        }
        if(punt1 == punt2 && punt1 == 4){
                punt1 = 3;
                punt2 = 3;
        }
    }
    return 0;
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

int corre_tenista(int posicion_tenista, int velocidad, int posicion_bola)
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
    //
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

int golpeo_bola(int posicion_tenista, int habilidad){
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



string saqueInicial(string nombre1, string nombre2){
    int ran;
    string tenista;
    ran = rand() % 2;
    if(ran == 1)
        tenista = nombre2;
    else
        tenista = nombre1;
    if(DEBUG_MODE)
        cout << "Saque para " << tenista << "!!" << endl;
    return tenista;
}

string juego(int habilidad1, int habilidad2, int velocidad1, int velocidad2, string nombre1, string nombre2){
    bool _ganador_punto = false, saque1, turno1;
    string ganador_punto;
    int pos1 = 4, pos2 = 4, pos_bola = 4;

    if(saqueInicial(nombre1, nombre2) == nombre1)
        saque1 = true;
    else
        saque1 = false;

    if(saque1){
        pos_bola = golpeo_bola(pos1, habilidad1);
        pos2 = corre_tenista(pos2, velocidad2, pos_bola);
        turno1 = false;
    }else{
        pos_bola = golpeo_bola(pos2, habilidad2);
        pos1 = corre_tenista(pos1, velocidad1, pos_bola);
        turno1 = true;
    }

    while (!_ganador_punto)
    {
        if(turno1){
            cout << underline << "Turno para " << nombre1 << normal << endl;
            if(pos1 != pos_bola || pos_bola < 1 || pos_bola > 7){
                cout << "Punto para " << nombre2 << "\n"<< endl;
                ganador_punto = nombre2;
                _ganador_punto = true;
            } else {
                pos_bola = golpeo_bola(pos1, habilidad1);
                pos2 = corre_tenista(pos2, velocidad2, pos_bola);
                turno1 = false;
            }
        } else {
            cout << underline << "Turno para " << nombre2 << normal << endl;
            if(pos2 != pos_bola || pos_bola < 1 || pos_bola > 7){
                cout << "Punto para " << nombre1 << "\n" << endl;
                ganador_punto = nombre1;
                _ganador_punto = true;
            } else {
                pos_bola = golpeo_bola(pos2, habilidad2);
                pos1 = corre_tenista(pos1, velocidad1, pos_bola);
                turno1 = true;
            }
        }

    }
    return ganador_punto;
}


