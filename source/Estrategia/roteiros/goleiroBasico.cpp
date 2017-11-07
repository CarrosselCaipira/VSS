#include "roteiro.hpp"

void Roteiro::goleiroBasico(Robo& r){

	//Se o robô estiver com a bola
	if(r.isRoboComBola(b.getPosicaoAtualBola(),RAIO_ATAQUE)) {

		// Se estiver na metade superior do campo.
		if(b.getPosicaoAtualBola().isInCampoMetadeSuperior()) {

			// Gira no sentido anti horário.
			r.atributos.set(CHUTE_GIRANDO_ANTI_HORARIO);
		}

		// Se estiver na metade inferior do campofico.
		else {

			// Gira no sentido horário.
			r.atributos.set(CHUTE_GIRANDO_HORARIO);
		}
	}

	// Se o robo estiver girando no sentido horário
	else if(r.atributos.test(CHUTE_GIRANDO_HORARIO)) {

		//Para de girar e fica a 90 graus
		r.atributos.reset(CHUTE_GIRANDO_HORARIO);
		posiciona90Graus(r);
	}

	// Se o robo estiver girando no sentido anti horário
	else if(r.atributos.test(CHUTE_GIRANDO_ANTI_HORARIO)) {

		//Para de girar e fica a 90 graus
		r.atributos.reset(CHUTE_GIRANDO_ANTI_HORARIO);
		posiciona90Graus(r);
	}

	//Se estiver na metade do adversário
	else if(b.getPosicaoAtualBola().isInCampoAdv()) {
		//posiciona o robô no meio do gol
		posicionaCentroGolXY(r);
	}

	//Se estiver na nossa metade do campo
	else {

		//Se estiver na faixa superior
		if (b.getPosicaoAtualBola().isInFaixaSuperior()) {
			//Para na trave superior
			posicionaTraveSuperior(r);
		}

		//Se estiver na faixa inferior
		else if (b.getPosicaoAtualBola().isInFaixaInferior()) {
			//Para na trave inferior
			posicionaTraveInferior(r);
		}

		//Se estiver na faixa central
		else{
			//Segue a bola em y e fica na linha do gol
			posicionaGolX(r);
			posicionaPosBolaEmY(r, b);
		}
	}
}
