#ifndef BOLA_H
#define BOLA_H

#include "propositoGeralAtuadores.hpp"

class Bola {
  estadoBola estadoAtualBola; // Todas as informacoes sobre a bola
  estadoBola estadoObjBola; // Todas as informacoes sobre o objetivo da bola. Por padrão é o centro do gol.
  estadoBola estadoPrevistoBola; // Todas as informacoes sobre as posicoes(provaveis) futuras da bola.

  public:
    // Retorna a posicao xy da bola.
    posXY getPosicaoAtualBola ();

    // Retorna o vetor sentido da bola
    vetorSentido getVetorSentidoAtualBola ();

    posXY getPosicaoAtualObjBola();

    void setPosicaoAtualBola (int x, int y);

    // Retorna a velocidade atual da bola
    float getVelocidadeAtualBola ();

    // Retorna a posicao xy prevista da bola.
    posXY getPosicaoPrevistoBola ();

    // Retorna o vetor sentido previsto da bola
    vetorSentido getVetorSentidoPrevistoBola ();

    // Retorna a velocidade prevista da bola
    float getVelocidadePrevistoBola ();

    void calculaEstadoPrevisto(); 

		// TO-DO -> criar funcao para determinar a posicao XY da bola quando ela atingir o gol
		// criar funcao para checar se a bola esta indo na diracao do nosso gol, se esta parada ou se esta indo na direcao do time adversario
		// criar funcao para determinar o vetor sentido (utilizando a posicao anterior e atual)

};

#endif /* BOLA_H*/
