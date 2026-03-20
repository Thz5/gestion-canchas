#ifndef HORARIO_H_INCLUDED
#define HORARIO_H_INCLUDED

class Horario {
private:
    int hora;
    bool disponibilidad;

public:
    ///SETTERS
    void setHora(int);
    void setDisponibilidad(bool);

    ///GETTERS
    int getHora();
    bool getDisponibilidad();

    void cargar();
    void mostrar();

};
#endif // HORARIO_H_INCLUDED
