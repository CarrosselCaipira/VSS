#include "bola.hpp"

posXY Bola::getPosicaoAtualBola() {

  return estadoAtualBola.posicao;
}

posXY Bola::getPosicaoAtualObjBola(){
  
  return estadoObjBola.posicao;
}

void Bola::setPosicaoAtualBola (int x, int y){
  this->estadoAtualBola.posicao.x = x;
  this->estadoAtualBola.posicao.y = y;
}

// vetorSentidoBola Bola::getVetorSentidoAtualBola () {
//   return estadoAtualBola.direcao;
// }

float Bola::getVelocidadeAtualBola() {
  return estadoAtualBola.velocidade;
}

// estadoBola Bola::getEstadoPrevisto (){
//   return estadoPrevistoBola;
// }

void Bola::calculaEstadoPrevisto(){

}