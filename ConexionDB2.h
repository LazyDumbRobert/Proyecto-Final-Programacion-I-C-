#pragma once

#include <mysql.h>
#include <iostream>

	using namespace std;

	class ConexionBD2 {
	private: MYSQL* conectar;
	public:
		void abrir_conexion() {
			conectar = mysql_init(0);
			conectar = mysql_real_connect(conectar, "localhost", "root", "RS200319156156561", "proyecto_final_programacion", 3306, NULL, 0);
		}
		MYSQL* getConectar() {
			return conectar;
		}
		void cerrar_conexion() {
			mysql_close(conectar);
		}


	};


