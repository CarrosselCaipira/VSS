#include "roteiro.hpp"

void Roteiro::volante(Robo& r){
	/* funcao de comportamento do volante */

	/*
	Duvidas:
		Ignorar previsão
		O volante utiliza a posição do atacante, mas não temos acesso a estes dados
	*/

	const posXY bolaPos = bola.getPosicaoAtualBola();
	const posXY roboPos = r.getPosicaoAtualRobo();
	const posXY atacantePos = atacante.getPosicaoAtualRobo();

	const float distBolaRoboX = bolaPos.x - roboPos.x;
	const float distBolaRoboY = bolaPos.y - roboPos.y;

	const float distRoboBolaX = roboPos.x - bolaPos.x;
	const float distRoboBolaY = roboPos.y - bolaPos.y;

	const float distBolaAtacanteX = atacantePos.x - roboPos.x;
	const float distBolaAtacanteY = atacantePos.y - roboPos.y;

	const float distBolaGolX = bolaPos.x - CENTRO_X_GOL;
	const float distBolaGolY = bolaPos.y - CENTRO_Y_GOL;

	const float distBola = sqrt(distBolaRoboX*distBolaRoboX + distBolaRoboY*distBolaRoboY);

	r.setAnguloAtualRobo(90);
	permanece_no_eixoX(*r);
	permanece_no_eixoY(*r);

	if(distRoboBolaX > TAM_ROBO / 2){
			if(!(abs(distBolaAtacanteY) <= TAM_ROBO)){
				r.setPosicaoObj(roboPos.x + TAM_ROBO*2, roboPos.y);
			}
			if(bola.getVetorSentidoAtualBola() <= 0){
				if((distBolaAtacanteX < 2 * TAM_ROBO && atacantePos.x < bolaPos.x) && abs(distBolaAtacanteY) < TAM_ROBO / 2){
					if(roboPos.y < bolaPos.y){
						r.setPosicaoObj(r.getPosicaoObj().x, r.getPosicaoObj().y - 1.5 * TAM_ROBO)
						if(r.getPosicaoObj().y < TAM_ROBO / 2){
							r.setPosicaoObj(r.getPosicaoObj().x, r.getPosicaoObj().y + TAM_ROBO)
						}
						else{
							r.setPosicaoObj(r.getPosicaoObj().x, roboPos.y - 1.5 * TAM_ROBO);
							if (r.getPosicaoObj().y > TAM_Y_CAMPO - (TAM_ROBO / 2))
								r.setPosicaoObj(r.getPosicaoObj().x, roboPos.y + TAM_ROBO);
						}
					}

				}
			}
			else{ //Se a bola esta saindo da defesa (indo p/ ataque)
				if(r.getPosicaoObj().x < TAM_X_DO_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2){ // se o robo está na área de defesa
					r.setPosicaoObj(TAM_X_DO_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2, r.getPosicaoObj().y);
				}

				if (!existeAdversarioProximo(bolaPos.x + TAM_ROBO, bolaPos.y, TAM_ROBO)) { //existeAdversarioProximo é uma função que ainda existe?
					if (distRoboBolaX > TAM_ROBO * 2 && abs(distRoboBolaY) < TAM_ROBO) { // Se o robo esta na direcao da bola e proximo a ela, retira o robo para deixar a bola passar
						//Nota: em comportamento temos uma função de desviar da bola, porem ela apenas desvia meio robo. Creio que seria melhor aumentá-la para um robo inteiro, dessa forma a função poderia ser utilizada aqui
						if (roboPos.y < bolaPos.y) {
							if (bolaPos.y - TAM_ROBO < TAM_ROBO / 2 ) //Se o robo não pode desviar da bola pro baixo, ele vai por cima
								r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y + TAM_ROBO); //Robo desviando por cima
							else
								r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y - TAM_ROBO); //Robo desviando por baixo
						} else { // roboPos.Y >= bolaPos.Y
							if (roboPos.Y + TAM_ROBO > TAM_Y_CAMPO - TAM_ROBO / 2) //Se o robo não pode desviar da bola pro baixo, ele vai por cima
								r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y + TAM_ROBO); //Robo desviando por cima
							else
								r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y - TAM_ROBO); //Robo desviando por baixo
						}
					} else { // Existe adversario perigoso mas existe atacante posicionado, entao retira volante para permitir passagem bola/atacante
						if (distBolaAtacanteX < TAM_ROBO && abs(distBolaAtacanteY) < TAM_ROBO / 2) {
							//Nota: em comportamento temos uma função de desviar da bola, porem ela apenas desvia meio robo. Creio que seria melhor aumentá-la para um robo inteiro, dessa forma a função poderia ser utilizada aqui
							if (roboPos.y < bolaPos.y) {
								if (bolaPos.y - TAM_ROBO < TAM_ROBO / 2 ) //Se o robo não pode desviar da bola pro baixo, ele vai por cima
									r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y + TAM_ROBO); //Robo desviando por cima
								else
									r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y - TAM_ROBO); //Robo desviando por baixo
							} else { // roboPos.Y >= bolaPos.Y
								if (roboPos.Y + TAM_ROBO > TAM_Y_CAMPO - TAM_ROBO / 2) //Se o robo não pode desviar da bola pro baixo, ele vai por cima
									r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y + TAM_ROBO); //Robo desviando por cima
								else
									r.setPosicaoObj(r.getPosicaoObj().x ,bolaPos.y - TAM_ROBO); //Robo desviando por baixo
							}
						}
					}
			}
		}
	}
