#ifndef DATE2_H_
#define DATE2_H_

// TAD Fecha representado como <dia,mes,año> con POO (encapsulación+privacidad)

class Horas {

public:
	int horas;
	int minutos;
	int segundos;

	Horas(int h, int m, int s); // throws Error
	Horas(const Horas* date);

	bool operator<(const Horas& other) const;

	friend ostream& operator<<(ostream& out, const Horas* d);
	friend istream& operator>>(istream& in, Horas* h);

	bool correctDate() const;
private:
};
#endif /* DATE2_H_ */

