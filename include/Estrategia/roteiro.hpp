#ifndef ROTEIRO_H
#define ROTEIRO_H

#include "comportamento.hpp"

enum roteiros {
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
};

#endif /* ROTEIRO_H */