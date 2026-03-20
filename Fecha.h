#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    /// SETTERS
    void setDia(int);
    void setMes(int);
    void setAnio(int);

    /// GETTERS
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    /// OTROS METODOS
    void Cargar();
    void Mostrar();
};



#endif // FECHA_H_INCLUDED
