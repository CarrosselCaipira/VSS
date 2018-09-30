#include "TecnicoOfencivo.hpp"

TecnicoOfencivo::TecnicoOfencivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b) : Tecnico(r, rAdv, b) {
  /* realizar a setagem dos roteiros e outras coisas de interesse que devem ser setadas */
  /* talvez tambem seja interessante definir (salvar) os indices dos robos que possuam determinado roteiro no vector de robos. Por exemplo, salvar o indice (provavelmente uma variavel membro privada desta classe) do atacante no vetor de robos, para nao precisarmos ficar buscando ele o tempo todo, ou ainda criar uma referencia para para sua posicao no vector (mais complexo e nao vejo, ainda, ganhos de performance significativos) */
}

TecnicoOfencivo::TecnicoOfencivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b) : Tecnico(r, rAdv, b) {
  /* realizar a setagem dos roteiros e outras coisas de interesse que devem ser setadas */
  /* talvez tambem seja interessante definir (salvar) os indices dos robos que possuam determinado roteiro no vector de robos. Por exemplo, salvar o indice (provavelmente uma variavel membro privada desta classe) do atacante no vetor de robos, para nao precisarmos ficar buscando ele o tempo todo, ou ainda criar uma referencia para para sua posicao no vector (mais complexo e nao vejo, ainda, ganhos de performance significativos) */
}

TecnicoOfencivo::run() {
  /* implementacao do roteiro, rodando os roteiros de cada jogador. Setar os roteiros de cada jogador eh uma etapa que provavelmente deve ser feita no Constrututor desta classe */
}

bool TecnicoOfencivo::isAtacantePosse() {

}

posXY TecnicoOfencivo::getPosAtualAtacante() {

}

void TecnicoOfencivo::permutaRoteiroAtkVol() {

}
