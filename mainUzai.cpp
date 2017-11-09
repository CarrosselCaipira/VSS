// #include "camera.hpp"
#include "robo.hpp"
#include <vector>
#include <iostream>
#include <unistd.h>
// #include "CPH.hpp"
// #include "radio.hpp"
#define FRAME_TIME 30

int main() {

	std::vector<Robo> robosTime(3);
	// setando os roteiros
	robosTime[0].setRoteiro(GOLEIRO_BASICO);
	robosTime[1].setRoteiro(VOLANTE_BASICO);
	robosTime[2].setRoteiro(ATACANTE_BASICO);

	int temp;
	posXY aux2;
	posXY aux;
	aux2.x = 2;
	aux2.y = 2;
	for (int i = 25; i < 85; i=i+10) {
		for (int j = 5; j < 130; j=j+5) {
		robosTime[0].setPosicaoAtualRobo(10, 75);
		robosTime[1].setPosicaoAtualRobo(50, 50);
		robosTime[2].setPosicaoAtualRobo(50, 100);
		// while(true) {
			// pegando as informacoes de localizacao a partir da camera para os robos e a bola
			posXY localObjeto;
			posXY bola;


			// if(aux2.y < 128)
			// 	aux2.y = aux2.y = aux2.y + 15;
			// else{
			// 	aux2.y = 2;
			// 	aux2.x = 122;
			// }
			aux2.x = i;
			aux2.y = j;


			robosTime[0].setPosicaoAtualBola(aux2);
			aux = robosTime[0].getPosicaoAtualRobo();
			robosTime[1].setPosicaoAtualBola(aux2);
			aux = robosTime[1].getPosicaoAtualRobo();
			robosTime[2].setPosicaoAtualBola(aux2);
			aux = robosTime[2].getPosicaoAtualRobo();

			// correndo os roteiros de cada robo
			std::cout << "BOLA X:" << aux2.x << '\n';
			std::cout << "BOLA Y:" << aux2.y << '\n';

			robosTime[0].run();
			aux =robosTime[0].getPosicaoObj();
			robosTime[0].setPosicaoAtualRobo(aux);
			std::cout << "Objetivo do ROBO1-> x:" << aux.x << " e y:"<< aux.y << '\n' <<'\n';

			robosTime[1].run();
			aux =robosTime[1].getPosicaoObj();
			robosTime[1].setPosicaoAtualRobo(aux);
			std::cout << "Objetivo do ROBO2-> x:" << aux.x << " e y:"<< aux.y << '\n' <<'\n';

			robosTime[2].run();
			aux =robosTime[2].getPosicaoObj();
			robosTime[2].setPosicaoAtualRobo(aux);
			std::cout << "Objetivo do ROBO3-> x:" << aux.x << " e y:"<< aux.y << '\n' <<'\n';
			std::cout << "------------------" << '\n';
			// usleep(500000);
			getchar();
			system("clear");
		}
	}
	// }

}
