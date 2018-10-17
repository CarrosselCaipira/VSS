#ifndef TECNICO_OFENSIVO_H
#define TECNICO_OFENSIVO_H

#include "tecnico.hpp"
#ifndef ROTEIRO_H
#define ROTEIRO_H
#include "roteiro.hpp"
#endif
#include <algorithm>

class TecnicoOfensivo : public Tecnico {
  private:
    short int indiceGoleiro; /* posicao no vector de robos do goleiro */
    short int indiceVolante; /* posicao no vector de robos do voltante */
    short int indiceAtacante; /* posicao no vector de robos do atacante */
    bool atacanteRetornou;

  public:
    TecnicoOfensivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b); // possivel troca de Bola& b por posXY& b
    TecnicoOfensivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b);

    bool isAtacantePosse();
    posXY getPosAtualAtacante();
    void permutaRoteiroAtkVol();
    void setEstrategiaAtacanteRetornou(bool set);
    bool getEstrategiaAtacanteRetornou();
    posXY getPosAtualBola();

    void run();
};

# endif /* TECNICO_OFENSIVO_H */
