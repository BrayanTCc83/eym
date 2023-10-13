#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "componentes.h"

const farad_metro_t $E = 8.85*10E-12;
const double micro = 10E-9;
const double M = 10E3;
const double m = 10E-3;

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

Capacitor *crearCapacitor(Material *dielectrico, area_t areaPlacas, distancia_t distancia) {
    Capacitor *capacitor = (Capacitor*) malloc(sizeof(Capacitor));
    capacitor->configuracion = (CapacitorConfiguracion*) malloc(sizeof(CapacitorConfiguracion));
    
    capacitor->configuracion->dielectrico = dielectrico;
    capacitor->configuracion->areaPlacas = areaPlacas;
    capacitor->configuracion->distancia = distancia;
    capacitor->carga = 0;
    capacitor->corriente = 0;
    capacitor->voltaje = 0;
    calcularPropiedades(capacitor);
    
    return capacitor;
}

Capacitor *crearCapacitorFijo(volt_t voltajeMaximo, micro_farad_t capacitancia) {
    Capacitor *capacitor = (Capacitor*) malloc(sizeof(Capacitor));
    capacitor->configuracion = NULL;

    capacitor->voltajeMaximo = voltajeMaximo;
    capacitor->capacitancia = capacitancia;
    capacitor->carga = 0;
    capacitor->corriente = 0;
    capacitor->voltaje = 0;

    return capacitor;
}

void cambiarMaterial(Capacitor *capacitor, Material *dielectrico) {
    if(!capacitor->configuracion)
        capacitor->configuracion = (CapacitorConfiguracion*) malloc(sizeof(CapacitorConfiguracion));

    capacitor->configuracion->dielectrico = dielectrico;
}

void cambiarGeometria(Capacitor *capacitor, area_t areaPlacas, distancia_t distancia) {
    if(!capacitor->configuracion)
        capacitor->configuracion = (CapacitorConfiguracion*) malloc(sizeof(CapacitorConfiguracion));
    
    capacitor->configuracion->areaPlacas = areaPlacas;
    capacitor->configuracion->distancia = distancia;
}

bool calcularPropiedades(Capacitor *capacitor) {
    if(!capacitor->configuracion)
        return false;

    capacitor->capacitancia = 
        capacitor->configuracion->dielectrico->constanteDielectrica * $E *
        (capacitor->configuracion->areaPlacas/(capacitor->configuracion->distancia)) / micro;
    capacitor->voltajeMaximo = 
        capacitor->configuracion->dielectrico->campoElectricoRuptura * 
        capacitor->configuracion->distancia * M;
    
    return true;
}

void asignarIdentificador(Capacitor* capacitor, const string nombre) {
    capacitor->nombre = nombre;
}

void mostrarCapacitor(Capacitor capacitor) {
    printf(" --- Capacitor ---\n");
    printf(" - Nombre:\t\t%s\n", capacitor.nombre?capacitor.nombre : "Sin nombre");
    printf(" - Voltaje maximo:\t%lf [V]\n", capacitor.voltajeMaximo);
    printf(" - Capacitancia:\t%lf [microF]\n", capacitor.capacitancia);
    printf(" - Carga actual:\t%lf [C]\n", capacitor.carga);
    printf(" - Voltaje actual:\t%lf [V]\n", capacitor.voltaje);
    printf(" - Corriente actual:\t%lf [A]\n", capacitor.corriente);
    
    if(!capacitor.configuracion)
        return;
    printf(" - Distancia placas:\t%lf [mm]\n", capacitor.configuracion->distancia);
    printf(" - Area placas: \t%lf [m2]\n", capacitor.configuracion->areaPlacas);
    printf(" - Dielectrico: \t%s\n", capacitor.configuracion->dielectrico->nombre);
}