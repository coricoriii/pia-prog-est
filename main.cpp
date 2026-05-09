#include <iostream>
#include <string>
#include "boxeadores.h"

using namespace std;

// aca es de que todo lo relacionado a ingresar datos, modificar, eliminar, etc etc
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

        switch (op) {
            case 1: 
                agregar_boxeador();
                break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 7);
}

// el matchmaking 
void menuEmparejamiento() {
    int op;
    do {
        cout << "\n========== EMPAREJAMIENTO ==========" << endl;
        cout << "1. Buscar mejor rival para un boxeador" << endl;
        cout << "2. Mostrar matriz de compatibilidad"    << endl;
        cout << "3. Guardar emparejamiento sugerido"     << endl;
        cout << "4. Ver emparejamientos guardados"       << endl;
        cout << "5. Volver al menu principal"            << endl;
        cout << "Opcion: ";
        cin  >> op;

        switch (op) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 5);
}

//menu de las categorias etc etc
void menuReportes() {
    int op;
    do {
        cout << "\n========== REPORTES Y ESTADISTICAS ==========" << endl;
        cout << "1. Generar ranking de boxeadores"      << endl;
        cout << "2. Generar reporte de emparejamientos" << endl;
        cout << "3. Mostrar estadisticas generales"     << endl;
        cout << "4. Volver al menu principal"           << endl;
        cout << "Opcion: ";
        cin  >> op;

        switch (op) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 4);
}

// aca el emnu de las graficas
void menuGraficas() {
    int op;
    do {
        cout << "\n========== GRAFICAS ==========" << endl;
        cout << "1. Grafica de boxeadores por categoria" << endl;
        cout << "2. Grafica de victorias por boxeador"   << endl;
        cout << "3. Volver al menu principal"            << endl;
        cout << "Opcion: ";
        cin  >> op;

        switch (op) {
            case 1: break;
            case 2: break;
            case 3: cout << "Volviendo..." << endl; break;
            default: cout << "Opcion invalida." << endl;
        }
    } while (op != 3);
}

// hila quien lea esto este es el principal
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