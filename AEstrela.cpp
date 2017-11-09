#include "AEstrela.hpp"

using namespace std;

GrafoEmGrade::GrafoEmGrade(int larg, int alt): largura(larg), altura(alt) {

	//For para colocar em cada posicao do vector de vizinhos.
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++) {

			Posicao p(i-1,j-1);

			if ((i-1)==0 && (j-1)==0) {

				continue;
			}

			else {

				vizinhos.push_back(p);
			}
		}
}

bool GrafoEmGrade::emGrade(Posicao coordenada) {

	int x,y;
	tie (x,y) = coordenada;

	return (x >= 0 && x < largura && y >= 0 && y < altura);
}

bool GrafoEmGrade::isObstaculo(Posicao coordenada) {

	return (this->obstaculos.count(coordenada) > 0);
}

vector<Posicao> GrafoEmGrade::retornaVizinhos(Posicao coordenada) {

    vector<Posicao> resultados;
	Posicao p;
	int coordx, coordy;

	tie(coordx,coordy) = coordenada;

	for (Posicao no : this->vizinhos) {

		int nox, noy;

		tie(nox,noy) = no;

		Posicao p(coordx + nox, coordy + noy);

      	if (emGrade(p) && !isObstaculo(p)) {

			resultados.push_back(p);
     	}
    }	

    return resultados;
}

void GrafoEmGrade::adicionaMultiplosObstaculos(Posicao coordenada, int larg, int alt) {
  
	int x,y;

	tie(x,y) = coordenada;

    for (int i = y; i < y + alt; i++) {
  			
  		for (int j = x; j < x + larg; j++) {
    	
    		this->obstaculos.insert(Posicao{j, i});
    	}
  	}
}


void GrafoEmGrade::adicionaUmObstaculo(Posicao obstaculo) {
  
	int linha, coluna;

	tie(coluna,linha) = obstaculo;

  	this->obstaculos.insert(Posicao{linha, coluna});
}

int GrafoEmGrade::pesoNoNo (Posicao noInicial, Posicao noFinal) {

	int xNoInicial, yNoInicial;
	int xNoFinal, yNoFinal;

	tie(yNoInicial, xNoInicial) = noInicial;
	tie(yNoFinal, xNoFinal) = noFinal;

	int distNosX = abs(xNoInicial - xNoFinal);
	int distNosY = abs(yNoInicial - yNoFinal);


	return (distNosX > distNosY) ? distNosX : distNosY;
}

bool FilaPrioridades::isVazia() { 

  	return fila.empty(); 
}

void FilaPrioridades::colocar(Posicao i, double p) {
    
    fila.emplace(i, p);
}

Posicao FilaPrioridades::retirarPop() {

    Posicao melhor = fila.top().first;
    fila.pop();
    return melhor;
}

GrafoEmGrade* AEstrela::preparaGrafo(GrafoEmGrade *grafo, vector<Posicao> obstaculos) {

	for (Posicao obs: obstaculos) {

		int x,y;

		tie(x,y) = obs;

		grafo->adicionaUmObstaculo(Posicao{x,y});
	}

	grafo->adicionaMultiplosObstaculos(Posicao{0,0},1,67);
	grafo->adicionaMultiplosObstaculos(Posicao{0,0},77,1);
	grafo->adicionaMultiplosObstaculos(Posicao{76,0},1,67);
	grafo->adicionaMultiplosObstaculos(Posicao{0,66},77,1);

	grafo->adicionaMultiplosObstaculos(Posicao{0,15},30,1);

	return grafo;
}

vector<Posicao> AEstrela::posXYtoPosicao(vector<posXY> v) {

	vector<Posicao> resul;

	for (auto item: v) {

		resul.push_back(Posicao{item.x, item.y});
	}

	return resul;
}

AEstrela::AEstrela (Robo& r, std::vector<posXY>& obs) : robo(r), posObstaculos(obs) {}

void AEstrela::calculaVelRodas() {
	
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

			posXY posInicial = robo.getPosicaoAtualRobo();
			posXY posMeta = robo.getPosicaoObj();

			Posicao inicio = Posicao{posInicial.x, posInicial.y};
			Posicao fim = Posicao{posMeta.x, posMeta.y};

			grafo = AEstrela::preparaGrafo(this->grafo, posXYtoPosicao(posObstaculos));
			AEstrela::aEstrela(this->grafo, inicio, fim, this->tracado, this->gasto);

			vector<Posicao> rota = AEstrela::reconstruirCaminho(inicio,fim,tracado);

			robo.setEstadoAtualComoEstadoPrev();
			/* analizar utilidade de salvarmos estado anterior, atualmente removida */

			if (rota.size() > 2) {

				int xNoInicial, yNoInicial;
				int xProxNo, yProxNo;

				tie(yNoInicial, xNoInicial) = rota[0];
				tie(yProxNo, xProxNo) = rota[1];			

				directionAngle = atan2(xNoInicial - xProxNo, yNoInicial - yProxNo) * 180 / M_PI;

			}

			else {

				int x,y;

				tie(x,y) = rota[0];

				directionAngle = atan2(x, y) * 180 / M_PI;
			}

			ang = (float) directionAngle;

			if (ang < 0) {
				ang += 360;
			}

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

			//Velocidade do robô calculada em função da força vinda do campo potencial
			vObj = (2 / MASSA_ROBO) * (sin(directionAngle * (M_PI / 180)) * (distObjRobo.y) + cos(directionAngle * (M_PI / 180)) * (distObjRobo.x));

			K_ro = vObj/(distEuclidianaObjRobo * cos(dAng * (M_PI / 180)));

			if (vObj < 127 && vObj >= 0){
				vObj = 127 - vObj;
			}
			else {
				if (vObj > -127 && vObj < 0)
					vObj = 127 + vObj;
			}

			vObj = vObj * cos(dAng * (M_PI / 180));

			wObj = K_ro * sin(dAng * (M_PI/180)) * cos(dAng * (M_PI / 180));

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

double AEstrela::heuristica(Posicao a, Posicao b) {
  
	int xa, ya, xb, yb;

	tie(ya,xa) = a;
	tie(yb,xb) = b;

	return abs(xa - xb) + abs(ya - yb);
}

void AEstrela::aEstrela (GrafoEmGrade *grafo, Posicao inicio, Posicao meta, Caminho& caminho, Custo& custo){

	FilaPrioridades fila;
  	fila.colocar(inicio, (double)0);

  	caminho[inicio] = inicio;
  	custo[inicio] = 0;
  
  	while (!fila.isVazia()) {

    	Posicao noAtual = fila.retirarPop();

    	if (noAtual == meta) {
      		break;
    	}

    	for (Posicao proximoNo : grafo->retornaVizinhos(noAtual)) {

      		double novoCusto = custo[noAtual] + grafo->pesoNoNo(noAtual, proximoNo);

      		if (!custo.count(proximoNo) || novoCusto < custo[proximoNo]) {

        		custo[proximoNo] = novoCusto;
        		double prioridade = novoCusto + heuristica(proximoNo, meta);
        		fila.colocar(proximoNo, prioridade);
        		caminho[proximoNo] = noAtual;
      		}
    	}
  	}
}

vector<Posicao> AEstrela::reconstruirCaminho(Posicao inicio, Posicao fim, Caminho& caminho) {

  	vector<Posicao> path;
  	Posicao atual = fim;
  	path.push_back(atual);

  	while (atual != inicio) {

    	atual = caminho[atual];
    	path.push_back(atual);
  	}

  	path.push_back(inicio); // optional
  	std::reverse(path.begin(), path.end());

  	return path;
}