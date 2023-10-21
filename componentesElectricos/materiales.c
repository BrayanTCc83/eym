#include <stdio.h>
#include "componentes.h"

Material *crearMaterial(const string_t nombre) {
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

void propiedadesResistivas(Material* material, ohm_metro_t resistividad, 
    celsius_inverse_t coeficienteTemperatura) {
    material->resistividad = resistividad;
    material->coeficienteTemperatura = coeficienteTemperatura;
}