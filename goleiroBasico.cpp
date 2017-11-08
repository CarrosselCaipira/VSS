#include "roteiro.hpp"

void Roteiro::goleiroBasico(Robo& r, posXY& b){

	//Se o robô estiver com a bola
	if(r.isRoboComBola(b, RAIO_ATAQUE)) {

		// Se a bola estiver na metade superior do campo.
		if(b.isInCampoMetadeSuperior()) {

			// Gira no sentido anti horário.
			r.atributos.set(CHUTE_GIRANDO_ANTI_HORARIO);
		}

		// Se a bola estiver na metade inferior do campo.
		else {

			// Gira no sentido horário.
			r.atributos.set(CHUTE_GIRANDO_HORARIO);
		}
	}

	// Se o robo estiver girando no sentido horário
	else if(r.atributos.test(CHUTE_GIRANDO_HORARIO)) {

		//Para de girar e fica a 90 graus
		r.atributos.reset(CHUTE_GIRANDO_HORARIO);
		Comportamento::posiciona90Graus(r);
	}

	// Se o robo estiver girando no sentido anti horário
	else if(r.atributos.test(CHUTE_GIRANDO_ANTI_HORARIO)) {

		//Para de girar e fica a 90 graus
		r.atributos.reset(CHUTE_GIRANDO_ANTI_HORARIO);
		Comportamento::posiciona90Graus(r);
	}

	//Se estiver na metade do adversário
	else if(b.isInCampoAdv()) {
		//posiciona o robô no meio do gol
		Comportamento::posicionaCentroGolXY(r);
	}

	//Se estiver na nossa metade do campo
	else {

		//Se estiver na faixa superior
		if (b.isInFaixaSuperior()) {
			//Para na trave superior
			Comportamento::posicionaTraveSuperior(r);
		}

		//Se estiver na faixa inferior
		else if (b.isInFaixaInferior()) {
			//Para na trave inferior
			Comportamento::posicionaTraveInferior(r);
		}

		//Se estiver na faixa central
		else{
			//Segue a bola em y e fica na linha do gol
			Comportamento::posicionaGolX(r);
			Comportamento::posicionaPosBolaEmY(r, b);
		}
	}
	
}
