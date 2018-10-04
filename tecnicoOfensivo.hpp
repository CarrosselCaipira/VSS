#ifndef TECNICO_OFENSIVO_H
#include "tecnico.hpp"
#include "roteiro.hpp"

class TecnicoOfensivo : public Tecnico {
  private:
    short int indiceAtacante;
    short int indiceVolante;
    short int indiceGoleiro;
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
