#include <iostream>
#include "Estudiante.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
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

            string codigo, nombres, apellidos, direccion, fecha_nacimiento;
            int telefono = 0, id_tipo_sangre = 0;
            int id_estudiante = 0;

            cout << "\n--- INGRESAR ESTUDIANTE ---" << endl;

            cout << "Ingrese Codigo: ";
            getline(cin, codigo);

            cout << "Ingrese Nombres: ";
            getline(cin, nombres);

            cout << "Ingrese Apellidos: ";
            getline(cin, apellidos);

            cout << "Ingrese Direccion: ";
            getline(cin, direccion);

            cout << "Ingrese Telefono: ";
            cin >> telefono;
            limpiarBuffer();

            cout << "Ingrese Fecha Nacimiento YYYY-MM-DD: ";
            getline(cin, fecha_nacimiento);

            cout << "Ingrese ID Tipo Sangre: ";
            cin >> id_tipo_sangre;
            limpiarBuffer();

            Estudiante e(
                id_estudiante,
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

            string codigo, nombres, apellidos, direccion, fecha_nacimiento;
            int telefono = 0, id_tipo_sangre = 0;
            int id_estudiante = 0;

            cout << "\n--- MODIFICAR ESTUDIANTE ---" << endl;

            cout << "Ingrese el ID del estudiante a modificar: ";
            cin >> id_estudiante;
            limpiarBuffer();

            cout << "Ingrese nuevo Codigo: ";
            getline(cin, codigo);

            cout << "Ingrese nuevos Nombres: ";
            getline(cin, nombres);

            cout << "Ingrese nuevos Apellidos: ";
            getline(cin, apellidos);

            cout << "Ingrese nueva Direccion: ";
            getline(cin, direccion);

            cout << "Ingrese nuevo Telefono: ";
            cin >> telefono;
            limpiarBuffer();

            cout << "Ingrese nueva Fecha Nacimiento YYYY-MM-DD: ";
            getline(cin, fecha_nacimiento);

            cout << "Ingrese nuevo ID Tipo Sangre: ";
            cin >> id_tipo_sangre;
            limpiarBuffer();

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

            int id_estudiante = 0;

            cout << "\n--- ELIMINAR ESTUDIANTE ---" << endl;

            cout << "Ingrese el ID del estudiante a eliminar: ";
            cin >> id_estudiante;
            limpiarBuffer();

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