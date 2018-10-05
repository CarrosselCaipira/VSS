#include "tecnicoOfensivo.hpp"

TecnicoOfensivo::TecnicoOfensivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b) : Tecnico(r, rAdv, b) {
  /* realizar a setagem dos roteiros e outras coisas de interesse que devem ser setadas */
  /* talvez tambem seja interessante definir (salvar) os indices dos robos que possuam determinado roteiro no vector de robos.
  Por exemplo, salvar o indice (provavelmente uma variavel membro privada desta classe) do atacante no vetor de robos, para nao precisarmos ficar
  buscando ele o tempo todo, ou ainda criar uma referencia para para sua posicao no vector (mais complexo e nao vejo, ainda, ganhos de performance significativos) */
  Tecnico::robosTime[this->indiceGoleiro].setRoteiro(GOLEIRO);
  Tecnico::robosTime[this->indiceVolante].setRoteiro(VOLANTE);
  Tecnico::robosTime[this->indiceAtacante].setRoteiro(ATACANTE);
}

TecnicoOfensivo::TecnicoOfensivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b) : Tecnico(r, rAdv, b) {
  /* realizar a setagem dos roteiros e outras coisas de interesse que devem ser setadas */
  /* talvez tambem seja interessante definir (salvar) os indices dos robos que possuam determinado roteiro no vector de robos.
  Por exemplo, salvar o indice (provavelmente uma variavel membro privada desta classe) do atacante no vetor de robos, para nao precisarmos ficar
  buscando ele o tempo todo, ou ainda criar uma referencia para para sua posicao no vector (mais complexo e nao vejo, ainda, ganhos de performance significativos) */
  Tecnico::robosTime[this->indiceGoleiro].setRoteiro(GOLEIRO);
  Tecnico::robosTime[this->indiceVolante].setRoteiro(VOLANTE);
  Tecnico::robosTime[this->indiceAtacante].setRoteiro(ATACANTE);
}

TecnicoOfensivo::run() {
  /* implementacao do roteiro, rodando os roteiros de cada jogador. Setar os roteiros de cada jogador eh uma etapa que provavelmente
  deve ser feita no Constrututor desta classe */

  /* a partir de agora, ao chamar o run, deve-se passar o this como segundo argumento caso o roteiro va usar funcoes do tecnico em questao.
  Exemplo: robosTime[this->indiceAtacante].run(this); // para rodar o roteiro do atacante. Caso o roteiro nao tenha necessidade de usar o tecnico, nao eh necessario passar o this, visto que ele eh um parametro opcional.
  */
}

bool TecnicoOfensivo::isAtacantePosse() {
  return Tecnico::robosTime[this->indiceAtacante].atributos.test(EM_POSSE_BOLA);
}

posXY TecnicoOfensivo::getPosAtualAtacante() {
  return Tecnico::robosTime[this->indiceAtacante].getPosicaoAtualRobo();
}

void TecnicoOfensivo::permutaRoteiroAtkVol() {
  short int aux = this->indiceAtacante; // aux serve para intermediar a troca de indices entre volante e atacante
  this->indiceAtacante = this->indiceVolante;
  this->indiceVolante = aux;

  Tecnico::robosTime[this->indiceAtacante].setRoteiro(ATACANTE);
  Tecnico::robosTime[this->indiceVolante].setRoteiro(VOLANTE);
}

void TecnicoOfensivo::setEstrategiaAtacanteRetornou(bool set){
  this->atacanteRetornou = set;
}

bool TecnicoOfensivo::getEstrategiaAtacanteRetornou(){
  return this->atacanteRetornou;
}
