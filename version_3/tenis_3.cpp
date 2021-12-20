#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
using namespace std;

//TODO:
//funcion cargar: hace falta con aux?
//funcion jugar partido
//funcion jugar torneo
//funcoin top4
//main
//funcion pedir_tenista
//para la funcion guardar, lo que yo hago es eliminar todo lo que haya dentro y metrs lo nuevo, esta bien asi? o hay que simplemente añadir?


const bool MODO_DEBUG = false, JUEGO_ALEATORIO = true;

const int MIN_HABILIDAD = 1, MAX_HABILIDAD = 3;
const int MIN_VELOCIDAD = 1, MAX_VELOCIDAD = 5;
const int ANCHO_PISTA = 7, LARGO_PISTA = 3, JUEGOS_SET = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
const int DIM_ARRAY_TENISTAS = 10;

typedef enum {NADIE, TENISTA1, TENISTA2} t_tenista;
typedef enum {NADA , QUINCE, TREINTA, CUARENTA, VENTAJA} t_puntos_juego;
typedef int t_conteo_golpes[DIM_ARRAY_GOLPES];


struct t_datos_partido{
    int posicion = ANCHO_PISTA / 2 + 1;
    t_puntos_juego puntos = NADA;
    int juegos = 0;
    int golpes_ganadores = 0;
    t_conteo_golpes golpes = {0};
};
struct t_datos_tenista {
    string iniciales;
    int habilidad;
    int velocidad;
    int partidos_ganados = 0;
    int partidos_perdidos = 0;
    t_datos_partido partido;
};
struct t_lista_tenistas {
    t_datos_tenista tenistas[DIM_ARRAY_TENISTAS];
    int contador = 0;
};

//Funciones para el menu
void mostrar_menu(int &opcion); //TODO: quitar funciones de opciones

//Funciones para manejar tenistas
bool cargar(t_lista_tenistas &lista_t);
void guardar(const t_lista_tenistas &lista_t);
void eliminar_tenista(t_lista_tenistas &lista_t, string iniciales);
int buscar_iniciales(const t_lista_tenistas &lista_t, string iniciales);
int pedir_tenista(const t_lista_tenistas &lista_t, int num);
void seleccionarTop4(const t_lista_tenistas &lista_t, int &ind_t1, int &ind_t2, int &ind_t3, int &ind_t4);

//Funciones para el inicio del partido
string introducir_iniciales();
int introducir_dato(string dato, int min_dato, int max_dato);
void introducir_tenista(t_lista_tenistas &lista_t);
t_tenista saque_inicial();

//Funciones relativas al marcador
string puntos_a_string(t_puntos_juego puntuacion);
void pintar_marcador(string iniciales1, string iniciales2, const t_datos_partido &datos_t1, const t_datos_partido &datos_t2, t_tenista servicio_para);
void pintar_marcador_final(string nombre1, string nombre2, int juegos1, int juegos2);
void sumar_punto(t_puntos_juego &puntos);
void actualizar_marcador(t_tenista ganador_punto, t_datos_partido &datos_t1, t_datos_partido &datos_t2, t_tenista &ganador_juego);

//Funciones relativas al juego
void lance(t_tenista bola_para, t_datos_tenista &tenista_golpea, t_datos_tenista &tenista_recibe, int &pos_bola, t_tenista &ganador_lance);
void jugar_punto(t_datos_tenista &tenista1, t_datos_tenista &tenista2, t_tenista servicio_para, t_tenista &ganador_punto);
void jugar_juego(t_datos_tenista &tenista1, t_datos_tenista &tenista2, t_tenista servicio_para, t_tenista &ganador_juego);
void jugar_partido(t_datos_tenista &tenista1, t_datos_tenista &tenista2, t_tenista& ganador_partido);
void jugar_torneo(t_lista_tenistas &lista_t, int ind_t1, int ind_t2, int ind_t3, int ind_t4);

//Funciones relativas a mostrar el partido graficamente
void pintar_iniciales(string iniciales, int pos_tenista);
void pintar_fila_fondo();
void pintar_campo_sin_bola();
void pintar_campo_con_bola(int pos_bola);
void pintar_fila_medio();
void pintar_peloteo(string nombre1, string nombre2, int pos_t1, int pos_t2, t_tenista bola_jugador, int pos_bola);

//Funciones para mostrar tenistas
void mostrar(const t_lista_tenistas lista_t);
void mostrar_iniciales(const t_lista_tenistas lista_t);

//Funciones relativas a mostrar las estadisticas graficamente y revisar si el set ha concluido
void mostrar_estadistica(string nombre_tenista, t_conteo_golpes golpes_tenista, int golpes_ganadores);
void hay_ganador_set(int juegos1, int juegos2, t_tenista &ganador);

//Funciones sobre la funcionalidad del movimiento del tenista
int corre_tenista(int posicion_tenista, int velocidad, int posicion_bola);
int golpeo_bola(int posicion_tenista, int habilidad);

int main(){
    srand(time(NULL));
    t_lista_tenistas lista_t;
    cargar(lista_t); //Cargamos los tenistas del fichero
    int opcion = -1;
    while(opcion != 0){
        mostrar_menu(opcion);
        switch (opcion){
        case 1:
            mostrar(lista_t);
            break;
        case 2:
            introducir_tenista(lista_t);
            break;
        case 3:{
            mostrar_iniciales(lista_t);
            string inciales;
            cout << "Introducir las inciales del tenista a eliminar: ";
            cin >> inciales;
            while(buscar_iniciales(lista_t, iniciales) == -1){
                cout << "   No existe ningun tenista con esas iniciales" << endl;
                cout << "Introducir las inciales del tenista a eliminar: ";
                cin >> iniciales;
            }
            eliminar_tenista(lista_t, iniciales);
            break;
        }
        case 4:{
            int posicion1, posicion2;
            posicion1 = pedir_tenista(lista_t, 1);
            posicion2 = pedir_tenista(lista_t, 2);
            while(posicion1 == posicion2){
                cout << "   Tenista repetido. Elija otro" << endl;
                posicion2 = pedir_tenista(lista_t, 2);
            }
            t_tenista ganador_partido;

            jugar_partido(lista_t.tenistas[posicion1], lista_t.tenistas[posicion2], ganador_partido);
            break;
        }
        case 5:{
            int posicion1, posicion2, posicion3, posicion4;
            if(lista_t.contador < 4)
                cout << "No hay suficientes tenistas para un torneo"
            else{
                posicion1 = pedir_tenista(lista_t, 1);
                posicion2 = pedir_tenista(lista_t, 2);
                while(posicion1 == posicion2){
                    cout << "   Tenista repetido. Elija otro" << endl;
                    posicion2 = pedir_tenista(lista_t, 2);
                }
                posicion3 = pedir_tenista(lista_t, 3);
                while(posicion3 == posicion1 || posicion3 == posicion2){
                    cout << "   Tenista repetido. Elija otro" << endl;
                    posicion3 = pedir_tenista(lista_t, 3);
                }
                posicion4 = pedir_tenista(lista_t, 4);
                while(posicion4 == posicion1 || posicion4 == posicion2 || posicion4 == posicion3){
                    cout << "   Tenista repetido. Elija otro" << endl;
                    posicion4 = pedir_tenista(lista_t, 4);
                }

                jugar_torneo(lista_t, posicion1, posicion2, posicion3, posicion4);
            }
            break;
        }
        case 6:
            int posicion1, posicion2, posicion3, posicion4;
            seleccionarTop4(lista_t, posicion1, posicion2, posicion3, posicion4);
            jugar_torneo(lista_t, posicion1, posicion2, posicion3, posicion4);
        }
    }
    guardar(lista_t);
    return 0;
}
//Funciones para el menu
void mostrar_menu(int &opcion){
    cout << "<1> Ver datos tenistas" << endl;
    cout << "<2> Nuevo tenista" << endl;
    cout << "<3> Eliminar tenista" << endl;
    cout << "<4> Jugar partido" << endl;
    cout << "<5> Torneo semifinales/finales" << endl;
    cout << "<6> Torneo top-4" << endl;
    cout << "<0> Salir" << endl << endl;
    cout << "Opcion: ";
    cin >> opcion;
}

//Funciones para manejar tenistas
bool cargar(t_lista_tenistas &lista_t){
    //TODO: asi esta bien? o mejor cargar con un archivo auxiliar?
    bool ok = false;
    ifstream archivo;
    char aux;

    archivo.open("tenistas.txt");

    if(archivo.is_open()){
        ok = true;
        while(!archivo.eof() && lista_t.contador < DIM_ARRAY_TENISTAS){
            archivo >> lista_t.tenistas[lista_t.contador].iniciales;
            archivo >> lista_t.tenistas[lista_t.contador].habilidad;
            archivo >> lista_t.tenistas[lista_t.contador].velocidad;
            archivo >> lista_t.tenistas[lista_t.contador].partidos_ganados;
            archivo >> lista_t.tenistas[lista_t.contador].partidos_perdidos;
            archivo.get(aux);
            lista_t.contador++;
        }
    }else{
        //TODO: poner mensaje en caso de que no se haya podido abrir el archivo
    }
    archivo.close();
    return ok;
}
void guardar(const t_lista_tenistas &lista_t){
    //TODO: con los tenistas que ya hay cargados que se hace?
    ofstream archivo;
    archivo.open("tenistas.txt", ofstream::out | ofstream::trunc);  //se haria eso?
    for(int i = 0; i < lista_t.contador; i++){
        archivo << lista_t.tenistas[i].iniciales << " ";
        archivo << lista_t.tenistas[i].habilidad << " ";
        archivo << lista_t.tenistas[i].velocidad << " ";
        archivo << lista_t.tenistas[i].partidos_ganados << " ";
        archivo << lista_t.tenistas[i].partidos_perdidos << endl;
    }
    cout << "\r\b";
    archivo.close();
}
int buscar_iniciales(const t_lista_tenistas &lista_t, string iniciales){
    int posicion = 0;
    while((lista_t.tenistas[posicion].iniciales != iniciales) && (posicion < lista_t.contador))
        posicion++;
    if(lista_t.tenistas[posicion].iniciales != iniciales)
        posicion = -1;
    return posicion;
}
void eliminar_tenista(t_lista_tenistas &lista_t, string iniciales){
    int posicion = buscar_iniciales(lista_t, iniciales);
    if(posicion != -1){
        for(int i = posicion; i < lista_t.contador - 1; i++){
            lista_t.tenistas[i] = lista_t.tenistas[i+1];
        }
        lista_t.contador--;
        cout << "   Tenista eliminado correctamente" << endl << endl;
    }else{
        cout << "   No existe ningun tenista con esas inciales" << endl << endl;
    }
}
int pedir_tenista(const t_lista_tenistas &lista_t, int num){
    //TODO: revisar esta funcion
    int posicion = -1;
    string iniciales;
    do{
        cout << "Introduce las iniciales del tenista " << num << " : ";
        cin >> iniciales;
        posicion = buscar_iniciales(lista_t, iniciales);
    }while(posicion == -1);
    return posicion;
}
void seleccionarTop4(const t_lista_tenistas &lista_t, int &ind_t1, int &ind_t2, int &ind_t3, int &ind_t4){
    int primero = -1, segundo, tercero, cuarto;
    for(int i = 0; i < TENISTAS.contador; i++){
        if(TENISTAS.elementos[i].partidos_ganados >= primero){
            cuarto = tercero;
            tercero = segundo;
            segundo = primero;
            primero = TENISTAS.elementos[i].partidos_ganados;

            indT4 = indT3;
            indT3 = indT2;
            indT2 = indT1;
            indT1 = i;

        }else if(TENISTAS.elementos[i].partidos_ganados >= segundo){
            cuarto = tercero;
            tercero = segundo;
            segundo = TENISTAS.elementos[i].partidos_ganados;

            indT4 = indT3;
            indT3 = indT2;
            indT2 = i;

        }else if(TENISTAS.elementos[i].partidos_ganados >= tercero){
            cuarto = tercero;
            tercero = TENISTAS.elementos[i].partidos_ganados;

            indT4 = indT3;
            indT3 = i;

        }else if(TENISTAS.elementos[i].partidos_ganados >= cuarto){
            cuarto = TENISTAS.elementos[i].partidos_ganados;

            indT4 = i;
        }
    }
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
void introducir_tenista(t_lista_tenistas &lista_t){
    string iniciales;
    if(lista_t.contador < 10){
        lista_t.tenistas[lista_t.contador].iniciales = introducir_iniciales();
        lista_t.tenistas[lista_t.contador].habilidad = introducir_dato("habilidad", MIN_HABILIDAD, MAX_HABILIDAD);
        lista_t.tenistas[lista_t.contador].velocidad = introducir_dato("velocidad", MIN_VELOCIDAD, MAX_VELOCIDAD);
        cout << "Nuevo tenista creado" << endl << endl;
        lista_t.contador++;
    }
}
string introducir_iniciales(){
    string iniciales;
    cout << "   >Introduce sus iniciales (3 letras): ";
    while(iniciales.length() != 3){
        cout << "   >Iniciales de solo 3 caracteres, vuelva a introducirlas: ";
        cin >> inciales;
    }
    return iniciales;
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
void pintar_marcador(string iniciales1, string iniciales2, const t_datos_partido &datos_t1, const t_datos_partido &datos_t2, t_tenista servicio_para){

    cout << endl << "   " << iniciales1 << "  " << datos_t1.juegos << " : " << puntos_a_string(datos_t1.puntos) << " ";
    if(servicio_para == TENISTA1) cout << '*';

    cout << endl << "   " << iniciales2 << "  " << datos_t2.juegos << " : " << puntos_a_string(datos_t2.puntos) << " ";
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
void actualizar_marcador(t_tenista ganador_punto, t_datos_partido &datos_t1, t_datos_partido &datos_t2, t_tenista &ganador_juego){
    if(ganador_punto == TENISTA1)
        sumar_punto(datos_t1.puntos);
    else
        sumar_punto(datos_t2.puntos);

    if(datos_t1.puntos == VENTAJA && int(datos_t2.puntos) < int(CUARENTA)){ //Gana el tenista 1 sin necesidad de ventaja
        ganador_juego = TENISTA1;
        datos_t1.juegos++;
    }else if(datos_t2.puntos == VENTAJA && int(datos_t1.puntos) < int(CUARENTA)){ //Gana el tenista 2 sin necesidad de ventaja
        ganador_juego = TENISTA2;
        datos_t2.juegos++;
    }else if(datos_t1.puntos == VENTAJA && datos_t2.puntos == VENTAJA){ //Se igualan a 40 los marcadores por estar en ventaja ambos
        datos_t1.puntos = CUARENTA;
        datos_t2.puntos = CUARENTA;
    }else if(int(datos_t1.puntos) == int(VENTAJA) + 1){ //Gana el tenista 1 tras estar en ventaja
        ganador_juego = TENISTA1;
        datos_t1.juegos++;
    }else if(int(datos_t2.puntos) == int(VENTAJA) + 1){  //Gana el tenista 2 tras estar en ventaja
        ganador_juego = TENISTA2;
        datos_t2.juegos++;
    }
}

//Funciones relativas al juego
void lance(t_tenista bola_para, t_datos_tenista &tenista_golpea, t_datos_tenista &tenista_recibe, int &pos_bola, t_tenista &ganador_lance){
    //TODO: ver si la funcion lance esta bien hecha así, sobre el tema del ganador del lance
    ganador_lance = NADIE;
    if(JUEGO_ALEATORIO)
        //Si estas en windows comentas {cin.get();} y descomentas {system("pause");}
        //En caso de mac al reves, comentas {system("pause");}, y descomentas {cin.get();}
        //Esto es para que todos los golpes del partido no te salgan de golpe, sino que salgan uno a uno
        //system("pause");
        cin.get();

    t_tenista tenista_ataca = bola_para;//TODO: preguntar sobre esta parte
    t_tenista tenista_defiende;
    if(tenista_ataca == TENISTA1)
        tenista_defiende = TENISTA2;
    else
        tenista_defiende = TENISTA1;

    cout << "Golpea " << tenista_golpea.iniciales << endl << endl;
    pos_bola = golpeo_bola(pos_bola, tenista_golpea.habilidad);
    tenista_golpea.partido.golpes[pos_bola]++;
    if(0 < pos_bola && pos_bola <= ANCHO_PISTA){
        //la bola entra dentro
        tenista_recibe.partido.posicion = corre_tenista(tenista_recibe.partido.posicion, tenista_recibe.velocidad, pos_bola);
        if(tenista_recibe.partido.posicion != pos_bola){ // el tenista que defiende no llega a la bola
            ganador_lance = tenista_ataca;
            tenista_golpea.partido.golpes_ganadores++;
        }
    }else{
        ganador_lance = tenista_defiende;
    }
}
void jugar_punto(t_datos_tenista &tenista1, t_datos_tenista &tenista2, t_tenista servicio_para, t_tenista &ganador_punto){
    ganador_punto = NADIE;
    t_tenista tenista_ataca = servicio_para;

    int medio_campo = ANCHO_PISTA / 2 + 1;
    int pos_bola = medio_campo;
    tenista1.partido.posicion = medio_campo, tenista2.partido.posicion = medio_campo;
    
    while(ganador_punto == NADIE){
        if(tenista_ataca == TENISTA1){
            lance(TENISTA1, tenista1, tenista2, pos_bola, ganador_punto);
            pintar_peloteo(tenista1.iniciales, tenista2.iniciales, tenista1.partido.posicion, tenista2.partido.posicion, TENISTA1, pos_bola);
            tenista_ataca = TENISTA2;
        }else{
            lance(TENISTA2, tenista2, tenista1, pos_bola, ganador_punto);
            pintar_peloteo(tenista1.iniciales, tenista2.iniciales, tenista1.partido.posicion, tenista2.partido.posicion, TENISTA2, pos_bola);
            tenista_ataca = TENISTA1;
        }
    }
}
void jugar_juego(t_datos_tenista &tenista1, t_datos_tenista &tenista2, t_tenista servicio_para, t_tenista &ganador_juego){
    ganador_juego = NADIE;
    t_tenista ganador_punto = NADIE;
    t_puntos_juego puntos1 = NADA, puntos2 = NADA;

    string servicio_s, ganador_punto_s;
    servicio_para == TENISTA1 ? servicio_s = tenista1.iniciales : servicio_s = tenista2.iniciales;
    cout << endl << "Servicio para " << servicio_s << endl;

    tenista1.partido.puntos = NADA;
    tenista2.partido.puntos = NADA;

    pintar_marcador(tenista1.iniciales, tenista2.iniciales, tenista1.partido, tenista2.partido, servicio_para);

    while(ganador_juego == NADIE){
        jugar_punto(tenista1, tenista2, servicio_para, ganador_punto);
        ganador_punto == TENISTA1 ? ganador_punto_s = tenista1.iniciales : ganador_punto_s = tenista2.iniciales;
        cout << "El ganador del punto es " << ganador_punto_s << endl;

        actualizar_marcador(ganador_punto, tenista1.partido, tenista2.partido, ganador_juego);
        if(ganador_juego == NADIE)
            pintar_marcador(tenista1.iniciales, tenista2.iniciales, tenista1.partido, tenista2.partido, servicio_para);
    }
    mostrar_estadistica(tenista1.iniciales, tenista1.partido.golpes, tenista1.partido.golpes_ganadores);
    mostrar_estadistica(tenista2.iniciales, tenista2.partido.golpes, tenista2.partido.golpes_ganadores);

    string ganador_juego_s;
    ganador_juego == TENISTA1 ? ganador_juego_s = tenista1.iniciales : ganador_juego_s = tenista2.iniciales;
    cout << endl << "El ganador del juego es " << ganador_juego_s << endl;
}
void jugar_partido(t_datos_tenista &tenista1, t_datos_tenista &tenista2, t_tenista& ganador_partido){
    t_tenista servicio_para = saque_inicial();
    t_tenista ganador_partido = NADIE, ganador_juego = NADIE;
    while(ganador_partido == NADIE){
        jugar_juego(tenista1, tenista2, servicio_para, ganador_juego);
        servicio_para == TENISTA1 ? servicio_para = TENISTA2 : servicio_para = TENISTA1;
        hay_ganador_set(tenista1.partido.juegos, tenista2.partido.juegos, ganador_partido);
    }
    if(ganador_partido == TENISTA1){
        tenista1.partidos_ganados++;
        tenista2.partidos_perdidos++;
    }else{
        tenista1.partidos_perdidos++;
        tenista2.partidos_ganados++;
    }
    pintar_marcador_final(tenista1.iniciales, tenista2.iniciales, tenista1.partido.juegos, tenista2.partido.juegos);
    string nombre_ganador;
    ganador_set == TENISTA1 ? nombre_ganador = tenista1.iniciales : nombre_ganador = tenista2.iniciales;
    cout << nombre_ganador << " se hizo con el partido" << endl << endl << "Gracias por jugar" << endl << endl;
}
void jugar_torneo(t_lista_tenistas &lista_t, int ind_t1, int ind_t2, int ind_t3, int ind_t4){
    t_datos_tenista tenista1, tenista2, tenista3, tenista4, finalista1, finalista2;
    tenista1 = lista_t.tenistas[ind_t1];
    tenista2 = lista_t.tenistas[ind_t2];
    tenista3 = lista_t.tenistas[ind_t2];
    tenista4 = lista_t.tenistas[ind_t3];

    t_tenista ganador1 = NADIE, ganador2 = NADIE, ganador_torneo = NADIE;

    cout << "* Primera semifinal: " << tenista1.iniciales << " vs " << tenista4.iniciales << " *" << endl;
    cout << "* Segunda semifinal: " << tenista2.iniciales << " vs " << tenista3.iniciales << " *" << endl << endl;
    cout << "* COMIENZA EL TORNEO *" << endl << endl;

    //PRIMERA SEMIFINAL
    cout << "* Primera semifinal: " << tenista1.iniciales << " vs " << tenista4.iniciales << " *" << endl;
    jugar_partido(tenista1, tenista4, ganador1);
    lista_t.tenistas[ind_t1] = tenista1; //Volvemos a guardar los auxiliares en la lista principal TODO: esta bien asi?
    lista_t.tenistas[ind_t4] = tenista4;
    if(ganador1 == TENISTA1)
        finalista1 = tenista1;
    else
        finalista1 = tenista4;
    cout << "* CAMPEON PRIMERA SEMIFINAL: " << finalista1.iniciales << " *" << endl << endl;

    //SEGUNDA SEMIFINAL
    cout << "* Segunda semifinal: " << tenista2.iniciales << " vs " << tenista3.iniciales << " *" << endl << endl;
    jugar_partido(tenista2, tenista3, ganador2);
    lista_t.tenistas[ind_t2] = tenista2; //Volvemos a guardar los auxiliares en la lista principal 
    lista_t.tenistas[ind_t3] = tenista3;
    if(ganador2 == TENISTA1)
        finalista2 = tenista2;
    else
        finalista2 = tenista3;
    cout << "* CAMPEON SEGUNDA SEMIFINAL: " << finalista2.inciales << " *" << endl << endl;

    //FINAL
    string iniciales_ganador;
    cout << "* Gran final: " << finalista1.inciales << " vs " << finalista2.iniciales << " *" << endl << endl;
    jugar_partido(finalista1, finalista2, ganador_torneo);

    int ind_f1, ind_f2;
    ind_f1 = buscar_iniciales(finalista1.inciales); //TODO: esta parte esta bien asi??
    ind_f2 = buscar_iniciales(finalista2.iniciales);
    lista_t.tenistas[ind_f1] = finalista1;
    lista_t.tenistas[ind_f2] = finalista2;

    if(ganador_torneo == TENISTA1)
        iniciales_ganador = finalista1.inciales;
    else
        iniciales_ganador = finalista2.iniciales;
    cout << "* CAMPEON DEL TORNEO : " << iniciales_ganador << " *" << endl << endl;
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

//Funciones para mostrar tenistas
void mostrar(const t_lista_tenistas lista_t){ //Formato tabla
    int caracteres_por_dato = 5;

    cout << endl << setfill(' ') << setw(caracteres_por_dato) << "INI";
    cout << setfill(' ') << setw(caracteres_por_dato) << "HAB";
    cout << setfill(' ') << setw(caracteres_por_dato) << "VEL";
    cout << setfill(' ') << setw(caracteres_por_dato) << "PG";
    cout << setfill(' ') << setw(caracteres_por_dato) << "PP" << endl;
    for(int i = 0; i < lista_t.contador; i++){
        cout << setfill(' ') << setw(caracteres_por_dato) << lista_t.tenistas[i].iniciales;
        cout << setfill(' ') << setw(caracteres_por_dato) << lista_t.tenistas[i].habilidad;
        cout << setfill(' ') << setw(caracteres_por_dato) << lista_t.tenistas[i].velocidad;
        cout << setfill(' ') << setw(caracteres_por_dato) << lista_t.tenistas[i].partidos_ganados;
        cout << setfill(' ') << setw(caracteres_por_dato) << lista_t.tenistas[i].partidos_perdidos << endl;
    }
    cout << endl;
}
void mostrar_iniciales(const t_lista_tenistas lista_t){
    cout << "Iniciales de los tenistas:  ";
    for(int i = 0; i < lista_t.contador; i++){
        cout << lista_t.tenistas[i].iniciales << " - ";
    }
    cout << "\b\b " << endl << endl;
}

//Funciones relativas a mostrar las estadisticas graficamente y revisar si el set ha concluido
void mostrar_estadistica(string nombre, const t_conteo_golpes golpes, int golpes_ganadores){
    int golpes_totales = 0, errores_no_forzados;
    double estadistica = 0;
    int caracteres_por_calle = 6, precision = 1;

    for(int i = 0; i < DIM_ARRAY_GOLPES ; i++){
        golpes_totales += golpes[i];
    }

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