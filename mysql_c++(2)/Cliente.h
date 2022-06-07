#pragma once
#include "Persona.h"
#include "ConexionDB2.h"
#include<string.h>
#include<stdio.h>
#include<mysql.h>



class Cliente : Persona {
private:
	string NIT, correo_electronico, fechaingreso;

public:
	Cliente() {

	}
	Cliente(string name, string lastname, string tel, string genre, string nit, string email, string date_ing) : Persona(name, lastname, tel, genre) {
		NIT = nit;
		correo_electronico = email;
		fechaingreso = date_ing;
	}
	//metodos set y get
	void setNit(string n) { NIT = n; }
	void setCorreo(string c_e) { correo_electronico = c_e; }
	void setFechaIng(string date_ing) { fechaingreso = date_ing; }
	void setNombres(string name) { nombres = name; }
	void setApellidos(string lastname) { apellidos = lastname; }
	void setTelefono(string tel) { telefono = tel; }
	void setGenero(string genre) { genero = genre; }

	string getNit() { return NIT; }
	string getCorreo() { return correo_electronico; }
	string getFechaIng() { return fechaingreso; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getTelefono() { return telefono; }
	string getGenero() { return genero; }

	void verificar_nit() {
			char rut[7];
			char rutvalidado[7];
			int total = 0;
			int a, b, c;
			int contador = 3;
			int acumulador = 0;
			int resto = 0;
			int digito = 0;
			
			printf("*** CALCULO DEL DIGITO VERIFICADOR RUT (CHILE) ***");
			printf("\n\n");
			printf("Ingrese el rut que ejecutar: ");
			cin >> rut;
			total = strlen(rut);
			if (total <= 7) {
				for (a = 0;a <= 7;a++) {
					if (rut[0] == rut[a]) {
						rutvalidado[0] = '0';
						rutvalidado[a + 1] = rut[0];
					}
					else {
						rutvalidado[a + 1] = rut[a];
					}
				}
			}
			else
			{
				for (b = 0;b <= 7;b++) {
					rutvalidado[b] = rut[b];
				}
			}
			for (c = 0;c <= 7;c++) {
				if (contador == 2) {
					acumulador = acumulador + ((rutvalidado[c] - 48) * contador);
					contador = 8;
				}
				else
				{
					acumulador = acumulador + ((rutvalidado[c] - 48) * contador);
				}
				contador = contador - 1;
			}
			digito = (11 - (acumulador % 11));
			if (digito >= 10) {
				if (digito == 10) {
					printf("\nEl digito verificador de su rut es: K");
				}
				else
				{
					printf("\nEl digito verificador de su rut es: 0");
				}
			}
			else
			{
				printf("\nEl digito verificador de su rut es: %d", digito);
			}
			getchar();
			getchar();
		}

	void leer() {
		system("cls");
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select *, if(genero = 1, 'Masculino','Femenino') as Genero from clientes;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "\t\tClientes" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "ID de cliente: " << fila[0] << endl;
					cout << "Nombres: " << fila[1] << endl;
					cout << "Apellidos: " << fila[2] << endl;
					cout << "NIT: " << fila[3] << endl;
					cout << "Telefono: " << fila[5] << endl;
					cout << "Correo electronico: " << fila[6] << endl;
					cout << "Fecha de ingreso: " << fila[7] << endl;
					cout << "Genero: " << fila[8] << endl;
					cout << "____________________________________________" << endl;
				}
			}
		}
		cout << "____________________________________________" << endl;
		cn.cerrar_conexion();
		system("pause");
	}


	
	void ingresar() {
		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string insertar = "INSERT INTO `proyecto_final_programacion`.`clientes`(`nombres`,`apellidos`,`NIT`,`genero`,`telefono`,`correo_electronico`,`fechaingreso`) VALUES('"+nombres+"','"+apellidos+"','"+NIT+"',if ('" + genero + "' = 'M', 1, 0),'"+telefono+"','"+correo_electronico+"','"+fechaingreso+"');";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				system("cls");
				cout << "Ingreso exitoso" << endl;
			}
		}
		else {
			system("cls");
			cout << "Hubo un error al ingresar los datos" << endl;

		}
		cn.cerrar_conexion();
		system("pause");
	}

	
	void eliminar(int id_p) {

		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string id_p1 = to_string(id_p);
			string eliminar = "DELETE from clientes where idcliente = " + id_p1 + "";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				system("cls");
				cout << "Eliminacion exitosa" << endl;

			}
		}
		else {
			system("cls");
			cout << "Hubo un error a la hora de eliminar el registro deseado" << endl;
		}
		cn.cerrar_conexion();
		system("pause");
	}

	void actualizar(int id_p) {

		int q_estado;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string id_p1 = to_string(id_p);
			string eliminar = "UPDATE `proyecto_final_programacion`.`clientes` SET `nombres` = '"+nombres+"', `apellidos` = '"+apellidos+"', `NIT` = '"+NIT+"', `genero` = '"+genero+"', `telefono` = '"+telefono+"', `correo_electronico` = '"+correo_electronico+"', `fechaingreso` = '"+fechaingreso+"' WHERE `idcliente` = "+id_p1+"";
			const char* i = eliminar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (!q_estado) {
				system("cls");
				cout << "Actualizacion exitosa" << endl;
			}
		}
		else {
			system("cls");
			cout << "Hubo un error a la hora de eliminar el registro deseado" << endl;
		}
		cn.cerrar_conexion();
		system("pause");
	}
};
