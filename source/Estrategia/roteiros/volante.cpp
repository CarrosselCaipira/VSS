#include "roteiro.hpp"

void Roteiro::volante(Robo& r){
	/* funcao de comportamento do volante */

	/*
	Duvidas e comentários:
		O código antigo começava setando as variavais pelo estadoPrev.
		Não sabemos se ainda funciona dessa forma, logo isso foi omitido do inicio do código.

		O volante utiliza a posição do atacante, mas não temos acesso a estes dados, estamos
		traduzindo o código como se esse acesso estivesse acontecendo. Parece que a posição
		do atacante é frequentemente utilizada.

		O volante muitas vezes se preocupa em desviar da bola em várias situações, creio que seria
		bom uma funça para fazer isso. (Ver se isso pode ser aprovado, pois deixaria o código mais limpo).

		existeAdversarioProximo

		chuteGirando

		trocaEminente

		verificação da area

		comportamento faixaSuperior e faixaInferior estão esquisitos
	*/

	const posXY bolaPos = bola.getPosicaoAtualBola(); // Posição atual da Bola
	const posXY roboPos = r.getPosicaoAtualRobo(); // Posição atual do Volante
	const posXY atacantePos = atacante.getPosicaoAtualRobo(); // Posição atual do Atacante

  // Distância entre a Bola e o Volante
	const float distBolaRoboX = bolaPos.x - roboPos.x;
	const float distBolaRoboY = bolaPos.y - roboPos.y;

  // Distância entre o Volante e a Bola
	const float distRoboBolaX = -distBolaRoboX;
	const float distRoboBolaY = -distBolaRoboY;

	const float distBolaAtacanteX = bolaPos.x - atacantePos.x;
	const float distBolaAtacanteY = bolaPos.y - atacantePos.y;

  // Distância entre a Bola e o Gol
	const float distBolaGolX = bolaPos.x - CENTRO_X_GOL;
	const float distBolaGolY = bolaPos.y - CENTRO_Y_GOL;

	//const float distBola = sqrt(distBolaRoboX*distBolaRoboX + distBolaRoboY*distBolaRoboY);

  const bool robo_abaixo_bola = roboPos.y < bolaPos.y;

	r.setAnguloObj(90);
	posiciona_segue_bola(*r);  // Por padrao fica alinhado com a bola
	permanece_no_eixoX(*r);  // Por padrao mantem o robo no eixo x atual

	if(distRoboBolaX > TAM_ROBO / 2){ // Se bola esta atras do robo (passou a defesa)
			if(!(abs(distBolaAtacanteY) <= TAM_ROBO)){ // Robo atacante não está alinhado com a bola em y
				r.setPosicaoObj(roboPos.x + TAM_ROBO*2, roboPos.y); // Volante tenta se manter à uma certa distância atrás da bola, tanto para evitar gol contra, quanto para bloquear a passagem de robos adversários
			}
			if(bola.getVetorSentidoAtualBola() <= 0){ // Se bola parada ou indo para o nosso gol
				if((distBolaAtacanteX < 2 * TAM_ROBO && atacantePos.x < bolaPos.x) && abs(distBolaAtacanteY) < TAM_ROBO / 2){ // Se tem atacante posicionado para empurrar a bola, entao retira volante do caminho
					if (robo_abaixo_bola) {
						if (bolaPos.y - TAM_ROBO < TAM_ROBO / 2 ) // Se o robo não pode desviar da bola pro baixo, ele vai por cima
							posiciona_acima_bola(*r); // Robo desviando por cima
						else
							posiciona_abaixo_bola(*r) // Robo desviando por baixo
					} else {
						if (roboPos.Y + TAM_ROBO > TAM_Y_CAMPO - TAM_ROBO / 2) // Se o robo não pode desviar da bola pro baixo, ele vai por cima
							posiciona_acima_bola(*r); // Robo desviando por cima
						else
							posiciona_abaixo_bola(*r) // Robo desviando por baixo
					}
				}
			}
			else{ // Se a bola esta saindo da defesa (indo p/ ataque)
				//Este if pode ser removido? Esta é uma condição importante para o robo não entrar na nossa area, mas há um outro if igual no final do código
				if(r.getPosicaoObj().x < TAM_X_DO_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2){ // Se o robo está na área de defesa
					r.setPosicaoObj(TAM_X_DO_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2, r.getPosicaoObj().y);
				}

				if (!existeAdversarioProximo(bolaPos.x + TAM_ROBO, bolaPos.y, TAM_ROBO)) { // existeAdversarioProximo é uma função que ainda existe?
					if (distRoboBolaX > TAM_ROBO * 2 && abs(distRoboBolaY) < TAM_ROBO) { // Se o robo esta na direcao da bola e proximo a ela, retira o robo para deixar a bola passar
						if (robo_abaixo_bola) {
							if (bolaPos.y - TAM_ROBO < TAM_ROBO / 2 ) // Se o robo não pode desviar da bola pro baixo, ele vai por cima
								posiciona_acima_bola(*r); // Robo desviando por cima
							else
								posiciona_abaixo_bola(*r) // Robo desviando por baixo
						} else {
							if (roboPos.Y + TAM_ROBO > TAM_Y_CAMPO - TAM_ROBO / 2) //Se o robo não pode desviar da bola pro baixo, ele vai por cima
								posiciona_acima_bola(*r); // Robo desviando por cima
							else
								posiciona_abaixo_bola(*r) // Robo desviando por baixo
						}
					} else { // Existe adversario perigoso mas existe atacante posicionado, entao retira volante para permitir passagem bola/atacante
						if (distBolaAtacanteX < TAM_ROBO && abs(distBolaAtacanteY) < TAM_ROBO / 2) {
							if (robo_abaixo_bola) {
								if (bolaPos.y - TAM_ROBO < TAM_ROBO / 2 ) // Se o robo não pode desviar da bola pro baixo, ele vai por cima
									posiciona_acima_bola(*r); // Robo desviando por cima
								else
									posiciona_abaixo_bola(*r); // Robo desviando por baixo
							} else{
								if (roboPos.y + TAM_ROBO > TAM_Y_CAMPO - TAM_ROBO / 2) // Se o robo não pode desviar da bola pro baixo, ele vai por cima
									posiciona_acima_bola(*r); // Robo desviando por cima
								else
									posiciona_abaixo_bola(*r) // Robo desviando por baixo
							}
						}
					}
			}
		}
	} else if (bolaPos.x < roboPos.x + TAM_ROBO / 2) { // Se bola esta na mesma linha do robo (ninguem esta a frente)
		if (vetorSentidoEmXBola <= 0) { // Se bola parada ou indo para o gol
			if (abs(distBolaRoboY) > TAM_ROBO * 2) { // Robo nao esta na direcao da bola, evita robo voltar para a bola e empurra-la para o gol fazendo contra
				r.setObjetivo(bolaPos.x - TAM_ROBO * 1.5, r.getPosicaoObj()); // Reposiciona na linha de defesa, tentando recolocar robo entre a bola e o nosso gol
			} else {
				r.setObjetivo(bolaPos.x + TAM_ROBO * 1.5, r.getPosicaoObj()); // Mantem a 1 robos a frente da bola
				// Verificar outros robos e tentar se posicionar antes da bola (futuro)
			}
		} else if (!existeAdversarioProximo(bolaPos.x + TAM_ROBO, bolaPos.y, TAM_ROBO)) {
			if (robo_abaixo_bola) {
				posiciona_abaixo_bola(*r); // Robo desviando por baixo
			} else {
				posiciona_acima_bola(*r); // Robo desviando por cima
			}
		} else { // Existe adversario perigoso mas existe atacante posicionado, entao retira volante para permitir passagem bola/atacante
			if (distBolaAtacanteX < TAM_ROBO && abs(distBolaAtacanteY) < TAM_ROBO / 2) {
				if (robo_abaixo_bola) {
					posiciona_abaixo_bola(*r); // Coloca o robo para a direita da bola
				} else {
					posiciona_acima_bola(*r); // Coloca o robo para a esquerda da bola
				}
			}
		}
	} else { // Se a bola esta aa frente do robo (no ataque)
		if (abs(distRoboBolaY) <= TAM_ROBO / 2 && distBolaRoboX < TAM_ROBO * 5 && estadoAtacante != ATACA && atacantePos.X > (roboPos.X + 4 * TAM_ROBO)) { // SBAI 2009 - Se isso é verdadeiro, o Volante e o atacante trocam de posições
      /* !!O segmento a seguir FAZ PARTE DO CÓDIGO, não são só comentários.
			É que existe a dúvida de como eles podem ser feitos nesse novo código

			trocarVolanteAtacante = indVolante; -  Creio que não funcionará mais desse jeito
			estadoAtacante = ATACA; //Coloca estado atacando - Creio que não funcionará mais desse jeito
			velObjetivo = 7; - aparentemente não setamos mais diretamente a velocidade dos robos
			*/
			posiciona_segue_bola(*r); // Objetivo inicial do Volante que se tornou Atacante é seguir a bola
			r.setAnguloObj(90);
		} else {
			if (abs(distRoboBolaY) <= TAM_ROBO / 2 && distBolaRoboX < TAM_ROBO / 2 + 4) {
				// Se a bola estiver perto do Volante no eixo y, e em frente ao robô em direção ao campo adversário X,
				// Ele realiza o chute girando. Caso contrário, o mesmo não é realizado.
				chuteGirando[indVolante] = true;
			} else {
				chuteGirando[indVolante] = false;
			}
			r.setObjetivo(bolaPos.x - TAM_ROBO * 2, bolaPos.y); //sbai2009 - o robo fica à uma certa distancia em x da bola, mas segue ela em y

			if (!campoTime(bolaPos)) { //Se a bola passou do meio de campo
				if (CENTRO_X_GOL - bolaPos.x != 0) {
					r.setPosicaoObj(r.getPosicaoObj().x,  CENTRO_Y_GOL - (CENTRO_Y_GOL - yBola) * (CENTRO_X_GOL - xObjetivo) / (CENTRO_X_GOL - xBola)); //Posiciona robo alinhado para chutar
					if (r.getPosicaoObj().y < TAM_ROBO / 2) // Se o robo estiver com o objetivo além da parede inferior, ele não vai tentar atravessa-la
						r.setObjetivo(r.getPosicaoObj().x, TAM_ROBO / 2);
					else if (yObjetivo > TAM_Y_CAMPO - TAM_ROBO / 2) // Se o robo estiver com o objetivo além da parede superior, ele não vai tentar atravessa-la
  					r.setObjetivo(r.getPosicaoObj().x, TAM_Y_CAMPO - TAM_ROBO / 2);
				} else {
					posicionaCentroCampoY(*r)
				}
				r.setAnguloObj(atang2(CENTRO_Y_GOL - bolaPos.y, CENTRO_X_GOL - bolaPos.x));
			}
		}
	}

	if ((roboPos.x - atacantePos.x) * (roboPos.y - atacantePos.y) + dy < TAM_ROBO * TAM_ROBO * 4) { // Se robos muito proximos - onde esta proximidade é definida pelo valor arbitrário (TAM_ROBO * 2)^2
		if (atacantePos.y > roboPos.y ) //Repele em Y
			r.setPosicaoObj(r.getPosicaoObj().x, atacantePos.y - TAM_ROBO * 2);
		else
			r.setPosicaoObj(r.getPosicaoObj().x, atacantePos.y + TAM_ROBO * 2);

		if (atacantePos.x > roboPos.x) //Repele em X
			r.setPosicaoObj(atacantePos.x - TAM_ROBO * 2, r.getPosicaoObj().y);
		else
			r.setPosicaoObj(atacantePos.x + TAM_ROBO * 2, r.getPosicaoObj().y);
  }

	if (xRobo > TAM_X_CAMPO - TAM_X_DO_GOL * 1.5) {
		xObjetivo = TAM_X_CAMPO * 0.8;
		yObjetivo = TAM_Y_CAMPO / 2;
	}

	if(r.getPosicaoObj().x < TAM_X_DO_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2){ // Se o robo está na área de defesa
		r.setPosicaoObj(TAM_X_DO_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2, r.getPosicaoObj().y);
	}

	if (!campoTime(bolaPos)) { // A bola está na metade do campo adversario
		posiciona_atras_do_meio_campo(r);
		if (faixaSuperior(bolaPos)){// Guarda a diagonal do meio quando a bola esta no canto superior do ataque
			r.setPosicaoObj(r.getPosicaoObj().x, TAM_Y_CAMPO/2 + TAM_Y_DO_GOL/2); //Poderia ser usado posiciona_faixa_superior, mas essa função está estranha
		} else if (faixaInferior(bolaPos)){ // Guarda a diagonal do meio quando a bola esta no canto inferior do ataque
			yObjetivo = TAM_Y_CAMPO/2 - TAM_Y_DO_GOL/2;
		}
		if (bolaPos.x <= atacantePos.x){// Se passou do atacante acompanha a bola tentando bloquear
			r.setPosicaoObj(r.getPosicaoObj().x, bolaPos.y);
		}
	}
	if ((xObjetivo <= TAM_X_DO_GOL + 2 * TAM_X_AREA + TAM_ROBO / 2) || (xRobo <= TAM_X_DO_GOL + 2 * TAM_X_AREA + TAM_ROBO / 2)) {
		xObjetivo = TAM_X_DO_GOL + 2 * TAM_X_AREA + TAM_ROBO / 2;
	}

	if (trocaEminente) { //trocaEminente é definido na estratégia do goleiro
		xObjetivo = TAM_X_AREA;
		yObjetivo = TAM_Y_CAMPO/2;
	}

	objetivoRobo[indVolante].x = xObjetivo;
	objetivoRobo[indVolante].y = yObjetivo;
	objetivoRobo[indVolante].angulo = angObjetivo;
	objetivoRobo[indVolante].vel = velObjetivo;

  //FIM da estratégia do volante, essa última parte precisa ser traduzida
}
