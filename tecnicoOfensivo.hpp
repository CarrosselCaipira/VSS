#ifndef TECNICO_OFENSIVO_H

#include "tecnico.hpp"
#include "roteiro.hpp"

class TecnicoOfensivo : public Tecnico {
  private:
    const short int indiceGoleiro = 0; /* posicao no vector de robos do goleiro */
    const short int indiceVolante = 1; /* posicao no vector de robos do voltante */
    const short int indiceAtacante = 2; /* posicao no vector de robos do atacante */
    bool atacanteRetornou;

  public:
    TecnicoOfensivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b); // possivel troca de Bola& b por posXY& b
    TecnicoOfensivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b);

    bool isAtacantePosse();
    posXY getPosAtualAtacante();
    void permutaRoteiroAtkVol();
    void setEstrategiaAtacanteRetornou(bool set);
    bool getEstrategiaAtacanteRetornou();

    run();
};

# endif /* TECNICO_OFENSIVO_H */
