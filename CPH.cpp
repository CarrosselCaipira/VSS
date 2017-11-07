#include "CPH.hpp"

CPH::CPH(Robo& r, std::vector<posXY>& obs) : robo(r), posOstaculos(obs) {

}

void CPH::inicializaObstMeta() {
	int i, j, k;

	/* Inicializa paredes do campo de futebol */
	for (i = 0; i < MAX_Y; i++) {

		for (j=0; j<MAX_X; j++) {

			if (i==0 || i==MAX_Y-1 || j==0 || j==MAX_X-1) {

				campoPotencial.matPot[i][j] = 1;
				campoPotencial.matBoolPot[i][j] = true;
			}

			else {

				campoPotencial.matPot[i][j] = 0;
				campoPotencial.matBoolPot[i][j] = false;
			}
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

	/* Define Celula que contem o objetivo do robo */
	campoPotencial.matBoolPot[(int)(robo.getPosicaoObj().x / DIV_CAMPO)][(int)(robo.getPosicaoObj().y / DIV_CAMPO)] = true;

	/* Parede virtual atras da bola para evitar que o robo conduza a bola contra o proprio gol */
	if (robo.getRoteiro() == ATACANTE_BASICO) {
		for (j = (robo.getPosicaoObj().y / DIV_CAMPO) - 1; j <= (robo.getPosicaoObj().y / DIV_CAMPO) + 2; j++) {
			for (i = (robo.getPosicaoObj().x / DIV_CAMPO) + 1; i < (robo.getPosicaoObj().x / DIV_CAMPO) + 4; i++) {
				campoPotencial.matBoolPot[i][j] = true; // parede virtual da meta
				campoPotencial.matPot[i][j] = 1;
			}
		}
	}

	/* ANALIZAR A NECESSIDADE DESTE TRECHO. REMOVIDO NA CBR2016 */
	/* posiciona os robos do time no campo potencial */
	/*for (i = 0; i < 3; i++) {
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
		campoPotencial.matPot[((int) posOstaculos[i].x / DIV_CAMPO)][((int) posOstaculos[i].y / DIV_CAMPO)] = 1;
		campoPotencial.matBoolPot[((int) posOstaculos[i].x / DIV_CAMPO)][((int) posOstaculos[i].y / DIV_CAMPO)] = true;
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

					resultTemp = W_SOR * (campoPotencial.matPot[i + 1][j]
								 + campoPotencial.matPot[i - 1][j]
								 + campoPotencial.matPot[i][j + 1]
								 + campoPotencial.matPot[i][j - 1]
								 - 4 * campoPotencial.matPot[i][j]) / 4
								 + campoPotencial.matPot[i][j];

					if ((campoPotencial.matPot[i][j] - resultTemp > PRECISAO_CONVERGENCIA) || (resultTemp - campoPotencial.matPot[i][j] > PRECISAO_CONVERGENCIA))

						convergiu = false;

					campoPotencial.matPot[i][j] = resultTemp;
				}

			}
		}
	} while (!convergiu);

	return convergiu;
}

void CPH::calculaVelRodas() {
	posXY distObjRobo;
	int flagDirection, i, j, wSignal, vSignal;
	float ang, directionAngle, distEuclidianaObjRobo, vObj, wObj, K_ro, vRodaEsq, vRodaDir;
	float forcaCelulaCampoPot; /**< Força aplicada na célula do campo potencial */

	/* Controle dos Robôs Atacante e Defensor */
	/* NA CBR2016 ESTA CONDICAO ESTAVA DEFINIDA PARA SEMPRE VERDADEIRA ("if(true)") >> NECESSARIA ANALISE */
	if (robo.getRoteiro() == ATACANTE_BASICO || robo.getRoteiro() == VOLANTE_BASICO) {
		if(robo.atributos.test(CHUTE_GIRANDO_HORARIO))
			robo.setVelocidadeAtualRobo(-5, 5);
		else if(robo.atributos.test(CHUTE_GIRANDO_ANTI_HORARIO))
			robo.setVelocidadeAtualRobo(5, -5);
		else {

			CPH::inicializaObstMeta();
			CPH::calculaCampoSOR();

			robo.setEstadoAtualComoEstadoPrev();
			/* analizar utilidade de salvarmos estado anterior, atualmente removida */
			robo.getDistObjRobo(distObjRobo);
			distEuclidianaObjRobo = robo.getDistEuclianaObjRobo();
			i = robo.getPosicaoAtualRobo().x / DIV_CAMPO;
			j = robo.getPosicaoAtualRobo().y / DIV_CAMPO;

			directionAngle = atan2((double) (campoPotencial.matPot[i][j - 1] - campoPotencial.matPot[i][j + 1]),
								   (double) (campoPotencial.matPot[i - 1][j] - campoPotencial.matPot[i + 1][j])) * 180 / M_PI;
			ang = (float) directionAngle;

			if (ang < 0) {
				ang += 360;
			}

			/* EH INTERESSANTE SUBSTITUIRMOS ESSAS DIRETIVAS DE PRE-COMPILACAO POR ALGUMA FORMA MAIS DINAMICA PARA MOSTRAR DADOS PARA DEBUG - UMA CLASSE QUE CONTENHA ESSA INFORMACAO (EM DEBUG OU NAO) TALVEZ? */
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
			if (float anguloAtual = robo.getAnguloAtualRobo() > 180) {
				robo.setAnguloAtualRobo(anguloAtual - 360);
			}

			double dAng = ang - robo.getAnguloAtualRobo();
			if (dAng > 180) {
				dAng -= 360;
			}

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

			//Força aplicada na célula do campo potencial
			forcaCelulaCampoPot = KF * campoPotencial.matPot[i][j];

			#ifdef DEBUG
			 printf("dAng = %f - %f = %f  \n", ang, robo.getAnguloAtualRobo(), dAng);
			#endif

			//Velocidade do robô calculada em função da força vinda do campo potencial
			vObj = (2 / MASSA_ROBO) * (forcaCelulaCampoPot * sin(directionAngle * (M_PI / 180)) * (distObjRobo.y) + forcaCelulaCampoPot * cos(directionAngle * (M_PI / 180)) * (distObjRobo.x));

			K_ro = vObj/(distEuclidianaObjRobo * cos(dAng * (M_PI / 180)));

			if (vObj < 127 && vObj >= 0){
				vObj = 127 - vObj;
			}
			else {
				if (vObj > -127 && vObj < 0)
					vObj = 127 + vObj;
			}

			vObj = vObj * cos(dAng * (M_PI / 180));

			wObj = K_ro * sin(dAng * (M_PI/180)) * cos(dAng * (M_PI / 180)) + K_ALFA * dAng;

			if (wObj < 0){
				wSignal = -1;
			}
			else {
				wSignal = 1;
			}

			if (vObj < 0){
				vSignal = -1;
			}
			else {
				vSignal = 1;
			}

			if (abs(vObj) > 127)
				vObj = 127 * vSignal;
			if (robo.getRoteiro() == ATACANTE_BASICO){ // Robo defensor
				if (distEuclidianaObjRobo < RAIO_DISTANCIA){ // Se a distancia for menor que o raio de distancia aceitavel chegou no objetivo
					if (abs(vObj) > 0)
						vObj = 0;
				}
			}
			if (distEuclidianaObjRobo > RAIO_DISTANCIA){ // Se a distancia for maior que o raio de distancia aceitavel esta errado
				if (abs(vObj) < 42)
					vObj = 42 * vSignal;
			} else {
				if (abs(dAng) >= 80)
					if (vObj > 0)
						vObj = 0;
			}
			switch((int) abs(vObj / 21)){
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
			/* RODA ESQUERDA */
			vRodaEsq = (int) ((2 * vObj - wObj * DIST_ENTRE_RODAS) / (2 * RAIO_DA_RODA)) / 21;
			vRodaEsq *= flagDirection;
			if (vRodaEsq > 7) {
				vRodaEsq = 7;
			}
			else {
				if (vRodaEsq < -7)
					vRodaEsq = -7;
			}
			if (vRodaEsq < 0)
				vRodaEsq = -vRodaEsq + 8;

			/* RODA DIREITA */
			vRodaDir = (int) ((2 * vObj + wObj * DIST_ENTRE_RODAS) / (2 * RAIO_DA_RODA)) / 21;
			vRodaDir *= flagDirection;
			if (vRodaDir > 7) {
				vRodaDir = 7;
			}
			else {
				if (vRodaDir < -7)
					vRodaDir = -7;
			}
			if (vRodaDir < 0)
				vRodaDir = -vRodaDir + 8;

			#ifdef DEBUG
			 printf("vObj = %f| wObj = %f |", vObj, wObj);
			 printf("vRodaEsq = %d |", vRodaEsq);
 			 printf("vRodaDir = %d |\n", vRodaDir);
			#endif
			/**
			 * Fim do novo controle de velocidade
			 */

			/**
			 * MB Após escolher a velocidade chamar a função calcula velocidade dos motores
			 * presente no controle de 2012, para evitar possíveis erros de
			 * velocidade
			 */

			robo.setVelocidadeAtualRobo(vRodaEsq, vRodaDir);
		/**
		 * CHUTE_GIRANDO
		 */
		}
	}
	/**
	* Controle do Robô Goleiro
	*/
	else {
		double lim = 180 / 8;
		robo.setEstadoAtualComoEstadoPrev();
		robo.getDistObjRobo(distObjRobo);
		distEuclidianaObjRobo = robo.getDistEuclianaObjRobo();

		ang = atan2(distObjRobo.y, distObjRobo.x) * 180 / M_PI;
		if (ang < 0) {
			ang += 2 * 180;
		}

		double dAng = ang - robo.getAnguloAtualRobo();
		if (dAng < 0) {
			dAng += 2 * 180;
		}

		if (distEuclidianaObjRobo < 10) {
			vObj = 2;
			wObj = 1;
		} else if (distEuclidianaObjRobo < 6) {
			vObj = 0;
			wObj = 0;
		} else {
			vObj = 3;
			wObj = 1;
		}

		if (dAng < lim) {
			vRodaEsq = vObj;
			vRodaDir = vObj;
		} else if (dAng < 180 / 2 - lim) {
			vRodaEsq = 0;
			vRodaDir = wObj;
		} else if (dAng < 180 / 2) {
			vRodaEsq = -wObj;
			vRodaDir = wObj;
		} else if (dAng < 180 / 2 + lim) {
			vRodaEsq = wObj;
			vRodaDir = -wObj;
		} else if (dAng < 180 - lim) {
			vRodaEsq = 0;
			vRodaDir = -wObj;
		} else if (dAng < 180 + lim) {
			vRodaEsq = -vObj;
			vRodaDir = -vObj;
		} else if (dAng < 3 * 180 / 2 - lim) {
			vRodaEsq = -wObj;
			vRodaDir = 0;
		} else if (dAng < 3 * 180 / 2) {
			vRodaEsq = -wObj;
			vRodaDir = wObj;
		} else if (dAng < 3 * 180 / 2 + lim) {
			vRodaEsq = wObj;
			vRodaDir = -wObj;
		} else if (dAng < 2 * 180 - lim) {
			vRodaEsq = wObj;
			vRodaDir = 0;
		} else {
			vRodaEsq = vObj;
			vRodaDir = vObj;
		}

		robo.setVelocidadeAtualRobo(vRodaEsq, vRodaDir);
	}
}
