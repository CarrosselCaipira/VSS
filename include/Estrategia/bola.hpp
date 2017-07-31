#ifndef BOLA_H
#define BOLA_H

#include "auxiliares.hpp"
#include "tipoClasses.hpp"

class Bola{
  estadoBola estadoAtualBola; // Todas as informacoes sobre a bola
  estadoBola estadoPrevistoBola; // Todas as informacoes sobre as posicoes(provaveis) futuras da bola.

  public:
    // Retorna a posicao xy da bola.
    inline posXY getPosicaoAtualBola ();

    // Retorna o vetor sentido da bola
    inline vetorSentido getVetorSentidoAtualBola ();

    // Retorna a velocidade atual da bola
    inline float getVelocidadeAtualBola ();

    // Retorna a posicao xy prevista da bola.
    inline posXY getPosicaoPrevistoBola ();

    // Retorna o vetor sentido previsto da bola
    inline vetorSentido getVetorSentidoPrevistoBola ();

    // Retorna a velocidade prevista da bola
    inline float getVelocidadePrevistoBola ();

};

#endif /* BOLA_H*/