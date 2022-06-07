#pragma once
#include "ConexionDB2.h"
#include "string"
#include<mysql.h>
#include<stdlib.h>
#include <windows.h>
#include <fstream>



class Compra_detalle {
private:
	string idcompra, precio_costo_unitario, nombreproducto;
	int precio_total = 0, cantidad;
	int idproducto, cantidad_productos = 0;

public:
	Compra_detalle() {

	}
	Compra_detalle(string id_compra_cs, int id_producto, int cantidad_vd, string preciounitario) {
		idcompra = id_compra_cs;
		idproducto = id_producto;
		cantidad = cantidad_vd;
		precio_costo_unitario = preciounitario;
	}

	//metodos set y get
	void setIdcompra(string id_compra) { idcompra = id_compra; }
	void setIdProducto(int id_producto) { idproducto = id_producto; }
	void setCantidad(float cantidad_vd) { cantidad = cantidad_vd; }
	void setPrecioUnitario(string preciounitario) { precio_costo_unitario = preciounitario; }


	string getIdcompra() { return idcompra; }
	int getIdProducto() { return idproducto; }
	int getCantidad() { return cantidad; }
	string getPrecioUnitario() { return precio_costo_unitario; }
	
	void ingresar() {
		int q_estado;
		string id_producto_aux;
		string cantidad_aux;
		ConexionBD2 cn = ConexionBD2();

		cn.abrir_conexion();
		if (cn.getConectar()) {
			id_producto_aux = to_string(idproducto);
			cantidad_aux = to_string(cantidad);
			string insertar = "INSERT INTO `proyecto_final_programacion`.`compras_detalle` ( `idcompra`, `idproducto`, `cantidad`, `precio_costo_unitario`)VALUES("+idcompra+","+id_producto_aux+","+cantidad_aux+","+precio_costo_unitario+");";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);

			if (q_estado) {
				cout << "Hubo un error al ingresar los datos" << endl;
			}
		}
		cn.cerrar_conexion();
	}
	

	void get_idcompra() {
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string consulta = "select max(idcompra) from compras";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					idcompra = fila[0];

				}
			}
		}
		cn.cerrar_conexion();
	}
	
	void suma_existencia(int cantidad, int codigo) {
		int q_estado;
		string cantidad_aux, codigo_aux;
		cantidad_aux = to_string(cantidad);
		codigo_aux = to_string(codigo);
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_producto_aux = to_string(idproducto);
			string consulta = "UPDATE `proyecto_final_programacion`.`productos` SET `existencia` = productos.existencia + " + cantidad_aux + " WHERE `idproducto` = " + codigo_aux + ";";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
		}
		cn.cerrar_conexion();
	}
	
	void datos_restantes_ventas_detalle() {
		int q_estado;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_producto_aux = to_string(idproducto);
			string consulta = "select precio_costo, producto from productos where idproducto = " + id_producto_aux + ";";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					precio_costo_unitario = fila[0];
					nombreproducto = fila[1];
				}
			}
		}
		cn.cerrar_conexion();
	}

	void abrir_archivo() {
		archivo = fopen("factura_compra.txt", "a+");
	}
	void cerrar_archivo() {
		fclose(archivo);
	}
	
	void imprimir_factura() {
		tifstream in(TEXT("factura_compra.txt"));
		PrintFile(in);
		in.close();
	}
	
	void lectura_productos(int codigo) {
		int q_estado;
		int sub_total = 0;
		string nombre_producto_marca, nombre_producto_marca_aux;
		ConexionBD2 cn = ConexionBD2();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_p1 = to_string(codigo);
			string consulta = "select producto,precio_costo, productos.idmarca, marcas.marca from productos inner join marcas on productos.idmarca = marcas.idmarca where idproducto = " + id_p1 + ";";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					nombre_producto_marca = fila[0];
					nombre_producto_marca_aux = fila[3];
					nombre_producto_marca = nombre_producto_marca + " " + nombre_producto_marca_aux;
					cout << "Producto: " << nombre_producto_marca << " " << "\tPrecio Unitario: " << fila[1] << " " << "\tID del producto: " << fila[2];
					cout << "\t" << "Cantidad del producto: ";
					cin >> cantidad;
					suma_existencia(cantidad, codigo);
					sub_total = cantidad * stoi(fila[1]);
					cout << "Subtotal: " << sub_total << endl;
					cout << "\n";
					cantidad_productos += 1;
					precio_total += sub_total;

					fprintf(archivo, "\n");
					fprintf(archivo, "Producto: ");
					fprintf(archivo, nombre_producto_marca.c_str());
					fprintf(archivo, "   ");
					fprintf(archivo, "Precio unitario: ");
					fprintf(archivo, fila[1]);
					fprintf(archivo, "   ");
					fprintf(archivo, "ID del producto: ");
					fprintf(archivo, (to_string(idproducto).c_str()));
					fprintf(archivo, "   ");
					fprintf(archivo, "Cantidad del producto: ");
					fprintf(archivo, (to_string(cantidad).c_str()));
					fprintf(archivo, "\n");
					fprintf(archivo, "Subtotal: ");
					fprintf(archivo, (to_string(sub_total).c_str()));
					fprintf(archivo, "\n");
				}
			}
		}
		cn.cerrar_conexion();
	}

	void cobrar() {
		float efectivo, vuelto;

		do {
			cout << "Efectivo: ";
			cin >> efectivo;

			fprintf(archivo, "Efectivo: ");
			fprintf(archivo, (to_string(efectivo).c_str()));
			fprintf(archivo, "\n");

			if (efectivo < precio_total) {
				cout << "El monto que acaba de ingresar es insuficiente, vuelva a intentarlo";
				system("pause");
			}
			else {
				vuelto = efectivo - precio_total;
				cout << "Vuelto: " << vuelto << endl;
				cout << "\n\n";
				cout << "Productos comprados " << cantidad_productos << endl;
				cout << "Tipo de pago EFECTIVO" << endl;
				cout << "\n\n";
				cout << "Gracias, vuelva pronto!" << endl;
				cout << "\n\n";

				fprintf(archivo, "Vuelto: ");
				fprintf(archivo, (to_string(vuelto).c_str()));
				fprintf(archivo, "\n");
				fprintf(archivo, "\n");
				fprintf(archivo, "Productos comprados: ");
				fprintf(archivo, (to_string(cantidad_productos).c_str()));
				fprintf(archivo, "\n");
				fprintf(archivo, "\n");
				fprintf(archivo, "Tipo de pago EFECTIVO");
				fprintf(archivo, "\n");
				fprintf(archivo, "\n");
				fprintf(archivo, "Gracias, vuelva pronto!: ");
				fprintf(archivo, "\n");
			}
		} while (efectivo < precio_total);


	}

	void ingreso_productos() {

		cin.ignore();
		while (idproducto != 0) {
			cout << "ID del producto: ";
			cin >> idproducto;
			if (idproducto != 0) {
				abrir_archivo();
				lectura_productos(idproducto);
				get_idcompra();
				datos_restantes_ventas_detalle();
				ingresar();
				cerrar_archivo();
			}
		}
		abrir_archivo();
		fprintf(archivo, "\n");
		fprintf(archivo, "\n");
		cout << "Total: " << precio_total << endl;

		fprintf(archivo, "Total: ");
		fprintf(archivo, (to_string(precio_total).c_str()));
		fprintf(archivo, "\n");
		fprintf(archivo, "\n");
		cobrar();
		cerrar_archivo();
		imprimir_factura();
		system("pause");
	}

};