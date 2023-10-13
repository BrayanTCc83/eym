#ifndef EYM_COMPONENTES
#define EYM_COMPONENTES
#include <stdbool.h>

typedef double volt_t;
typedef double ampere_t;
typedef double coulomb_t;
typedef double ohm_t, ohm_metro_t;
typedef double micro_farad_t;
typedef double farad_metro_t;
typedef double joule_t;
typedef double watt_t;
typedef double longitud_t, distancia_t, area_t;
typedef char* string;

typedef struct {
    ohm_metro_t resistividad;
    double constanteDielectrica;
    double campoElectricoRuptura;
    string nombre;
} Material;

typedef struct {
    ohm_t       resistencia;
    volt_t      voltaje;
    ampere_t    corriente;
} Resistor;

typedef struct {
    distancia_t distancia;
    area_t      areaPlacas;
    Material    *dielectrico;
} CapacitorConfiguracion;

typedef struct {
    // Propiedades de los materiales del capacitor
    CapacitorConfiguracion *configuracion;
    // Propiedades resultantes del capacitor
    coulomb_t   carga;
    micro_farad_t     capacitancia;
    volt_t      voltajeMaximo, voltaje;
    ampere_t    corriente;
    // Referencia externa
    string      nombre;
} Capacitor;

typedef struct {
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
Capacitor *crearCapacitorFijo(volt_t, micro_farad_t);
void cambiarMaterial(Capacitor*, Material*);
void cambiarGeometria(Capacitor*, area_t, distancia_t);
bool calcularPropiedades(Capacitor*);
void asignarIdentificador(Capacitor*, const string);
void mostrarCapacitor(Capacitor);

#endif