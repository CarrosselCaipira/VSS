#include "roteiro.hpp"

void Roteiro::goleiro(Robo& r, Tecnico* tecnico){

    // A bola esta na metade adversaria do campo
    if (b.isInCampoAdv()){
        // Posiciona o goleiro em 1/3 da distância y da bola em relacao ao meio vertical
        Comportamento::posicionaGolX(r);
		Comportamento::posicionaPosBolaEmYPonderado(r, b);
    }

    // A bola esta na nossa metade do campo
    else {
        // Segue a bola em Y
        if(b.isInFaixaSuperior()){
            Comportamento::posicionaTraveSuperior(r);
        }
        else if (b.isInFaixaInferior()){
            Comportamento::posicionaTraveInferior(r);
        }
        else{
            Comportamento::posicionaGolX(r);
            Comportamento::posicionaPosBolaEmY(r, b);
        }
    }

}
