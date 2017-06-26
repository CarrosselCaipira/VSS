    #ifndef ROBO_H
#define ROBO_H

#include "tipoEstruturas.hpp"
#include "roteiros.hpp"
 /*
// nao deve ficar nessa classe
#define EM_DISPUTA 0
#define EM_PENALIDADE 1
#define EM_TIRO_DE_META 2
#define EM_FALTA 3
unsigned short int situacaoAtual; // Situacao atual do jogo. (ex.: em penalidade, em disputa).
*/
class Robo {
    estadoRobo estadoAtualRobo; // Todas as informacoes atuais sobre o robo.
    estadoRobo estadoPrevRobo; // Todas as informacoes sobre as posicoes futuras do robo.
    estadoRobo objRobo; // Informações sobre o objetivo do robo.
    bool chuteGirando = false;

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

        // Define o vetor de sentido de deslocamento do robo.
        inline void setVetorSentidoAtualRobo(const vetorSentido vetor);

        // Define o angulo atual do robo.
        inline void setAnguloAtualRobo (const float angulo);

        // Define a velocidade de cada roda do robo.
        inline void setVelocidadeAtualRobo (const velocidadeRobo velocidade);
        /****************************************************************/

        /********************* POSICAO PREVISTA ROBO ********************/
        // Define as coordenadas previstas do robo.
        inline void setPosicaoPrevRobo (const posXY posicao);

        // Define as componentes de movimentacao previstas do robo.
        inline void setVetorSentidoPrevRobo (const vetorSentido vetor);

        // Define o angulo previsto do robo.
        inline void setAnguloPrevRobo (const float angulo);

        // Define a velocidade prevista do robo.
        inline void setVelocidadePrevRobo (const velocidadeRobo velocidade);
        /****************************************************************/

        /************************ OBJETIVO DO ROBO **********************/
        // Define a posicao objetivo do robo.
        inline void setPosicaoObj (const posXY posicao);

        // Define a situacao atual de jogo (ex.: em penalidade, em disputa).
        inline void setSituacaoAtual(const int situacao);

        // Define o angulo de chegada do robo no objetivo.
        inline void setAnguloObj (const float angulo);

        // Define a velocidade de chegada do robo no objetivo.
        inline void setVelocidadeObj(const velocidadeRobo velocidade);
        /****************************************************************/

        /*********************** FUNCAO ROTEIRO *************************/
        virtual void run();

};

#endif /* ROBO_H */
