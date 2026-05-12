#include <iostream>
#include <string>
#include <regex>
#include <ctime>
#include "Estudiante.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

bool contieneCaracteresPeligrosos(string texto) {
    string peligrosos[] = { "'", "\"", ";", "--", "/*", "*/", "=", "<", ">" };

    for (string p : peligrosos) {
        if (texto.find(p) != string::npos) {
            return true;
        }
    }

    return false;
}

bool validarCodigo(string codigo) {
    regex patron("^E[0-9]{3}$");
    return regex_match(codigo, patron);
}

bool validarLetrasEspacios(string texto) {
    regex patron("^[A-Za-zÁÉÍÓÚáéíóúÑñ ]+$");
    return regex_match(texto, patron);
}

bool validarTelefono(string telefono) {
    regex patron("^[0-9]{8}$");
    return regex_match(telefono, patron);
}

bool esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool validarFechaReal(int anio, int mes, int dia) {
    if (anio < 1900 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    int diasMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    if (mes == 2 && esBisiesto(anio)) {
        return dia <= 29;
    }

    return dia <= diasMes[mes - 1];
}

bool validarFechaNacimiento(string fecha) {
    regex patron("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");

    if (!regex_match(fecha, patron)) {
        return false;
    }

    int anio = stoi(fecha.substr(0, 4));
    int mes = stoi(fecha.substr(5, 2));
    int dia = stoi(fecha.substr(8, 2));

    if (!validarFechaReal(anio, mes, dia)) {
        return false;
    }

    time_t ahora = time(0);
    tm fechaActual;

#ifdef _WIN32
    localtime_s(&fechaActual, &ahora);
#else
    localtime_r(&ahora, &fechaActual);
#endif

    int anioActual = fechaActual.tm_year + 1900;
    int mesActual = fechaActual.tm_mon + 1;
    int diaActual = fechaActual.tm_mday;

    if (anio > anioActual) {
        return false;
    }

    if (anio == anioActual && mes > mesActual) {
        return false;
    }

    if (anio == anioActual && mes == mesActual && dia > diaActual) {
        return false;
    }

    return true;
}

string pedirCodigo() {
    string codigo;

    do {
        cout << "Ingrese Codigo, ejemplo E001: ";
        getline(cin, codigo);

        if (codigo.empty()) {
            cout << "Error: el codigo es obligatorio." << endl;
        }
        else if (codigo.length() > 4) {
            cout << "Error: el codigo debe tener maximo 4 caracteres." << endl;
        }
        else if (!validarCodigo(codigo)) {
            cout << "Error: el codigo debe tener formato E001, E002, E003." << endl;
        }
        else {
            break;
        }

    } while (true);

    return codigo;
}

string pedirNombreOCampo(string mensaje, string nombreCampo) {
    string valor;

    do {
        cout << mensaje;
        getline(cin, valor);

        if (valor.empty()) {
            cout << "Error: " << nombreCampo << " es obligatorio." << endl;
        }
        else if (valor.length() > 60) {
            cout << "Error: " << nombreCampo << " debe tener maximo 60 caracteres." << endl;
        }
        else if (!validarLetrasEspacios(valor)) {
            cout << "Error: " << nombreCampo << " solo permite letras y espacios." << endl;
        }
        else {
            break;
        }

    } while (true);

    return valor;
}

string pedirDireccion() {
    string direccion;

    do {
        cout << "Ingrese Direccion: ";
        getline(cin, direccion);

        if (direccion.empty()) {
            cout << "Error: la direccion es obligatoria." << endl;
        }
        else if (direccion.length() > 100) {
            cout << "Error: la direccion debe tener maximo 100 caracteres." << endl;
        }
        else if (contieneCaracteresPeligrosos(direccion)) {
            cout << "Error: la direccion contiene caracteres no permitidos." << endl;
        }
        else {
            break;
        }

    } while (true);

    return direccion;
}

int pedirTelefono() {
    string telefono;

    do {
        cout << "Ingrese Telefono, 8 digitos: ";
        getline(cin, telefono);

        if (telefono.empty()) {
            cout << "Error: el telefono es obligatorio." << endl;
        }
        else if (!validarTelefono(telefono)) {
            cout << "Error: el telefono debe contener exactamente 8 numeros." << endl;
        }
        else {
            break;
        }

    } while (true);

    return stoi(telefono);
}

string pedirFechaNacimiento() {
    string fecha;

    do {
        cout << "Ingrese Fecha Nacimiento YYYY-MM-DD: ";
        getline(cin, fecha);

        if (fecha.empty()) {
            cout << "Error: la fecha de nacimiento es obligatoria." << endl;
        }
        else if (!validarFechaNacimiento(fecha)) {
            cout << "Error: la fecha debe ser real, con formato YYYY-MM-DD y no puede ser futura." << endl;
        }
        else {
            break;
        }

    } while (true);

    return fecha;
}

int pedirEntero(string mensaje) {
    string valor;
    regex patron("^[0-9]+$");

    do {
        cout << mensaje;
        getline(cin, valor);

        if (valor.empty()) {
            cout << "Error: el campo es obligatorio." << endl;
        }
        else if (!regex_match(valor, patron)) {
            cout << "Error: solo se permiten numeros." << endl;
        }
        else {
            break;
        }

    } while (true);

    return stoi(valor);
}

int main() {

    int opcion = 0;

    do {
        cout << "\n======================================" << endl;
        cout << "        MENU DE ESTUDIANTES" << endl;
        cout << "======================================" << endl;
        cout << "1. Ingresar estudiante" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Modificar estudiante" << endl;
        cout << "4. Eliminar estudiante" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        limpiarBuffer();

        if (opcion == 1) {

            cout << "\n--- INGRESAR ESTUDIANTE ---" << endl;

            string codigo = pedirCodigo();
            string nombres = pedirNombreOCampo("Ingrese Nombres: ", "nombres");
            string apellidos = pedirNombreOCampo("Ingrese Apellidos: ", "apellidos");
            string direccion = pedirDireccion();
            int telefono = pedirTelefono();
            string fecha_nacimiento = pedirFechaNacimiento();
            int id_tipo_sangre = pedirEntero("Ingrese ID Tipo Sangre: ");

            Estudiante e(
                0,
                codigo,
                nombres,
                apellidos,
                direccion,
                fecha_nacimiento,
                telefono,
                id_tipo_sangre
            );

            e.crear();

        }
        else if (opcion == 2) {

            cout << "\n--- LISTADO DE ESTUDIANTES ---" << endl;

            Estudiante e;
            e.leer();

        }
        else if (opcion == 3) {

            cout << "\n--- MODIFICAR ESTUDIANTE ---" << endl;

            int id_estudiante = pedirEntero("Ingrese el ID del estudiante a modificar: ");
            string codigo = pedirCodigo();
            string nombres = pedirNombreOCampo("Ingrese Nombres: ", "nombres");
            string apellidos = pedirNombreOCampo("Ingrese Apellidos: ", "apellidos");
            string direccion = pedirDireccion();
            int telefono = pedirTelefono();
            string fecha_nacimiento = pedirFechaNacimiento();
            int id_tipo_sangre = pedirEntero("Ingrese ID Tipo Sangre: ");

            Estudiante e;
            e.setId_estudiante(id_estudiante);
            e.setCodigo(codigo);
            e.setNombres(nombres);
            e.setApellidos(apellidos);
            e.setDireccion(direccion);
            e.setTelefono(telefono);
            e.setFecha_nacimiento(fecha_nacimiento);
            e.setId_Tipo_Sangre(id_tipo_sangre);

            e.actualizar();

        }
        else if (opcion == 4) {

            cout << "\n--- ELIMINAR ESTUDIANTE ---" << endl;

            int id_estudiante = pedirEntero("Ingrese el ID del estudiante a eliminar: ");

            Estudiante e;
            e.setId_estudiante(id_estudiante);
            e.borrar();

        }
        else if (opcion == 5) {

            cout << "\nSaliendo del sistema..." << endl;

        }
        else {

            cout << "\nOpcion no valida. Intente nuevamente." << endl;

        }

    } while (opcion != 5);

    return 0;
}