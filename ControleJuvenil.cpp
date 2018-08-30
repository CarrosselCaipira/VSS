// Controle Juvenil

// É necessário criar const float dist_sombra_bola = 5x1.44;       // Distancia para o cálculo da sombra da bola (onda o robo chega para ficar alinhado com o objetivo da bola)
// É necessário criar a classe da bola e seu objetivo

// 0) Verifica se o robô está alinhado com o objetivo da bola
//     - Sim: 1 reta, acelera
//     - Não: É menor que um theta crítico?
//         - Sim: PID (passo 5)
//         - Não: Cálculo caminhos (passo 1)
// 1) Calcula a "sombra da bola" = SB(XB - sombra, YB - sombra) para metade inferior
//                                 SB(XB - sombra, YB + sombra) para metade superior
//      var dist_sombra = distancia antes da bola pro robo conseguir se alinhar
// 2) Traca reta entre robo e a sombra
//      m = deltaY / deltaX
//      m > 0 para robo embaixo da bola
//      m < 0 para robo acima da bola
// 3) Checa por obstaculos na faixa com reta mais espessa
//      var espessura = margem de seguranca da reta
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

void CJ::calculaSombra() {
    posXY sombra;
    // Reta entre a bola e o objetivo dela
    Reta r(this->bola.estadoAtualBola.posicao, this->bola.estadoObjBola.posicao);

    // Calcula a sombra de fato, usando a equacao da reta
    // A coordenada x é sempre inferior (para trás)
    sombra.posicao.x = this->bola.estadoAtualBola.posicao.x - distancia * cos(r.angulo);
    // A coordenada y depende em qual campo está a bola
    if(this->bola.estadoAtualBola.posicao.isInCampoMetadeSuperior()) {
        sombra.posicao.y = this->bola.estadoAtualBola.posicao.y + distancia * sin(r.angulo);
    }
    else {
        sombra.posicao.y = this->bola.estadoAtualBola.posicao.y - distancia * sin(r.angulo);
    }
    // Verifica se a projeção da sombra fica dentro do campo. Se ficar fora, sombra.y = bola.y
    if(!sombra.isInCampo()) sombra.y = this->bola.estadoAtualBola.posicao.y;
}

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