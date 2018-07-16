// Controle Juvenil

// É necessário criar const float dist_sombra_bola = 5x1.44;       // Distancia para o cálculo da sombra da bola (onda o robo chega para ficar alinhado com o objetivo da bola)
// É necessário criar a classe da bola e seu objetivo

// 0) Verifica se o robô está alinhado com o objetivo da bola
//     - Sim: 1 reta, acelera
//     - Não: É menor que um theta crítico?
//         - Sim: PID (passo 5)
//         - Não: Cálculo caminhos (passo 1)
// 1) Calcula a "sombra da bola" = SB(XB - 5, YB - 5) para metade inferior
//                                 SB(XB - 5, YB + 5) para metade superior
// 2) Traca reta entre robo e a sombra
// 3) Checa por obstaculos na faixa
//     - Não há: Fim
//     - Há: Calcula as demais retas
// 4) Rotaciona o robô até alinhar com a reta 
// 5) Controle de velocidade
//     - Mais rápido quanto mais longe
//     - PID ou Fuzzy para manter-se alinhado

// CJ(Robo& r, std::vector<posXY>& obs);

#include "ControleJuvenil.hpp"

CJ::CJ(Robo& r, std::vector<posXY>& obs): robo(r), posObstaculos(obs) {}

void CJ::pid() {}

void CJ::calculaSombra() {}

void CJ::calculaVelRodas{
    if(this->robo.getPosicaoAtualRobo().isInRaio(sombra, raioDaSombra)) {
        /* Só precisa de uma reta em direção ao gol */
    }
    // Serão necessárias duas ou mais retas
    else {
        if(this->robo.getAnguloAtualRobo() < this->thetaCritico) {
            CJ::pid(); // Corrige automaticamente pelo PID
            return;
        }
        // O erro é superior ao theta crítico. Precisa parar e realinhar
        
    }
}


Reta::Reta(Reta& r) {

}

Reta::Reta(const posXY& ponto, const float angulo) {
    this->angulo = angulo;
    this->pontoInicio = ponto;
}

Reta::Reta(const posXY& pontoA, const posXY& pontoB) {
    this->pontoInicio = pontoA;
    this->pontoFim = pontoB;
    this->angulo = atan2(pontoA.y - pontoB.y, pontoA.x - pontoB.x);
}