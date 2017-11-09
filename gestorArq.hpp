#include "propositoGeralCamera.hpp"
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>


class GestorArq {
	private:
		/* PARAMETROS RELACIONADOS COM A LEITURA DO ARQUIVO DE CONFIGURACAO */
		cv::FileStorage arq; /** objeto que usado para acessarmos o arquivo .yml do disco. */
		std::map<int, std::string> identificacaoCores; /**< mapa que associa um numero inteiro a uma string (referencia: http://www.cplusplus.com/reference/map/map/) */

	protected:
		std::string nomeArqConfig = "configuracoes.yml"; /**< nome do arquivo de configuracao */

		/* PARAMETROS DE CALIBRAGEM VINDOS DO YML */
		std::vector<ParamHSV> paramHSVCores; /**< Parametros de HSV min max para cada cor possivel e outras configuracoes de filtragem. */
		cv::Rect retanguloCampo; /**< Retangulo que representa a area onde esta localizado o campo */
		int areaROIFrameAnterior; /**< Tamanaho da area a se procurar por uma cor com relacao ao frame anterior. Exemplo: Considerando que areaROIFrameAnterior = 50. No frame anterior a cor alaranjado foi encontrada no ponto x: 50 y:30, a busca pela cor alaranjado no frame atual sera numa area de 50 X 50 pixels envolta do ponto x:50, y:30. Entao a busca se iniciara em x:0 y:0 (y ficaria negativo (-20), entao eh saturado para zero.) e terminara em x:100, y:80.*/
		/* PARAMETROS DE PESISTENCIA DE BUSCA DE ELEMENTOS */
		/* OBS: O METODO ATUAL NAO PREVE MANEIRAS 'ELEGANTES' DE TRATAMENTO QUANDO MAIS DE UM ELEMENTO EH ENCONTRADO NA REGIAO DE INTERESSE, SE UMA COR SO POSSUI UMA CORRESPONDENCIA NO CAMPO POR EXMEPLO, SE FOREM ENCONTRADAS 2 NUMA ROI, FICAREMOS APENAS COM A REGIAO COM MAIOR AREA. */
		int numeroTentativasBuscaROI; /**< Numero de tentativas maximas em que sera feita a busca por elementos da cor especificada em uma determinada sessao da imagem (regiao menor que o campo inteiro definida pelo retanguloDeRecorte). Se colocado um numero muito grande, o programa demorara mais para encontrar os elementos e se colocado um numero muito pequeno pode ser que sejam perdidos elementos pois, a cada nova tentativa, a amplitude de cor eh aumentada conforme a proporcao definida abaixo. */
		int proporcaoAumentoAmplitudeROI; /**< Proporcao de aumento da amplitude de cor para a regiao definida pelo retanguloDeRecorte. Exemplo: para uma proporcao = 3, a cada nova tentativa de busca a amplitude de cor sera expandia em 3. Entao para uma cor com parametros iniciais de H_MIN: 59, H_MAX: 137, S_MIN: 173, S_MAX: 255, V_MIN: 147, V_MAX: 255, na segunda busca ficaria H_MIN: 59 - 3, H_MAX: 137 + 3, S_MIN: 173 - 3, S_MAX: 255 + 3, V_MIN: 147 - 3, V_MAX: 255 + 3, na terceira busca H_MIN: 59 - 6, H_MAX: 137 + 6, S_MIN: 173 - 6, S_MAX: 255 + 6, V_MIN: 147 - 6, V_MAX: 255 + 6 e na quarta busca H_MIN: 59 - 9, H_MAX: 137 + 9, S_MIN: 173 - 9, S_MAX: 255 + 9, V_MIN: 147 - 9, V_MAX: 255 + 9. */
		int numeroTentativasBuscaCampoTodo; /**< Mesma ideia do parametro numeroTentativasBuscaROI, mas agora para o campo todo. Aqui eh necessario ainda mais cuidado pois aumentos drasticos de amplitude poderao gerar muitos falsos positivos. */
		int proporcaoAumentoAmplitudeCampoTodo; /**< Mesma ideia do parametro proporcaoAumentoAmplitudeROI, mas com uma proporcao menor, ja que pode-se gerar muitos falsos positivos com aumentos drasticos de amplitude. */
		double TamanhoEmPixelsObjeto; /* Tamanaho do objeto, em pixels, para fazermos a conversao de pixels para centimetros. Exemplo: Um objeto deixado no campo para medirmos possui 60 pixels. Combinado com o valor de TamanhoEmCentimetrosObjeto de, por exemplo, 10cm, cada centimetro do "mundo real" corresponde a 6 pixels do mundo visto pela camera. Ou ainda, cada pixel da imagem seria 0,166666667 cm */
		double TamanhoEmCentimetrosObjeto; /* Tamanho do objeto mencionado acima, em centimetros. */
		int isLadoEsquerdo; /* 1 se estamos do lado esquerdo do campo, 0 caso estejamos do lado direito. DEVERIA SER UM BOOL, MAS TEMOS PROBLEMAS DE COMPATIBILIDADE COM A EXTRACAO NO YAML. ANALIZAR! */

	public:
		double proporcaoPixelCentimetro; /* Numero de centimetros que corresponde cada pixel. Para converter um valor de pixels para centimetros, basta multiplicar por este valor. */

		/** @fn GestoArq()
		 *  @brief Construtor da Classe GestorArq. Faz a configuracao do mapa que assossia um numero inteiro com a string que sera buscada no arquivo de configuracaoes
		 *
		 *  @warning Ao fazer alteracoes no arquivo de configuracoes e/ou na enumeracao Cores eh necessaria adcionar as novas cores a esta funcao, senao um erro sera gerado.
		 */
		GestorArq();

		/** @fn void setNomeArqConfig(const std::string nome)
		 *  @brief Define o nome do arquivo de configuracao a ser utilizado. Nao eh necessario chamar esta funcao caso o nome do arquivo de configuracao seja 'configuracoes.yml.'
		 *  @param nome Caminho ate o arquivo de configuracao(com final .yml)
		 */
		void setNomeArqConfig(const std::string nome);

		/** @fn void getConfigDoArquivo()
		 *  @brief Faz a leitura dos dados de cada cor do arquivo .yml e os armazena no vector paramHSVCores
		 */
		void getConfigCorDoArquivo();
};
