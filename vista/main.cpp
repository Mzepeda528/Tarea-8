#include <iostream>
#include "Estudiante.h"
using namespace std;
int main() {


	string codigo, nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;

	cout << " Ingrese Codigo:";
	cin >> codigo;
	cin.ignore();
	cout << "Ingrese Nombres:";
	getline(cin, nombres);
	cout << "Ingrese Apelidos:";
	getline(cin, apellidos);
	cout << "Ingrese Direccion:";
	getline(cin, direccion);
	cout << "Ingrese Telefono:";
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese Fecha Nacimiento:";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese Tipo Sangre:";
	cin >> id_tipo_sangre;

	Estudiante e = Estudiante(id_estudiante, codigo, nombres, apellidos, direccion, fecha_nacimiento, telefono, id_tipo_sangre);
	e.crear();
	e.leer();

	//Actualizacion
	cout << "Ingrese el ID a modificar:";
	cin >> id_estudiante;
	cout << " Ingrese Codigo:";
	cin >> codigo;
	cin.ignore();
	cout << "Ingrese Nombres:";
	getline(cin, nombres);
	cout << "Ingrese Apelidos:";
	getline(cin, apellidos);
	cout << "Ingrese Direccion:";
	getline(cin, direccion);
	cout << "Ingrese Telefono:";
	cin >> telefono;
	cin.ignore();
	cout << "Ingrese Fecha Nacimiento:";
	getline(cin, fecha_nacimiento);
	cout << "Ingrese Tipo Sangre:";
	cin >> id_tipo_sangre;

	e.setId_estudiante(id_estudiante);
	e.setCodigo(codigo);
	e.setNombres(nombres);
	e.setApellidos(apellidos);
	e.setDireccion(direccion);
	e.setTelefono(telefono);
	e.setFecha_nacimiento(fecha_nacimiento);
	e.setId_Tipo_Sangre(id_tipo_sangre);
	e.leer();
	cout << "Ingrese el ID a Eliminar:";
	cin >> id_estudiante;
	e.setId_estudiante(id_estudiante);
	e.borrar();
	e.leer();

	e.actualizar();

};
