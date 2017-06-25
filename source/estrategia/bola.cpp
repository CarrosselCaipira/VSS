#include "bola.h"

posXY Bola::getPosicaoAtualBola () {
  return estadoAtualBola.posicao;
}

vetorSentidoBola Bola::getVetorSentidoAtualBola () {
  return estadoAtualBola.direcao;
}

float Bola::getVelocidadeAtualBola () {
  return estadoAtualBola.velocidade;
}

estadoBola Bola::getEstadoPrevisto (){
  return estadoPrevistoBola;
}

void Bola::calculaEstadoPrevisto (){

}
