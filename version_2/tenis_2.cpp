#include <iostream>
#include <string>
#include <ctime>
#include <iomanip> 
using namespace std;

const bool MODO_DEBUG = false, JUEGO_ALEATORIO = true;

const int MIN_HABILIDAD = 1, MAX_HABILIDAD = 3;
const int MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;
const int ANCHO_PISTA = 7, LARGO_PISTA = 3, JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;

typedef enum {NADIE, TENISTA1, TENISTA2} t_tenista;
typedef enum {NADA , QUINCE, TREINTA, CUARENTA, VENTAJA} t_puntos_juego;
typedef int t_conteo_golpes[DIM_ARRAY_GOLPES];

//Funciones para el inicio del partido
int introducirDato(string dato, int min_dato, int max_dato);
void introducir_tenista(string &iniciales, int &habilidad, int &velocidad);
t_tenista saque_inicial();

//Funciones relativas al marcador
string puntos_a_string(t_puntos_juego puntuacion);
void pintar_marcador(string nombre1, string nombre2, t_puntos_juego puntos1, t_puntos_juego puntos2, int juegos1, int juegos2, t_tenista servicio_para);
void pintar_marcador_final(string nombre1, string nombre2, int juegos1, int juegos2);
void sumar_punto(t_puntos_juego &puntos);
void actualizar_marcador(t_tenista ganador_punto, t_puntos_juego &puntos1, t_puntos_juego &puntos2, int &juegos1, int &juegos2, t_tenista &ganador_juego);

//Funciones relativas al juego
void lance(t_tenista tenista_que_golpea, string nombre, int habilidad, t_conteo_golpes golpes, int &golpes_ganados, int velocidad, int &pos_recibe, int &pos_bola, t_tenista &ganador_lance);
void jugar_punto(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_punto);
void jugar_juego(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, int &juegos1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int &juegos2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_juego);

//Funciones relativas a mostrar el partido graficamente
void pintar_iniciales(string iniciales, int pos_tenista);
void pintar_fila_fondo();
void pintar_campo_sin_bola();
void pintar_campo_con_bola(int pos_bola);
void pintar_fila_medio();
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);

//Funciones relativas a mostrar las estadisticas graficamente y revisar si el set ha concluido
void mostrar_estadistica(string nombre_tenista, t_conteo_golpes golpes_tenista, int golpes_ganadores);
void hay_ganador_set(int juegos1, int juegos2, t_tenista &ganador);

//Funciones sobre la funcionalidad del movimiento del tenista
int corre_tenista(int posicion_tenista, int velocidad, int posicion_bola);
int golpeo_bola(int posicion_tenista, int habilidad);

int main(){
    srand(time(NULL));
    string nombre1, nombre2;
    t_puntos_juego puntos1 = NADA, puntos2 = NADA;
    t_conteo_golpes golpes1 = {0}, golpes2 = {0};
    int golpes_ganados1 = 0, golpes_ganados2 = 0;
    int habilidad1, habilidad2, velocidad1, velocidad2, juegos1 = 0, juegos2 = 0;
    t_tenista ganador_juego = NADIE, ganador_set = NADIE;
    t_tenista servicio = saque_inicial();

    cout << endl << "Bienvenidos al simulador de partidos de tenis" << endl;

    //Datos tenista 1
    cout << endl << "Datos del tenista 1" << endl;
    introducir_tenista(nombre1, habilidad1, velocidad1);

    //Datos tenista 2
    cout << endl << "Datos del tenista 2" << endl;
    introducir_tenista(nombre2, habilidad2, velocidad2);

    //Juego
    while(ganador_set == NADIE){
        jugar_juego(servicio, nombre1, habilidad1, velocidad1, juegos1, golpes1, golpes_ganados1, nombre2, habilidad2, velocidad2, juegos2, golpes2, golpes_ganados2, ganador_juego);
        servicio == TENISTA1 ? servicio = TENISTA2 : servicio = TENISTA1;
        hay_ganador_set(juegos1, juegos2, ganador_set);
    }
    pintar_marcador_final(nombre1, nombre2, juegos1, juegos2);
    string nombre_ganador;
    ganador_set == TENISTA1 ? nombre_ganador = nombre1 : nombre_ganador = nombre2;
    cout << nombre_ganador << " se hizo con el partido" << endl << endl << "Gracias por jugar" << endl << endl;
    
    return 0;
}

//Funciones para el inicio del partido
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

//Funciones relativas al marcador
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
void pintar_marcador_final(string nombre1, string nombre2, int juegos1, int juegos2){
    cout << endl << "   " << nombre1 << " " << juegos1 << endl;
    cout << "   " << nombre2 << " " << juegos2 << endl << endl;
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

    if(puntos1 == VENTAJA && int(puntos2) < int(CUARENTA)){ //Gana el tenista 1 sin necesidad de ventaja
        ganador_juego = TENISTA1;
        juegos1++;
    }else if(puntos2 == VENTAJA && int(puntos1) < int(CUARENTA)){ //Gana el tenista 2 sin necesidad de ventaja
        ganador_juego = TENISTA2;
        juegos2++;
    }else if(puntos1 == VENTAJA && puntos2 == VENTAJA){ //Se igualan a 40 los marcadores por estar en ventaja ambos
        puntos1 = CUARENTA;
        puntos2 = CUARENTA;
    }else if(int(puntos1) == int(VENTAJA) + 1){ //Gana el tenista 1 tras estar en ventaja
        ganador_juego = TENISTA1;
        juegos1++;
    }else if(int(puntos2) == int(VENTAJA) + 1){  //Gana el tenista 2 tras estar en ventaja
        ganador_juego = TENISTA2;
        juegos2++;
    }
}

//Funciones relativas al juego
void lance(t_tenista tenista_que_golpea, string nombre, int habilidad, t_conteo_golpes golpes, int &golpes_ganados, int velocidad, int &pos_recibe, int &pos_bola, t_tenista &ganador_lance){
    ganador_lance = NADIE;
    if(JUEGO_ALEATORIO)
        //Si estas en windows comentas {cin.get();} y descomentas {system("pause");}
        //En caso de mac al reves, comentas {system("pause");}, y descomentas {cin.get();}
        //Esto es para que todos los golpes del partido no te salgan de golpe, sino que salgan uno a uno
        //system("pause");
        cin.get();

    cout << "Golpea " << nombre << endl << endl;
    pos_bola = golpeo_bola(pos_bola, habilidad);
    golpes[pos_bola]++;
    if(0 < pos_bola && pos_bola <= ANCHO_PISTA){
        //la bola entra dentro
        pos_recibe = corre_tenista(pos_recibe, velocidad, pos_bola);
        if(pos_recibe != pos_bola){
            ganador_lance = tenista_que_golpea; // el tenista que defiende no llega a la bola
            golpes_ganados++;
        }
        
    }else{
        if(tenista_que_golpea == TENISTA1) ganador_lance = TENISTA2;
        else ganador_lance = TENISTA1;
    }
}
void jugar_punto(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_punto){
    ganador_punto = NADIE;
    t_tenista tenista_ataca = servicio;

    int medio_campo = ANCHO_PISTA / 2 + 1;
    int pos1 = medio_campo, pos2 = medio_campo, pos_bola = medio_campo;
    
    while(ganador_punto == NADIE){
        if(tenista_ataca == TENISTA1){
            lance(TENISTA1, nombre1, habilidad1, golpes1, golpes_ganados1, velocidad2, pos2, pos_bola, ganador_punto);
            pintar_peloteo(nombre1, nombre2, pos1, pos2, TENISTA1, pos_bola);
            tenista_ataca = TENISTA2;
        }else{
            lance(TENISTA2, nombre2, habilidad2, golpes2, golpes_ganados2, velocidad1, pos1, pos_bola, ganador_punto);
            pintar_peloteo(nombre1, nombre2, pos1, pos2, TENISTA2, pos_bola);
            tenista_ataca = TENISTA1;
        }
    }
}
void jugar_juego(t_tenista servicio, string nombre1, int habilidad1, int velocidad1, int &juegos1, t_conteo_golpes golpes1, int &golpes_ganados1, string nombre2, int habilidad2, int velocidad2, int &juegos2, t_conteo_golpes golpes2, int &golpes_ganados2, t_tenista &ganador_juego){
    ganador_juego = NADIE;
    t_tenista ganador_punto = NADIE;
    t_puntos_juego puntos1 = NADA, puntos2 = NADA;

    string servicio_s, ganador_punto_s;
    servicio == TENISTA1 ? servicio_s = nombre1 : servicio_s = nombre2;
    cout << endl << "Servicio para " << servicio_s << endl;

    pintar_marcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, servicio);

    while(ganador_juego == NADIE){
        jugar_punto(servicio, nombre1, habilidad1, velocidad1, golpes1, golpes_ganados1, nombre2, habilidad2, velocidad2, golpes2, golpes_ganados2, ganador_punto);
        ganador_punto == TENISTA1 ? ganador_punto_s = nombre1 : ganador_punto_s = nombre2;
        cout << "El ganador del punto es " << ganador_punto_s << endl;

        actualizar_marcador(ganador_punto, puntos1, puntos2, juegos1, juegos2, ganador_juego);
        if(ganador_juego == NADIE)
            pintar_marcador(nombre1, nombre2, puntos1, puntos2, juegos1, juegos2, servicio);
    }
    mostrar_estadistica(nombre1, golpes1, golpes_ganados1);
    mostrar_estadistica(nombre2, golpes2, golpes_ganados2);

    string ganador_juego_s;
    ganador_juego == TENISTA1 ? ganador_juego_s = nombre1 : ganador_juego_s = nombre2;
    cout << endl << "El ganador del juego es " << ganador_juego_s << endl;
}

//Funciones relativas a mostrar el partido graficamente
void pintar_inciales(string iniciales, int pos_tenista){
    cout << " ";
    for(int i = 1; i < pos_tenista; i++) {
        cout << "  ";
        }
    cout << iniciales << endl;
}
void pintar_fila_fondo(){
    cout << " ";
    for(int i = 0; i < ANCHO_PISTA; i++){
        cout << " -";
    }
    cout << endl;
}
void pintar_campo_sin_bola(){
    for(int i = 0; i <= ANCHO_PISTA; i++) cout << " |";
    cout << endl;
}
void pintar_campo_con_bola(int pos_bola){
    for(int i = 0; i <= ANCHO_PISTA; i++){
        if(i == pos_bola) 
            cout << "o|";
        else
            cout << " |";
    }
    if(pos_bola == ANCHO_PISTA+1) cout << "o";
    cout << endl;
}
void pintar_fila_medio(){
    cout << "-";
    for(int i = 1; i <= ANCHO_PISTA; i++) {
        cout << "-" << i;
        }
    cout << "--" << endl;
}
void pintar_peloteo(string nombre1, string nombre2, int pos1, int pos2, t_tenista tenista, int pos_bola){
    pintar_inciales(nombre1, pos1);
    pintar_fila_fondo();

    if(tenista == TENISTA1){
        for(int i = 0; i < LARGO_PISTA; i++) pintar_campo_sin_bola();
    }else{
        pintar_campo_con_bola(pos_bola);
        for(int i = 0; i < LARGO_PISTA - 1; i++) pintar_campo_sin_bola();
    }

    pintar_fila_medio();

    if(tenista == TENISTA1){
        for(int i = 0; i < LARGO_PISTA - 1; i++) pintar_campo_sin_bola();
        pintar_campo_con_bola(pos_bola);
    }else{
        for(int i = 0; i < LARGO_PISTA; i++) pintar_campo_sin_bola();
    }
    pintar_fila_fondo();
    pintar_inciales(nombre2, pos2);
    cout << endl;
}

//Funciones relativas a mostrar las estadisticas graficamente y revisar si el set ha concluido
void mostrar_estadistica(string nombre, t_conteo_golpes golpes, int golpes_ganadores){
    int golpes_totales = 0, errores_no_forzados;
    double estadistica = 0;
    int caracteres_por_calle = 6, precision = 1;

    for(int i = 0; i < DIM_ARRAY_GOLPES ; i++) golpes_totales += golpes[i];
    errores_no_forzados = golpes[0] + golpes[DIM_ARRAY_GOLPES-1];

    cout << endl;
    cout << "Estadisticas de " << nombre << endl;
    cout << "   " << "Golpes totales: "<< golpes_totales << endl;
    cout << "   " << "Golpes ganadores: " << golpes_ganadores << endl;
    cout << "   " << "Errores no forzados: " << errores_no_forzados << endl;
    cout << "   " << "Distribucion de los golpes en la pista " << endl;

    cout << setfill(' ') << setw(caracteres_por_calle*2) << "Calle";
    for(int i = 0; i < DIM_ARRAY_GOLPES; i++)                           //<-- Mostramos las calles
        cout << setfill(' ') << setw(caracteres_por_calle) << i;

    cout << endl << setfill(' ') << setw(caracteres_por_calle*2) << "%";
    for(int i = 0; i < DIM_ARRAY_GOLPES; i++){                          //<-- Mostramos las estadísticas por calle
        estadistica = (golpes[i] / double(golpes_totales) * 100);
        cout << setfill(' ') << setw(caracteres_por_calle) << fixed << setprecision(precision) << estadistica;
    }
    cout << endl;
}
void hay_ganador_set(int juegos1, int juegos2, t_tenista &ganador){
    ganador = NADIE;
    if(juegos1 - juegos2 >= 2 && juegos1 + juegos2 >= JUEGOS_SET)
        ganador = TENISTA1;
    else if(juegos2 - juegos1 >= 2 && juegos1 + juegos2 >= JUEGOS_SET)
        ganador = TENISTA2;
}

//Funciones sobre la funcionalidad del movimiento del tenista
int corre_tenista(int posicion_tenista, int velocidad, int pos_bola){
    int distancia = abs(posicion_tenista - pos_bola);
    int posicion_final;

    if(distancia <= velocidad){
        if(MODO_DEBUG)
            cout << "Su rival llega a la bola" << endl << endl;
        posicion_final = pos_bola;

    }else{
        if(MODO_DEBUG)
            cout << "Su rival no llega a la bola" << endl << endl;

        if(posicion_tenista < pos_bola)
            posicion_final = posicion_tenista + velocidad;
        else
            posicion_final = posicion_tenista - velocidad;
    }
    return posicion_final;
}
int golpeo_bola(int posicion_tenista, int habilidad){
    int destino_bola, distancia;

    if(MODO_DEBUG)
        cout << endl << "El jugador dispara hacia la calle ";

    if(JUEGO_ALEATORIO){ //El propio elije programa a donde dispara la bola
        destino_bola = (rand()%ANCHO_PISTA) + 1;
        if(MODO_DEBUG)
            cout << destino_bola << endl;
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
            int random_fuera = rand()%2;
            if(random_fuera == 0) 
                destino_bola--;
            else 
                destino_bola++;

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