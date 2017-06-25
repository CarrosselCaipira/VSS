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
  estadoAtualRobo.posicao.x = posicao.x;
  estadoAtualRobo.posicao.y = posicao.y;
}

void Robo::setVetorSentidoAtualRobo(const vetorSentido vetor) {
  estadoAtualRobo.direcao.x = vetor.x;
  estadoAtualRobo.direcao.y = vetor.y;
}

void Robo::setAnguloAtualRobo (const float angulo) {
  estadoAtualRobo.angulo = angulo;
}

void Robo::setVelocidadeAtualRobo (const velocidadeRobo velocidade) {
  estadoAtualRobo.velocidade.rodaEsq = velocidade.rodaEsq;
  estadoAtualRobo.velocidade.rodaDir = velocidade.rodaDir;
}
/****************************************************************/

/********************* POSICAO PREVISTA ROBO ********************/
void Robo::setPosicaoPrevRobo (const posXY posicao) {
  estadoPrevRobo.posicao.x = posicao.x;
  estadoPrevRobo.posicao.y = posicao.y;
}

void Robo::setVetorSentidoPrevRobo(const vetorSentido vetor) {
  estadoPrevRobo.direcao.x = vetor.x;
  estadoPrevRobo.direcao.y = vetor.y;
}

void Robo::setAnguloPrevRobo (const float angulo) {
  estadoPrevRobo.angulo = angulo;
}

void Robo::setVelocidadePrevRobo (const velocidadeRobo velocidade) {
  estadoPrevRobo.velocidade.rodaEsq = velocidade.rodaEsq;
  estadoPrevRobo.velocidade.rodaDir = velocidade.rodaDir;
}
/****************************************************************/

/************************ OBJETIVO DO ROBO **********************/
void Robo::setPosicaoObj (const posXY posicao) {
  objRobo.posicao.x = posicao.x;
  objRobo.posicao.y = posicao.y;
}

void Robo::setAnguloObj (const float angulo) {
  objRobo.angulo = angulo;
}

void Robo::setVelocidadeObj (const velocidadeRobo velocidade){
  objRobo.velocidade.rodaEsq = velocidade.rodaEsq;
  objRobo.velocidade.rodaDir = velocidade.rodaDir;
}
/****************************************************************/

/// SOB ANALISE
void Robo::setSituacaoAtual(const int situacao){
  situacaoAtual = (unsigned short int)situacao;
}

void Robo::saturaPosicoes(posXY &posicao){

}
