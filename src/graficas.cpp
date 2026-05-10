#include "graficas.h"
#include "boxeadores.h"
#include "matplotlibcpp.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>

using namespace std;

void grafica_boxeadores_por_categoria() {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir boxeadores.dat\n");
        return;
    }

    int contCat[6] = {0};
    Boxeador b;

    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1) {
            for (int i = 0; i < 6; i++) {
                if (strcmp(b.categoria, categorias[i]) == 0) {
                    contCat[i]++;
                }
            }
        }
    }
    fclose(f);

    vector<double> valores;
    vector<string> etiquetas;
    vector<double> posiciones;

    for (int i = 0; i < 6; i++) {
        if (contCat[i] > 0) {
            valores.push_back((double)contCat[i]);
            etiquetas.push_back(string(categorias[i]));
            posiciones.push_back((double)etiquetas.size() - 1);
        }
    }

    if (valores.empty()) {
        printf("No hay boxeadores activos para graficar.\n");
        return;
    }

    auto f1 = matplotlibcpp::figure(true);
    auto b1 = matplotlibcpp::bar(posiciones, valores);
    matplotlibcpp::xticks(posiciones, etiquetas);
    matplotlibcpp::title("Boxeadores por Categoria");
    matplotlibcpp::xlabel("Categoria");
    matplotlibcpp::ylabel("Cantidad");
    matplotlibcpp::show();
}

void grafica_victorias_por_boxeador() {
    FILE *f = fopen("boxeadores.dat", "rb");
    if (f == NULL) {
        printf("Error al abrir boxeadores.dat\n");
        return;
    }

    vector<double> victorias;
    vector<string> nombres;
    vector<double> posiciones;
    Boxeador b;

    while (fread(&b, sizeof(Boxeador), 1, f) == 1) {
        if (b.activo == 1) {
            victorias.push_back((double)b.record.victorias);
            nombres.push_back(string(b.nombre));
            posiciones.push_back((double)nombres.size() - 1);
        }
    }
    fclose(f);

    if (victorias.empty()) {
        printf("No hay boxeadores activos para graficar.\n");
        return;
    }

    auto f2 = matplotlibcpp::figure(true);
    auto b2 = matplotlibcpp::bar(posiciones, victorias);
    matplotlibcpp::xticks(posiciones, nombres);
    matplotlibcpp::title("Victorias por Boxeador");
    matplotlibcpp::xlabel("Boxeador");
    matplotlibcpp::ylabel("Victorias");
    matplotlibcpp::show();
}