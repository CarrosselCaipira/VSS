#ifndef ROTEIRO_H
#define ROTEIRO_H

#include "comportamento.hpp"

class Atacante : public Robo {
	friend comportamento;
	public:
		void run();
};

class Goleiro : public Robo{
	friend comportamento;
	public:
		void run();
};

class Volante : public Robo{
	friend comportamento;
	public:
		void run();
};

#endif /* ROTEIRO_H */