#include "camera.hpp"
#include "robo.hpp"
#include "CPH.hpp"
#include "radio.hpp"

#define FRAME_TIME 30

int main() {
	std::vector<Robo> robosTime(3);
	std::vector<Robo> robosTimeAdv(3);

	Camera cam(1);
	Radio radio(robosTime);
	CPH campoPotencial1(robosTime[0], robosTimeAdv);
	CPH campoPotencial2(robosTime[1], robosTimeAdv);
	CPH campoPotencial3(robosTime[2], robosTimeAdv);

	// setando os roteiros
	robosTime[0].setRoteiro(GOLEIRO_BASICO);
	robosTime[1].setRoteiro(VOLANTE_BASICO);
	robosTime[2].setRoteiro(ATACANTE_BASICO);

	while(true) {
		// pegando as informacoes de localizacao a partir da camera para os robos e a bola
		posXY localObjeto;
		posXY bola;
		// procurando pela bola
		cam.setCorObjeto(ALARANJADO);
		cam.getPosicaoAtualObjeto(bola);
		// procurando pelos robos aliados
		cam.setCorObjeto(CORES);
		cam.getPosicaoAtualObjeto(localObjeto);
		robosTime[0].setPosicaoAtualRobo(localObjeto);

		cam.setCorObjeto(CORES);
		cam.getPosicaoAtualObjeto(localObjeto);
		robosTime[1].setPosicaoAtualRobo(localObjeto);

		cam.setCorObjeto(CORES);
		cam.getPosicaoAtualObjeto(localObjeto);
		robosTime[2].setPosicaoAtualRobo(localObjeto);

		// procurando pelos robos adversarios
		cam.setCorObjeto(CORES);
		cam.getPosicaoAtualObjeto(localObjeto);
		robosTimeAdv[0].setPosicaoAtualRobo(localObjeto);

		cam.setCorObjeto(CORES);
		cam.getPosicaoAtualObjeto(localObjeto);
		robosTimeAdv[1].setPosicaoAtualRobo(localObjeto);

		cam.setCorObjeto(CORES);
		cam.getPosicaoAtualObjeto(localObjeto);
		robosTimeAdv[2].setPosicaoAtualRobo(localObjeto);

		// correndo os roteiros de cada robo
		robosTime[0].run();
		robosTime[1].run();
		robosTime[2].run();

		// calculando velocidade das rodas para o robo 1
		campoPotencial1.calculaVelRodas();
		// calculando velocidade das rodas para o robo 2
		campoPotencial2.calculaVelRodas();
		// calculando velocidade das rodas para o robo 3
		campoPotencial3.calculaVelRodas();
		radio.enviaDados();
		cv::waitKey(FRAME_TIME);
		cam.getNextFrame();
	}
}
