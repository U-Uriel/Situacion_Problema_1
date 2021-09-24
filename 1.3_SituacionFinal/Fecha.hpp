#include<string>
#pragma once
using std::string;

class Fecha{
    protected:
        int dia, mes, año;

    public:
        //Crea un objeto de fecha pasandole el año, mes y dia.
        Fecha(){this->año = 0; this->mes = 0; this->dia = 0;}
        Fecha(int dia, int mes, int año):
        dia(dia), mes(mes), año(año){}

        bool operator<=(Fecha const& fecha1);
        bool operator>=(Fecha const& fecha1);
        bool operator<(Fecha const& fecha1);
        bool operator>(Fecha const& fecha1);
        bool operator==(Fecha const& fecha1);
        friend std::ostream & operator<<(std::ostream & os, const Fecha & fecha);
};
bool Fecha::operator<=(Fecha const& fecha1){
    if (this->año <= fecha1.año){
        return true;
    }else if (this->año == fecha1.año){
        if (this->mes <= fecha1.mes){
            return true;
        }else if (this->mes == fecha1.mes){
            if (this->dia <= fecha1.dia){
                return true;
            }else{ //dia mayor
                return false;
            }
        }else{ //mes mayor
            return false;
        }
    }else{ //año mayor
        return false;
    }
}

bool Fecha::operator<(Fecha const& fecha1){
    if (this->año < fecha1.año){
        return true;
    }else if (this->año == fecha1.año){
        if (this->mes < fecha1.mes){
            return true;
        }else if (this->mes == fecha1.mes){
            if (this->dia < fecha1.dia){
                return true;
            }else{ //dia mayor
                return false;
            }
        }else{ //mes mayor
            return false;
        }
    }else{ //año mayor
        return false;
    }
}

bool Fecha::operator>(Fecha const& fecha1){
    if (this->año > fecha1.año){
        return true;
    }else if (this->año == fecha1.año){
        if (this->mes > fecha1.mes){
            return true;
        }else if (this->mes == fecha1.mes){
            if (this->dia > fecha1.dia){
                return true;
            }else{ //dia menor
                return false;
            }
        }else{ //mes menor
            return false;
        }
    }else{ //año menor
        return false;
    }
}

bool Fecha::operator>=(Fecha const& fecha1){
    if (this->año >= fecha1.año){
        return true;
    }else if (this->año == fecha1.año){
        if (this->mes >= fecha1.mes){
            return true;
        }else if (this->mes == fecha1.mes){
            if (this->dia >= fecha1.dia){
                return true;
            }else{ //dia menor
                return false;
            }
        }else{ //mes menor
            return false;
        }
    }else{ //año menor
        return false;
    }
}

bool Fecha::operator==(Fecha const& fecha1){
    return ((this->año == fecha1.año) &&
            (this->mes == fecha1.mes) &&
            (this->dia == fecha1.dia) );
}

std::ostream & operator<<(std::ostream & os, const Fecha & fecha){
    os << fecha.dia << "-";
    os << fecha.mes << "-";
    os << fecha.año;

    return os;
}

