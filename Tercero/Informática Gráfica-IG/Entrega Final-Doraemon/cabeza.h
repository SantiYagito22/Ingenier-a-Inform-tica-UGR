#include "gorrocoptero.h"
#include "nariz.h"
#include "ojos.h"
#include "boca.h"
#include "bigotes.h"

class Cabeza : public Malla3D{
protected:
    Gorrocoptero * gorrocoptero= nullptr;
    Nariz * nariz= nullptr;
    Boca * boca= nullptr;
    Bigotes * bigotes= nullptr;
    Ojos * ojos= nullptr;
    Esfera * cabeza= nullptr;
    Esfera * cabezaBlanca= nullptr;
    Material Mcabeza,Mblanco;

public:
    Cabeza();

    void draw(float giro,int modo,char letra,bool tapa,bool TenemosCono,bool suave,bool plano,bool ra);

    void cambiarAmarillo(bool poneQuita);


};