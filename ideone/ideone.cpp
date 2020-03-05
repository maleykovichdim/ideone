#include "pch.h"
#include <iostream>
using namespace std;


class Printer {
	public:

	enum  PRINTER_TYPE { _empty = 0, _int = 1, p_int, _float, p_float, _double, p_double, _string } printer_types;

	Printer() :m_type(_empty), m_data(NULL) {}


	~Printer()
	{
		if (m_data)//was allocated
			delete[] m_data;
	}

	void print (ostream& os = std::cout) const
	{
		switch (m_type) {
		case(_empty): break;

		case(_int): 
			os << *((int*)m_small_buffer) << std::endl;
			break;

		case(p_int):
			os << "[" << *(*((int**)m_small_buffer)) << "]" << std::endl;
			break;

		case(_float):
			os << *((float*)m_small_buffer) << std::endl;
			break;

		case(p_float):
			os << "[" << *(*((float**)m_small_buffer)) << "]" << std::endl;
			break;

		case(_double):
			os << *((double*)m_small_buffer) << std::endl;
			break;

		case(p_double):
			os << "[" <<  *(*((double**)m_small_buffer)) << "]" << std::endl;
			break;

		case(_string):
			os << m_data << std::endl;
			break;

		default:
			break;

		}

	}



/////////////////////////////////////////////////////////////
	Printer & operator=(const int & v)
	{
		memcpy(m_small_buffer, &v, sizeof(int));
		m_type = _int;
		return *this;
	}

	Printer & operator=(const int * v)
	{
		memcpy(m_small_buffer, &v, sizeof(int*));
		m_type = p_int;
		return *this;
	}
/////////////////////////////////////////////////////////////
	Printer & operator=(const float & v)
	{
		memcpy(m_small_buffer, &v, sizeof(float));
		m_type = _float;
		return *this;
	}

	Printer & operator=(const float * v)
	{
		memcpy(m_small_buffer, &v, sizeof(float*));
		m_type = p_float;
		return *this;
	}
//////////////////////////////////////////////////////////////
	Printer & operator=(const double & v)
	{
		memcpy(m_small_buffer, &v, sizeof(double));
		m_type = _double;
		return *this;
	}

	Printer & operator=(const double * v)
	{
		memcpy(m_small_buffer, &v, sizeof(double*));
		m_type = p_double;
		return *this;
	}



//////////////////////////////////////////////////////////////
	Printer & operator=(const  std::string & v)
	{
		int size = (int)v.size();
		m_data = new char[size + 1];

		memcpy(m_data, v.c_str(), size);
		m_data[size] = '\0';
		m_type = _string;
		return *this;
	}
//////////////////////////////////////////////////////////////
	friend ostream& operator <<(ostream& os, const Printer& c);

protected:
	char  m_small_buffer[8];
	char * m_data;
	int m_type;//0 - not set //1 -int  //2 - * int //3 float //4 *float
};

ostream& operator<<(ostream& os, const Printer& c)
{
	c.print(os);
	return os;
}


int main() {
	Printer printer;

	printer = 42;
	printer.print(); //should print "42" to standard output

	int* value = new int(10);
	printer = value;
	printer.print(); // should print "[10]"

	*value = 20; // the value pointer did not change, changed a value by it
	printer.print(); // should print "[20]"

	float* fvalue = new float(9.81);
	printer = fvalue;
	printer.print(); // should print "[9.81]"

	*fvalue = 0.2 + 0.3;
	printer.print(); // should print "[0.5]"

	printer = std::string("Hello world");
	printer.print();
	//should print "Hello world"

	printer = 2.718281;
	printer.print();
	//should print "2.718281"

	delete fvalue;
	delete value;
	return 0;
}

#if 0
// the standard output should be:
42
[10]
[20]
[9.81]
[0.5]
Hello world
2.71828

#endif