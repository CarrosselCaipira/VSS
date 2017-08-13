#ifndef ROBO_H
#define ROBO_H

#include "tipoEstruturas.hpp"
#include "roteiro.hpp"
#include <cstring>
#include <bitset>

enum INDEX_ATRIBUTOS {
	CHUTE_GIRANDO,
	CHUTANDO,

	/* Adicionar os novos atributos antes de BITSET_SIZE */
	BITSET_SIZE
};

class Robo {
    estadoRobo estadoAtualRobo; /**< Todas as informacoes atuais sobre o robo. */
    estadoRobo estadoPrevRobo; /**< Todas as informacoes sobre as posicoes futuras do robo. */
    estadoRobo estadoObjRobo; /**< Informações sobre o objetivo do robo. */

		std::bitset<BITSET_SIZE> atributos;
    ROTEIROS tipoJogador; // identificao de qual roteiro esta sendo seguido pelo robo no momento.

    friend class Comportamento;
    friend class Roteiro;

    public:
        /*************************** CONSTRUTOR *************************/
        // inicializa todas as componentes do robo com zero e define o roteiro atual do robo como "INDEFINIDO".
        Robo();
        /****************************************************************/

        /***************************** GETTERS **************************/

        /************************ POSICAO ATUAL ROBO ********************/
        // Retorna as coordenadas do robo.
        posXY getPosicaoAtualRobo ();

        // Retorna as componentes de movimentacao do robo.
        vetorSentido getVetorSentidoAtualRobo ();

        // Retorna o angulo do robo.
        float getAnguloAtualRobo ();

        // Retorna a velocidade do robo.
        velocidadeRobo getVelocidadeAtualRobo ();
        /****************************************************************/

        /********************* POSICAO PREVISTA ROBO ********************/
        // Retorna as coordenadas previstas do robo.
        posXY getPosicaoPrevRobo ();

        // Retorna as componentes de movimentacao previstas do robo.
        vetorSentido getVetorSentidoPrevRobo ();

        // Retorna o angulo previsto do robo.
        float getAnguloPrevRobo ();

        // Retorna a velocidade prevista do robo.
        velocidadeRobo getVelocidadePrevRobo ();
        /****************************************************************/

        /************************ OBJETIVO DO ROBO **********************/
        // Retorna a velocidade esperada quando chegar no objetivo.
        velocidadeRobo getVelocidadeAtualObj ();

        // Retorna a posicao do objetivo do  robo.
        posXY getPosicaoObj ();

        // Retorna o angulo esperado do robo quando chegar no objetivo.
        float getAnguloObj ();
        /****************************************************************/

				/*********************** FUNCAO ROTEIRO *************************/
        /* Define o identificador de roteiro do robo */
        void getRoteiro();
				/****************************************************************/

        /***************************** SETTERS **************************/

        /************************ POSICAO ATUAL ROBO ********************/
        // Define a posicao XY do robo.
        void setPosicaoAtualRobo (const posXY posicao);
        void setPosicaoAtualRobo (const float x, const float y);

        // Define o vetor de sentido de deslocamento do robo.
        void setVetorSentidoAtualRobo(const vetorSentido vetor);
        void setVetorSentidoAtualRobo(const float vetorX, const float vetorY);

        // Define o angulo atual do robo.
        void setAnguloAtualRobo (const float angulo);

        // Define a velocidade de cada roda do robo.
        void setVelocidadeAtualRobo (const velocidadeRobo velocidade);
        void setVelocidadeAtualRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir);
        /****************************************************************/

        /********************* POSICAO PREVISTA ROBO ********************/
        // Define as coordenadas previstas do robo.
        void setPosicaoPrevRobo (const posXY posicao);
        void setPosicaoPrevRobo (const float x, const float y);

        // Define as componentes de movimentacao previstas do robo.
        void setVetorSentidoPrevRobo (const vetorSentido vetor);
        void setVetorSentidoPrevRobo(const float x, const float y);

        // Define o angulo previsto do robo.
        void setAnguloPrevRobo (const float angulo);

        // Define a velocidade prevista do robo.
        void setVelocidadePrevRobo (const velocidadeRobo velocidade);
        void setVelocidadePrevRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir);
        /****************************************************************/

        /************************ OBJETIVO DO ROBO **********************/
        // Define a posicao objetivo do robo.
        void setPosicaoObj (const posXY posicao);
        void setPosicaoObj (const float x, const float y);

        // Define o angulo de chegada do robo no objetivo.
        void setAnguloObj (const float angulo);

        // Define a velocidade de chegada do robo no objetivo.
        void setVelocidadeObj(const velocidadeRobo velocidade);
        void setVelocidadeObj (const unsigned char velRodaEsq, const unsigned char velRodaDir);
        /****************************************************************/

        /*********************** FUNCAO ROTEIRO *************************/
        /* Define o identificador de roteiro do robo */
        void setRoteiro(ROTEIROS r);
				/****************************************************************/

				/*********************** ESTADOS DO ROBO *************************/
				/* define o estado atual como sendo o estado previsto (faz a copia das variaveis de estadoPrevRobo para estadoAtualRobo) */
				void setEstadoAtualComoEstadoPrev();

				/* define o estado atual como sendo o estado no objetivo (faz a copia das variaveis de estadoObjRobo para estadoAtualRobo) */
				void setEstadoAtualComoEstadoObj();

				/* definie o estado previsto como sendo o estado atual (faz a copia das variaveis de estadoAtualRobo para estadoPrevRobo) */
				void setEstadoPrevComoEstadoAtual();

				/* define o estado previsto como sendo o estado no objetivo (faz a copia das variaveis de estadoAtualRobo para estadoPrevRobo) */
				void setEstadoPrevComoEstadoObj();
				/****************************************************************/

        /* Corre o roteiro determinado por tipo_jogador */
        void run();
};

#endif /* ROBO_H */
