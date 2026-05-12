#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
#include "Persona.h"
#include <mysql.h>

using namespace std;

class Estudiante : public Persona {
private:
    int id_estudiante = 0;
    string codigo = "";

    string escaparSQL(MYSQL* conn, string texto) {
        char* buffer = new char[texto.length() * 2 + 1];

        mysql_real_escape_string(
            conn,
            buffer,
            texto.c_str(),
            texto.length()
        );

        string textoSeguro(buffer);
        delete[] buffer;

        return textoSeguro;
    }

    bool existeCodigo(MYSQL* conn, string cod, int idExcluir = 0) {
        string codigoSeguro = escaparSQL(conn, cod);

        string consulta = "SELECT id_estudiante FROM estudiantes WHERE codigo = '" + codigoSeguro + "'";

        if (idExcluir > 0) {
            consulta += " AND id_estudiante <> " + to_string(idExcluir);
        }

        consulta += " LIMIT 1";

        if (mysql_query(conn, consulta.c_str()) != 0) {
            cout << "Error al validar codigo duplicado: " << mysql_error(conn) << endl;
            return true;
        }

        MYSQL_RES* resultado = mysql_store_result(conn);

        if (resultado == NULL) {
            cout << "Error al obtener resultado de validacion: " << mysql_error(conn) << endl;
            return true;
        }

        bool existe = mysql_num_rows(resultado) > 0;
        mysql_free_result(resultado);

        return existe;
    }

    bool existeEstudiante(MYSQL* conn, int id) {
        string consulta = "SELECT id_estudiante FROM estudiantes WHERE id_estudiante = " + to_string(id) + " LIMIT 1";

        if (mysql_query(conn, consulta.c_str()) != 0) {
            cout << "Error al validar estudiante: " << mysql_error(conn) << endl;
            return false;
        }

        MYSQL_RES* resultado = mysql_store_result(conn);

        if (resultado == NULL) {
            cout << "Error al obtener resultado de estudiante: " << mysql_error(conn) << endl;
            return false;
        }

        bool existe = mysql_num_rows(resultado) > 0;
        mysql_free_result(resultado);

        return existe;
    }

    bool existeTipoSangre(MYSQL* conn, int idTipoSangre) {
        string consulta = "SELECT id_tipo_sangre FROM tipos_sangre WHERE id_tipo_sangre = " + to_string(idTipoSangre) + " LIMIT 1";

        if (mysql_query(conn, consulta.c_str()) != 0) {
            cout << "Error al validar tipo de sangre: " << mysql_error(conn) << endl;
            return false;
        }

        MYSQL_RES* resultado = mysql_store_result(conn);

        if (resultado == NULL) {
            cout << "Error al obtener resultado de tipo de sangre: " << mysql_error(conn) << endl;
            return false;
        }

        bool existe = mysql_num_rows(resultado) > 0;
        mysql_free_result(resultado);

        return existe;
    }

public:
    Estudiante() {}

    Estudiante(int id_est, string cod, string nom, string ape, string dir, string fn, int tel, int id_ts)
        : Persona(nom, ape, dir, fn, tel, id_ts) {
        id_estudiante = id_est;
        codigo = cod;
    }

    void crear() {
        int q_estado = 0;

        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        MYSQL* conn = cn.getConector();

        if (conn) {

            if (existeCodigo(conn, codigo)) {
                cout << "Error: el codigo ya existe. No se puede duplicar." << endl;
                cn.cerrar_conexion();
                return;
            }

            if (!existeTipoSangre(conn, id_tipo_sangre)) {
                cout << "Error: el ID de tipo de sangre no existe en la tabla tipos_sangre." << endl;
                cn.cerrar_conexion();
                return;
            }

            string codigoSeguro = escaparSQL(conn, codigo);
            string nombresSeguro = escaparSQL(conn, nombres);
            string apellidosSeguro = escaparSQL(conn, apellidos);
            string direccionSeguro = escaparSQL(conn, direccion);
            string fechaSeguro = escaparSQL(conn, fecha_nacimiento);

            string consulta =
                "INSERT INTO estudiantes "
                "(codigo, nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre) "
                "VALUES ('" + codigoSeguro + "', '" + nombresSeguro + "', '" + apellidosSeguro + "', '" +
                direccionSeguro + "', " + to_string(telefono) + ", '" + fechaSeguro + "', " +
                to_string(id_tipo_sangre) + ")";

            q_estado = mysql_query(conn, consulta.c_str());

            if (!q_estado) {
                cout << "Ingreso de datos exitoso." << endl;
            }
            else {
                cout << "Error al insertar estudiante: " << mysql_error(conn) << endl;
            }
        }
        else {
            cout << "Error: no se pudo conectar a la base de datos." << endl;
        }

        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        cn.abrir_conexion();

        MYSQL* conn = cn.getConector();

        if (conn) {
            string consulta =
                "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, "
                "e.fecha_nacimiento, e.telefono, e.id_tipo_sangre "
                "FROM estudiantes e "
                "ORDER BY e.id_estudiante ASC";

            if (mysql_query(conn, consulta.c_str()) != 0) {
                cout << "Error al consultar estudiantes: " << mysql_error(conn) << endl;
                cn.cerrar_conexion();
                return;
            }

            MYSQL_RES* resultado = mysql_store_result(conn);

            if (resultado == NULL) {
                cout << "Error al obtener estudiantes: " << mysql_error(conn) << endl;
                cn.cerrar_conexion();
                return;
            }

            my_ulonglong num_filas = mysql_num_rows(resultado);

            if (num_filas == 0) {
                cout << "No hay estudiantes registrados." << endl;
            }

            for (my_ulonglong i = 0; i < num_filas; i++) {
                MYSQL_ROW fila = mysql_fetch_row(resultado);

                cout << "ID: " << (fila[0] ? fila[0] : "") <<
                    " | Codigo: " << (fila[1] ? fila[1] : "") <<
                    " | Nombres: " << (fila[2] ? fila[2] : "") <<
                    " | Apellidos: " << (fila[3] ? fila[3] : "") <<
                    " | Direccion: " << (fila[4] ? fila[4] : "") <<
                    " | Fecha Nac: " << (fila[5] ? fila[5] : "") <<
                    " | Telefono: " << (fila[6] ? fila[6] : "") <<
                    " | ID Sangre: " << (fila[7] ? fila[7] : "") << endl;
            }

            mysql_free_result(resultado);
        }
        else {
            cout << "Error: no se pudo conectar a la base de datos." << endl;
        }

        cn.cerrar_conexion();
    }

    void actualizar() {
        int q_estado = 0;

        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        MYSQL* conn = cn.getConector();

        if (conn) {

            if (id_estudiante <= 0) {
                cout << "Error: ID de estudiante invalido." << endl;
                cn.cerrar_conexion();
                return;
            }

            if (!existeEstudiante(conn, id_estudiante)) {
                cout << "Error: el estudiante no existe." << endl;
                cn.cerrar_conexion();
                return;
            }

            if (existeCodigo(conn, codigo, id_estudiante)) {
                cout << "Error: el codigo ya pertenece a otro estudiante." << endl;
                cn.cerrar_conexion();
                return;
            }

            if (!existeTipoSangre(conn, id_tipo_sangre)) {
                cout << "Error: el ID de tipo de sangre no existe en la tabla tipos_sangre." << endl;
                cn.cerrar_conexion();
                return;
            }

            string codigoSeguro = escaparSQL(conn, codigo);
            string nombresSeguro = escaparSQL(conn, nombres);
            string apellidosSeguro = escaparSQL(conn, apellidos);
            string direccionSeguro = escaparSQL(conn, direccion);
            string fechaSeguro = escaparSQL(conn, fecha_nacimiento);

            string consulta =
                "UPDATE estudiantes SET "
                "codigo = '" + codigoSeguro + "', "
                "nombres = '" + nombresSeguro + "', "
                "apellidos = '" + apellidosSeguro + "', "
                "direccion = '" + direccionSeguro + "', "
                "telefono = " + to_string(telefono) + ", "
                "fecha_nacimiento = '" + fechaSeguro + "', "
                "id_tipo_sangre = " + to_string(id_tipo_sangre) + " "
                "WHERE id_estudiante = " + to_string(id_estudiante);

            q_estado = mysql_query(conn, consulta.c_str());

            if (!q_estado) {
                cout << "Modificacion de datos exitosa." << endl;
            }
            else {
                cout << "Error al modificar estudiante: " << mysql_error(conn) << endl;
            }
        }
        else {
            cout << "Error: no se pudo conectar a la base de datos." << endl;
        }

        cn.cerrar_conexion();
    }

    void borrar() {
        int q_estado = 0;

        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();

        MYSQL* conn = cn.getConector();

        if (conn) {

            if (id_estudiante <= 0) {
                cout << "Error: ID de estudiante invalido." << endl;
                cn.cerrar_conexion();
                return;
            }

            if (!existeEstudiante(conn, id_estudiante)) {
                cout << "Error: el estudiante no existe. No se puede eliminar." << endl;
                cn.cerrar_conexion();
                return;
            }

            string consulta = "DELETE FROM estudiantes WHERE id_estudiante = " + to_string(id_estudiante);

            q_estado = mysql_query(conn, consulta.c_str());

            if (!q_estado) {
                cout << "Eliminacion de datos exitosa." << endl;
            }
            else {
                cout << "Error al eliminar estudiante: " << mysql_error(conn) << endl;
            }
        }
        else {
            cout << "Error: no se pudo conectar a la base de datos." << endl;
        }

        cn.cerrar_conexion();
    }

    void setId_estudiante(int id) {
        id_estudiante = id;
    }

    void setCodigo(string cod) {
        codigo = cod;
    }

    void setNombres(string nom) {
        nombres = nom;
    }

    void setApellidos(string ape) {
        apellidos = ape;
    }

    void setDireccion(string dir) {
        direccion = dir;
    }

    void setTelefono(int tel) {
        telefono = tel;
    }

    void setFecha_nacimiento(string fn) {
        fecha_nacimiento = fn;
    }

    void setId_Tipo_Sangre(int ts) {
        id_tipo_sangre = ts;
    }
};