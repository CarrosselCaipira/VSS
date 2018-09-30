#ifndef TECNICO_OFENCIVO_H
#include "tecnico.hpp"

class TecnicoOfencivo : public Tecnico {
  private:
    bool isAtacantePosse();
    posXY getPosAtualAtacante();
    void permutaRoteiroAtkVol();

  public:
    TecnicoOfencivo(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b);
    TecnicoOfencivo(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b);

    run();
};

# endif /* TECNICO_OFENCIVO_H */
