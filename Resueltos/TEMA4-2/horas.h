#ifndef DATE2_H_
#define DATE2_H_

#include <iostream>

class Horas {

public:
	int horas;
	int minutos;
	int segundos;

	Horas(); // constructor predeterminado
	Horas(int h, int m, int s); // constructor con argumentos
	Horas(const Horas& date); // constructor por copia

	bool operator==(const Horas& other) const;
	bool operator<(const Horas& other) const;
	bool operator<=(const Horas& other) const;

	friend std::ostream& operator<<(std::ostream& out, const Horas& d);
	friend std::istream& operator>>(std::istream& in, Horas& h);

	bool correctDate() const;
};
#endif /* DATE2_H_ */

