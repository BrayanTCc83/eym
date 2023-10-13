#ifndef EYM_COMPONENTES
#define EYM_COMPONENTES
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef double volt_t;
typedef double ampere_t;
typedef double coulomb_t;
typedef double ohm_t, ohm_metro_t;
typedef double farad_metro_t;
typedef double mcr_farad_t;
typedef double joule_t;
typedef double watt_t;
typedef double longitud_t, distancia_t, area_t;
typedef char* string;

typedef struct {
    ohm_metro_t resistividad;
    watt_t factorPotencia;
    double constanteDielectrica;
    double campoElectricoRuptura;
    string nombre;
} Material;

typedef struct estado_componente_t {
    // Valores del componente
    coulomb_t   carga;
    volt_t      voltaje;
    ampere_t    corriente;
} EstadoComponente;

typedef struct configuracion_t {
    union {
        distancia_t distancia;
        longitud_t  longitud;
    };
    area_t      area;
    Material    *material;
} ResistorConfiguracion, CapacitorConfiguracion;

typedef struct resistor_t {
    // Propiedades de los materiales del resistor
    ResistorConfiguracion *configuracion;
    // Referencia externa
    string      nombre;
    // Propiedades del resistor
    EstadoComponente estado;
    watt_t      potenciaMaxima;
    ohm_t       resistencia;
} Resistor;

typedef struct capacitor_t {
    // Propiedades de los materiales del capacitor
    CapacitorConfiguracion *configuracion;
    // Referencia externa
    string      nombre;
    // Propiedades del capacitor
    EstadoComponente estado;
    volt_t      voltajeMaximo;
    mcr_farad_t capacitancia;
} Capacitor;

typedef struct inductor_t {
    volt_t      voltaje;
    ampere_t    corriente;
} Inductor;

typedef struct {
    volt_t      voltaje;
    ampere_t    corriente;
} Fuente;

Material *crearMaterial(const string);
void propiedadesDielectricas(Material*,double, double);

Capacitor *crearCapacitor(Material*, area_t, distancia_t);
Capacitor *crearCapacitorFijo(volt_t, mcr_farad_t);
void cambiarMaterial(Capacitor*, Material*);
void cambiarGeometria(Capacitor*, area_t, distancia_t);
bool calcularPropiedadesCapacitor(Capacitor*);
void asignarIdentificador(Capacitor*, const string);
void mostrarEstadoCapacitor(Capacitor);
void mostrarCapacitor(Capacitor);

Resistor *crearResistor(Material*, area_t, longitud_t);
Resistor *crearResistorFijo(ohm_t, watt_t);
bool calcularPropiedadesResistor(Resistor*);

#endif