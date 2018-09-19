#ifndef CONTROLE_JUVENIL_H
#define CONTROLE_JUVENIL_H

#include "robo.hpp"
#include "comportamento.hpp"
#include "roteiro.hpp"
#include "bola.hpp"
#include <vector>


class CJ{
    private:
        const float dist_sombra_bola = 3.5;
        Robo& robo;
        Bola& bola;
        std::vector<posXY>& posObstaculos; /* < Vector contendo as posicoes dos obtaculos em campo (outros robos do time, robos da equipe adversaria, etc.), eh interessante que se use as posicoes previstas desses objetos, mas nada impede que as posicoes atuais sejam usadas. */
        Reta retaBolaObj; /* Reta entre a bola e o objetivo dela */
        std::vector<Reta> retas; /* Vetor de retas para a trajetória. Número de retas é igual ao número de obstáculos mais 2 */  
        float thetaCritico; /* Angulo a partir do qual deve-se recalcular o caminho */
        float vEsq, vDir = 127; /* Velocidade das rodas do robô */
        float constanteGiro = 1; /* Constante pela qual o erro no angulo é multiplicado antes da correção */
        void pid(); /* Ajuste da trajetória através do PID */
        void determinaFrente(); /* Verifica qual lado do robô está mais próximo do objetivo */
        posXY calculaSombra(Bola bola, float dist_sombra);
        
    public:
        CJ(Robo& r);
        
        void calculaVelRodas();
};

struct Reta{
    posXY pontoInicio, pontoFim;
    float angulo, comprimento, largura;
    Reta();
    Reta(Reta& r);  /* Copy constructor */
    Reta(const posXY& ponto, const float angulo); /* Ponto e ângulo */
    Reta(const posXY& pontoA, const posXY& pontoB); /* Ponto e ponto */
    void geraReta(Reta& r);
    void geraReta(const posXY& ponto, const float angulo);
    void geraReta(const posXY& pontoA, const posXY& pontoB);
};

#endif /* CONTROLE_JUVENIL_H */