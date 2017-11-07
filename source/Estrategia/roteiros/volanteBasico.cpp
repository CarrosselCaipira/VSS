#include "roteiro.hpp"

void Roteiro::volanteBasico(Robo& r){
	//Se o robô estiver com a bola
	if(r.isRoboComBola(b.getPosicaoAtualBola(),RAIO_ATAQUE)) {
		//Se a bola está no intervalo do robô em y
		if(b.getPosicaoAtualBola().isBolaNoIntervaloYRobo()){
			//O objetivo vai ser o meio do gol do adversário
			posicionaCentroGolXYAdv(r);
		}
		//Se não está no intervalo do robô em y
		else {
			//posiciona a posição em y
			posicionaPosBolaEmY(r, b);
		}
	}
	//Se estiver na faixa superior ou na faixa inferior
	if (b.getPosicaoAtualBola().isInFaixaSuperior() || b.getPosicaoAtualBola().isInFaixaInferior()){
		//segue a bola em X, mantendo-se um robô à frente e segue a bola em y
		segueBolaEmXFrente(r, b);
		posicionaPosBolaEmY(r, b);

	}
	//Se estiver na faixa central
	else {
		//Se estiver no campo sem area gol do nosso time
		if(b.getPosicaoAtualBola().isInCampoSemAreaGolTime()){
			//marca a passagem da bola
			tangenciaLinhaFrenteAreaGol(r);
			posicionaPosBolaEmY(r, b);

		}
		//Se não estiver no campo do nosso time
		else if(b.getPosicaoAtualBola().isInCampoAdv()){
			//fica no meio de campo e segue a bola em y com 90 graus
			posiciona90Graus(r);
			posicionaPosBolaEmY(r, b);
			posicionaAtrasMeioCampo(r);
		}
	}
}
