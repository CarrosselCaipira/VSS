#include "CPH.hpp"

CPH::CPH(Robo& r) : robo(r) {

}

void CPH::inicializa_obst_meta() {
	int i, j, k;

	/* Inicializa paredes do campo de futebol */
	for (i = 0; i < MAX_Y; i++) { // Parede da esquerda
		campoPotencial.matPot[0][i] = 1;
		campoPotencial.matBoolPot[0][i] = true;
	}
	for (i = 0; i < MAX_Y; i++) { // Parede da direita
		campoPotencial.matPot[MAX_X - 1][i] = 1;
		campoPotencial.matBoolPot[MAX_X - 1][i] = true;
	}
	for (i = 0; i < MAX_X; i++) { // Parede de baixo
		campoPotencial.matPot[i][0] = 1;
		campoPotencial.matBoolPot[i][0] = true;
	}
	for (i = 0; i < MAX_X; i++) { // Parede de cima
		campoPotencial.matPot[i][MAX_Y - 1] = 1;
		campoPotencial.matBoolPot[i][MAX_Y - 1] = true;
	}

	/* Inicializa células livres */
	for (i = 1; i < MAX_X - 1; i++) {
		for (j = 1; j < MAX_Y - 1; j++) {
			campoPotencial.matBoolPot[i][j] = false;
			campoPotencial.matPot[i][j] = 0;
		}
	}

	/* Define Células que contém o objetivo do robô */
	campoPotencial.matBoolPot[robo.getPosicaoObj().x][robo.getPosicaoObj().y] = true;

	/* Parede virtual atrás da bola para evitar que o robô conduza a bola contra o próprio gol */
	if (indJogador == indAtacante) {
		for (j = robo.getPosicaoObj().y - 1; j <= robo.getPosicaoObj().y + 2; j++) {
			for (i = robo.getPosicaoObj().x + 1; i < robo.getPosicaoObj().x + 4; i++){
				campoPotencial.matBoolPot[i][j] = true; // parede virtual da meta
				campoPotencial.matPot[i][j] = 1;
				}
			}
	}
	for (i = 0; i <= 2; i++) {
		if (i != indJogador) {
			if ((robo.getPosicaoObj().x < estadoPrev[i].x / DIV_CAMPO - 1
					|| robo.getPosicaoObj().x > estadoPrev[i].x / DIV_CAMPO + 1)
					&& (robo.getPosicaoObj().y < estadoPrev[i].y / DIV_CAMPO - 1
							|| robo.getPosicaoObj().y > estadoPrev[i].y / DIV_CAMPO + 1))
				for (j = (int) estadoPrev[i].x / DIV_CAMPO - 1;
						j <= (int) estadoPrev[i].x / DIV_CAMPO + 1; j++) {
					for (k = (int) estadoPrev[i].y / DIV_CAMPO - 1;
							k <= (int) estadoPrev[i].y / DIV_CAMPO + 1; k++) {
						campoPotencial.matPot[j][k] = 1;
						campoPotencial.matBoolPot[j][k] = true;
					}
				}
		}
	}
	/**
	 * Insere obstáculos no campo potencial referente aos robôs adversários
	 */
	for (i = 4; i <= 6; i++) {
		campoPotencial.matPot[(int) estadoPrev[i].x / DIV_CAMPO][(int) estadoPrev[i].y
				/ DIV_CAMPO] = 1;
		campoPotencial.matBoolPot[(int) estadoPrev[i].x / DIV_CAMPO][(int) estadoPrev[i].y
				/ DIV_CAMPO] = true;

	}
}
