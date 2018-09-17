#include "camera.hpp"
#include "robo.hpp"
// #include "CPH.hpp"
// #include "AEstrela.hpp"
// #include "radio.hpp"

#define FRAME_TIME 30
#define DESLOCA_BITS 2

int main() {
	const int quadrosPulados = 0;
	std::vector<Robo> robosTime(3);
	// USANDO ESTE VECTOR PARA MANTER AS POSICOES ANTERIORES CASO NAO CONSIGA ENCONTRAR NOVAS, RETORNA AS ANTERIORES MESMO
	std::vector<posXY> posRobosTime(3);
	// COMO ADVERSARIOS SAO APENAS OBSTACULOS (POR ENQUANTO), ELES PODEM SER APENAS PONTOS NO CAMPO
  std::vector<posXY> robosTimeAdv;
	// A BOLA ESTA NA MESMA CATEGORIA DOS ADVERSARIOS, NO MOMENTO EH APENAS UM PONTO NO CAMPO
	posXY bola;

	Camera cam("outcpp4.avi");
	//Radio radio(robosTime);

	// setando os roteiros
	robosTime[0].setRoteiro(GOLEIRO_BASICO);
	robosTime[1].setRoteiro(VOLANTE_BASICO);
	robosTime[2].setRoteiro(ATACANTE_BASICO);

	cv::Mat Frame1;
	cv::Mat Frame2;
	cv::Mat Frame3;
	cv::Mat Frame4;

	posXY aux;
	for(int i = 0; i < quadrosPulados; i++) {
		cam.getNextFrame();
		std::cout << "Pulando frames guys" << std::endl;
		cv::waitKey(1);
	}

	while(true) {
    CPH campoPotencial1(robosTime[0], robosTimeAdv);
    CPH campoPotencial2(robosTime[1], robosTimeAdv);
    CPH campoPotencial3(robosTime[2], robosTimeAdv);
		// procurando pela bola
		cam.setCorObjeto(ALARANJADO);
		cam.getPosicaoAtualObjeto(bola);
		/* BEGIN DEBUG */
	  std::cout << " bola: " << "x: " << bola.x << " y: "<< bola.y << std::endl;
		Frame1 = cam.getFrameOriginalRecortadoFlip();
		cv::Point centroCirculoBola(bola.x / cam.proporcaoPixelCentimetro, bola.y / cam.proporcaoPixelCentimetro);
		int raioCirculo = 5;
		cv::circle(Frame1, centroCirculoBola, raioCirculo, cv::Scalar(204, 0, 204), 5);
		cv::flip(Frame1, Frame1, 0);
		cv::imshow("FrameOriginal Bola Detectada", Frame1);
		/* END DEBUG */

		// procurando pelos robos aliados
		cam.setCorObjeto(AMARELO, ROSA);
		cam.getPosicaoAtualObjeto(posRobosTime[0]);
		robosTime[0].setAnguloAtualRobo(cam.getAnguloObjeto());
		robosTime[0].setPosicaoAtualRobo(posRobosTime[0]);
		robosTime[0].setPosicaoAtualBola(bola);

		/* BEGIN DEBUG */
	  std::cout << " ROBO0: " << "x: " << posRobosTime[0].x << " y: "<< posRobosTime[0].y;
		Frame2 = cam.getFrameOriginalRecortadoFlip();
		cv::Point centroCirculoRobo0(posRobosTime[0].x / cam.proporcaoPixelCentimetro, posRobosTime[0].y / cam.proporcaoPixelCentimetro);
		cv::Point localEstrategiaRobo0(robosTime[0].getPosicaoObj().x / cam.proporcaoPixelCentimetro, robosTime[0].getPosicaoObj().y / cam.proporcaoPixelCentimetro);
		raioCirculo = 5;
		cv::circle(Frame2, centroCirculoRobo0, raioCirculo, cv::Scalar(100, 100, 100), 5);
		cv::circle(Frame2, localEstrategiaRobo0, raioCirculo, cv::Scalar(255, 0, 0), 5);
		cv::flip(Frame2, Frame2, 0);
		cv::imshow("FrameOriginal Robo Detectado E Obj Robo0 AZUL", Frame2);
		/* END DEBUG */
		// getchar();

		cam.setCorObjeto(AMARELO, VERDE);
		cam.getPosicaoAtualObjeto(posRobosTime[1]);
		robosTime[1].setAnguloAtualRobo(cam.getAnguloObjeto());
		robosTime[1].setPosicaoAtualRobo(posRobosTime[1]);
		robosTime[1].setPosicaoAtualBola(bola);

		/* BEGIN DEBUG */
	  std::cout << " ROBO1: " << "x: " << posRobosTime[1].x << " y: "<< posRobosTime[1].y;
		Frame3 = cam.getFrameOriginalRecortadoFlip();
		cv::Point centroCirculoRobo1(posRobosTime[1].x / cam.proporcaoPixelCentimetro, posRobosTime[1].y / cam.proporcaoPixelCentimetro);
		cv::Point localEstrategiaRobo1(robosTime[1].getPosicaoObj().x / cam.proporcaoPixelCentimetro, robosTime[1].getPosicaoObj().y / cam.proporcaoPixelCentimetro);
		raioCirculo = 5;
		cv::circle(Frame3, centroCirculoRobo1, raioCirculo, cv::Scalar(100, 100, 100), 5);
		cv::circle(Frame3, localEstrategiaRobo1, raioCirculo, cv::Scalar(0, 255, 0), 5);
		cv::flip(Frame3, Frame3, 0);
		cv::imshow("FrameOriginal Robo Detectado E Obj Robo1 VERDE", Frame3);
		// getchar();
		/* END DEBUG */

		cam.setCorObjeto(AMARELO, ROXO);
		cam.getPosicaoAtualObjeto(posRobosTime[2]);
		robosTime[2].setAnguloAtualRobo(cam.getAnguloObjeto());
		robosTime[2].setPosicaoAtualRobo(posRobosTime[2]);
		robosTime[2].setPosicaoAtualBola(bola);

		/* BEGIN DEBUG */
	  std::cout << " ROBO2: " << "x: " << posRobosTime[2].x << " y: "<< posRobosTime[2].y;
		Frame4 = cam.getFrameOriginalRecortadoFlip();
		cv::Point centroCirculoRobo2(posRobosTime[2].x / cam.proporcaoPixelCentimetro, posRobosTime[2].y / cam.proporcaoPixelCentimetro);
		cv::Point localEstrategiaRobo2(robosTime[2].getPosicaoObj().x / cam.proporcaoPixelCentimetro,  robosTime[2].getPosicaoObj().y / cam.proporcaoPixelCentimetro );
		raioCirculo = 5;
		cv::circle(Frame4, centroCirculoRobo2, raioCirculo, cv::Scalar(100, 100, 100), 5);
		cv::circle(Frame4, localEstrategiaRobo2, raioCirculo, cv::Scalar(0, 0, 255), 5);
		cv::flip(Frame4, Frame4, 0);
		cv::imshow("FrameOriginal Robo Detectado E Obj Robo2 VERMELHO", Frame4);
		/* END DEBUG */
		// getchar();

        /**************************************************************************/
		// procurando pelos robos adversarios
		cam.setCorObjeto(AMARELO);
		cam.getPosicaoAtualObjeto(robosTimeAdv);

		// correndo os roteiros de cada robo
		std::cout << "Correndo estrategia0" << '\n';
		robosTime[0].run();
		std::cout << "Correndo estrategia1" << '\n';
		robosTime[1].run();
		std::cout << "Correndo estrategia2" << '\n';
		robosTime[2].run();

		// calculando velocidade das rodas para o robo 1
		//campoPotencial1.calculaVelRodas();
		std::cout << "Calculanda vel rodas Robo1" << '\n';
		// calculando velocidade das rodas para o robo 2
		//campoPotencial2.calculaVelRodas();
		std::cout << "Calculanda vel rodas Robo2" << '\n';
		// calculando velocidade das rodas para o robo 3
		//campoPotencial3.calculaVelRodas();
		std::cout << "Calculanda vel rodas Robo3" << '\n';
    // corrigindo a velocidade das rodas para funcionar com o radio novo
    for(int i = 0; i < robosTime.size(); i++) {
			velocidadeRobo v = robosTime[i].getVelocidadeAtualRobo();
			v.rodaEsq = v.rodaEsq << DESLOCA_BITS;
			v.rodaDir = v.rodaDir << DESLOCA_BITS;
			// v.rodaEsq = 255;
			// v.rodaDir = 255;
			robosTime[i].setVelocidadeAtualRobo(v);
		}

		for(int i = 0; i < robosTime.size(); i++) {
			std::cout << "Velocidade Robo " << i << ": " << "Roda esquerda: " << (int)(robosTime[i].getVelocidadeAtualRobo().rodaEsq) << " Roda direita: " << (int)(robosTime[i].getVelocidadeAtualRobo().rodaDir) << '\n';
		}

		// getchar();
		//radio.enviaDados();
		cv::waitKey(FRAME_TIME);
		cam.getNextFrame();

		Frame1.release();
		Frame2.release();
		Frame3.release();
		Frame4.release();

	}
}
