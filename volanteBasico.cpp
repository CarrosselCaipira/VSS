#include "roteiro.hpp"

void Roteiro::volanteBasico(Robo& r, posXY& b){

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
	//Se estiver na faixa central
	else {
		//Se estiver na faixa superior ou na faixa inferior
		if ((b.isInCampoSemAreaGolTime() || b.isInCampoSemAreaGolAdv())){
			//segue bola em Y
			Comportamento::posicionaVolantePosNatural(r, b);
			r.setPosicaoAtualRobo(r.getPosicaoObj());
			//Se y do voltante é igual ao y da bola e está no campo do adversário
			if(r.getPosicaoAtualRobo().y == b.y && b.isInCampoSemAreaGolAdv() && b.isInAreaAtaqueVolatante()){
				Comportamento::chutaFrente(r, b);
			}
		}
	}
	// getchar()
}
