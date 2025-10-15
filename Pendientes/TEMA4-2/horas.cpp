#include <iostream>
using namespace std;

#include "horas.h"


Horas::Horas(int h, int m, int s) : horas(h), minutos(m), segundos(s) { //throws domain_error
	if (!correctDate()) throw domain_error("Hora incorrecta");
}

Horas::Horas(const Horas& h) : horas(h.horas), minutos(h.minutos), segundos(h.segundos) {
}

bool Horas::operator<(const Horas& other) const
{
	if (horas < other.horas) return true;
	else if (horas > other.horas) return false;
	else if (minutos < other.minutos) return true;
	else if (minutos > other.minutos) return false;
	else return segundos < other.segundos;
}

// Funciones externas a la clase

ostream& operator<<(ostream& out, const Horas& h) {
	out << h.horas << ":" << h.minutos << ":" << h.segundos << endl;
	return out;
}

std::istream& operator>>(istream& in, Horas& h){
	in >> h.horas;
	in.ignore(1, ':');
	in >> h.minutos;
	in.ignore(1, ':');
	in >> h.segundos;

	return in;
}


// Private operations

// (0 <= horas <= 23)
// (0 <= minutos <= 59)
// (0 <= segundos <= 59)
bool Horas::correctDate() const {
	bool correct;

	if ((horas < 0) || (horas > 23) || (minutos < 0) || (minutos > 59) || (segundos < 0) || (segundos > 59)) correct = false;
	else correct = true;

	return correct;
}

