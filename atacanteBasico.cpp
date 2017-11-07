#include "roteiro.hpp"

void Roteiro::atacanteBasico(Robo& r, posXY& b) {

	//Se o robô estiver com a bola
	if(r.isRoboComBola(b, RAIO_ATAQUE)) {
		//Se a bola está no intervalo do robô em y
		if(r.isBolaNoIntervaloYRobo(b)){
			//O objetivo vai ser o meio do gol do adversário
			Comportamento::posicionaCentroGolXYAdv(r);
		}
		//Se não está no intervalo do robô em y
		else {
			//posiciona a posição em y
			Comportamento::posicionaPosBolaEmY(r, b);
		}
	}
	//Se estiver na metade do adversário
	else if(b.isInCampoAdv()) {
		//Se estiver na faixa superior
		if (b.isInFaixaSuperior()) {
			//Segue a bola por baixo
			Comportamento::posicionaAbaixoBola(r, b);
			Comportamento::posicionaPosBolaEmX(r, b);
		}
		//Se estiver na faixa inferior
		else if (b.isInFaixaInferior()) {
			//Segue a bola por cima
			Comportamento::posicionaAcimaBola(r, b);
			Comportamento::posicionaPosBolaEmX(r, b);
		}
		//Se estiver na faixa central
		else {
			//Segue a bola
			Comportamento::posicionaPosBola(r, b);
		}
	}
	//Se não estiver na metade do adversario
	else {
		//Espera para contra-ataquie
		Comportamento::posicionaPosBolaEmY(r, b);
		Comportamento::permaneceNoEixoX(r);
	}

}