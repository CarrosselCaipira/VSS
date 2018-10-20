// Este arquivo deve estar uma subpasta chamada da raiz do codigo e preferencialmente deve ser denominada Testes
#include "../camera.hpp"
#include "../robo.hpp"
#include "../CPH.hpp"
#include "../radio.hpp"
#include "../tecnicoOfensivo.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// Variaveis globais porque sim
int sliderXbola;
int sliderYbola;
cv::Mat imgAtacante;
cv::Mat imgGoleiro;
cv::Mat imgVolante;
cv::Mat aux;
std::vector<Robo> robosTime(3);
std::vector<Robo> robosAdv(3);
Bola bola;

// Representacao por cores:
// VERMELHO: bola
// AZUL: objetivo do robô

static void trackBarXGoleiro( int, void* ) {
    imgGoleiro = aux.clone();  
    // Circulo que representa o objetivo do Goleiro 
    cv::circle(imgGoleiro, cv::Point(robosTime[0].getPosicaoObj().x, robosTime[0].getPosicaoObj().y), 8, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
    // Circulo que representa a bola
    cv::circle(imgGoleiro, cv::Point(sliderXbola, sliderYbola), 5, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // Atualiza o valor da bola na variavel
    bola.setPosicaoAtualBola(sliderXbola, sliderYbola);
}

static void trackBarYGoleiro( int, void* ) {
    imgGoleiro = aux.clone();  
    // Circulo que representa o objetivo do Goleiro 
    cv::circle(imgGoleiro, cv::Point(robosTime[0].getPosicaoObj().x, robosTime[0].getPosicaoObj().y), 8, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
    // Circulo que representa a bola
    cv::circle(imgGoleiro, cv::Point(sliderXbola, sliderYbola), 5, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // Atualiza o valor da bola na variavel
    bola.setPosicaoAtualBola(sliderXbola, sliderYbola);
}

static void trackBarXVolante( int, void* ) {
    imgVolante = aux.clone();  
    // Circulo que representa o objetivo do Volante 
    cv::circle(imgVolante, cv::Point(robosTime[1].getPosicaoObj().x, robosTime[1].getPosicaoObj().y), 8, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
    // Circulo que representa a bola
    cv::circle(imgVolante, cv::Point(sliderXbola, sliderYbola), 5, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // Atualiza o valor da bola na variavel
    bola.setPosicaoAtualBola(sliderXbola, sliderYbola);
}

static void trackBarYVolante( int, void* ) {
    imgVolante = aux.clone();  
    // Circulo que representa o objetivo do Volante 
    cv::circle(imgVolante, cv::Point(robosTime[1].getPosicaoObj().x, robosTime[1].getPosicaoObj().y), 8, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
    // Circulo que representa a bola
    cv::circle(imgVolante, cv::Point(sliderXbola, sliderYbola), 5, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // Atualiza o valor da bola na variavel
    bola.setPosicaoAtualBola(sliderXbola, sliderYbola);
}

static void trackBarXAtacante( int, void* ) {
    imgAtacante = aux.clone(); 
    // Circulo que representa o objetivo do Atacante 
    cv::circle(imgAtacante, cv::Point(robosTime[2].getPosicaoObj().x, robosTime[2].getPosicaoObj().y), 8, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
    // Circulo que representa a bola
    cv::circle(imgAtacante, cv::Point(sliderXbola, sliderYbola), 5, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // Atualiza o valor da bola na variavel
    bola.setPosicaoAtualBola(sliderXbola, sliderYbola);
}

static void trackBarYAtacante( int, void* ) {
    imgAtacante = aux.clone();  
    // Circulo que representa o objetivo do Atacante 
    cv::circle(imgAtacante, cv::Point(robosTime[2].getPosicaoObj().x, robosTime[2].getPosicaoObj().y), 8, cv::Scalar(255, 0, 0), cv::FILLED, cv::LINE_8);
    // Circulo que representa a bola
    cv::circle(imgAtacante, cv::Point(sliderXbola, sliderYbola), 5, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // Atualiza o valor da bola na variavel
    bola.setPosicaoAtualBola(sliderXbola, sliderYbola);
}

int main(int argc, char** argv){
    TecnicoOfensivo tecnico(robosTime, robosAdv, bola);
    
    // Iniciando as imagens que serao mostradas em cada janela
    // Utilize cv::imread(argv[1], 1) caso seja dada uma imagem como entrada
    aux = cv::Mat(TAM_Y_CAMPO, TAM_X_CAMPO, CV_8UC3, cv::Scalar(255, 255, 255));
    //aux = cv::imread(argv[1], 1);

    imgAtacante = aux.clone();
    imgGoleiro = aux.clone();
    imgVolante = aux.clone();
       
    // Criando as janelas para cada robo
    // Apesar de estarem em janelas diferentes, as variaveis sao comuns entre elas
    // se quiser, comente as janelas porem isso tera que ser feito em todos os locais onde ha a mencao delas, como no createTrackbar()
    cv::namedWindow("Goleiro");
    cv::namedWindow("Volante");
    cv::namedWindow("Atacante");
    
    sliderXbola = 50;
    sliderYbola = 50;

    // Inicializando os robos com suas posicoes, angulos e sentidos
    // Se necessario testar outras situacoes, altere aqui (a menos que seja necessario criar uma nova sliderbar, se for o caso Boa Sorte)
    robosTime[0].setPosicaoAtualRobo(TAM_X_GOL + TAM_ROBO/2, TAM_Y_CAMPO/2); // o goleiro nao precisa de muita coisa
    
    robosTime[1].setPosicaoAtualRobo(TAM_X_CAMPO/2 - 5, TAM_Y_CAMPO/2+20);
    robosTime[1].setAnguloAtualRobo(0); // desencargo de consciencia
    robosTime[1].setVetorSentidoAtualRobo(1, 0); // um vetor paralelo ao eixo horizontal do campo
    
    robosTime[2].setPosicaoAtualRobo(TAM_X_CAMPO/2, TAM_Y_CAMPO/2+5);
    robosTime[2].setAnguloAtualRobo(0); // desencargo de consciencia
    robosTime[2].setVetorSentidoAtualRobo(1, 0); // um vetor paralelo ao eixo horizontal do campo
    
    // Criando as sliderbars para as coordenadas da bola
    cv::createTrackbar("XBola", "Goleiro", &sliderXbola, TAM_X_CAMPO, trackBarXGoleiro);
    cv::createTrackbar("YBola", "Goleiro", &sliderYbola, TAM_Y_CAMPO, trackBarYGoleiro);
    cv::createTrackbar("XBola", "Volante", &sliderXbola, TAM_X_CAMPO, trackBarXVolante);
    cv::createTrackbar("YBola", "Volante", &sliderYbola, TAM_Y_CAMPO, trackBarYVolante);
    cv::createTrackbar("XBola", "Atacante", &sliderXbola, TAM_X_CAMPO, trackBarXAtacante);
    cv::createTrackbar("YBola", "Atacante", &sliderYbola, TAM_Y_CAMPO, trackBarYAtacante);

    while (true){
        //Mostrando as imagens em suas respectivas janelas
        cv::imshow("Goleiro", imgGoleiro);
        cv::imshow("Volante", imgVolante);
        cv::imshow("Atacante", imgAtacante);

        // Prints no console porque sim
        //std::cout << "(" << robosTime[0].getPosicaoObj().x << ", " << robosTime[0].getPosicaoObj().y << ")\n";
        //std::cout << "(" << robosTime[1].getPosicaoObj().x << ", " << robosTime[1].getPosicaoObj().y << ")\n";
        //std::cout << "(" << robosTime[2].getPosicaoObj().x << ", " << robosTime[2].getPosicaoObj().y << ")\n";

        cv::waitKey(30);
        tecnico.run();
        // Ao rodar, ira aparecer um monte de mensagens de erro, mas e so dar uma mexida nos sliderbars
        // que os valores sao atualizados e nao (pelo menos nao deve) aparecera mais mensagens
    }
}