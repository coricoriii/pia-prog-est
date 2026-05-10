#include <iostream>
#include <string>
#include "boxeadores.h"
#include "emparejamientos.h"
#include "reportes.h"
#include "validaciones.h"
#include "graficas.h"

using namespace std;

void menuGestion() {
    int op;
    do {
        cout << "\n========== GESTION DE BOXEADORES ==========" << endl;
        cout << "1. Agregar boxeador"             << endl;
        cout << "2. Buscar boxeador por ID"       << endl;
        cout << "3. Modificar boxeador"           << endl;
        cout << "4. Eliminar boxeador"            << endl;
        cout << "5. Registrar resultado de pelea" << endl;
        cout << "6. Listar boxeadores activos"    << endl;
        cout << "7. Volver al menu principal"     << endl;
        cout << "Opcion: ";
        cin  >> op;
        cin.ignore();

        switch (op) {
            case 1: agregar_boxeador();        break;
            case 2: buscar_boxeador();         break;
            case 3: modificar_boxeador();      break;
            case 4: eliminar_boxeador();       break;
            case 5: registrar_resultado();     break;
            case 6: listar_boxeadores_activos(); break;
            case 7: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 7);
}

void menuEmparejamiento() {
    int op;
    do {
        cout << "\n========== EMPAREJAMIENTO ==========" << endl;
        cout << "1. Buscar mejor rival para un boxeador" << endl;
        cout << "2. Mostrar matriz de compatibilidad"    << endl;
        cout << "3. Ver emparejamientos guardados"       << endl;
        cout << "4. Volver al menu principal"            << endl;
        cout << "Opcion: ";
        cin  >> op;
        cin.ignore();

        switch (op) {
            case 1: mejor_rival();          break;
            case 2: mostrar_matriz();       break;
            case 3: ver_emparejamientos();  break;
            case 4: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 4);
}

void menuReportes() {
    char op;
    do {
        cout << "\n========== REPORTES Y ESTADISTICAS ==========" << endl;
        cout << "A. Generar ranking de boxeadores"      << endl;
        cout << "B. Generar reporte de emparejamientos" << endl;
        cout << "C. Mostrar estadisticas generales"     << endl;
        cout << "D. Volver al menu principal"           << endl;
        cout << "Opcion: ";
        cin  >> op;
        cin.ignore();

        switch (op) {
            case 'A': case 'a': reporte_boxeadores();      break;
            case 'B': case 'b': reporte_emparejamientos(); break;
            case 'C': case 'c': estadisticas_generales();  break;
            case 'D': case 'd': cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida. Use A, B, C o D." << endl;
        }
    } while (op != 'D' && op != 'd');
}

void menuGraficas() {
    int op;
    do {
        cout << "\n========== GRAFICAS ==========" << endl;
        cout << "1. Grafica de boxeadores por categoria" << endl;
        cout << "2. Grafica de victorias por boxeador"   << endl;
        cout << "3. Volver al menu principal"            << endl;
        cout << "Opcion: ";
        cin  >> op;
        cin.ignore();

        switch (op) {
            case 1: grafica_boxeadores_por_categoria(); break;
            case 2: grafica_victorias_por_boxeador();   break;
            case 3: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 3);
}

int main() {
    int op;
    cout << "Bienvenido al Sistema de Emparejamiento de Boxeadores" << endl;

    do {
        cout << "\n========== SISTEMA DE EMPAREJAMIENTO DE BOXEADORES ==========" << endl;
        cout << "1. Gestion de boxeadores"   << endl;
        cout << "2. Emparejamiento"          << endl;
        cout << "3. Reportes y estadisticas" << endl;
        cout << "4. Graficas"                << endl;
        cout << "5. Salir"                   << endl;
        cout << "Opcion: ";
        cin  >> op;
        cin.ignore();

        switch (op) {
            case 1: menuGestion();        break;
            case 2: menuEmparejamiento(); break;
            case 3: menuReportes();       break;
            case 4: menuGraficas();       break;
            case 5: cout << "Hasta luego!" << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 5);

    return 0;
}
