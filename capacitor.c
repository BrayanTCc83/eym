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
    capacitor->estado.carga = 0;
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
    capacitor->estado.carga = 0;
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

void asignarIdentificador(Capacitor* capacitor, const string nombre) {
    capacitor->nombre = nombre;
}

void mostrarEstadoCapacitor(Capacitor capacitor) {
    printf("\t--- Capacitor [%s]---\n", capacitor.nombre?capacitor.nombre : "Sin nombre");
    printf(" - Voltaje maximo:\t%lf [V]\n", capacitor.voltajeMaximo);
    printf(" - Capacitancia:\t%lf [mcrF]\n", capacitor.capacitancia);
    printf(" - Carga actual:\t%lf [C]\n", capacitor.estado.carga);
    printf(" - Corriente actual:\t%lf [A]\n", capacitor.estado.corriente);
    printf(" - Voltaje actual:\t%lf [V]\n", capacitor.estado.voltaje);
}

void mostrarCapacitor(Capacitor capacitor) {
    mostrarEstadoCapacitor(capacitor);
    
    if(!capacitor.configuracion)
        return;
    printf(" - Distancia placas:\t%lf [mm]\n", capacitor.configuracion->distancia);
    printf(" - Area placas: \t%lf [m2]\n", capacitor.configuracion->area);
    printf(" - Dielectrico: \t%s\n", capacitor.configuracion->material->nombre);
}