#include "roteiro.hpp"
#include "tecnicoOfensivo.hpp"

void Roteiro::goleiro(Robo& r, Tecnico* tecnico){

    if(tecnico == NULL) {
        std::cerr << "ERRO: @Roteiro::atacante. Ponteiro para tecnico nao definido. Saindo..." << '\n';
        exit(1);
    }

    TecnicoOfensivo* Tecnico = (TecnicoOfensivo*) tecnico; /* convertendo um tecnico generico em um TecnicoOfensivo. */
    posXY b = Tecnico->getPosAtualBola();        
    
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
            Comportamento::posicionaPosBolaEmYObj(r, b);
        }
    }

}
