#include "comportamento.hpp"
#include "posicionameto.hpp"

void Comportamento::posiciona_centro_golXY(Robo& r) {
	posXY p;
	p.x = CENTRO_X_GOL;
	p.y = CENTRO_Y_GOL;

	r.setPosicaoObj(p);
}
