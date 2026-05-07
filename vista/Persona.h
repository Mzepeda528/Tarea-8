#pragma once
#include <iostream>
using namespace std;

class Persona
{
protected:
	string nombres, apellidos, direccion, fecha_nacimiento;
	int telefono = 0, id_tipo_sangre = 0;
	Persona() {}
	Persona(string nom, string ape, string dir, string fn, int tel, int id_ts) {
		nombres = nom;
		apellidos = ape;
		direccion = dir;
		fecha_nacimiento = fn;
		telefono = tel;
		id_tipo_sangre = id_ts;

	}

};