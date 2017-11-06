#include "roteiro.hpp"
#include "auxiliares.hpp"
#include <cmath>

void Roteiro::atacanteBasico(Robo& r, Bola& b) {

	//Se o robô estiver com a bola
  if(roboComBola(b.getPosicaoAtualBola(),RAIO_ATAQUE)) {
		//Se a bola está no intervalo do robô em y
		if(bolaNoIntervaloYRobo(b.getPosicaoAtualBola())) {
			//O objetivo vai ser o meio do gol do adversário
			posicionaCentroGolXYAdv(r);
		}
		//Se não está no intervalo do robô em y
		else {
			//posiciona a posição em y
			posicionaPosBolaEmY(r, b);
		}
	}
	//Se estiver na metade do adversário
	else if(campoAdv(b.getPosicaoAtualBola())) {
		//Se estiver na faixa superior
		if (faixaSuperior(b.getPosicaoAtualBola())) {
			//Segue a bola por baixo
			posicionaAbaixoBola(r, b);
			posicionaPosBolaEmX(r, b);
		}
		//Se estiver na faixa inferior
		else if (faixaInferior(b.getPosicaoAtualBola())) {
			//Segue a bola por cima
			posicionaAcimaBola(r, b);
			posicionaPosBolaEmX(r, b);
		}
		//Se estiver na faixa central
		else {
			//Segue a bola
			posicionaPosBola(r, b);
		}
	}
	//Se não estiver na metade do adversario
	else {
		//Espera para contra-ataquie
		posicionaPosBolaEmY(r, b);
		permaneceNoEixoX(r);
	}

}
