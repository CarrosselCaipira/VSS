#include "roteiro.hpp"

void Roteiro::volanteBasico(Robo& r, posXY& b){
	//Se o robô estiver com a bola
	if(r.isRoboComBola(b,RAIO_ATAQUE)) {
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
	//Se estiver na faixa superior ou na faixa inferior
	if (b.isInFaixaSuperior() || b.isInFaixaInferior()){
		//segue a bola em X, mantendo-se um robô à frente e segue a bola em y
		Comportamento::segueBolaEmXFrente(r, b);
		Comportamento::posicionaPosBolaEmY(r, b);

	}
	//Se estiver na faixa central
	else {
		//Se estiver no campo sem area gol do nosso time
		if(b.isInCampoSemAreaGolTime()){
			//marca a passagem da bola
			Comportamento::tangenciaLinhaFrenteAreaGol(r);
			Comportamento::posicionaPosBolaEmY(r, b);

		}
		//Se não estiver no campo do nosso time
		else if(b.isInCampoAdv()){
			//fica no meio de campo e segue a bola em y com 90 graus
			Comportamento::posiciona90Graus(r);
			Comportamento::posicionaPosBolaEmY(r, b);
			Comportamento::posicionaAtrasMeioCampo(r);
		}
	}
}
