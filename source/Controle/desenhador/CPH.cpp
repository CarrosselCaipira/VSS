#include "CPH.hpp"

CPH::CPH(Robo& r, std::vector<posXY>& obs) : robo(r), posOstaculos(obs) {

}

void CPH::inicializaObstMeta() {
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

	/* Inicializa celulas livres */
	for (i = 1; i < MAX_X - 1; i++) {
		for (j = 1; j < MAX_Y - 1; j++) {
			campoPotencial.matBoolPot[i][j] = false;
			campoPotencial.matPot[i][j] = 0;
		}
	}

	/* ANALISE DE NECESSIDADE E FUNCIONALIDADE - ADICIONADO EM CBR2016 */
	// Fazer verificacao do robo goleiro estando atras da linha imaginaria
	if ((robo.getRoteiro() == GOLEIRO) && (robo.getPosicaoPrevRobo().x / DIV_CAMPO) < MAX_X / 6){
		for (i = 0; i < MAX_Y; i++) { // Parede da esquerda
			campoPotencial.matPot[MAX_X / 6][i] = 1;
			campoPotencial.matBoolPot[MAX_X / 6][i] = true;
		}
	}
	/*******************************************************************/

	/* Define Celulas que contem o objetivo do robo */
	campoPotencial.matBoolPot[(robo.getPosicaoObj().x / DIV_CAMPO)][(robo.getPosicaoObj().y / DIV_CAMPO)] = true;

	/* Parede virtual atras da bola para evitar que o robo conduza a bola contra o proprio gol */
	if (robo.getRoteiro() == ATACANTE) {
		for (j = (robo.getPosicaoObj().y / DIV_CAMPO) - 1; j <= (robo.getPosicaoObj().y / DIV_CAMPO) + 2; j++) {
			for (i = (robo.getPosicaoObj().x / DIV_CAMPO) + 1; i < (robo.getPosicaoObj().x / DIV_CAMPO) + 4; i++) {
				campoPotencial.matBoolPot[i][j] = true; // parede virtual da meta
				campoPotencial.matPot[i][j] = 1;
			}
		}
	}

	/* ANALIZAR A NECESSIDADE DESTE TRECHO. REMOVIDO NA CBR2016 */
	/* posiciona os robos do time no campo potencial */
	/*for (i = 0; i <= 2; i++) {
		if (i != indJogador) {

			// IMPORTANTE: ENTENDER CONDICAO E SUBSTITUIR POR FUNCAO BOOLEANA
			if (((robo.getPosicaoObj().x / DIV_CAMPO) < (estadoPrev[i].x / DIV_CAMPO) - 1 || (robo.getPosicaoObj().x / DIV_CAMPO) > (estadoPrev[i].x / DIV_CAMPO) + 1) && ((robo.getPosicaoObj().y / DIV_CAMPO) < (estadoPrev[i].y / DIV_CAMPO) - 1 || (robo.getPosicaoObj().y / DIV_CAMPO) > (estadoPrev[i].y / DIV_CAMPO) + 1)) {

				for (j = ((int) estadoPrev[i].x / DIV_CAMPO) - 1; j <= ((int) estadoPrev[i].x / DIV_CAMPO) + 1; j++) {
					for (k = ((int) estadoPrev[i].y / DIV_CAMPO) - 1; k <= ((int) estadoPrev[i].y / DIV_CAMPO) + 1; k++) {
						campoPotencial.matPot[j][k] = 1;
						campoPotencial.matBoolPot[j][k] = true;
					}
				}

			}
		}
	} */
	/***********************************************************/

	/* Insere no campo potencial os obstaculos (robos adversarios, por exemplo) */
	for (i = 0; i < posOstaculos.size(); i++) {
		campoPotencial.matPot[((int) posOstaculos.x / DIV_CAMPO)][((int) posOstaculos.y / DIV_CAMPO)] = 1;
		campoPotencial.matBoolPot[((int) posOstaculos.x / DIV_CAMPO)][((int) posOstaculos.y / DIV_CAMPO)] = true;
	}

}

bool CPH::calculaCampoSOR() {
	int i, j;
	float resultTemp;
	bool convergiu = true;

	do {
		convergiu = true;
		for (i = 1; i < MAX_X - 1; i++) {
			for (j = 1; j < MAX_Y - 1; j++) {
				if (campoPotencial.matBoolPot[i][j] == false) {
					resultTemp = W_SOR
							* (campoPotencial.matPot[i + 1][j]
									+ campoPotencial.matPot[i - 1][j]
									+ campoPotencial.matPot[i][j + 1]
									+ campoPotencial.matPot[i][j - 1]
									- 4 * campoPotencial.matPot[i][j]) / 4
							+ campoPotencial.matPot[i][j];
					if ((campoPotencial.matPot[i][j] - resultTemp > PRECISAO_CONVERGENCIA)
							|| (resultTemp - campoPotencial.matPot[i][j] > PRECISAO_CONVERGENCIA))
						convergiu = false;
					campoPotencial.matPot[i][j] = resultTemp;
				}

			}
		}
	} while (!convergiu);
	return convergiu;
}

void CPH::calculaVelRodas() {
	float wObj, vObj, vAnt = 0, F, dx, dy, v_CPO[2], d, angRobo, angRoboAnt, xRobo, yRobo, ang, auxAng;
	int ve, vd, pe, pd, i, j, wSignal, vSignal, flagDirection;
	double directionAngle, K_ro, K_alfa, lim = 180 / 8;
	static int count = 0;

	/* Controle dos Robôs Atacante e Defensor */
	/* NA CBR2016 ESTA CONDICAO ESTAVA DEFINIDA PARA SEMPRE VERDADEIRA ("if(true)") >> NECESSARIA ANALISE */
	if (robo.getRoteiro() == ATACANTE || robo.getRoteiro() == VOLANTE) {
		if(atributos.test(CHUTANDO) == false){

			inicializa_obst_meta();
			calcula_campo_SOR();

			robo.setEstadoAtualComoEstadoPrev();
			dx = robo.getPosicaoObj().x - xRobo;
			dy = robo.getPosicaoObj().x - yRobo;
			d = sqrt(dx * dx + dy * dy);
			i = xRobo / DIV_CAMPO;
			j = yRobo / DIV_CAMPO;

			directionAngle = atan2((double) (campoPotencial[indJogador].matPot[i][j - 1] - campoPotencial[indJogador].matPot[i][j + 1]),
								   (double) (campoPotencial[indJogador].matPot[i - 1][j] - campoPotencial[indJogador].matPot[i + 1][j]))* 180/M_PI;
			ang = (float) directionAngle;

			if (ang < 0) {
				ang += 360;
			}

			#ifdef DEBUG
				printf("[%d](%f)\n", indJogador, (float)directionAngle);
				printf("[%d](%f)\n[        ][%f][        ]\n[%f][        ][%f]\n[        ][%f][        ]\n",
					indJogador, (float) directionAngle,
					campoPotencial[indJogador].matPot[i][j + 1],
					campoPotencial[indJogador].matPot[i - 1][j],
					campoPotencial[indJogador].matPot[i + 1][j],
					campoPotencial[indJogador].matPot[i][j - 1]);
			#endif

			/**
			 * ver cálculo dos ângulos para que o robô não precise dar uma volta inteira.
			 * Utilizando flag de direção, primeiro e quarto quadrante flag = 1, e segundo e terceiro quadrante flag = -1.
			 */

			/**
			 * Início do Novo Controle de Velocidade
			 */
			if (robo.getAnguloAtualRobo() > 180) {
				robo.getAnguloAtualRobo() -= 360;
			}
			double dAng = ang - robo.getAnguloAtualRobo();
			if (dAng > 180) {
				dAng -= 360;
			}
			auxAng = dAng;
			if ((dAng <= 90 && dAng > 0) || (dAng <= 0 && dAng >= -90)) {
				flagDirection = 1;
			} else if ((dAng <= 180 && dAng > 90) || (dAng < -90 && dAng >= -180)) {
				flagDirection = -1;
				if (dAng <= 180 && dAng > 90) {
					dAng = 180 - dAng;
				} else {
					dAng = -180 - dAng;
				}
			}
			/**
			 * Início do trecho do código que deve ser alterado
			 * Alterar cálculo das velocidades angular e linear a seguir
			 */

			//Força aplicada na célula  do campo potencial
			F = KF * campoPotencial[indJogador].matPot[i][j];
			 printf("dAng = %f - %f = %f  \n", ang, robo.getAnguloAtualRobo(), dAng);

			//Velocidade do robô calculada em função da força vinda do campo potencial
			vObj = (2/MASSA_ROBO)*(F*sin(directionAngle * (M_PI/180))*(dy) + F*cos(directionAngle * (M_PI/180))*(dx)) + pow(vAnt, 2);
			K_ro = vObj/(d*cos(dAng * (M_PI/180)));
			if (vObj < 127 && vObj >= 0){
				vObj = 127 - vObj;
			} else {
				if (vObj > -127 && vObj < 0)
					vObj = 127 + vObj;
			}
			vObj = vObj*cos(dAng * (M_PI/180));

			vAnt = vObj;
			// double errorAng = atan2(sin(dAng * (M_PI/180)), cos(dAng * (M_PI/180)));
			// wObj = K_ro*sin(dAng)*cos(dAng) + PID(errorAng, angRoboAnt, angRobo);
			wObj = K_ro*sin(dAng * (M_PI/180))*cos(dAng * (M_PI/180)) + K_ALFA*dAng;
			if (wObj < 0){
				wSignal = -1;
			} else {
				wSignal = 1;
			}
			if (vObj < 0){
				vSignal = -1;
			} else {
				vSignal = 1;
			}

			if (abs(vObj) > 127)
				vObj = 127*vSignal;
			if (indJogador != indAtacante){ // Robo defensor
				if (d < RAIO_DISTANCIA){ // Se a distancia for menor que o raio de distancia aceitavel chegou no objetivo
					if (abs(vObj) > 0)
						vObj = 0;
				}
			}
			if (d > RAIO_DISTANCIA){ // Se a distancia for maior que o raio de distancia aceitavel esta errado
				if (abs(vObj) < 42)
					vObj = 42*vSignal;
			} else {
				if (abs(dAng) >= 80 || velObjetivo == 0)
					if (vObj > 0)
						vObj = 0;
			}
			switch((int) abs(vObj/21)){
				case 1:
					if (abs(wObj) > 6)
						wObj = 6 * wSignal;
					break;
				case 2:
					if (abs(wObj) > 11)
						wObj = 11 * wSignal;

					break;
				case 3:
					if (abs(wObj) > 17)
						wObj = 17 * wSignal;
					break;
				case 4:
					if (abs(wObj) > 22)
						wObj = 22 * wSignal;
					break;
				case 5:
					if (abs(wObj) > 30)
						wObj = 30 * wSignal;
					break;
				case 6:
					if (abs(wObj) > 36)
						wObj = 36 * wSignal;
					break;
				// case 7:
					// if (abs(wObj) > 42)
					// 	wObj = 42 * wSignal;
					// break;
			}

			/**
			 * Fim do trecho do código que deve ser alterado para o cálculo de
			 * velocidade considerando a função candidata de Lyapunov
			 */
			 printf("vObj = %f| wObj = %f |", vObj, wObj);
			pe = (int) ((2 * vObj - wObj * DIST_ENTRE_RODAS) / (2 * RAIO_DA_RODA)) / 21;
			 printf("pe = %d |", pe);
			pe *= flagDirection;
			if (pe > 7) {
				pe = 7;
			} else if (pe < -7)
				pe = -7;
			if (pe < 0)
				pe = -pe + 8;
			pd = (int) ((2 * vObj + wObj * DIST_ENTRE_RODAS) / (2 * RAIO_DA_RODA)) / 21;
			 printf("pd = %d |\n", pd);
			pd *= flagDirection;
			if (pd > 7) {
				pd = 7;
			} else if (pd < -7)
				pd = -7;
			if (pd < 0)
				pd = -pd + 8;
			/**
			 * Fim do novo controle de velocidade
			 */

			/**
			 * MB Após escolher a velocidade chamar a função calcula velocidade dos motores
			 * presente no controle de 2012, para evitar possíveis erros de
			 * velocidade
			 */

			cmdEnviado[0][indJogador].esq = pe * 1;
			cmdEnviado[0][indJogador].dir = pd * 1;
		/**
		 * Chute rodando no pr´oprio eixo
		 */
		} else {
			xRobo = estadoPrev[indJogador].x;
			yRobo = estadoPrev[indJogador].y;
			if (yRobo <= 65){ //Canto inferior
				cmdEnviado[0][indJogador].esq = -5 * 1;
				cmdEnviado[0][indJogador].dir = 5 * 1;
			} else { // Canto superior
				cmdEnviado[0][indJogador].esq = 5 * 1;
				cmdEnviado[0][indJogador].dir = -5 * 1;
				printf("chute esquerda\n");
			}
		}

	/**
	 * Controle do Robô Goleiro
	 */
	} else {
		double lim = 180 / 8;

		angRobo = estadoPrev[indJogador].angulo;
		xRobo = estadoPrev[indJogador].x;
		yRobo = estadoPrev[indJogador].y;
		dx = robo.getPosicaoObj().x - xRobo;
		dy = robo.getPosicaoObj().x - yRobo;
		d = sqrt(dx * dx + dy * dy);

		ang = atan2(dy, dx) * 180 / M_PI;
		if (ang < 0) {
			ang += 2 * 180;
		}
		double dAng = ang - robo.getAnguloAtualRobo();
		if (dAng < 0) {
			dAng += 2 * 180;
		}

		if (d < 10) {
			vObj = 2;
			wObj = 1;
		} else if (d < 6) {
			vObj = 0;
			wObj = 0;
		} else {
			vObj = 3;
			wObj = 1;
		}

		if (dAng < lim) {
			ve = vObj;
			vd = vObj;
		} else if (dAng < 180 / 2 - lim) {
			ve = 0;
			vd = wObj;
		} else if (dAng < 180 / 2) {
			ve = -wObj;
			vd = wObj;
		} else if (dAng < 180 / 2 + lim) {
			ve = wObj;
			vd = -wObj;
		} else if (dAng < 180 - lim) {
			ve = 0;
			vd = -wObj;
		} else if (dAng < 180 + lim) {
			ve = -vObj;
			vd = -vObj;
		} else if (dAng < 3 * 180 / 2 - lim) {
			ve = -wObj;
			vd = 0;
		} else if (dAng < 3 * 180 / 2) {
			ve = -wObj;
			vd = wObj;
		} else if (dAng < 3 * 180 / 2 + lim) {
			ve = wObj;
			vd = -wObj;
		} else if (dAng < 2 * 180 - lim) {
			ve = wObj;
			vd = 0;
		} else {
			ve = vObj;
			vd = vObj;
		}

		cmdEnviado[0][indJogador].esq = ve * 1;
		cmdEnviado[0][indJogador].dir = vd * 1;
	}
}
