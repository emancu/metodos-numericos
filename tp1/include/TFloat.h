/******************************************************
 * Clase TFloat - Versi�n 1.01
 *
 * La clase TFloat encapsula el comportamiento de una
 * aritm�tica finita de punto flotante que utiliza una
 * cantidad arbitraria de bits en la representaci�n de
 * la mantisa.
 *
 * La clase est� basada en el tipo de datos double de C++
 * y por lo tanto la m�xima precisi�n para la mantisa est�
 * limitada a 52 bits.
 *
 * Esta clase fue desarrollada por el grupo de docentes del
 * laboratorio de M�todos Num�ricos (DC-FCEyN-UBA) con el
 * objetivo de que sea utilizada por los alumnos de esta
 * materia en el desarrollo de los trabajos pr�cticos de la
 * misma.
 *
 * Esta implementaci�n puede contener errores. En caso de
 * encontrar alg�n error, se agradecer� que el mismo sea
 * informado a metnum-labo@dc.uba.ar para que pueda ser
 * corregido en las futuras versiones.
 *
 *****************************************************/

#ifndef __TFLOAT_H__
#define __TFLOAT_H__

#include <iostream>
#include <bitset>

using namespace std;

class TFloat
{
  public:
	/**
	 * Constructores y destructor
	 * El par�metro t en cada constructor indica la cantidad
	 * de bits de mantisa que se desean usar en el TFloat
	 */
    TFloat();
	TFloat(size_t t);
	TFloat(double f, size_t t);
	TFloat(float f, size_t t);
	TFloat(int i, size_t t);
	~TFloat(){}

	/**
	 * Los siguientes sirven para setear y obtener la precisi�n
	 * utilizada por el TFloat
	 */
	size_t precision() { return _t; } const
	void set_precision(const size_t t) { _t = (t <= 52? t : 52); }

	// Operadores de asignacion y comparacion
	void operator=(const TFloat& );
	void operator=(const double& );
	bool operator==(const TFloat& ) const;

	// Operadores aritm�ticos
	TFloat operator+(const TFloat&) const;
	TFloat operator-(const TFloat&) const;
	TFloat operator*(const TFloat&) const;
	TFloat operator/(const TFloat&) const;

	// Operadores aritm�ticos (que reciben un tipo primitivo)
	TFloat operator+(const double&) const;
	TFloat operator-(const double&) const;
	TFloat operator*(const double&) const;
	TFloat operator/(const double&) const;

	/**
	 * La siguiente funci�n calcula el valor del n�mero e
	 * elevado al valor del TFloat
	 */
	TFloat exponencial() const;

	/**
	 * La siguiente funci�n devuelve el valor del TFloat en un
	 * double. Esta funci�n sirve por ejemplo para imprimir por
	 * pantalla el valor del TFloat.
	 */
	double dbl() const;

private:
	size_t _t;
	double _valor;
	void recortar();
};

#endif //__TFLOAT_H__
