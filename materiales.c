#include <stdio.h>
#include "componentes.h"

Material *crearMaterial(const string nombre) {
    Material *material = (Material*) malloc(sizeof(Material));
    material->nombre = nombre;
    material->campoElectricoRuptura = 0;
    material->constanteDielectrica = 0;
    material->resistividad = 0;

    return material;
}

void propiedadesDielectricas(Material *material, double campoElectrico, double constanteDielectrica) {
    material->campoElectricoRuptura = campoElectrico;
    material->constanteDielectrica = constanteDielectrica;
}