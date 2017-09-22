#include "roteiro.hpp"
#include "auxiliares.hpp"
#include <cmath>

void Roteiro::atacante(Robo& r){
	
	posXY bolaPos = bola.getPosicaoAtualBola();
	posXY roboPos = r.getPosicaoAtualRobo();

	float distBolaRoboX = bolaPos.x - roboPos.x;
	float distBolaRoboY = bolaPos.y - roboPos.y;

	float distBolaGolX = bolaPos.x - CENTRO_X_GOL;
	float distBolaGolY = bolaPos.y - CENTRO_Y_GOL;

	float distBola = sqrt(distBolaRoboX*distBolaRoboX + distBolaRoboY*distBolaRoboY);

	roboPos = r.getPosicaoPrevRobo();

	if (distBola < RAIO_ATACA) { 

		// estadoAtacante = ATACA; ?

		if ((distBolaRoboX < TAM_ROBO) && (abs(distBolaRoboY) < TAM_ROBO / 2))
			r.setPosicaoObj(roboPos.x, CENTRO_Y_GOL);
		else
			r.setPosicaoObj(roboPos.x, CENTRO_Y_GOL);

		r.setPosicaoObj(CENTRO_X_GOL, CENTRO_Y_GOL);

		r.setAnguloObj(atang2x(-distBolaGolY, -distBolaGolX));

	} else {
		
		//estadoAtacante = POSICIONA; ?
		r.setAnguloObj(atang2x(-distBolaGolY, -distBolaGolX));
		r.setPosicaoObj(bolaPos);
	}

	posXY posOBj = r.getPosicaoObj();

	// O objetivo esta dentro da area do nosso gol? (antes da linha da area do nosso gol)
	if (posObj.x < TAM_X_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2) {
		if (bolaPos.x > roboPos.x && bolaPos.x > INICIO_AREA_ATUACAO_ATACANTE)
			r.setPosicaoObj(posBola.x, r.getPosicaoObj().y);
		else
			r.setPosicaoObj(INICIO_AREA_ATUACAO_ATACANTE, r.getPosicaoObj().y);
	}
	/*
	A bola esta no canto superior direito ou no canto inferior direito? (quadrado inutil ("zonas de escanteio"))
	*/
	if (bolaPos.x > 140 && bolaPos.y >= 100 || bolaPos.x > 140 && bolaPos.y <= 30) {
		r.setPosicaoObj(140 - TAM_ROBO / 2, r.getPosicaoObj().y);
		//r.setVelocidadeObj(0, 0); ???
	}


	if (bolaPos.x < TAM_X_CAMPO / 2 && posBola.x < roboPos.x) {
		
		if (bolaPos.y > TAM_Y_CAMPO / 2 + TAM_Y_GOL / 2) {
			// Posicionamento estrategico
			// Posiciona o robo atras da linha vertical do meio de campo (25cm atras do meio de campo)
			r.setPosicaoObj(TAM_X_GOL + 2 * TAM_X_AREA_GOL + 20, 22);
		}
		else if (bolaPos.y < TAM_Y_CAMPO / 2 - TAM_Y_GOL / 2) {
			// Posicionamento estrategico
			// Posiciona o robo atras da linha vertical do meio de campo (25cm atras do meio de campo)
			r.setPosicaoObj(TAM_X_GOL + 2 * TAM_X_AREA_GOL + 20, TAM_Y_CAMPO - 22);
		} else {
			// Posicionamento estrategico
			// Posiciona o robo no meio do campo
			r.setPosicaoObj(TAM_X_CAMPO / 2, TAM_Y_CAMPO / 2);
		}
		
	}
}
