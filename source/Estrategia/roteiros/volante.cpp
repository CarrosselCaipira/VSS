#include "roteiro.hpp"

void Roteiro::volante(Robo& r){
	/* funcao de comportamento do volante */

	/*
	Duvidas:
		Ignorar previsão
		O volante utiliza a posição do atacante, mas não temos acesso a estes dados
	*/

	const posXY posicaoAtualRobo, posicaoAtualBola, distRoboBola, posicaoObj; //*- ao inves de dar gets usa essas varuaveis
	int distBolaRoboY,
	posicaoAtualRobo = r.getPosAtualRobo();
	posicaoAtualBola = bola.getPosAtualBola();

	distRoboBola.x = posicaoAtualRobo.x - posicaoAtualBola.x;
	distRoboBola.y = posicaoAtualRobo.y - posicaoAtualBola.y;

	r.setAnguloAtualRobo(90);
	r.setPosicaoAtual(PosicaoAtualRobo.x, PosicaoAtualBola.y);

	if(distRoboBola.x > TAM_ROBO){
		if(abs(distRoboBola.y) <= TAM_ROBO)
			posicaoObj.x = posicaoAtualRobo.x;
		if(bola.getVetorSentidoAtualBola().x <= 0){
			//Esta proxima condição considera a posição do atacante
			if((posicaoAtualBola.x - atacante.getPosicaoAtualRobo().x < 2 * TAM_ROBO && atacante.getPosicaoAtualRobo().x < posicaoAtualBola.x) && abs(posicaoAtualBola.y - atacante.getPosicaoAtualRobo().y) < TAM_ROBO / 2){
				if(distRoboBola.y ){

				}
			}
		}

	}
}
