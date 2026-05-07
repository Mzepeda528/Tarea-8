#pragma once
#include <iostream>
#include <mysql.h>
using namespace std;
class ConexionBD {
private: MYSQL* conector;
public:
	void abrir_conexion() {
		conector = mysql_init(0);
		conector = mysql_real_connect(conector, "localhost", "root", "Manuel1234!", "db_escuela", 3306, NULL, 0);
	}
	MYSQL* getConector() {
		return conector;
	}
	void cerrar_conexion() {
		mysql_close(conector);
	}

};
