#ifndef CAMERA_H
#define CAMERA_H

#include "propositoGeralAtuadores.hpp"
#include "gestorArq.hpp"
#include <bitset>
#include <iostream>
#include <algorithm>

class Camera : public GestorArq {
	protected:
		/* BITSET DE REGISTRO DE ALTERACOES/ATUALIZACOES PARA CADA COR */
		std::bitset<NUM_TOTAL_CORES> corProcessada;

		/* 'BITSET' (VECTOR BOOL) PARA REGISTRO DE QUAIS RETANGULOS FORAM ENCONTRADOS A PARTIR DAS POSICOES ANTERIORES. CADA COR POSSUI UM BITSET. EXEMPLO: NO FRAME ANTERIOR EXISTIAM 3 OBJETOS DA COR AZUL, LOGO, A COR AZUL POSSUI UM BITSET DE 3 ELEMENTOS. ESSES ELEMENTOS IRAO REPRESENTAR AS REGIOES DE BUSCA PARA O FRAME ATUAL E SE FOI ENCONTRADO ALGUM OBJETO DA COR NO FRAME ATUAL.  */
		// std::vector<std::vector<bool>> objetosEncontrados;

		/* PARAMETROS PARA O METODO CANY PARA DETECCAO DE BORDA. REFERENCIAS: https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html */
		int limiteInferior = 100; /**< Limite inferior para a deteccao das bordas. Se o gradiente do pixel eh inferior a este limite, o pixel eh rejeitado. O pixel eh aceito apenas se o gradiente for maior que limite superior, que eh o limite inferior multiplicado pela proporcao abaixo. Se o gradiente do pixel estiver entre os dois limites, ele aceito apenas se estiver conectado com um pixel que tem o valor de seu gradiente maior que o limite superior. */
		int proporcaoLimiarInferiorSuperior = 2; /**< Proporcao dos limites inferior:superior. Aqui estamos usando usa proporcao 2:1. Para o Cany eh recomendada uma proporcao de 2:1 ou 3:1 */
		int tamanhoKernelSobel = 3; /**< Tamanho do kernel de Sobel que sera usado internamente pela funcao Cany. O tamanho do kernel deve ser entre 3 e 7 (inclusive) e deve ser impar. */

		/* PARAMETROS PARA DETECCAO DE RETANGULOS */
		int distanciaDespresivelCentros = 20; /**< Distancia em pixel de centros de retangulo despresiveis. Na procura por cores, as vezes a mesma posicao eh considerada diferente. Se a diferenca entre os dois centros for menor ou igual a 5, esse centro eh despresado. */
		int minAreaRetangulo = 5; /**< Area minima para ser considerado um retangulo valido para deteccao */
		int maxAreaRetangulo = 20; /**< Area maxima para ser considerado um retangulo valido para deteccao */

		/* PARAMETROS RELACIONADOS COM AS IMAGENS */
		cv::VideoCapture camera; /**< Objeto que recebe o conteudo de video, seja um video gravado ou da camera (tempo real) */
		cv::Mat frameOriginal; /**< Frames originais vindos da fonte (o objeto acima: cv::VideoCapture camera) que pode ser uma imagem estatica, camera ou video gravado. */
		cv::Mat frameOriginalRecortado; /**< Recorte da regiao do frameOriginal que contem apenas do campo */
		cv::Mat hsvFrameOrignal; /**< framesOriginal convertido para o formato de cor HSV. */
		cv::Mat imgBinarizada; /**< Imagem binarizada. Usando a imagem em hsv, faz-se a saturacao das cores afim de obter uma imagem de apenas duas cores (preto e branco) onde branco representa o objeto que estamos tentando encontar (bola, tag de time, tag de robo, etc.) e preto a regiao de NAO interesse. */

		/* PARAMETROS DO RETANGULO DE RECORTE DA REGIAO DE INTERESSE */
		cv::Rect retanguloDeRecorte; /**< Retangulo de selecao de regiao de interesse na imagem HSV */

		/* PARAMETROS DEFINIDOS PELOS GETTERS */
		Cores cor1; /**< Cor do objeto a ser procurado. Cor primaria (tags de time ou bola) */
		Cores cor2; /**< Cor do objeto a ser procurado. Cor secundaria (tags de jogador) */
		int numObjetosCor1; /**< Numero de objetos que devem ser procurados da cor1. Cor1 eh a cor primaria (tag de time ou bola) */
		int numObjetosCor2; /**< Numero de objetos que devem ser procurados. Cor2 eh a cor secundaria(tag jogador) */

	public:
		/** @var centroRetangulos
		 *  @brief Vetor de vetores de posicoes XY para o retangulo de cada cor no instante atual.
		 *
		 *  @note Este vector eh publico para permitir que, caso ocorram erros de identificacao de objetos, o objeto que esta tentando determinar sua posicao possa fazer uma melhor escolha baseado nas localizacoes obtidas
		 */
		std::vector<std::vector<Retangulo>> centroAtualRetangulos;

		/** @var centroAntRetangulos
		 *  @brief Vetor de vetores de posicoes XY para o retangulo de cada cor no instante anterior.
		 *
		 *  @note Este vector eh publico para permitir que, caso ocorram erros de identificacao de objetos, o objeto que esta tentando determinar sua posicao possa fazer uma melhor escolha baseado nas localizacoes obtidas
		 */
		std::vector<std::vector<Retangulo>> centroAntRetangulos;

	private:
		/** @fn void inicializaVect()
		 *  @brief Faz a inicializacao (alocacao) dos NUM_TOTAL_CORES vectors imgBinarizada, circulos, paramHSVCores e alteracoes.
		 */
		void inicializaVect();

		/** @fn filtragemHSVParamYMLCorPrimaria()
		 *  @brief Faz a filtragem e saturacao da cor primaria (tag de time ou bola) utilizando os parametros de H, S e V min e max obtidos do arquivo .yml
		 *
		 *  @see gestorArq.hpp
		 */
		void filtragemHSVParamYMLTotal(const Cores cor, int aumentoAmplitudeCor = 0);

		/** @fn filtragemHSVParamYMLCorSecundaria()
		 *  @brief Faz a filtragem e saturacao da cor secundaria (tag de jogador) utilizando os parametros de H, S e V min e max obtidos do arquivo .yml. Esta filtragem difere da filtragem da cor primaria no sentido de que para fazer a filtragem das cores secundarias nao eh necessario observar (e filtrar) a imagem como um todo a procura das cores primarias, apenas as regioes envolta das cores primarias, otimizando o processamento e minimizando falsos positivos.
		 *
		 *  @see gestorArq.hpp
		 */
		void filtragemHSVParamYMLParcial(const Cores cor, int aumentoAmplitudeCor = 0);

		/** @fn alteraMorfologia(const Cores cor)
		 *  @brief Faz a erosao e dilatacao (nesta ordem) da imagem binarizada para eliminar ruidos (erosao) e destacar ainda mais as regioes de interesse. Os parametros de erosao/dilatacao numero de vezes a erodir/dilatar e o tamanho do retangulo vem do arquivo de configuracao.
		 *  @param cor Cor binarizada que sera afetada pela erosao e dilatacao. Como cor eh uma enumaracao, usamos cor como indice do vetor de imagens binarizadas.
		 *
		 *  @see gestorArq.hpp
		 *  @see propositoGeralCamera.hpp
		 */
		void alteraMorfologia(const Cores cor);

		/** @fn void retanguloEntornoPonto(const posXY p)
		 *  @brief Seta o retangulo envolta de um ponto passado por parametro com uma area entorno do retangulo de area X area pixels. Este retangulo sera usado para fazer o recorte da regiao de interesse na imagem como um todo para evitar a procura de cores secundarias pelo campo todo ja que estao sempre acompanhadas das cores primarias.
		 *  @param p Posicao central do retangulo a ser criado.
		 *  @param area Altura e largura da regiao de interesse.
		 */
		void retanguloEntornoPonto(const posXY p, const int area);
		int detectaRetangulos(const Cores cor);
		void corrigeCoodernadas(posXY& p);
		bool procuraEnvoltaPosOutraCorFrameAtual(const Cores corBuscada, const Cores corBase);
		bool procuraEnvoltaPosFrameAnterior(const Cores cor);
		bool procuraCampoTodo(const Cores cor);
		void controlaOcorrenciasDuplicadas(const Cores cor);
		void eliminaExtrasPorArea(const Cores cor);
		bool processaCor2();
		bool processaCor1();
		void getIndexMaisProximo(int& indexVect1, int& indexVect2);

	public:
		cv::Mat getFrameOriginalRecortado();

		/** @fn Camera(const int indexEntrada, const std::string caminhoArquivoConfiguracoes)
		 *  @brief Construtor da classe de camera. Cria a instancia do objeto camera tetando abrir a camera definida pelo index passado como parametro e define manualmente o caminho para o arquivo de configuracao de cores.
		 *  @param indexEntrada Index do dispositivo de video usado para adquirirmos os frames.
		 *  @param caminhoArquivoConfiguracoes Caminho para o arquivo de configuracao que, por padrao, eh 'configuracaoes.yml'.
		 *
		 *  @tip Em notebooks um indexEntrada = 0 define a webcam embutida e indexEntrada = 1 uma camera externa.
		 */
		Camera(const int indexEntrada, const std::string caminhoArquivoConfiguracoes = "configuracoes.yml");

		/** @fn Camera(const std::string caminhoVideoGravado)
		 *  @brief Construtor da classe de camera. Cria a instancia do objeto camera tetando abrir o arquivo de video passado como parametro.
		 *  @param caminhoVideoGravado Caminho para o arquivo de video.
		 *  @param caminhoArquivoConfiguracoes Caminho para o arquivo de configuracao que, por padrao, eh 'configuracaoes.yml'.
		 *
		 *  @tip Aparentemente, apenas arquivos .avi sao suportados. Para mais detalhes de formatos ir para a documentacao do opencv: http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html#videocapture
		 */
		Camera(const std::string caminhoVideoGravado, const std::string caminhoArquivoConfiguracoes = "configuracoes.yml");

		/** @fn ~Camera()
		 *  @brief Desaloca e libera os recursos solicitados pela classe
		 */
		~Camera();

		/** @fn getNextFrame()
		 *	@param liberaAoFimDeAquivo Parametro nao obrigatorio que, se em true, ao acabar o arquivo de video, a funcao libera a camera da fonte de frames. Se em false, a funcao nao libera a camera e isso deve ser feito manualmente atraves da funcao void liberaCamera(). Quando a camera eh libera, para que possa ser usada novamente, deve ser reinstanciada.
		 *  @brief Faz a variavel membro frameOriginal receber o proximo frame do video e reseta o bitset. Esta funcao precisa ser chamada sempre para que novas imagens cheguem da camera e sejam processadas.
		 *  @return Retorna Zero se tudo ocorreu bem (conseguiu 'pegar' um frame novo da fonte) e retorna -1 caso o frame esteja vazio (geralmente, fim de arquivo de video).
		 */
		int getNextFrame(bool liberaAoFimDeAquivo = true);

		/** @fn void liberaCamera()
		 *  @brief Libera manualmente a camera
		 */
	 	void liberaCamera();

		int getPosicaoAtualObjeto(posXY& posicaoObj);

		/** @fn setNumObjetos(const int n)
		 *  @brief Define o numero de objetos a serem detectados.
		 *  @param n Numero de objetos a serem detectados.
		 */
		void setNumObjetosCor(const int numCor1, const int numCor2 = 0 );

		/** @fn setCorObjetos(const Cores c)
		 *  @brief Define a cor do(s) obejto(s) a ser(serem) detectados
		 *  @param c Cor do objeto a ser detectado. Deve ser uma das cores definidas pela enumeracao Cores.
		 */
		void setCorObjeto(const Cores cor1, const Cores cor2  = INDEFINIDA );

		/*TO-DO:
		 *CRIAR FUNCAO PARA CRIACAO DAS JANEAS;
		 *CRIAR FUNCAO DE LIMITADOR DE AREA DE PROCESSAMENTO (FOCAR APENAS NO CAMPO)
		 *CRIACAO DOS SLIDERS DE CALIBRACAO. TANDO PARA OS PARAMETROS DE H, S e V MAX E MIN MAS PARA DE DETECACAO DE CIRCULOS.
		 *CRIACAO DA ROTINA PARA SALVAR OS DADOS DOS SLIDERS EM XML/YAML
		 *CRIACAO DA ROTINA PARA RECURAR OS DADOS DOS SLIDERS DO ARQUIVO XML - DONE
		 *CRIAR ROTINA DE CALIBRACAO POR CLICK NA TELA. DURATE A CALIBRAGEM, CLICA-SE COM O BOTAO ESQUERDO SOBRE A JANELA DOS FRAMES ORIGINAIS FAZEMOS A LEITURA DOS VALORES DE HSV DAQUELE PONTO, AO CLICAR MAIS DE UMA VEZ FAZ-SE A MEDIA DOS VALORES. PARA ESQUECER O FRAME ANTERIOR (CLICOU NO LUGAR ERRADO NA HORA DE CALIBRAR) CLICAR COM O BOTAO DIREITO NA MESMA TELA. TEREMOS UM COMBOBOX PARA DEFINIR QUAL COR ESTA SENDO CALIBRADA. POR EXEMPLO: ESTAMOS CALIBRANDO A COR AZUL, QUE EH A TAG DO TIME, EXISTEM VARIAS EM CAMPO, ENTAO PARA TERMOS UMA MELHOR APROXIMACAO, PODE-SE CLICAR COM O BOTAO ESQUERDO(CALIBRANDO) EM TODAS AS TAGS. FAREMOS A MESMA COISA PARA PARA AS DEMAIS CORES. APOS ISSO, SALVAMOS NO XML.
		 *FILTRO DE RGB AO INVÉS DE HSV (USAR MESMA IDEIA DE SATURAÇÃO QUE FOI USADA COM O HSV)
		 *Classe derivada de camera para fazer a calibracao das cores a partir dos arquivos XML/YAML
		 **/

};

#endif /* CAMERA_H */
