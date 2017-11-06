#ifndef ROTEIRO_H
#define ROTEIRO_H

#include "comportamento.hpp"

enum ROTEIROS {
	INDEFINIDO,
	ATACANTE,
	VOLANTE,
	GOLEIRO
};

class Roteiro {
	public:
		static void atacante(Robo& r);
		static void volante(Robo& r);
		static void goleiro(Robo& r);
		static void atacanteBasico(Robo& r);
		static void volanteBasico(Robo& r);
		static void goleiroBasico(Robo& r);

};

#endif /* ROTEIRO_H */
