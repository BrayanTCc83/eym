#include <stdio.h>
#include "componentes.h"

extern farad_metro_t $E;

int main() {
    Material *mica = crearMaterial("Mica");
    propiedadesDielectricas(mica, 50, 5.2);

    Capacitor *capacitor1 = crearCapacitor(mica, 0.12, 0.3);
    asignarIdentificador(capacitor1, "C1"); 

    Capacitor *capacitor2 = crearCapacitorFijo(50, 25);
    mostrarCapacitor(*capacitor1);
    mostrarCapacitor(*capacitor2);

    return 0;
}