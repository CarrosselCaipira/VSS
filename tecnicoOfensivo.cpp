#include "tecnicoOfensivo.hpp"

TecnicoOfensivo::TecnicoOfensivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b) : Tecnico(r, rAdv, b) {
  /* realizar a setagem dos roteiros e outras coisas de interesse que devem ser setadas */
  /* talvez tambem seja interessante definir (salvar) os indices dos robos que possuam determinado roteiro no vector de robos. 
  Por exemplo, salvar o indice (provavelmente uma variavel membro privada desta classe) do atacante no vetor de robos, para nao precisarmos ficar 
  buscando ele o tempo todo, ou ainda criar uma referencia para para sua posicao no vector (mais complexo e nao vejo, ainda, ganhos de performance significativos) */

  robosTime = r;

  robosTime[0].setRoteiro(GOLEIRO);
  robosTime[1].setRoteiro(VOLANTE);
  robosTime[2].setRoteiro(ATACANTE);
  
  indiceGoleiro = 0;
  indiceVolante = 1;
  indiceAtacante = 2;

}

TecnicoOfensivo::TecnicoOfensivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b) : Tecnico(r, rAdv, b) {
  /* realizar a setagem dos roteiros e outras coisas de interesse que devem ser setadas */
  /* talvez tambem seja interessante definir (salvar) os indices dos robos que possuam determinado roteiro no vector de robos. 
  Por exemplo, salvar o indice (provavelmente uma variavel membro privada desta classe) do atacante no vetor de robos, para nao precisarmos ficar 
  buscando ele o tempo todo, ou ainda criar uma referencia para para sua posicao no vector (mais complexo e nao vejo, ainda, ganhos de performance significativos) */
  robosTime = r;  

  robosTime[0].setRoteiro(GOLEIRO);
  robosTime[1].setRoteiro(VOLANTE);
  robosTime[2].setRoteiro(ATACANTE);
  
  indiceGoleiro = 0;
  indiceVolante = 1;
  indiceAtacante = 2;
}

TecnicoOfensivo::run() {
  /* implementacao do roteiro, rodando os roteiros de cada jogador. Setar os roteiros de cada jogador eh uma etapa que provavelmente 
  deve ser feita no Constrututor desta classe */
}

bool TecnicoOfensivo::isAtacantePosse() {
  return robosTime[indiceAtacante].atributos.test(EM_POSSE_BOLA);
}

posXY TecnicoOfensivo::getPosAtualAtacante() {
  return robosTime[indiceAtacante].getPosicaoAtualRobo();
}

void TecnicoOfensivo::permutaRoteiroAtkVol() {
  short int aux = indiceAtacante; // aux serve para intermediar a troca de indices entre volante e atacante
  indiceAtacante = indiceVolante;
  indiceVolante = aux;

  robosTime[indiceAtacante].setRoteiro(ATACANTE);
  robosTime[indiceVolante].setRoteiro(VOLANTE);  
}

void TecnicoOfensivo::setEstrategiaAtacanteRetornou(bool set){
  atacanteRetornou = set;
}

bool TecnicoOfensivo::getEstrategiaAtacanteRetornou(){
  return atacanteRetornou;
}