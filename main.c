#include <stdio.h>
#include "./componentesElectricos/componentes.h"

extern farad_metro_t $E;

int main() {
    Material *mica = crearMaterial("Mica");
    propiedadesDielectricas(mica, 50, 5.2);

    Material *cobre = crearMaterial("Cobre");
    propiedadesResistivas(cobre, 1.68E-8, 3.9E-3);

    Capacitor *capacitor1 = crearCapacitor(mica, 0.12, 0.3);
    asignarIdentificador((componente_ptr)capacitor1, "C1"); 

    Capacitor *capacitor2 = crearCapacitorFijo(50, 25);
    asignarIdentificador((componente_ptr)capacitor2, "C2"); 

    Resistor *resistor1 = crearResistor(cobre, 2.5E-8, 10);
    asignarIdentificador((componente_ptr)resistor1, "R1");

    Resistor *resistor2 = crearResistorFijo(10, 0.25);
    asignarIdentificador((componente_ptr)resistor2, "R2");

    //mostrarCapacitor(capacitor1);
    //mostrarCapacitor(capacitor2);
    mostrarResistor(resistor1);
    variarTemperatura(resistor1, 50);
    mostrarResistor(resistor1);
    //mostrarResistor(resistor2);

    return 0;
}