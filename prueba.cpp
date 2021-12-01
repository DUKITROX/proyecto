#include <iostream>
#include <iomanip>
using namespace std;

typedef enum {NADIE, TENISTA1, TENISTA2} t_tenista;
const int ANCHO_PISTA = 7;
const int LARGO_PISTA = 3;
const int DIM_ARRAY_GOLPES = ANCHO_PISTA + 2;
typedef int t_conteo_golpes [DIM_ARRAY_GOLPES];

void mostrar_estadistica(t_tenista tenista, string nombre, t_conteo_golpes golpes, int golpes_ganadores){
    int golpes_totales = 0, errores_no_forzados;
    double estadistica = 0;
    int caracteres_por_calle = 6, precision = 1;

    for(int i = 0; i < DIM_ARRAY_GOLPES ; i++) golpes_totales += golpes[i];
    errores_no_forzados = golpes[0] + golpes[DIM_ARRAY_GOLPES-1];

    cout << "Estadisticas de " << nombre << ":" << endl;
    cout << "   " << "Golpes totales: "<< golpes_totales << endl;
    cout << "   " << "Golpes ganadores: " << golpes_ganadores << endl;
    cout << "   " << "Errores no forzados: " << errores_no_forzados << endl;
    cout << "   " << "Distribucion de los golpes en la pista: " << endl;

    cout << setfill(' ') << setw(caracteres_por_calle*2) << "Calle";
    for(int i = 0; i < DIM_ARRAY_GOLPES; i++)                           //<-- Mostramos las calles
        cout << setfill(' ') << setw(caracteres_por_calle) << golpes[i];

    cout << endl << setfill(' ') << setw(caracteres_por_calle*2) << "%";
    for(int i = 0; i < DIM_ARRAY_GOLPES; i++){                          //<-- Mostramos las estadísticas por calle
        estadistica = (golpes[i] / double(golpes_totales)) * 100;
        cout << setfill(' ') << setw(caracteres_por_calle) << fixed << setprecision(precision) << estadistica;
    }
    
    cout << endl;
}

int main(){
    t_conteo_golpes golpes = {0,1,2,3,4,5,6,7,8};
    int golpes_ganadores = 12;
    mostrar_estadistica(TENISTA1, "DKT", golpes, golpes_ganadores);
    return 0;
}