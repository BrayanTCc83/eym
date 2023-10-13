#include "componentes.h"

Resistor *crearResistor(Material* material, area_t area, longitud_t longitud) {
    Resistor *resistor = (Resistor*) malloc(sizeof(Resistor));
    resistor->configuracion = (ResistorConfiguracion*) malloc(sizeof(ResistorConfiguracion));
    
    resistor->configuracion->material = material;
    resistor->configuracion->area = area;
    resistor->configuracion->longitud = longitud;
    resistor->estado.carga = 0;
    resistor->estado.corriente = 0;
    resistor->estado.voltaje = 0;
}

Resistor *crearResistorFijo(ohm_t resistencia, watt_t potenciaMaxima) {
    Resistor *resistor = (Resistor*) malloc(sizeof(Resistor));

    resistor->resistencia = resistencia;
    resistor->potenciaMaxima = potenciaMaxima;
    resistor->estado.carga = 0;
    resistor->estado.corriente = 0;
    resistor->estado.voltaje = 0;
}

bool calcularPropiedadesResistor(Resistor* resistor) {
    if(!resistor->configuracion)
        return false;

    resistor->resistencia = 
        resistor->configuracion->material->resistividad 
        (resistor->configuracion->longitud/(resistor->configuracion->area));
    resistor->potenciaMaxima = 
        resistor->configuracion->material->factorPotencia * 
        resistor->configuracion->longitud;
}