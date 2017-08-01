#include "robo.hpp"

/***************************** GETTERS **************************/

/************************ POSICAO ATUAL ROBO ********************/
posXY Robo::getPosicaoAtualRobo () {
  return estadoAtualRobo.posicao;
}

vetorSentido Robo::getVetorSentidoAtualRobo () {
  return estadoAtualRobo.direcao;
}

float Robo::getAnguloAtualRobo () {
  return estadoAtualRobo.angulo;
}

velocidadeRobo Robo::getVelocidadeAtualRobo () {
  return estadoAtualRobo.velocidade;
}
/****************************************************************/

/********************* POSICAO PREVISTA ROBO ********************/
posXY Robo::getPosicaoPrevRobo () {
  return estadoPrevRobo.posicao;
}

vetorSentido Robo::getVetorSentidoPrevRobo () {
  return estadoPrevRobo.direcao;
}

float Robo::getAnguloPrevRobo () {
  return estadoPrevRobo.angulo;
}

velocidadeRobo Robo::getVelocidadePrevRobo () {
  return estadoPrevRobo.velocidade;
}
/****************************************************************/

/************************ OBJETIVO DO ROBO **********************/
velocidadeRobo Robo::getVelocidadeObj () {
  return objRobo.velocidade;
}

posXY Robo::getPosicaoObj () {
  return objRobo.posicao;
}

float Robo::getAnguloObj () {
  return objRobo.angulo;
}
/****************************************************************/

/***************************** SETTERS **************************/

/************************ POSICAO ATUAL ROBO ********************/
void Robo::setPosicaoAtualRobo (const posXY posicao) {
  estadoAtualRobo.posicao = posicao;
}

void Robo::setPosicaoAtualRobo (const float x, const float y) {
  estadoAtualRobo.posicao.x = x;
  estadoAtualRobo.posicao.y = y;
}

void Robo::setVetorSentidoAtualRobo(const vetorSentido vetor) {
  estadoAtualRobo.direcao = vetor;
}

void Robo::setVetorSentidoAtualRobo(const float vetorX, const float vetorY) {
  estadoAtualRobo.direcao.x = vetorX;
  estadoAtualRobo.direcao.y = vetorY;
}

void Robo::setAnguloAtualRobo (const float angulo) {
  estadoAtualRobo.angulo = angulo;
}

void Robo::setVelocidadeAtualRobo (const velocidadeRobo velocidade) {
  estadoAtualRobo.velocidade = velocidade;
}

void Robo::setVelocidadeAtualRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir) {
  estadoAtualRobo.velocidade.rodaEsq = velRodaEsq;
  estadoAtualRobo.velocidade.rodaDir = velRodaDir;
}
/****************************************************************/

/********************* POSICAO PREVISTA ROBO ********************/
void Robo::setPosicaoPrevRobo (const posXY posicao) {
  estadoPrevRobo.posicao = posicao;
}

void Robo::setPosicaoPrevRobo (const float x, const float y) {
  estadoPrevRobo.posicao.x = x;
  estadoPrevRobo.posicao.y = y;
}

void Robo::setVetorSentidoPrevRobo(const vetorSentido vetor) {
  estadoPrevRobo.direcao.x = vetor.x;
  estadoPrevRobo.direcao.y = vetor.y;
}

void Robo::setVetorSentidoPrevRobo(const float x, const float y) {
  estadoPrevRobo.direcao.x = x;
  estadoPrevRobo.direcao.y = y;
}

void Robo::setAnguloPrevRobo (const float angulo) {
  estadoPrevRobo.angulo = angulo;
}

void Robo::setVelocidadePrevRobo (const velocidadeRobo velocidade) {
  estadoPrevRobo.velocidade = velocidade;
}

void Robo::setVelocidadePrevRobo (const unsigned char velRodaEsq, const unsigned char velRodaDir) {
  estadoPrevRobo.velocidade.rodaEsq = velRodaEsq;
  estadoPrevRobo.velocidade.rodaDir = velRodaDir;
}
/****************************************************************/

/************************ OBJETIVO DO ROBO **********************/
void Robo::setPosicaoObj (const posXY posicao) {
  objRobo.posicao = posicao;
}

void Robo::setPosicaoObj (const float x, const float y) {
  objRobo.posicao.x = x;
  objRobo.posicao.y = y;
}

void Robo::setAnguloObj (const float angulo) {
  objRobo.angulo = angulo;
}

void Robo::setVelocidadeObj (const velocidadeRobo vel){
  objRobo.velocidade = vel;
}

void Robo::setVelocidadeObj (const unsigned char velRodaEsq, const unsigned char velRodaDir) {
  objRobo.velocidade.rodaEsq = velRodaEsq;
  objRobo.velocidade.rodaDir = velRodaDir;
}

void Robo::set_roteiro(roteiros r) {
  tipo_jogador = r;
}

void Robo::run() {
  switch (tipo_jogador) {
    case ATACANTE:
      Roteiro::atacante(*this);
      break;

    case VOLANTE:
      Roteiro::volante(*this);
      break;
      
    case GOLEIRO:
      Roteiro::goleiro(*this);
      break;
  }
}

/****************************************************************/

/*
/// SOB ANALISE
void Robo::setSituacaoAtual(const int situacao){
  situacaoAtual = (unsigned short int)situacao;
}

void Robo::saturaPosicoes(posXY &posicao){

}
*/