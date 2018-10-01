#ifndef TECNICO_OFENCIVO_H
#include "tecnico.hpp"

class TecnicoOfensivo : public Tecnico {
  private:
    bool isAtacantePosse();
    posXY getPosAtualAtacante();
    void permutaRoteiroAtkVol();

  public:
    TecnicoOfensivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b);
    TecnicoOfensivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b);

    run();
};

# endif /* TECNICO_OFENCIVO_H */
