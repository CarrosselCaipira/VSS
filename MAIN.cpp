#include "camera.hpp"
#include "robo.hpp"
#include "CPH.hpp"
#include "radio.hpp"

#define FRAME_TIME 30

int main() {
	const int quadrosPulados = 50;
	std::vector<Robo> robosTime(3);
	// USANDO ESTE VECTOR PARA MANTER AS POSICOES ANTERIORES CASO NAO CONSIGA ENCONTRAR NOVAS, RETORNA AS ANTERIORES MESMO
	std::vector<posXY> posRobosTime(3);
	// COMO ADVERSARIOS SAO APENAS OBSTACULOS (POR ENQUANTO), ELES PODEM SER APENAS PONTOS NO CAMPO
  std::vector<posXY> robosTimeAdv;
	// A BOLA ESTA NA MESMA CATEGORIA DOS ADVERSARIOS, NO MOMENTO EH APENAS UM PONTO NO CAMPO
	posXY bola;

	Camera cam("outcpp4.avi");
	// Radio radio(robosTime);
	CPH campoPotencial1(robosTime[0], robosTimeAdv);
	CPH campoPotencial2(robosTime[1], robosTimeAdv);
	CPH campoPotencial3(robosTime[2], robosTimeAdv);

	// setando os roteiros
	robosTime[0].setRoteiro(GOLEIRO_BASICO);
	robosTime[1].setRoteiro(VOLANTE_BASICO);
	robosTime[2].setRoteiro(ATACANTE_BASICO);

	cv::Mat Frame;

	for(int i = 0; i < quadrosPulados; i++) {
		cam.getNextFrame();
		std::cout << "Pulando frames guys" << std::endl;
		cv::waitKey(30);
	}

	while(true) {
		// procurando pela bola
		cam.setCorObjeto(ALARANJADO);
		cam.getPosicaoAtualObjeto(bola);

		/* BEGIN DEBUG */
	  std::cout << " bola: " << "x: " << bola.x << " y: "<< bola.y << std::endl;
		Frame = cam.getFrameOriginalRecortado();
		cv::Point centroCirculoBola(bola.x, bola.y);
		int raioCirculo = 5;
		cv::circle(Frame, centroCirculoBola, raioCirculo, cv::Scalar(0, 255, 0), 5);
		cv::imshow("FrameOriginal Bola Detectada", Frame);
		/* END DEBUG */

		// procurando pelos robos aliados
		cam.setCorObjeto(AMARELO, ROSA);
		cam.getPosicaoAtualObjeto(posRobosTime[0]);
		robosTime[0].setPosicaoAtualRobo(posRobosTime[0]);
		robosTime[0].setPosicaoAtualBola(bola);

		/* BEGIN DEBUG */
	  std::cout << " ROBO0: " << "x: " << posRobosTime[0].x << " y: "<< posRobosTime[0].y;
		Frame = cam.getFrameOriginalRecortado();
		cv::Point centroCirculoRobo0(posRobosTime[0].x * cam.proporcaoPixelCentimetro
* cam.proporcaoPixelCentimetro, posRobosTime[0].y * cam.proporcaoPixelCentimetro
* cam.proporcaoPixelCentimetro);
		cv::Point localEstrategiaRobo0(robosTime[0].getPosicaoObj().x * cam.proporcaoPixelCentimetro
* cam.proporcaoPixelCentimetro, robosTime[0].getPosicaoObj().y / cam.proporcaoPixelCentimetro
/ cam.proporcaoPixelCentimetro);
		raioCirculo = 5;
		cv::circle(Frame, centroCirculoRobo0, raioCirculo, cv::Scalar(0, 255, 0), 5);
		cv::circle(Frame, localEstrategiaRobo0, raioCirculo, cv::Scalar(0, 0, 255), 5);
		cv::imshow("FrameOriginal Robo Detectado E Obj Robo0", Frame);
		/* END DEBUG */
		// getchar();

		cam.setCorObjeto(AMARELO, ROXO);
		cam.getPosicaoAtualObjeto(posRobosTime[1]);
		robosTime[1].setPosicaoAtualRobo(posRobosTime[1]);
		robosTime[1].setPosicaoAtualBola(bola);

		/* BEGIN DEBUG */
	  std::cout << " ROBO1: " << "x: " << posRobosTime[1].x << " y: "<< posRobosTime[1].y;
		Frame = cam.getFrameOriginalRecortado();
		cv::Point centroCirculoRobo1(posRobosTime[1].x / cam.proporcaoPixelCentimetro, posRobosTime[1].y / cam.proporcaoPixelCentimetro);
		cv::Point localEstrategiaRobo1(robosTime[1].getPosicaoObj().x / cam.proporcaoPixelCentimetro, robosTime[0].getPosicaoObj().y / cam.proporcaoPixelCentimetro);
		raioCirculo = 5;
		cv::circle(Frame, centroCirculoRobo1, raioCirculo, cv::Scalar(0, 255, 0), 5);
		cv::circle(Frame, localEstrategiaRobo1, raioCirculo, cv::Scalar(0, 0, 255), 5);
		cv::imshow("FrameOriginal Robo Detectado E Obj Robo1", Frame);
		/* END DEBUG */
		// getchar();

		cam.setCorObjeto(AMARELO, VERDE);
		cam.getPosicaoAtualObjeto(posRobosTime[2]);
		robosTime[2].setPosicaoAtualRobo(posRobosTime[2]);
		robosTime[2].setPosicaoAtualBola(bola);

		/* BEGIN DEBUG */
	  std::cout << " ROBO2: " << "x: " << posRobosTime[2].x << " y: "<< posRobosTime[2].y;
		Frame = cam.getFrameOriginalRecortado();
		cv::Point centroCirculoRobo2(posRobosTime[2].x / cam.proporcaoPixelCentimetro, posRobosTime[2].y / cam.proporcaoPixelCentimetro);
		cv::Point localEstrategiaRobo2(robosTime[2].getPosicaoObj().x / cam.proporcaoPixelCentimetro,  robosTime[2].getPosicaoObj().y / cam.proporcaoPixelCentimetro );
		raioCirculo = 5;
		cv::circle(Frame, centroCirculoRobo2, raioCirculo, cv::Scalar(0, 255, 0), 5);
		cv::circle(Frame, localEstrategiaRobo2, raioCirculo, cv::Scalar(0, 0, 255), 5);
		cv::imshow("FrameOriginal Robo Detectado E Obj Robo2", Frame);
		/* END DEBUG */
		// getchar();

        /**************************************************************************/
		// procurando pelos robos adversarios
		cam.setCorObjeto(AZUL);
		cam.getPosicaoAtualObjeto(robosTimeAdv);

		// correndo os roteiros de cada robo
		std::cout << "Correndo estrategia0" << '\n';
		robosTime[0].run();
		std::cout << "Correndo estrategia1" << '\n';
		robosTime[1].run();
		std::cout << "Correndo estrategia2" << '\n';
		robosTime[2].run();

		// calculando velocidade das rodas para o robo 1
		std::cout << "Calculando vel rodas Robo1" << '\n';
		campoPotencial1.calculaVelRodas();
		// calculando velocidade das rodas para o robo 2
		std::cout << "Calculando vel rodas Robo2" << '\n';
		// campoPotencial2.calculaVelRodas();
		// calculando velocidade das rodas para o robo 3
		std::cout << "Calculando vel rodas Robo3" << '\n';
		campoPotencial3.calculaVelRodas();
    // corrigindo a velocidade das rodas para funcionar com o radio novo
    for(int i = 0; i < robosTime.size(); i++) {
			velocidadeRobo v = robosTime[i].getVelocidadeAtualRobo();
			v.rodaEsq = 255;
			v.rodaDir = 255;
			robosTime[i].setVelocidadeAtualRobo(v);
		}

		for(int i = 0; i < robosTime.size(); i++) {
			std::cout << "Velocidade Robo " << i << ": " << "Roda esquerda: " << robosTime[i].getVelocidadeAtualRobo().rodaEsq << " Roda direita: " << robosTime[i].getVelocidadeAtualRobo().rodaDir << '\n';
		}

		// radio.enviaDados();
		cv::waitKey(FRAME_TIME);
		cam.getNextFrame();
	}
}
