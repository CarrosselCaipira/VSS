#include "tecnico.hpp"

Tecnico::Tecnico(std::vector<Robo>& r, std::vector<Robo>& rAdv, Bola& b) : robosTime(r), robosAdv(rAdv), bola(b) {}

Tecnico::Tecnico(std::vector<Robo>& r, std::vector<posXY>& rAdv, posXY& b) : robosTime(r), robosAdv_posXY(rAdv), bola_posXY(b) {}
