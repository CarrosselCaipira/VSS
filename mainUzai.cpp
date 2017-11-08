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


	for (int i = 10; i < 130; i=i+5) {
		for (int j = 0; j < 160; j=j+5) {
			// while(true) {
			// pegando as informacoes de localizacao a partir da camera para os robos e a bola
			posXY localObjeto;
			posXY bola;
			posXY aux;
			posXY aux2;

			aux2.x = i;
			aux2.y = j;
			//pegando a posição atual do robô


			robosTime[0].setPosicaoAtualRobo(10, 10);
			robosTime[0].setPosicaoAtualBola(aux2);
			// std::cout << "ROBO1" << '\n';
			aux = robosTime[0].getPosicaoAtualRobo();
			// std::cout << "Posição do robô 1: " << aux.y<<'\n';
			/*--*/
			robosTime[1].setPosicaoAtualRobo(20, 10);
			robosTime[1].setPosicaoAtualBola(aux2);
			// std::cout << "ROBO2" << '\n';
			aux = robosTime[1].getPosicaoAtualRobo();
			// std::cout << "Posição do robô 1: " << aux.y<<'\n';
			/*--*/
			robosTime[2].setPosicaoAtualRobo(20, 30);
			robosTime[2].setPosicaoAtualBola(aux2);
			// std::cout << "ROBO3" << '\n';
			aux = robosTime[2].getPosicaoAtualRobo();
			// std::cout << "Posição do robô 1: " << aux.x<<'\n';
			/*--*/

			// correndo os roteiros de cada robo
			std::cout << "BOLA X:" << aux2.x << '\n';
			std::cout << "BOLA Y:" << aux2.y << '\n';

			robosTime[0].run();
			aux =robosTime[0].getPosicaoObj();
			std::cout << "Objetivo do ROBO1-> x:" << aux.x << " e y:"<< aux.y << '\n' <<'\n';

			robosTime[1].run();
			aux =robosTime[1].getPosicaoObj();
			std::cout << "Objetivo do ROBO2-> x:" << aux.x << " e y:"<< aux.y << '\n' <<'\n';

			robosTime[2].run();
			aux =robosTime[2].getPosicaoObj();
			std::cout << "Objetivo do ROBO3-> x:" << aux.x << " e y:"<< aux.y << '\n' <<'\n';
			// getchar();
			std::cout << "------------------" << '\n';
			usleep(400000);

		}
	}
	// }

}
