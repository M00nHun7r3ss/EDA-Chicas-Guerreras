#ifndef DATE2_H_
#define DATE2_H_

// TAD Fecha representado como <dia,mes,año> con POO (encapsulación+privacidad)

class horas {
private:
	int _horas;
	int _minutos;
	int _segundos;

	bool correctDate() const;

public:
	horas(int h, int m, int s); // throws Error
	horas(const horas& date);

	bool operator<(const Date2& other) const;

	friend ostream& operator<<(ostream& out, const Date2& d);
	friend std::istream& operator>>(std::istream& in, const Date2& h);

	// getters
	inline int getHoras() { return _horas; }
	inline int getMinutos() { return _minutos; }
	inline int getSegundos() { return  _segundos; }
};
#endif /* DATE2_H_ */

