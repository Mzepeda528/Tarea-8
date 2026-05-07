#pragma once
#include <iostream>
#include "ConexionBD.h"
#include "Persona.h"
#include <mysql.h>
#include <string>

using namespace std;

// Heredamos de forma pública para acceder a los atributos de Persona
class Estudiante : public Persona {
private:
    int id_estudiante = 0;
    string codigo = "";

public:
    Estudiante() {}
    Estudiante(int id_est, string cod, string nom, string ape, string dir, string fn, int tel, int id_ts)
        : Persona(nom, ape, dir, fn, tel, id_ts) {
        id_estudiante = id_est;
        codigo = cod; // Asignación correcta
    }

    // Metodo Crear
    void crear() {
        int q_estado = 0;
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        if (cn.getConector()) {
            string t = to_string(telefono); // Corregido 'telegono'
            string id_ts_str = to_string(id_tipo_sangre);

            // Corregido 'strig' y nombres de variables
            string consulta = "insert into estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipo_sangre) VALUES ('" + codigo + "','" + nombres + "','" + apellidos + "','" + direccion + "'," + t + ",'" + fecha_nacimiento + "'," + id_ts_str + "); ";

            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c); 

            if (!q_estado) {
                cout << "Ingreso de Datos Exitoso..." << endl;
            }
            else {
                cout << "xxxx Consulta Fallida xxxx..." << endl;
            }
        }
        else {
            cout << "xxxx Conexion Fallida xxxx " << endl;
        }
        cn.cerrar_conexion(); 
    } 

    // Metodo Leer
    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* conn = cn.getConector();

        if (conn) {
            string consulta = "SELECT * FROM estudiantes";
            const char* c = consulta.c_str();
            mysql_query(conn, c);

            MYSQL_RES* resultado = mysql_store_result(conn);
            int num_filas = mysql_num_rows(resultado);

            for (int i = 0; i < num_filas; i++) {
                MYSQL_ROW fila = mysql_fetch_row(resultado);
                cout << "ID: " << fila[0] <<
                    " | Codigo: " << fila[1] <<
                    " | Nombres: " << fila[2] <<
                    " | Apellidos: " << fila[3] <<
                    " | Direccion: " << fila[4] <<
                    " | Fecha Nac: " << fila[5] <<
                    " | Telefono: " << fila[6] <<
                    " | ID Sangre: " << fila[7] << endl;
            }
        }
        else {
            cout << "Error al conectar a la base de datos" << endl;
        }
        cn.cerrar_conexion();
    }
};