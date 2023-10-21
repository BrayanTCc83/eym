#include <stdio.h>
#include "componentes.h"

Resistor *crearResistor(Material* material, area_t area, longitud_t longitud) {
    Resistor *resistor = (Resistor*) malloc(sizeof(Resistor));
    resistor->tipo = RESISTOR_T;
    resistor->configuracion = (ResistorConfiguracion*) malloc(sizeof(ResistorConfiguracion));
    
    resistor->configuracion->material = material;
    resistor->configuracion->area = area;
    resistor->configuracion->longitud = longitud;
    //resistor->estado.carga = 0;
    resistor->estado.corriente = 0;
    resistor->estado.voltaje = 0;

    calcularPropiedadesResistor(resistor);
    return resistor;
}

Resistor *crearResistorFijo(ohm_t resistencia, watt_t potenciaMaxima) {
    Resistor *resistor = (Resistor*) malloc(sizeof(Resistor));

    resistor->resistencia = resistencia;
    resistor->potenciaMaxima = potenciaMaxima;
    //resistor->estado.carga = 0;
    resistor->estado.corriente = 0;
    resistor->estado.voltaje = 0;

    return resistor;
}

bool calcularPropiedadesResistor(Resistor* resistor) {
    if(!resistor->configuracion)
        return false;

    resistor->resistencia = 
        resistor->configuracion->material->resistividad * 
        (resistor->configuracion->longitud/(resistor->configuracion->area));
    resistor->potenciaMaxima = 
        resistor->configuracion->material->factorPotencia * 
        resistor->configuracion->longitud;
    printf("Resistividad: %lf\n", resistor->configuracion->material->resistividad);
    return true;
}

static celsius_t temperaturaBase = 20;
void variarTemperatura(Resistor* resistor, celsius_t temperatura) {
    resistor->resistencia = resistor->resistencia * (1 + 
        resistor->configuracion->material->coeficienteTemperatura*(temperatura - temperaturaBase));
}

void mostrarResistor(Resistor* resistor) {
    mostrarEstado(*((componente_ptr)resistor));
    printf(" - Resistencia:\t\t%.10lf [Ohm]\n", resistor->resistencia);
    printf(" - Potencia maxima:\t%.10lf [W]\n", resistor->potenciaMaxima);

    if(!resistor->configuracion)
        return;
    printf(" - Longitud:\t\t%.10lf [m]\n", resistor->configuracion->distancia);
    printf(" - Area transversal:\t%.10lf [m2]\n", resistor->configuracion->area);
    printf(" - Conductor: \t\t%s\n", resistor->configuracion->material->nombre);
}