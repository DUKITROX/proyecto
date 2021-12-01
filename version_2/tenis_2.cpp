#include <iostream>
#include <string>
#include <ctime>
#include <iomanip> 
//TODO: meter lo de "Errores no forzados en estadistica"

using namespace std;

const bool MODO_DEBUG = false, JUEGO_ALEATORIO = false;

const int MIN_HABILIDAD = 1, MAX_HABILIDAD = 3;
const int MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;
const int ANCHO_PISTA = 7, LARGO_PISTA = 3, JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;

typedef enum {NADIE, TENISTA1, TENISTA2} t_tenista;
typedef enum {NADA , QUINCE, TREINTA, CUARENTA, VENTAJA} t_puntos_juego;
typedef int t_conteo_golpes[ANCHO_PISTA + 2];

int introducirDato(string dato, int min_dato, int max_dato);
void introducir_tenista(string &iniciales, int &habilidad, int &velocidad);
t_tenista saque_inicial();

string puntos_a_string(t_puntos_juego puntuacion);
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego puntos1, t_puntos_juego puntos2, int juegos1, int juegos2, t_tenista servicio_para);
void sumar_punto(t_puntos_juego &puntos);
void actualizar_marcador(t_tenista ganador_punto, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int &juegos1, int &juegos2, t_tenista &ganador_juego);

void lance(t_tenista tenista_que_golpea, string nombre, int habilidad, t_conteo_golpes golpes, int &golpes_ganados, int velocidad, int &pos_recibe, int &pos_bola, t_tenista &ganador_lance);
void jugar_punto(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_punto);
void jugar_juego(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, int &juegos1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int &juegos2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_juego, t_puntos_juego &puntos1, t_puntos_juego &puntos2);

void pintar_iniciales(string iniciales, int pos_tenista);
void pintar_fila_fondo(int ancho_pista);
void pintar_campo(int ancho_pista, int largo_pista, int pos_bola, t_tenista tenista);
void pintar_fila_medio(int ancho_pista);
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);

void mostrar_estadistica(t_tenista tenista, string nombre_tenista, t_conteo_golpes golpes_tenista, int golpes_ganadores);

int corre_tenista(int posicion_tenista, int velocidad, int posicion_bola);
int golpeo_bola(int posicion_tenista, int habilidad);

int main(){

    srand(time(NULL));
    string nombre1, nombre2;
    t_tenista tenista1 = TENISTA1, tenista2 = TENISTA2;
    t_puntos_juego puntos1 = NADA, puntos2 = NADA;
    t_conteo_golpes golpes1, golpes2; //TODO: estan bien inicializados asi los arrays de puntos? o como se incializan?
    int golpes_ganados1 = 0, golpes_ganados2 = 0;
    int habilidad1, habilidad2, velocidad1, velocidad2, juegos1 = 0, juegos2 = 0;
    bool ganador_set = false;
    t_tenista servicio = saque_inicial();
    t_tenista ganador_juego = NADIE;

    cout << "Bienvenidos al simulador de partidos de tenis" << endl;
    cout << endl;

    //Datos tenista 1
    cout << endl << "Datos del tenista 1" << endl;
    introducir_tenista(nombre1, habilidad1, velocidad1);

    //Datos tenista 2
    cout << endl << "Datos del tenista 2" << endl;
    introducir_tenista(nombre2, habilidad2, velocidad2);



    //Juego
    while(ganador_set == false){
        jugar_juego(servicio, nombre1, habilidad1, velocidad1, juegos1, golpes1, golpes_ganados1, nombre2, habilidad2, velocidad2, juegos2, golpes2, golpes_ganados2, ganador_juego, puntos1, puntos2);
        if(juegos1 - juegos2 >= 2 && juegos1 >= JUEGOS_SET)
            ganador_set = TENISTA1;
        else if(juegos2 - juegos1 >= 2 && juegos2 >= JUEGOS_SET)
            ganador_set = TENISTA2;
    }

    cout << endl << "   " << nombre1 << " " << juegos1 << endl;
    cout << "   " << nombre2 << " " << juegos2 << endl << endl;
    string nombre_ganador;
    ganador_set == TENISTA1 ? nombre_ganador = nombre1 : nombre_ganador = nombre2;
    cout << nombre_ganador << " se hizo con el partido" << endl << endl << "Gracias por jugar" << endl;
    
    return 0;
}



int introducir_dato(string dato, int min, int max){
    int dato_i;
    cout << "   >Introduzca su " << dato << " (valor entre " << min << " y " << max << "): ";
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
t_tenista saque_inicial(){
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
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego puntos1, t_puntos_juego puntos2, int juegos1, int juegos2, t_tenista servicio_para){

    string marcador1 = puntos_a_string(puntos1);
    string marcador2 = puntos_a_string(puntos2);

    cout << endl << "   " << nombre1 << "  " << juegos1 << " : " << marcador1 << " ";
    if(servicio_para == TENISTA1) cout << '*';

    cout << endl << "   " << nombre2 << "  " << juegos2 << " : " << marcador2 << " ";
    if(servicio_para == TENISTA2) cout << '*';
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
void mostrar_estadistica(t_tenista tenista, string nombre_tenista, t_conteo_golpes golpes_tenista, int golpes_ganadores){
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
void jugar_punto(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_punto){
    ganador_punto = NADIE;
    int habilidad_ataca, velocidad_defiende, golpes_ganados_ataca;
    string nombre_ataca;
    t_conteo_golpes golpes_ataca;
    t_tenista tenista_ataca = servicio, tenista_defiende;

    int medio_campo = ANCHO_PISTA / 2 + 1;
    int pos1 = medio_campo, pos2 = medio_campo, pos_bola = medio_campo;
    int pos_ataca, pos_defiende;
    while(ganador_punto == NADIE){
        if(tenista_ataca == TENISTA1){
            nombre_ataca = nombre1;
            habilidad_ataca = habilidad1;
            velocidad_defiende = velocidad2;

            pos_ataca = pos1;
            pos_defiende = pos2;

            for(int i = 0; i < DIM_ARRAY_GOLPES; i++) golpes_ataca[i] = golpes1[i]; //Copiamos los golpes del tenista1
            golpes_ganados_ataca = golpes_ganados1;

            tenista_defiende = TENISTA2;
        }else{
            nombre_ataca = nombre2;
            habilidad_ataca = habilidad2;
            velocidad_defiende = velocidad1;

            pos_ataca = pos2;
            pos_defiende = pos1;

            for(int i = 0; i < DIM_ARRAY_GOLPES; i++) golpes_ataca[i] = golpes2[i]; //Copiamos los golpes del tenista2

            tenista_defiende = TENISTA1;
        }
        lance(tenista_ataca, nombre1, habilidad_ataca, golpes_ataca, golpes_ganados_ataca, velocidad_defiende, pos_defiende, pos_bola, ganador_punto);
        cout << "Golpea " << nombre_ataca << endl << endl;
        pintar_peloteo(nombre1, nombre2, pos1, pos2, tenista_defiende, pos_bola);

        if(tenista_ataca == TENISTA1){
            tenista_ataca = TENISTA2;
            for(int i = 0; i < DIM_ARRAY_GOLPES; i++) golpes1[i] = golpes_ataca[i]; //Copiamos el golpe del lance a las stats del tenista1
        }else if(tenista_ataca == TENISTA2){
            tenista_ataca = TENISTA1;
            for(int i = 0; i < DIM_ARRAY_GOLPES; i++) golpes2[i] = golpes_ataca[i]; //Copiamos el golpe del lance a las stats del tenista2
        }
    }
    ganador_punto = NADIE;
}
void jugar_juego(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, int &juegos1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int &juegos2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_juego, t_puntos_juego &puntos1, t_puntos_juego &puntos2){
    //TODO: estoy pidiendo los puntos por parametros porque no se como meterlos en actualizar marcador
    t_tenista ganador_punto = NADIE;

    string servicio_s;
    servicio == TENISTA1 ? servicio_s = nombre1 : servicio_s = nombre2;

    cout << endl << "Servicio para " << servicio_s << endl;
    while(ganador_juego == NADIE){
        pintar_marcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, servicio);
        jugar_punto(servicio, nombre1, habilidad1, velocidad1, golpes1, golpes_ganados1, nombre2, habilidad2, velocidad2, golpes2, golpes_ganados2, ganador_punto);
        actualizar_marcador(ganador_punto, puntos1, puntos2, juegos1, juegos2, ganador_juego);
        if(servicio == TENISTA1)
            servicio = TENISTA2;
        else if(servicio == TENISTA2)
            servicio = TENISTA1;
    }
    mostrar_estadistica(TENISTA1, nombre1, golpes1, golpes_ganados1);
    mostrar_estadistica(TENISTA2, nombre2, golpes2, golpes_ganados2);
    string nombre_ganador;
    ganador_juego == TENISTA1 ? nombre_ganador = nombre1 : nombre_ganador = nombre2;
    cout << "El ganador del juego es " << nombre_ganador << endl;
    ganador_juego = NADIE;
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

    if(saque_inicial() == tenista1)
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
            cout << "Turno para " << nombre1 << endl;
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
            cout << "Turno para " << nombre2 << endl;
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