#ifndef ROTEIRO_H
#define ROTEIRO_H

class Atacante : public Robo {
	public:
		void run();
};

class Goleiro : public Robo{
	public:
		void run();
};

class Volante : public Robo{
	public:
		void run();
};

#endif /* ROTEIRO_H */