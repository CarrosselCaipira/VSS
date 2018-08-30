#ifndef CONTROLE_JUVENIL_H
#define CONTROLE_JUVENIL_H

#include "robo.hpp"
#include "comportamento.hpp"
#include "roteiro.hpp"
#include "bola.hpp"
#include <vector>


class CJ{
    posXY const float dist_sombra_bola = 5x1.44;
    Robo& robo;
    Bola& bola;
    std::vector<posXY>& posOstaculos; /* < Vector contendo as posicoes dos obtaculos em campo (outros robos do time, robos da equipe adversaria, etc.), eh interessante que se use as posicoes previstas desses objetos, mas nada impede que as posicoes atuais sejam usadas. */
    private:

        std::vector<Reta> retas; /* Vetor de retas para a trajetória. Número de retas é igual ao número de obstáculos mais 2 */  
        float thetaCritico; /* Angulo a partir do qual deve-se recalcular o caminho */
        
        void pid(); /* Ajuste da trajetória através do PID */
        
    public:
        CJ(Robo& r, std::vector<posXY>& obs);
        
        void calculaVelRodas();
};

struct Reta{
    posXY pontoInicio, pontoFim;
    float angulo, comprimento, largura;

    Reta(Reta& r);  /* Copy constructor */
    Reta(const posXY& ponto, const float angulo); /* Ponto e ângulo */
    Reta(const posXY& pontoA, const posXY& pontoB); /* Ponto e ponto */
};

#endif /* CONTROLE_JUVENIL_H */