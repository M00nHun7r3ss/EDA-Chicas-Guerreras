#include <iostream>
using namespace std;

#include "horas.h"


horas::horas(int h, int m, int s) : _horas(h), _minutos(m), _segundos(s) { //throws domain_error
	if (!correctDate()) throw domain_error("Hora incorrecta");
}

horas::horas(const horas& h) : _horas(), month(date.month), year(date.year) {
}

bool Date2::operator<(const Date2& other) const {
	if (year < other.year) return true;
	else if (year > other.year) return false;
	else if (month < other.month) return true;
	else if (month > other.month) return false;
	else return day < other.day;
}


/*void Date2::print() const {
	cout << day << "/" << month << "/" << year << endl;
}*/


// Función externa a la clase
ostream& operator<<(ostream& out, const Date2& d) {
	out << d.day << "/" << d.month << "/" << d.year;
	return out;
}


// Private operations

// (0 <= horas <= 23)
// (0 <= minutos <= 59)
// (0 <= segundos <= 59)
bool horas::correctDate() const {
	bool correct;

	if ((_horas < 0) || (_horas > 23) || (_minutos < 0) || (_minutos > 59) || (_segundos < 0) || (_segundos > 59)) correct = false;
	else correct = true;

	return correct;
}

