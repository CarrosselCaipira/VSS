#ifndef ROBO_H
#define ROBO_H

#include "tipoEstruturas.hpp"
#include "roteiro.hpp"

class Robo {
    estadoRobo estadoAtualRobo; // Todas as informacoes atuais sobre o robo.
    estadoRobo estadoPrevRobo; // Todas as informacoes sobre as posicoes futuras do robo.
    estadoRobo objRobo; // Informações sobre o objetivo do robo.

    roteiros tipo_jogador;

    friend comportamento;
    friend roteiro;

    public:

        /***************************** GETTERS **************************/

        /************************ POSICAO ATUAL ROBO ********************/
        // Retorna as coordenadas do robo.
        inline posXY getPosicaoAtualRobo ();

        // Retorna as componentes de movimentacao do robo.
        inline vetorSentido getVetorSentidoAtualRobo ();

        // Retorna o angulo do robo.
        inline float getAnguloAtualRobo ();

        // Retorna a velocidade do robo.
        inline velocidadeRobo getVelocidadeAtualRobo ();
        /****************************************************************/

        /********************* POSICAO PREVISTA ROBO ********************/
        // Retorna as coordenadas previstas do robo.
        inline posXY getPosicaoPrevRobo ();

        // Retorna as componentes de movimentacao previstas do robo.
        inline vetorSentido getVetorSentidoPrevRobo ();

        // Retorna o angulo previsto do robo.
        inline float getAnguloPrevRobo ();

        // Retorna a velocidade prevista do robo.
        inline velocidadeRobo getVelocidadePrevRobo ();
        /****************************************************************/

        /************************ OBJETIVO DO ROBO **********************/
        // Retorna a velocidade esperada quando chegar no objetivo.
        inline velocidadeRobo getVelocidadeAtualObj ();

        // Retorna a posicao do objetivo do  robo.
        inline posXY getPosicaoObj ();

        // Retorna o angulo esperado do robo quando chegar no objetivo.
        inline float getAnguloObj ();
        /****************************************************************/

        /***************************** SETTERS **************************/

        /************************ POSICAO ATUAL ROBO ********************/
        // Define a posicao XY do robo.
        inline void setPosicaoAtualRobo (const posXY posicao);
        inline void setPosicaoAtualRobo (const float x, const float y);

        // Define o vetor de sentido de deslocamento do robo.
        inline void setVetorSentidoAtualRobo(const vetorSentido vetor);
        inline void setVetorSentidoAtualRobo(const float vetorX, const float vetorY);

        // Define o angulo atual do robo.
        inline void setAnguloAtualRobo (const float angulo);

        // Define a velocidade de cada roda do robo.
        inline void setVelocidadeAtualRobo (const velocidadeRobo velocidade);
        inline void setVelocidadeAtualRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir);
        /****************************************************************/

        /********************* POSICAO PREVISTA ROBO ********************/
        // Define as coordenadas previstas do robo.
        inline void setPosicaoPrevRobo (const posXY posicao);
        inline void setPosicaoPrevRobo (const float x, const float y);

        // Define as componentes de movimentacao previstas do robo.
        inline void setVetorSentidoPrevRobo (const vetorSentido vetor);
        inline void setVetorSentidoPrevRobo(const float x, const float y);

        // Define o angulo previsto do robo.
        inline void setAnguloPrevRobo (const float angulo);

        // Define a velocidade prevista do robo.
        inline void setVelocidadePrevRobo (const velocidadeRobo velocidade);
        inline void setVelocidadePrevRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir);
        /****************************************************************/

        /************************ OBJETIVO DO ROBO **********************/
        // Define a posicao objetivo do robo.
        inline void setPosicaoObj (const posXY posicao);
        inline void setPosicaoObj (const float x, const float y);

        // Define o angulo de chegada do robo no objetivo.
        inline void setAnguloObj (const float angulo);

        // Define a velocidade de chegada do robo no objetivo.
        inline void setVelocidadeObj(const velocidadeRobo velocidade);
        inline void setVelocidadeObj (const unsigned char velRodaEsq, const unsigned char velRodaDir);
        /****************************************************************/

        /*********************** FUNCAO ROTEIRO *************************/
        /* Define o identificador de roteiro do robo */
        inline void set_roteiro(roteiros r);

        /* Corre o roteiro determinado por tipo_jogador */
        void run();

        /* 
        // analise de necessidade
        // Define a situacao atual de jogo (ex.: em penalidade, em disputa).
        inline void setSituacaoAtual(const int situacao);
        */
};

#endif /* ROBO_H */
