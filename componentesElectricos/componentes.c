#include "./componentes.h"
#include <stdio.h>

static const string_t componente_ref_nombre[] = {
    "Capactitor", "Resistor", "Inductor"
};
static string_t componenteNombre(componente_ref_t tipo) {
    if(tipo >= COMPONENTES_N)
        return "Componente no encontrado";
    return componente_ref_nombre[tipo];
}

void mostrarEstado(componente_t componente) {
    printf("\t--- %s [%s]---\n",
        componenteNombre(componente.tipo),
        componente.nombre ? componente.nombre : "Sin nombre"
    );
    printf(" - Corriente actual:\t%.10lf [A]\n", componente.estado.corriente);
    printf(" - Voltaje actual:\t%.10lf [V]\n", componente.estado.voltaje);
}

void asignarIdentificador(componente_ptr componente, const string_t nombre) {
    if(componente->tipo >= COMPONENTES_N)
        return;
    componente->nombre = nombre;
}