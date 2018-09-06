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

void CJ::pid() {

}

posXY CJ::calculaSombra(float dist_sombra) {
    posXY sombra;
    // Reta entre a bola e o objetivo dela
    this->retaBolaObj.geraReta(this->bola.estadoAtualBola.posicao, this->bola.estadoObjBola.posicao);

    // Calcula a sombra de fato, usando a equacao da reta
    // A coordenada x é sempre inferior (para trás)
    sombra.posicao.x = this->bola.estadoAtualBola.posicao.x - dist_sombra * cos(r.angulo);
    // A coordenada y depende em qual campo está a bola
    if(this->bola.estadoAtualBola.posicao.isInCampoMetadeSuperior()) {
        sombra.posicao.y = this->bola.estadoAtualBola.posicao.y + dist_sombra * sin(r.angulo);
    }
    else {
        sombra.posicao.y = this->bola.estadoAtualBola.posicao.y - dist_sombra * sin(r.angulo);
    }
    // Verifica se a projeção da sombra fica dentro do campo. Se ficar fora, sombra.y = bola.y
    if(!sombra.isInCampo()) sombra.y = this->bola.estadoAtualBola.posicao.y;

    // Retorna a posicao da sombra como ponto XY
    return sombra;
}

void determinaFrente() {
    
}

void CJ::calculaVelRodas{
    float dAngulo;
    // Verifica se o robo ja está proximo ao objetivo
    if(this->robo.getPosicaoAtualRobo().isInRaio(this->robo.estadoObjRobo.posicao, RAIO_DE_TOLERANCIA)) {
        // Calcula a diferenca entre o angulo do robo e o angulo da reta entre a bola e o objetivo dela
        dAngulo = retaBolaObj.angulo - this->robo.getAnguloAtualRobo;
        // Verifica se o robo está alinhado com a bola e o objetivo dela
        if(dAngulo < this->thetaCritico) {
            // Anda em linha reta
            vEsq = VEL_MAX;
            vDir = VEL_MAX;
        }
        // O robo ainda precisa se alinhar antes de chutar
        else {
            vEsq = 128 + dAngulo * constanteGiro;
            vDir = 128 - dAngulo * constanteGiro;
        }

    }
    // Serão necessárias duas ou mais retas
    else {
        // Reta entre o robo e o objetivo
        Reta retaRoboObj(this->robo.estadoAtualRobo.posicao, this->robo.estadoObjRobo.posicao);

        // Diferença entre o angulo objetivo e o atual do robo
        float dAngulo = retaRoboObj.angulo - this->robo.getAnguloAtualRobo();
        if(dAngulo < this->thetaCritico) {
            CJ::pid(); // Corrige automaticamente pelo PID
            return;
        }
        else {
            // O erro é superior ao theta crítico. Precisa parar e realinhar
            vEsq += dAngulo;
            vDir -= dAngulo;
        }
        
    }
    // Define as velocidades de cada roda
    this->robo.setVelocidadeAtualRobo(vEsq, vDir);
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