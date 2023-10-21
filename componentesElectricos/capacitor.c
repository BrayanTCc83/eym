#include <stdio.h>
#include "componentes.h"

const farad_metro_t $E = 8.85*10E-12;
const double mcr = 10E-9;
const double M = 10E3;
const double m = 10E-3;

Capacitor *crearCapacitor(Material *dielectrico, area_t areaPlacas, distancia_t distancia) {
    Capacitor *capacitor = (Capacitor*) malloc(sizeof(Capacitor));
    capacitor->configuracion = (CapacitorConfiguracion*) malloc(sizeof(CapacitorConfiguracion));
    
    capacitor->configuracion->material = dielectrico;
    capacitor->configuracion->area = areaPlacas;
    capacitor->configuracion->distancia = distancia;
    capacitor->carga = 0;
    capacitor->estado.corriente = 0;
    capacitor->estado.voltaje = 0;
    calcularPropiedadesCapacitor(capacitor);
    
    return capacitor;
}

Capacitor *crearCapacitorFijo(volt_t voltajeMaximo, mcr_farad_t capacitancia) {
    Capacitor *capacitor = (Capacitor*) malloc(sizeof(Capacitor));
    capacitor->configuracion = NULL;

    capacitor->voltajeMaximo = voltajeMaximo;
    capacitor->capacitancia = capacitancia;
    capacitor->carga = 0;
    capacitor->estado.corriente = 0;
    capacitor->estado.voltaje = 0;

    return capacitor;
}

void cambiarMaterial(Capacitor *capacitor, Material *dielectrico) {
    if(!capacitor->configuracion)
        capacitor->configuracion = (CapacitorConfiguracion*) malloc(sizeof(CapacitorConfiguracion));

    capacitor->configuracion->material = dielectrico;
}

void cambiarGeometria(Capacitor *capacitor, area_t areaPlacas, distancia_t distancia) {
    if(!capacitor->configuracion)
        capacitor->configuracion = (CapacitorConfiguracion*) malloc(sizeof(CapacitorConfiguracion));
    
    capacitor->configuracion->area = areaPlacas;
    capacitor->configuracion->distancia = distancia;
}

bool calcularPropiedadesCapacitor(Capacitor *capacitor) {
    if(!capacitor->configuracion)
        return false;

    capacitor->capacitancia = 
        capacitor->configuracion->material->constanteDielectrica * $E *
        (capacitor->configuracion->area/(capacitor->configuracion->distancia)) / mcr;
    capacitor->voltajeMaximo = 
        capacitor->configuracion->material->campoElectricoRuptura * 
        capacitor->configuracion->distancia * M;
    
    return true;
}

void mostrarCapacitor(Capacitor* capacitor) {
    mostrarEstado(*((componente_ptr)capacitor));
    printf(" - Carga actual:\t%.10lf [C]\n", capacitor->carga);
    printf(" - Voltaje maximo:\t%.10lf [V]\n", capacitor->voltajeMaximo);
    printf(" - Capacitancia:\t%.10lf [mcrF]\n", capacitor->capacitancia);
    
    if(!capacitor->configuracion)
        return;
    printf(" - Distancia placas:\t%.10lf [mm]\n", capacitor->configuracion->distancia);
    printf(" - Area placas: \t%.10lf [m2]\n", capacitor->configuracion->area);
    printf(" - Dielectrico: \t%s\n", capacitor->configuracion->material->nombre);
}