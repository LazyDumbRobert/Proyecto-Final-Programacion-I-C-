#pragma once
#include<iostream>
#include<string>

using namespace std;

class Persona {
protected:
	string nombres, apellidos, telefono, genero;

protected:
	Persona() {

	}
	Persona(string name, string lastname, string tel, string genre) {
		nombres = name;
		apellidos = lastname;
		telefono = tel;
		genero = genre;
	}


	//Metodos set y get

};