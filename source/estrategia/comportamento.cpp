#include "comportamento.hpp"
#include "posicionameto.hpp"

void comportamento::posiciona_centro_gol(Robo& r) {
	posXY p;
	p.x = CENTRO_X_GOL;
	p.y = CENTRO_Y_GOL;

	r.setPosicaoObj(p);
}
