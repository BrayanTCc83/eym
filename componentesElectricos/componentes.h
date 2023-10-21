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
typedef double celsius_inverse_t, celsius_t;
typedef double mcr_farad_t;
typedef double joule_t;
typedef double watt_t;
typedef double longitud_t, distancia_t, area_t;
typedef char* string_t;

typedef struct estado_componente_t {
    // Valores del componente
    volt_t      voltaje;
    ampere_t    corriente;
} EstadoComponente;

typedef enum componente_ref {
    CAPACITOR_T,
    RESISTOR_T,
    INDUCTOR_T,
    COMPONENTES_N
} componente_ref_t;

typedef struct componente_t_def {
    componente_ref_t tipo;
    string_t nombre;
    EstadoComponente estado;
} componente_t;

typedef componente_t* componente_ptr;

typedef struct {
    ohm_metro_t resistividad;
    celsius_inverse_t coeficienteTemperatura;
    watt_t factorPotencia;
    double constanteDielectrica;
    double campoElectricoRuptura;
    string_t nombre;
} Material;

typedef struct configuracion_t {
    union {
        distancia_t distancia;
        longitud_t  longitud;
    };
    area_t      area;
    Material    *material;
} ResistorConfiguracion, CapacitorConfiguracion;

typedef struct resistor_t {
    componente_ref_t tipo;
    // Referencia externa
    string_t      nombre;
    // Propiedades del resistor
    EstadoComponente estado;
    // Propiedades de los materiales del resistor
    ResistorConfiguracion *configuracion;
    watt_t      potenciaMaxima;
    ohm_t       resistencia;
} Resistor;

typedef struct capacitor_t {
    componente_ref_t tipo;
    // Referencia externa
    string_t      nombre;
    // Propiedades del capacitor
    EstadoComponente estado;
    // Propiedades de los materiales del capacitor
    CapacitorConfiguracion *configuracion;
    coulomb_t   carga;
    volt_t      voltajeMaximo;
    mcr_farad_t capacitancia;
} Capacitor;

typedef struct inductor_t {
    componente_ref_t tipo;
    volt_t      voltaje;
    ampere_t    corriente;
} Inductor;

typedef struct {
    volt_t      voltaje;
    ampere_t    corriente;
} Fuente;

Material *crearMaterial(const string_t);
void propiedadesDielectricas(Material*,double, double);
void propiedadesResistivas(Material*, ohm_metro_t, celsius_inverse_t);

Capacitor *crearCapacitor(Material*, area_t, distancia_t);
Capacitor *crearCapacitorFijo(volt_t, mcr_farad_t);
void cambiarMaterial(Capacitor*, Material*);
void cambiarGeometria(Capacitor*, area_t, distancia_t);
bool calcularPropiedadesCapacitor(Capacitor*);
void mostrarCapacitor(Capacitor*);

Resistor *crearResistor(Material*, area_t, longitud_t);
Resistor *crearResistorFijo(ohm_t, watt_t);
void variarTemperatura(Resistor*, celsius_t);
bool calcularPropiedadesResistor(Resistor*);
void mostrarResistor(Resistor*);

void mostrarEstado(componente_t);
void asignarIdentificador(componente_ptr, const string_t);

#endif