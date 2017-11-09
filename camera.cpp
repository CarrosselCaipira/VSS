#include "camera.hpp"

Camera::Camera(const std::string caminhoVideoGravado, const std::string caminhoArquivoConfiguracoes /* = "configuracoes.yml" */) {
	// abre o arquivo de video de onde chegaram os frames a serem analizados
	this->camera.open(caminhoVideoGravado);
	// altera o nome do arquivo de configuracao padrao.
	GestorArq::setNomeArqConfig(caminhoArquivoConfiguracoes);
	// faz a configuracao dos valores das cores vindas do arquivo de configuracao.
	GestorArq::getConfigCorDoArquivo();
	// inicializa (aloca) os vectors.
	Camera::inicializaVect();
	// faz a solicitacao para o primeiro frame.
	Camera::getNextFrame();

}

Camera::Camera(const int indexEntrada, const std::string caminhoArquivoConfiguracoes /* = "configuracoes.yml" */) {
	// abre a camera de onde chegaram os frames a serem analizados
	this->camera.open(indexEntrada);
	// altera o nome do arquivo de configuracao padrao.
	GestorArq::setNomeArqConfig(caminhoArquivoConfiguracoes);
	// faz a configuracao dos valores das cores vindas do arquivo de configuracao.
	GestorArq::getConfigCorDoArquivo();
	// inicializa (aloca) os vectors.
	Camera::inicializaVect();
	// faz a solicitacao para o primeiro frame.
	Camera::getNextFrame();
}

Camera::~Camera() {
	Camera::liberaCamera();
}

void Camera::inicializaVect() {
	// alocando as linhas da matriz de posicoes
	this->centroAtualRetangulos.resize(NUM_TOTAL_CORES);
	this->centroAntRetangulos.resize(NUM_TOTAL_CORES);
}

void Camera::retanguloEntornoPonto(const posXY p, const int area) {
	this->retanguloDeRecorte.width = area; // largura (trocar por valores do arquivo de configuracao)
	this->retanguloDeRecorte.height = area; // altura (trocar por valores do arquivo de configuracao)
	this->retanguloDeRecorte.x = p.x - (this->retanguloDeRecorte.width / 2);
	this->retanguloDeRecorte.y = p.y - (this->retanguloDeRecorte.height / 2);
}

void Camera::filtragemHSVParamYMLTotal(const Cores cor, int aumentoAmplitudeCor /* = 0 */) {
	// definindo os novos valores de cor e impedindo que, se alterados pelo segundo parametro, os parametros ainda respeitem os limites de cor
	// nos minimos diminuise os valores
	int H_MIN = ((GestorArq::paramHSVCores[cor].H_MIN - aumentoAmplitudeCor) < 0) ? 0 : (GestorArq::paramHSVCores[cor].H_MIN - aumentoAmplitudeCor);
	int S_MIN = ((GestorArq::paramHSVCores[cor].S_MIN - aumentoAmplitudeCor) < 0) ? 0 : (GestorArq::paramHSVCores[cor].S_MIN - aumentoAmplitudeCor);
	int V_MIN = ((GestorArq::paramHSVCores[cor].V_MIN - aumentoAmplitudeCor) < 0) ? 0 : (GestorArq::paramHSVCores[cor].V_MIN - aumentoAmplitudeCor);

	// nos maximo aumentase os valores
	int H_MAX = ((GestorArq::paramHSVCores[cor].H_MAX + aumentoAmplitudeCor) > 255) ? 255 : (GestorArq::paramHSVCores[cor].H_MAX + aumentoAmplitudeCor);
	int S_MAX = ((GestorArq::paramHSVCores[cor].S_MAX + aumentoAmplitudeCor) > 255) ? 255 : (GestorArq::paramHSVCores[cor].S_MAX + aumentoAmplitudeCor);
	int V_MAX = ((GestorArq::paramHSVCores[cor].V_MAX + aumentoAmplitudeCor) > 255) ? 255 : (GestorArq::paramHSVCores[cor].V_MAX + aumentoAmplitudeCor);

	// binarizando a imagem a partir dos parametros de cor vindos do arquivo de configuracao
	cv::inRange(this->hsvFrameOrignal, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), this->imgBinarizada);


}

void Camera::filtragemHSVParamYMLParcial(const Cores cor, int aumentoAmplitudeCor /* = 0 */) {

	// testando os limites da regiao de recorte.
	// PARA AS COLUNAS
	// Se estiver iniciando para coordenadas alem dos limites da imagem, inicia a ROI no limite da imagem (borda de cima)
	if((this->retanguloDeRecorte.x + this->retanguloDeRecorte.width) > this->hsvFrameOrignal.cols){
		this->retanguloDeRecorte.x = this->hsvFrameOrignal.cols - this->retanguloDeRecorte.width;
	}
	else{
		// Se estiver menor que as paredes da imagem (inicia em coordenada negativa), satura para 0 (borda de baixo)
		if(this->retanguloDeRecorte.x < 0) {
			this->retanguloDeRecorte.x = 0;
		}
	}

	// PARA AS LINHAS
	// Se estiver iniciando para coordenadas alem dos limites da imagem, inicia a ROI no limite da imagem (borda de cima)
	if((this->retanguloDeRecorte.y + this->retanguloDeRecorte.height) > this->hsvFrameOrignal.rows){
		this->retanguloDeRecorte.y = this->hsvFrameOrignal.rows - this->retanguloDeRecorte.height;
	}
	else{
		// Se estiver menor que as paredes da imagem (inicia em coordenada negativa), satura para 0 (borda de baixo)
		if(this->retanguloDeRecorte.y < 0) {
			this->retanguloDeRecorte.y = 0;
		}
	}

	// definindo os novos valores de cor e impedindo que, se alterados pelo segundo parametro, os parametros ainda respeitem os limites de cor
	// nos minimos diminuise os valores
	int H_MIN = ((GestorArq::paramHSVCores[cor].H_MIN - aumentoAmplitudeCor) < 0) ? 0 : (GestorArq::paramHSVCores[cor].H_MIN - aumentoAmplitudeCor);
	int S_MIN = ((GestorArq::paramHSVCores[cor].S_MIN - aumentoAmplitudeCor) < 0) ? 0 : (GestorArq::paramHSVCores[cor].S_MIN - aumentoAmplitudeCor);
	int V_MIN = ((GestorArq::paramHSVCores[cor].V_MIN - aumentoAmplitudeCor) < 0) ? 0 : (GestorArq::paramHSVCores[cor].V_MIN - aumentoAmplitudeCor);

	// nos maximo aumentase os valores
	int H_MAX = ((GestorArq::paramHSVCores[cor].H_MAX + aumentoAmplitudeCor) > 255) ? 255 : (GestorArq::paramHSVCores[cor].H_MAX + aumentoAmplitudeCor);
	int S_MAX = ((GestorArq::paramHSVCores[cor].S_MAX + aumentoAmplitudeCor) > 255) ? 255 : (GestorArq::paramHSVCores[cor].S_MAX + aumentoAmplitudeCor);
	int V_MAX = ((GestorArq::paramHSVCores[cor].V_MAX + aumentoAmplitudeCor) > 255) ? 255 : (GestorArq::paramHSVCores[cor].V_MAX + aumentoAmplitudeCor);


	/* BEGIN DEBUG */
	// cv::rectangle(this->frameOriginal, this->retanguloDeRecorte, cv::Scalar(255), 1, 8, 0);
	// cv::imshow("Retangulo na original", this->frameOriginal);
	// cv::waitKey(0);


	/* END DEBUG */

	// fazendo o recorte da regiao de interesse (ROI: Region of interest)
	cv::Mat ROI = this->hsvFrameOrignal(this->retanguloDeRecorte);

	// binarizando a imagem a partir dos parametros de cor vindos do arquivo de configuracao
	cv::inRange(ROI, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), this->imgBinarizada);
}

// retorna o frame recortado do campo
cv::Mat Camera::getFrameOriginalRecortado() {
	// fazendo uma copia profunda do frame recortado
	cv::Mat Frame = this->frameOriginalRecortado.clone();

	return Frame;
}

// retorna o frame recortado do campo para colocar os pontos retornados das funcoes de localizacao de cores
cv::Mat Camera::getFrameOriginalRecortadoFlip() {
	// fazendo uma copia profunda do frame recortado
	cv::Mat Frame = this->frameOriginalRecortado.clone();
	// girando o Frame no eixo x (o que esta embaixo fica em cima e vice versa)
	cv::flip(Frame, Frame, 0);

	return Frame;
}

int Camera::getNextFrame(bool liberaAoFimDeAquivo /* = true */) {
	// faz a leitura de um frame do arquivo ou da camera e armazena em frameOriginal
	this->camera.read(this->frameOriginal);
	// faz o teste para checar se o frame vindo da fonte esta vazio (geralmente usado para checar se um arquivo de video chegou ao fim)
	if(this->frameOriginal.empty()) {
		// libera a camera
		if(liberaAoFimDeAquivo)
			this->camera.release();
		return -1;
	}

	// fazendo o recorte da imagem original para ficarmos apenas com o campo
	this->frameOriginalRecortado = this->frameOriginal(GestorArq::retanguloCampo);

	// se estamos do lado esquerdo, nao faz nada com a imagem. MAs caso estejamos do lado direito (isLadoEsquerdo == 0) invertemos a imagem
	if(GestorArq::isLadoEsquerdo == 0) {
		// invertendo a imagem no eixo y (o que esta na direita vai para a esquerda e vice-versa)
		cv::flip(this->frameOriginalRecortado, this->frameOriginalRecortado, 1);
	}

	// IDEIA: FUTURAMENTE, TROCAR O TIPO lab PARA O TIPO HSV PARA POUPARMOS UMA CONVERSAO
	cv::Mat lab_image;
  cv::cvtColor(this->frameOriginalRecortado, lab_image, CV_BGR2Lab);
   // Extraindo o canal L
  std::vector<cv::Mat> lab_planes(3);
  cv::split(lab_image, lab_planes);  // lab_planes[0] contem o canal L

  // aplicando o algorimo do CLAHE no canal L
  cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
  clahe->setClipLimit(4);
  cv::Mat dst;
  clahe->apply(lab_planes[0], dst);

	// Fundindo o canal L equalizado devolta a imagem lab
  dst.copyTo(lab_planes[0]);
  cv::merge(lab_planes, lab_image);

	// convertendo para BGR
	cv::Mat image_clahe;
	cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

	// Aplicando um blur para reducao de ruido
	cv::GaussianBlur(image_clahe, image_clahe, cv::Size(3, 3), 2, 2 );

	/* BEGIN DEBUG */
	// display the results  (you might also want to see lab_planes[0] before and after).
	// cv::imshow("image original", this->frameOriginal);
	// cv::imshow("image CLAHE RGB", image_clahe);
	// cv::waitKey();
	/* END DEBUG */

	// reseta o bitset indicando que nenhuma cor foi processada ainda
	this->corProcessada.reset();
	// faz a conversao do novo frame para HSV
	// cv::cvtColor(this->frameOriginal, this->hsvFrameOrignal, cv::COLOR_BGR2HSV);
	cv::cvtColor(image_clahe, this->hsvFrameOrignal, cv::COLOR_BGR2HSV);
	// para cada cor
	for(int i = 0; i < NUM_TOTAL_CORES; i++) {

		// std::cout << "@getNextFrame Temos da cor atual do frame anterior " << i << " " << this->centroAtualRetangulos[i].size() << " elementos" << '\n';
		// salvando as posicoes de cada objeto de cada cor do frame anterior
		this->centroAntRetangulos[i] = this->centroAtualRetangulos[i];
		// std::cout << "@getNextFrame Temos da cor anterior ao frame atual " << i << " " << this->centroAtualRetangulos[i].size() << " elementos" << '\n';
		// limpando o vetor de centros para a atualizacao
		this->centroAtualRetangulos[i].clear();
	}


	return 0;
}

void Camera::liberaCamera() {
	this->camera.release();
}

void Camera::setNumObjetosCor(const int numCor1, const int numCor2 /* = 0 */) {
	this->numObjetosCor1 = numCor1;
	this->numObjetosCor2 = numCor2;
}

void Camera::setCorObjeto(const Cores c1, const Cores c2 /* = INDEFINIDA */) {
	this->cor1 = c1;
	this->cor2 = c2;
}

// faz as operacoes de erosao e dilatacao das duas imagens binarizadas
void Camera::alteraMorfologia(const Cores cor) {
	// ALTERACOES MORFOLOGICAS DA COR PRIMARIA (COR1)
	// criando um elemento retangular de erosao
	cv::Mat elementoDeErosao = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(GestorArq::paramHSVCores[cor].LarguraRetanguloErode, GestorArq::paramHSVCores[cor].AlturaRetanguloErode));

	// criando um elemento retangular de dilatacao
	cv::Mat elementoDeDilatacao = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(GestorArq::paramHSVCores[cor].LarguraRetanguloDilatate, GestorArq::paramHSVCores[cor].AlturaRetanguloDilatate));

	// fazendo o numero de erosoes indicadas no arquivo de configuracao da cor
	for(int i = 0; i < GestorArq::paramHSVCores[cor].VezesErode; i++)
		cv::erode(this->imgBinarizada, this->imgBinarizada, elementoDeErosao);

	// fazendo o numero de dilatacoes indicadas no arquivo de configuracao da cor
	for(int i = 0; i < GestorArq::paramHSVCores[cor].VezesErode; i++)
		cv::dilate(this->imgBinarizada, this->imgBinarizada, elementoDeDilatacao);
}

int Camera::detectaRetangulos(const Cores cor) {
	// vetor que armazenara os contornos encontrados na imagem
	std::vector<std::vector<cv::Point>> contornos;
	// quantos retangulos foram encontrados ate agora no total
	int retangulosDetectadosTotal = this->centroAtualRetangulos[cor].size();

	// aplicando o filtro de destaque de bodas na imagem binarizada
	cv::Canny(this->imgBinarizada, this->imgBinarizada, this->limiteInferior, this->limiteInferior * this->proporcaoLimiarInferiorSuperior, this->tamanhoKernelSobel);

	// Modo CV_RETR_EXTERNAL: apenas precisamos dos contornos mais externos dos objetos filtrados pois nao existem outras cores dentro das tags e, se por ventura o filtro falhar e indicar cores diferentes na parte interna, nos apenas a ignoramos e ficamos com a parte externa. Com isso tambem indicamos que nao existe hierarquia nas cores
	cv::findContours(this->imgBinarizada, contornos, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS);

	// se nao existem contornos, nao ha o que fazer, entao retorna
	if (contornos.size() == 0) {
		return 0;
	}

	// Analisando os contornos detectados
	for (int i = 0; i < contornos.size(); i++) {
		// usando o metodo dos momentos para deteccao de objetos
		cv::Moments momento = moments((cv::Mat)contornos[i]);
		Retangulo r;
		r.tamanhoArea = momento.m00;
		// substituir futuramente o tamanho maximo e minimo por valores vindos de YAML
		// se o numero de cores bater apenas adicione ao vector os contornos encontrados. Se forem diferentes os valores, verifica se o contorno respeita ao intervalo de tamanho da cor
		if(r.tamanhoArea <= GestorArq::paramHSVCores[cor].AreaMaxima && r.tamanhoArea >= GestorArq::paramHSVCores[cor].AreaMinima) {
			r.posicao.x = momento.m10 / r.tamanhoArea;
			r.posicao.y = momento.m01 / r.tamanhoArea;
			this->centroAtualRetangulos[cor].push_back(r);
		}
	}

	// retorna o numero de elementos encontrados nesta tentativa. (Total de encontrados agora) - (Total de encontrados antes)
	return (this->centroAtualRetangulos[cor].size() - retangulosDetectadosTotal);
}
/*
processaCor2
	procura_envolta_posXY_mesma_cor_frame_anterior (return 0)
	procura_campo_todo (return 0)
	procura_envolta_posXY_outra_cor_frame_atual (return -1) >> depois
processaCor1
	procura_envolta_posXY_mesma_cor_frame_anterior
	procura_envolta_posXY_outra_cor_frame_atual
	procura_campo_todo
*/

// procura a corBuscada em locais proximos a corBase no frame atual
// assumimos que a corBase eh uma cor com poucas correspondencias, por exemplo, uma cor de tag. Em geral so ha uma correspondencia para a corBase.
// bool Camera::procuraEnvoltaPosOutraCorFrameAtual(const Cores corBuscada, const Cores corBase) {
// 	bool encontrado = false;
// 	// alocando a quantidade necessaria de flags de encontrado e setando todas como false
// 	std::vector<bool> tempEncontrados(this->centroAtualRetangulos[corBase].size(), false); /**< Cada posicao i deste vector representa se uma regiao i da cor base ja foi processada e foi encontrado UM elemento da corBuscada no local. */
// 	std::vector<int> direcaoAlteracaoAmplitude(this->centroAtualRetangulos[corBase].size(), 1); /**< Cada posicao i deste vector representa uma regiao i da cor base. Se existem mais objetos que o desejado na regiao i, a posicao i deste vector sera setada para -1, se existem menos objetos que o desejado na regiao i, a posicao i do vector setada para 1. */
//
// 	// se a corBase estiver definida e existe registro desta no frame atual
// 	if((corBase != INDEFINIDA) && (this->centroAtualRetangulos[corBase].size() > 0)) {
//
// 		// Para cada tentativa, procura em todos as possiveis regioes. Se nao encontrar em nenhuma das regioes o elemento procurado, vai para a proxima tentativa com um aumento de amplitude definido em camera.hpp. Faz isso ate encontrar uma regiao que contem o elemento ou ate acabarem as tentativas.
// 		for(int k = 0; k <= this->numeroTentativasBuscaROI && !encontrado; k++) {
//
// 				// para cada retangulo da corBase do frame atual (em geral a cor2 ira aparecer apenas uma vez, mas serao varidas apena para futuras expancoes e futuros testes mais 'robustos' contra erros). Neste caso, se existir mais de um retangulo da cor2, ficaremos com o de maior area, ja que o fato de um retangulo ser ou nao encontrado afeta apenas o loop acima, nao o que percorre pelos retangulos. Alteracoes futuras podem achar interessante parar este loop assim que um objeto for encontrado também...
// 				for(int i = 0; i < this->centroAtualRetangulos[corBase].size(); i++) {
// 					// se este objeto ja foi detectado nesta regiao, ignora e vai para a proxima iteracao. Util para nao reprocessar se ja foi encontrado antes de um aumento de amplitude de cor.
// 					if(tempEncontrados[i] == true)
// 						continue;
// 					// definindo a regiao de procura como sendo em torno do objeto i (ja detectado) numa area de 50 X 50 pixels
// 					Camera::retanguloEntornoPonto(this->centroAtualRetangulos[corBase][i].posicao, 50);
// 					// fazendo a filtragem na regiao definida pelo retangulo acima variando a amplitude da cor.
// 					Camera::filtragemHSVParamYMLParcial(corBuscada, k * this->proporcaoAumentoAmplitudeROI * direcaoAlteracaoAmplitude[i]);
// 					// faz a erosao e dilatacao da regiao
// 					Camera::alteraMorfologia(corBuscada);
// 					// faz a deteccao dos retangulos da cor do parametro na regiao
// 					int numDetectados = Camera::detectaRetangulos(corBuscada);
// 					// checa se encontrou UM objeto da cor do parametro na regiao para a busca.
// 					if(numDetectados == 1) {
// 						// informando que ja foi encontrado o elemento da cor do parametro no local esperado.
// 						tempEncontrados[i] = true;
// 						// como so encontrou um elemento, so ele foi adicionado o vector de encontrados entao so ele precisa ter sua posicao corrigida
// 						Camera::corrigeCoodernadas(this->centroAtualRetangulos[corBuscada].back().posicao);
// 					}
// 					else {
// 						// checa se existem mais objetos encontrados do que devem ser procurados
// 						if(numDetectados > 1) {
// 							// como foram encontrados (e adicionados ao vetor de encontrados) mais de um elemento, percorre todos os encontrados (numero de encontrados = numDetectados) nessa regiao (iteracao) e corrige suas posicoes
// 							for(int j = (this->centroAtualRetangulos[corBuscada].size() - 1); j => (this->centroAtualRetangulos[corBuscada].size() - numDetectados); j++) {
// 								// retornando para a posicao relativa ao campo todo (antes estava com relacao a ROI)
// 								Camera::corrigeCoodernadas(this->centroAtualRetangulos[corBuscada][j].posicao);
// 							}
// 							direcaoAlteracaoAmplitude[i] = -1; // se eh maior que o numero esperado, diminue a amplitude do filtro (diminue a chance de encontrarmos falsos positivos na regiao)
// 						}
// 						else /* numDetectados < 1 (== 0) */
// 							direcaoAlteracaoAmplitude[i] = 1; // se eh menor que o esperado, aumenta a amplitude do filtro (aumenta a chance de encontrarmos algo na regiao)
// 					}
//
// 				}
//
// 				// Depois de passar por todas as regioes possiveis onde possa estar localisada a corBase...
// 				// se encontrou algum objeto da corBuscada na regiao envolta da corBase
// 				if(this->centroAtualRetangulos[corBuscada].size() >=  1) {
// 					// informando que ja foi encontrado o elemento da cor passada como parametro
// 					encontrado = true;
// 					// impede centros repetidos e, caso ainda existam mais centros que o maximo, fica com os que possuem maior area. Se o texte abaixo de quantidade de encontrados receber duplicatas suficientes para completar o numero de cores, estaremos com problemas, pois seria registrado que nao precisamos mais procurar a bor buscada porque esta ja foi processada
// 					Camera::controlaOcorrenciasDuplicadas(cor);
// 					if(this->centroAtualRetangulos[corBuscada].size() >= GestorArq::paramHSVCores[corBuscada].NumObjetosCor)
// 						// informando que a cor passada como parametro foi processada com sucesso
// 						this->corProcessada.set(corBuscada);
// 				}
// 		}
// 	}
//
// 	return encontrado;
// }

/* IDEIA: PODEMOS REMOVER A REGIAO ONDE OS ELEMENTOS FORAM ENCONTRADOS DA IMAGEM DEIXANDO A REGIAO EM PRETO PARA EVITAR DUPLICATAS */
// o que estamos tentando procurar nas regioes envolta das posicoes anteriores eh apenas uma correspondencia.
// se em todas as areas que deveriam ter objetos foram os objetos da cor procurada, a cor eh considerada processada e a funcao retorna true, do contrario, retorna false
bool Camera::procuraEnvoltaPosFrameAnterior(const Cores cor) {
	bool falseEncontrado; /**< indica se foram re-encontrados todos os objetos que foram encontrados no frame anterior. Ex.: Existiam 3 objetos no frame anterior, se, envolta das posicoes anteriores desses 3 objetos forem encontrados mais 3 objetos, o vector encontradosRegiao em todas suas posicoes sera true. */
	bool encontrado = false; /**< indica se foram encontrados TODOS os objetos da cor. */
	bool encontradoTodosPossiveis = false; /**< indica se foram encontrados todos os objetos da cor considerando todas as areas possiveis que temos. Ex.: encontradoTodosPossiveis eh true quando temos 5 objetos no total, mas no frame anterior so temos 3 encontrados e os 3 anteriores foram encontrados fazendo a busca local */
	std::vector<bool> encontradosRegiao(this->centroAntRetangulos[cor].size(), false); /**< Cada posicao i deste vector representa se uma regiao i da cor base ja foi processada e foi encontrado UM elemento da corBuscada no local. */

	/* BEGIN DEBUG
	std::cout << '\n' << "INICIO PROCURANDO ENVOLTA DA POSICAO DO FRAME ANTERIOR" << '\n';
	END DEBUG */

	/* BEGIN DEBUG
	std::cout << "@procuraEnvoltaPosFrameAnterior this->centroAntRetangulos[cor].size() " << this->centroAntRetangulos[cor].size() << '\n';
	//getchar();
	END DEBUG */

	// existe registro anterior da cor2 no frame anterior
	if(this->centroAntRetangulos[cor].size() > 0) {
		// Para cada tentativa, procura em todos as possiveis regioes. Se nao encontrar em nenhuma das regioes o elemento procurado, vai para a proxima tentativa com um aumento de amplitude definido em camera.hpp. Faz isso ate encontrar uma regiao que contem o elemento ou ate acabarem as tentativas.
		for(int k = 0; k <= GestorArq::numeroTentativasBuscaROI && !encontradoTodosPossiveis; k++) {

			/* BEGIN DEBUG
			std::cout << "@procuraEnvoltaPosFrameAnterior Temos: " << this->centroAntRetangulos[cor].size() << " locais para procurar correspondencias"<< '\n';
			END DEBUG */

			// para cada retangulo da cor procurada no frame anterior (em geral cores secundarias irao aparecer apenas uma vez, mas serao varidas apena para futuras expancoes e futuros testes mais 'robustos' contra erros). Neste caso, se existir mais de um retangulo da cor2, ficaremos com o de maior area, ja que o fato de um retangulo ser ou nao encontrado afeta apenas o loop acima, nao o que percorre pelos retangulos. Alteracoes futuras podem achar interessante parar este loop assim que um objeto for encontrado também...
			for(int i = 0; i < this->centroAntRetangulos[cor].size(); i++) {
				// se este objeto ja foi detectado, ignora e vai para a proxima iteracao. Util para nao reprocessar se ja foi encontrado antes de um aumento de amplitude de cor.
				if(encontradosRegiao[i] == true)
					continue;
				// definindo a regiao de procura como sendo em torno do objeto i (ja detectado) numa area de 80 X 80 pixels
				Camera::retanguloEntornoPonto(this->centroAntRetangulos[cor][i].posicao, GestorArq::areaROIFrameAnterior);
				// fazendo a filtragem na regiao definida pelo retangulo acima variando a amplitude da cor.
				Camera::filtragemHSVParamYMLParcial(cor, k * GestorArq::proporcaoAumentoAmplitudeROI);
				// faz a erosao e dilatacao da regiao
				Camera::alteraMorfologia(cor);
				// faz a deteccao dos retangulos da cor do parametro na regiao
				int numDetectados = Camera::detectaRetangulos(cor);

				/* BEGIN DEBUG
				cv::imshow("Binarizada ROI cor agora", this->imgBinarizada);
				// cv::waitKey(0);

				std::cout << "@procuraEnvoltaPosFrameAnterior O inicio da regiao de recorte na iteracao " << i << " eh: x = " << this->centroAntRetangulos[cor][i].posicao.x << " y = " << this->centroAntRetangulos[cor][i].posicao.y << '\n';
				std::cout << "@procuraEnvoltaPosFrameAnterior Valor de numDetectados: " << numDetectados << std::endl;
				std::cout << "@procuraEnvoltaPosFrameAnterior Tetativa de busca no local: " << k << '\n';
				//getchar();
				// if(k > 0)
					// getchar();
				 END DEBUG */

				// checa se encontrou UM objeto da cor do parametro na regiao para a busca.
				// checa se existem mais objetos encontrados do que devem ser procurados
				if(numDetectados >= 1) {
					encontradosRegiao[i] = true;

					/* BEGIN DEBUG
					std::cout << "@procuraEnvoltaPosFrameAnterior Numero de objetos ja encontrado da cor atual: " << this->centroAtualRetangulos[cor].size() << '\n';
					END DEBUG */

					//std::max((int)(this->centroAtualRetangulos[cor].size() - numDetectados), 0)

					// como foram encontrados (e adicionados ao vetor de encontrados) mais de um elemento, percorre todos os encontrados nessa regiao e corrige suas posicoes
					for(int j = (this->centroAtualRetangulos[cor].size() - 1); j >= ((int)this->centroAtualRetangulos[cor].size() - numDetectados); j--) {
						// retornando para a posicao relativa ao campo todo (antes estava com relacao a ROI)
						Camera::corrigeCoodernadas(this->centroAtualRetangulos[cor][j].posicao);
					}
				}
			}

			/* BEGIN DEBUG
			std::cout << "@procuraEnvoltaPosFrameAnterior VECTOR DE ENCONTRADOS NA REGIAO:" << '\n';
			for(int q = 0; q < encontradosRegiao.size(); q++)
				std::cout << "@procuraEnvoltaPosFrameAnterior encontradosRegiao[" << q << "]: " << encontradosRegiao[q] << '\n';
			END DEBUG */

			// verificando se todos os objetos da cor foram encontrados. Se um false for encontrado significa que ainda nao foram encontrados todos os elementos. Se nao for encontrado nenhum false, significa que todos os elementos foram encontrados
			falseEncontrado = false;
			for(int l = 0; l < encontradosRegiao.size(); l++) {
				if(encontradosRegiao[l] == false)
					falseEncontrado = true;
			}

			/* BEGIN DEBUG
			std::cout << "@procuraEnvoltaPosFrameAnterior falseEncontrado (funcao HOME MADE): " << falseEncontrado << '\n';
			 END DEBUG */

			// se foram encontrados todos os objetos, entao informa que a cor foi processada como um todo. Se nao encontrou falsos, a funcao fez seu trabalho
			if(falseEncontrado == false) {
				encontradoTodosPossiveis = true;

				/* BEGIN DEBUG
				std::cout << "@procuraEnvoltaPosFrameAnterior Todos os valores possiveis foram encontrados." << std::endl;
				 END DEBUG */

				// impede centros repetidos e, caso ainda existam mais centros que o maximo, fica com os que possuem maior area. Se o texte abaixo de quantidade de encontrados receber duplicatas suficientes para completar o numero de cores, estaremos com problemas, pois seria registrado que nao precisamos mais procurar a bor buscada porque esta ja foi processada
				Camera::controlaOcorrenciasDuplicadas(cor);
				// se sem as duplicatas encontrou todos ou mais objetos, assumios a cor como processada
				if(this->centroAtualRetangulos[cor].size() >=  GestorArq::paramHSVCores[cor].NumObjetosCor) {
					this->corProcessada.set(cor);
					encontrado = true;
				}
			}

		}

		/* BEGIN DEBUG */
		//std::cout << "@procuraEnvoltaPosFrameAnterior ANTES Indo eliminar por area. Existem: " << this->centroAtualRetangulos[cor].size() << " elementos agora." << '\n';
		/* END DEBUG */

		// considerando que a area quando se procura numa regiao fechada de um falso positivo eh menor que a da cor real, entao elimina por area os extras
		// Camera::eliminaExtrasPorArea(cor);

		/* BEGIN DEBUG */
		//std::cout << "@procuraEnvoltaPosFrameAnterior DEPOIS Eliminados por area. Agora existem: " << this->centroAtualRetangulos[cor].size() << " elementos." << '\n';
		/* END DEBUG */

	}

	return encontrado;
}

// removida alteracao de aplitude de cor, agora so procura aumentando a amplitude de cor. Se achar mais, remove com comparacao de area ou de extras duplicados
// se encontrados todos ou mais objetos, a cor eh considerada processada e a funcao retorna true, do contrario, retorna false
bool Camera::procuraCampoTodo(const Cores cor) {
	bool encontrado = false;

	/* BEGIN DEBUG
		std::cout << "@procuraCampoTodo NAO TEVE JEITO CARA, APELAMOS PRO CAMPO TODO." << '\n';
		std::cout << "numeroTentativasBuscaROI" << numeroTentativasBuscaROI << '\n';
		std::cout << "proporcaoAumentoAmplitudeROI" << proporcaoAumentoAmplitudeROI << '\n';
		std::cout << "numeroTentativasBuscaCampoTodo" << numeroTentativasBuscaCampoTodo << '\n';
		std::cout << "proporcaoAumentoAmplitudeCampoTodo" << proporcaoAumentoAmplitudeCampoTodo << '\n';
		getchar();
	END DEBUG */

	// Tentamos encontrar os objetos no campo como um todo utilizando o aumento de amplitude
	for(int k = 0; k <= GestorArq::numeroTentativasBuscaCampoTodo && !encontrado; k++) {
		// fazedo a filtragem (binarizacao) da cor2 (observa o campo todo)
		Camera::filtragemHSVParamYMLTotal(cor, k * GestorArq::proporcaoAumentoAmplitudeCampoTodo);
		// faz a erosao e dilatacao da regiao
		Camera::alteraMorfologia(cor);

		// faz a deteccao dos retangulos da cor passada como parametro no campo todo
		// checa se encontrou um objeto da cor passada como parametro na regiao para a busca
		int numDetectados = Camera::detectaRetangulos(cor);
		// se encontrou todos os objetos da cor, ai sim pode dizer que esta pronto
		/* SOB ANALISE NOTA: TALVEZ SEJA INTERESSANTE CHECAR QUANDO O NUMERO DE DETECTADOS FOR MAIOR OU IGUAL, POIS QUANDO FOR MAIOR, PEGAMOS MAIS ELEMENTOS QUE O NECESSARIO, MAS A FUNCAO DE controlaOcorrenciasDuplicadas NOS DEIXARA COM A OPCAO MAIS VIAVEL. CONTRA-ARGUMENTO: COM O DESLOCAMENTO DE CORES, PODE-SE AUMENTAR A AREA DA COR DESEJADA, O QUE PODE EVITAR QUE PEGUEMOS O OBJETO ERRADO */
		if(numDetectados >=  GestorArq::paramHSVCores[cor].NumObjetosCor) {
			// informando que a cor passada como parametro foi processada com sucesso
			this->corProcessada.set(cor);
			// informando que ja foi encontrado o elemento da cor passada como parametro
			encontrado = true;
			// impede centros repetidos e, caso ainda existam mais centros que o maximo, fica com os que possuem maior area
			Camera::controlaOcorrenciasDuplicadas(cor);
		}
	}

	return encontrado;
}

void Camera::controlaOcorrenciasDuplicadas(const Cores cor) {
	std::vector<bool> duplicata(this->centroAtualRetangulos[cor].size(), false); /**< vector booleano indicando se o retangulo da posicao i do vetor de retangulos encontrados eh duplicada ou nao (ele eh iniciado com false). A posicao que possuir um false eh considerada a original e sera colocada no vector resultante. Do contrario, sera ignorada e descartada. */

	// se nao existe objectos suficientes para dar conflito (dois ou mais) da cor procurada, logicamente, nao precisa remover duplicatas
	if(this->centroAtualRetangulos[cor].size() < 2) {
		return;
	}

	for(int i = 0; i < this->centroAtualRetangulos[cor].size() - 1; i++) {
		// para todos os retangulos depois, faz a comparacao. Se um retangulo ja foi marcado como duplicado (duplicado == true), ele eh pulado
		for(int j = i + 1; j < this->centroAtualRetangulos[cor].size() && !duplicata[i]; j++) {
			// se a distancia entre o centro do retangulo i for menor que a distancia Despresivel entre Centros (ver e definir em Camera.hpp), marca como duplicata (true na posicao i do vector de duplicatas). Se ja esta marcado como duplicata, nao faz nada.
			// calculando a distancia euclidiana entre o retangulo i e o retangulo j.
			if((this->centroAtualRetangulos[cor][i].posicao.getDistEucliana(this->centroAtualRetangulos[cor][j].posicao) < this->distanciaDespresivelCentros) && (!duplicata[j]))
				duplicata[j] = true; // indicando que a posicao i do vetor de retangulos, na verdade, eh uma duplicata.
		}
	}

	// verificando se existe um 'true' no vetor de indicacao de duplicatas. Se nao existir 'true' signifca que nao ha duplicatas, logo nao eh necessario fazer nada. Caso exista um true, copiaremos para um vetor temporario e limparemos o vetor de retangulos e salvaremos apenas as posicoes i que estiverem com 'false' no vector duplicada.
	if (*(std::find(duplicata.begin(), duplicata.end(), true))) {
		// salvando o vetor de retangulos em um vetor temporario
		std::vector<Retangulo> tempCentroRetangulos = this->centroAtualRetangulos[cor];
		// limpando o vetor de retangulos original
		this->centroAtualRetangulos[cor].clear();
		// para cada retangulo encontrado a principio...
		for(int i = 0; i < tempCentroRetangulos.size(); i++){
			// se nao eh duplicata, coloca no vetor 'limpo'
			if(!duplicata[i])
				this->centroAtualRetangulos[cor].push_back(tempCentroRetangulos[i]);
		}
	}

	// Camera::eliminaExtrasPorArea(cor);

}

// se o numero de objetos com tamanho entre o definido no arquivo de configuracao for maior que o numero de elementos da cor informado no arquivo de configuracao ordena por tamanho e fica com os de area maior
void Camera::eliminaExtrasPorArea(const Cores cor) {
	// IDEIA: TALVEZ REMOVER ESTE TESTE PARA A FUNCAO CHAMADORA

	// se ainda nao estiver com o tamanho adequado de elementos
	if(this->centroAtualRetangulos[cor].size() > GestorArq::paramHSVCores[cor].NumObjetosCor) {
		// IDEIA CENTRAL: ordenamos o vetor em ordem decrescente com relacao a area de cada retangulo e ficamos apenas com os retangulos maiores.
		// ordena os elementos do menor para o menor (ORDEM NORMAL)
		// FUTURO: TROCAR O COMPORTAMENTO DO OPERADOR < PARA QUE O VETOR SEJA ORDENADO EM ORDEM REVERSA.
		std::sort(this->centroAtualRetangulos[cor].begin(), this->centroAtualRetangulos[cor].end());
		// inverte a sequencia ordenada, fica, entao, do maior ao menor
		std::reverse(this->centroAtualRetangulos[cor].begin(), this->centroAtualRetangulos[cor].end());
		this->centroAtualRetangulos[cor].resize(GestorArq::paramHSVCores[cor].NumObjetosCor);
	}

}

bool Camera::processaCor2() {
	bool encontrado = false;

	/* BEGIN DEBUG
	std::cout << "@processaCor2 INICIO PROCESSAMENTO COR2" << '\n';
	END DEBUG */

	// procurando o elemento levando em conta sua posicao no frame anterior
	encontrado = Camera::procuraEnvoltaPosFrameAnterior(this->cor2);

	/* BEGIN DEBUG
	std::cout << "@processaCor2 encontrado depois de procuraEnvoltaPosFrameAnterior: " << encontrado << '\n';
	std::cout << "@processaCor2 Numero de objetos encontrados da cor2: " << this->centroAtualRetangulos[this->cor2].size() << ". Estes sao: " << '\n';
	for(int i = 0; i < centroAtualRetangulos[this->cor2].size(); i++)
		std::cout << "@processaCor2 centroAtualRetangulos[this->cor2][" << i << "]: " << this->centroAtualRetangulos[this->cor2][i].posicao.x << "e " << this->centroAtualRetangulos[this->cor2][i].posicao.y << '\n';
	//getchar();
	END DEBUG */

	// nao existe registro ou nao foi possivel encontrar o objeto na regiao entorno dos registros.
	if(encontrado == false) {
		encontrado = Camera::procuraCampoTodo(this->cor2);

		/* BEGIN DEBUG
		std::cout << "@processaCor2 encontrado depois de procuraCampoTodo: " << encontrado << '\n';
		std::cout << "@processaCor2 Numero de objetos encontrados da cor2: " << this->centroAtualRetangulos[this->cor2].size() << ". Estes sao: " << '\n';
		for(int i = 0; i < centroAtualRetangulos[this->cor2].size(); i++)
			std::cout << "@processaCor2 centroAtualRetangulos[this->cor2][" << i << "]: " << this->centroAtualRetangulos[this->cor2][i].posicao.x << "e " << this->centroAtualRetangulos[this->cor2][i].posicao.y << '\n';
		//getchar();
		END DEBUG */
	}

	/* BEGIN DEBUG
	std::cout << "@processaCor2 FIM PROCESSAMENTO COR2" << '\n';
	END DEBUG */

	return encontrado;
}


/* TODO: PERMITIR QUE OBJETOS DIFERENTES DA MESMA COR SEJAM ENCONTRADOS DE FORMAS DIFERENTES
 * AO ENTRAR EM CONFLITOS DE CANDIDATOS A CORES, TALVEZ SEJA INTERESSANTE ORDENAR POR PROXIMIDADE DO LOCAL ANTERIOR
 * Salvar as alteracoes feitas ao filtro em um hash duplo cor >> posicao = filtro
 * Salvar os pares de cores em uma matriz de combinacao
 */

bool Camera::processaCor1() {
	bool encontrado = false;

	/* BEGIN DEBUG
	std::cout << "@processaCor1 INICIO PROCESSAMENTO COR1" << '\n';
	END DEBUG */

	// procura em volta na regiao onde foi encontrada no frame anterior
	encontrado = Camera::procuraEnvoltaPosFrameAnterior(this->cor1);

	/* BEGIN DEBUG
	std::cout << "@processaCor1 encontrado depois de procuraEnvoltaPosFrameAnterior: " << encontrado << '\n';
	std::cout << "@processaCor1 Numero de objetos encontrados da cor2: " << this->centroAtualRetangulos[this->cor1].size() << ". Estes sao: " << '\n';
	for(int i = 0; i < centroAtualRetangulos[this->cor1].size(); i++)
		std::cout << "@processaCor1 centroAtualRetangulos[this->cor1][" << i << "]: " << this->centroAtualRetangulos[this->cor1][i].posicao.x << "e " << this->centroAtualRetangulos[this->cor1][i].posicao.y << '\n';
	//getchar();
	 END DEBUG */


	// se nao foi encontrada uma correspondencia da cor1 na regiao envolta do frame anterior, procura alguma correspondencia da cor1 proximo ao locais atuais da cor2
	// if(encontrado == false)
	// 	encontrado = Camera::procuraEnvoltaPosOutraCorFrameAtual(this->cor1, this->cor2);

	// se ainda nao foi encontrado, observa o campo como um todo
	if(encontrado == false)
		encontrado = Camera::procuraCampoTodo(this->cor1);

	/* BEGIN DEBUG
	std::cout << "@processaCor1 encontrado: " << encontrado << '\n';
	std::cout << "@processaCor1 Numero de objetos encontrados da cor1: " << this->centroAtualRetangulos[this->cor1].size() << ". Estes sao: " << '\n';
	for(int i = 0; i < centroAtualRetangulos[this->cor1].size(); i++)
		std::cout << "@processaCor1 centroAtualRetangulos[this->cor1][" << i << "]: " << this->centroAtualRetangulos[this->cor1][i].posicao.x << "e " << this->centroAtualRetangulos[this->cor1][i].posicao.y << '\n';
	//getchar();
	std::cout << "@processaCor1 FIM PROCESSAMENTO COR1" << '\n';
	END DEBUG */

	return encontrado;
}

// corrige as coordenas da cor encontrada na ROI para bater com as coordenas da imagem como um todo
void Camera::corrigeCoodernadas(posXY& p) {
	posXY temp = p;
	p.x = p.x + this->retanguloDeRecorte.x;
	p.y = p.y + this->retanguloDeRecorte.y;
}

// determina qual posicao (indice) do vetor v se encontra mais proxima do ponto p
// int getIndexMaisProximo(posXY p, std::vector<Retangulo>& v) {
// 		int indexCorPrimariaProxima = -1; /**< Indice no vetor de cores primarias do elemento mais proximo do elemento encontrado da cor2 */
// 		double minDist = std::numeric_limits<double>::max(); // definindo a distancia inicial como a maior possivel
//
// 		// para cada um dos objetos encontrados da cor1, iremos combina-lo com um objeto da cor2
// 		for(int i = 0; i < v.size(); i++) {
// 			// combina com o local da cor 2 encontrada e determina a distancia euclidiana entre elas
// 			double atualDist = v[i].posicao.getDistEucliana(p);
// 			// se a nova posicao eh mais proxima que a anterior, atualiza o possivel par
// 			if(atualDist < minDist) {
// 				// atualizando a menor distancia como sendo a atual
// 				minDist = atualDist;
// 				// salvando o indice atual (que eh o que possui menor distancia para o objeto da cor2)
// 				indexCorPrimariaProxima = i;
// 			}
// 		}
//
// 	return indexCorPrimariaProxima;
// }

/* indexVect1: indice do vect1 (marcador time geralmente). Existem mais dessas que de jogador teoricamente; */
/* indexVect2: indice do vect2 (marcador jogador geralmente); */
// determina qual eh a combinacao de cores mais proxima entre a cor2 e a cor1. Ex.: Estamos procurando cor1: Amarelo, cor2: Verde. Encontramos 3 Amarelos e 2 Verdes, essa funcao ira determinar quais elementos dos vetors de amarelos e de verdes estao mais proximos um do outro.
void Camera::getIndexMaisProximo(std::vector<Retangulo>& vect1, std::vector<Retangulo>& vect2, int& indexVect1, int& indexVect2) {
	indexVect1 = -1;
	indexVect2 = -1;
	double minDist = std::numeric_limits<double>::max(); // definindo a menor distancia inicial como a maior possivel para um double

	// para todos os objetos da cor2 (tag jogador)
	for(int i = 0; i < vect2.size(); i ++) {
		for(int j = 0; j < vect1.size(); j++) {
			// calculando a distancia de um centro da cor1 para um centro da cor2
			double atualDist = vect2[i].posicao.getDistEucliana(vect1[j].posicao);
			// se a nova posicao eh mais proxima que a anterior, atualiza o possivel par
			if(atualDist < minDist) {
				// atualizando a menor distancia como sendo a atual
				minDist = atualDist;
				// salvando o par de indices que possuem a menor distancia entre eles
				indexVect1 = j; // indice do vector da cor1
				indexVect2 = i; // indice do vector da cor2
			}
		}
	}

}

void Camera::converteCoordenadasParaOrigemNoInferiorEsquerdo(posXY& p) {
	p.y = this->frameOriginalRecortado.rows - p.y;
}

// NOTA: PARA PRINTAR OS ELEMENTOS ENCONTRADOS NO CAMPO EH NECESSARIO UTILIZAR A FUNCAO: cv::flip(FrameOrigem, FrameDestino, 0); que vai espelhar a imagem no eixo x (o que estava embaixo agora estara em cima e vice versa). O ponto retornado desta funcao devera ser colocado na imagem invertida FrameDestino
// retornos: -1 -> Nao foi definida cor primaria
// 						0 -> Tudo ocorreu como planejado
// 						1 -> Nao conseguiu encontrar os objetos de forma alguma
// 						2 -> Conseguiu encontrar o objeto mas apenas para a cor1
// 						3 -> Conseguiu encontrar o objeto mas apenas para a cor2
// 						4 -> Nao fez absolumente nada (nao entrou em if algum)
int Camera::getPosicaoAtualObjeto(posXY& posicaoObj, bool emCentimetros /* = true */) {
	bool resuCor1 = false;
	bool resuCor2 = false;

	// se existe cor secundaria
	if(this->cor2 != INDEFINIDA) {
		if(this->corProcessada.test(this->cor2) == false)
			resuCor2 = Camera::processaCor2();
	}

	if(this->cor1 != INDEFINIDA) {
		if(this->corProcessada.test(this->cor1) == false)
			resuCor1 = Camera::processaCor1();
	}
	else {
		std::cerr << std::endl << "ERRO: " << "@Camera->getPosicaoAtualObjeto: " << "COR INDEFINIDA PARA COR PRIMARIA. CERTIFIQUE-SE DE DEFINIR UMA COR PRIMARIA ANTES DE UTILIZAR A FUNCAO, ELA EH A PRINCIPAL COR DA BUSCA Camera::getPosicaoAtualObjeto." << std::endl;
		return -1;
	}

	// se a cor2 ja foi processada, encontra o par mais proximo, calcula o ponto medio entre a cor2 e a cor1 e faz um retorno sem erros.
	// NOTA: AQUI ASSUMINOS A IDEIA QUE EH PREFERIVEL RETORNAR A ULTIMA POSICAO DO OBJETO DO QUE UMA POSICAO ATUAL DUVIDOSA
	//
	// checando se deve existir objetos da cor2
	if(this->cor2 != INDEFINIDA) {
		// checando se foi processada corretamente a cor2
		if(resuCor2 == true) {
			/* BEGIN DEBUG
			std::cout << "@getPosicaoAtualObjeto Entrei pra calcular o ponto medio guys." << '\n';
			//getchar();
			 END DEBUG */

			/* BEGIN DEBUG
			std::cout << "@getPosicaoAtualObjeto centroAtualRetangulos[this->cor1].size(): " <<  centroAtualRetangulos[this->cor1].size() << '\n';
			if(indexCor1 >= 0)
				std::cout << "@getPosicaoAtualObjeto centroAtualRetangulos[this->cor1][indexCor1]: " << centroAtualRetangulos[this->cor1][indexCor1].posicao.x << "e " << centroAtualRetangulos[this->cor1][indexCor1].posicao.y << '\n';
			else
				std::cout << "@getPosicaoAtualObjeto Na verdade, nosso objeto teve problemas com cores e retornaremos apenas a posicao da dor 2." << '\n';
			std::cout << "@getPosicaoAtualObjeto centroAtualRetangulos[this->cor2].size(): " <<  centroAtualRetangulos[this->cor2].size() << '\n';
			std::cout << "@getPosicaoAtualObjeto centroAtualRetangulos[this->cor2][indexCor2]: " << centroAtualRetangulos[this->cor2][indexCor2].posicao.x << "e " << centroAtualRetangulos[this->cor2][indexCor2].posicao.y << '\n';
			//getchar();
			END DEBUG */

			// se a cor1 foi processada corretamente, retorna o ponto medio das cores mais proximas umas das outras
			if(resuCor1 == true) {
				int indexCor1;
				int indexCor2;
				Camera::getIndexMaisProximo(this->centroAtualRetangulos[this->cor1], this->centroAtualRetangulos[this->cor2], indexCor1, indexCor2);

				posicaoObj = this->centroAtualRetangulos[this->cor1][indexCor1].posicao.getPontoMedio(this->centroAtualRetangulos[this->cor2][indexCor2].posicao);

				// convertendo para centimetros o valor das posicoes
				if(emCentimetros)
					posicaoObj = posicaoObj * GestorArq::proporcaoPixelCentimetro;

				// colocando a origem no canto inferior esquerdo (estava originalmente no canto superior esquerdo)
				Camera::converteCoordenadasParaOrigemNoInferiorEsquerdo(posicaoObj);

				/* TODO: REMOVER AS CORES EXTRAS POR AREA DE FORMA A MANTER AS QUE FORAM USADAS ANTES DE FINALZAR O PROCESSAMENTO POIS DA FOMAR COMO ESTA, ESTAMOS SALVANDO AS POSICOES ANTERIORES DE TODAS AS ENCONTRADAS. IDEIA: AUMENTAR A AREA DOS RETANGULOS ESCOLHIDOS E USAR ELIMINACAO POR AREA. */
				return 0;
			}
			else { // se ocorreu uma falha ao processarmos a cor1 sabemos onde esta a cor2, entao o centro do objeto eh o centro da cor2
				// ficando com as areas maiores. Aqui estamos supondo que deve exister soh uma cor correspondente da cor2. Talvez no futuro implementaremos de uma forma diferente para escolhermos as posicoes da cor2
				Camera::eliminaExtrasPorArea(this->cor2);
				posicaoObj = this->centroAtualRetangulos[this->cor2][0].posicao;

				// convertendo para centimetros o valor das posicoes
				if(emCentimetros)
					posicaoObj = posicaoObj * GestorArq::proporcaoPixelCentimetro;

				Camera::converteCoordenadasParaOrigemNoInferiorEsquerdo(posicaoObj);

				std::cerr << std::endl << "AVISO: " << "@Camera->getPosicaoAtualObjeto: " << "NAO FOI POSSIVEL ENCONTRAR A POSICAO PARA A COR1, ESTAMOS RETORNANDO A POSICAO DA COR2 APENAS. TENTE AJUSTAR OS FILTROS OU AJUSTAR A AREA DE BUSCA ENVOLTA DO FRAME ANTERIOR." << std::endl;
				return 3;
			}
		}
		// cor2 nao processada corretamente, tenta retornar apenas a cor1 mais proxima da ultima posicao conhecida da cor2
		else {
			// checa se eh possivel utilizar a posicao atual da cor1 (se foi processaca corretamente)
			if(resuCor1 == true) {
				// se existe uma posicao antiga conhecida para a cor2, vamos procurar em todas as localizacoes conhecidas da cor1 e ver qual delas esta mais proxima da localizacao antiga da cor2 e retornamos apenas a localizacao do marcador de time.
				if(this->centroAntRetangulos[this->cor2].size() > 0) {
					int indexCor1;
					int indexCor2;
					Camera::getIndexMaisProximo(this->centroAtualRetangulos[this->cor1], this->centroAntRetangulos[this->cor2], indexCor1, indexCor2);

					posicaoObj = this->centroAtualRetangulos[this->cor1][indexCor1].posicao;

					// convertendo para centimetros o valor das posicoes
					if(emCentimetros)
						posicaoObj = posicaoObj * GestorArq::proporcaoPixelCentimetro;

					Camera::converteCoordenadasParaOrigemNoInferiorEsquerdo(posicaoObj);

					std::cerr << std::endl << "AVISO: " << "@Camera->getPosicaoAtualObjeto: " << "NAO FOI POSSIVEL ENCONTRAR A POSICAO PARA A COR2, ESTAMOS RETORNANDO A POSICAO DA COR1 MAIS PROXIMA DA ANTERIOR CONHECIDA PARA A COR2. TENTE AJUSTAR OS FILTROS OU AJUSTAR A AREA DE BUSCA ENVOLTA DO FRAME ANTERIOR." << std::endl;
					return 2;
				}
			}
			else {
				std::cerr << std::endl << "ERRO: " << "@Camera->getPosicaoAtualObjeto: " << "NAO FOI POSSIVEL ENCONTRAR A POSICAO O OBJETO DE FORMA ALGUMA. TENTE AJUSTAR OS FILTROS OU AJUSTAR A AREA DE BUSCA ENVOLTA DO FRAME ANTERIOR." << std::endl;
				return 1;
			}
		}
	}
	// so precisamos encontrar um objeto da cor1
	else {
		// testando se a cor primaria foi corretamente processada
		if(resuCor1 == true) {
			Camera::eliminaExtrasPorArea(this->cor1);
			posicaoObj = this->centroAtualRetangulos[this->cor1][0].posicao;

			// convertendo para centimetros o valor das posicoes
			if(emCentimetros)
				posicaoObj = posicaoObj * GestorArq::proporcaoPixelCentimetro;

			Camera::converteCoordenadasParaOrigemNoInferiorEsquerdo(posicaoObj);

			return 0;
		}
		else {
			std::cerr << std::endl << "ERRO: " << "@Camera->getPosicaoAtualObjeto: " << "NAO FOI POSSIVEL ENCONTRAR A POSICAO O OBJETO DE FORMA ALGUMA. TENTE AJUSTAR OS FILTROS OU AJUSTAR A AREA DE BUSCA ENVOLTA DO FRAME ANTERIOR." << std::endl;
			return 1;
		}
	}
	return 4;
}

int Camera::getPosicaoAtualObjeto(std::vector<posXY>& posicaoObj, bool emCentimetros /* = true */) {
	bool resuCor1 = false;

	if(this->cor1 != INDEFINIDA) {
		if(this->corProcessada.test(this->cor1) == false)
			resuCor1 = Camera::processaCor1();
	}
	else {
		std::cerr << std::endl << "ERRO: " << "@Camera->getPosicaoAtualObjeto: std::vector : " << "COR INDEFINIDA PARA COR PRIMARIA. CERTIFIQUE-SE DE DEFINIR UMA COR PRIMARIA ANTES DE UTILIZAR A FUNCAO, ELA EH A PRINCIPAL COR DA BUSCA Camera::getPosicaoAtualObjeto." << std::endl;
		return -1;
	}

	// se existe algum objeto encontrado da cor1, vamos acreditar que sao os robos adversarios. Normalmente esse numero eh maior ou igual ao numero correto de robos do time adversario (logo, resuCor1 = true), mas caso nao for (resu = false), repassamos as posicoes de tudo o que conseguimos descorbrir
	if(this->centroAtualRetangulos[this->cor1].size() > 0) {
		// eliminando as cores menores caso tenham extras
		Camera::eliminaExtrasPorArea(this->cor1);
		// realocando o vector de posicoes para ficar do tamanho certo
		posicaoObj.resize(this->centroAtualRetangulos[this->cor1].size());
		for(int i = 0; i < this->centroAtualRetangulos[this->cor1].size(); i++) {
			posicaoObj[i] = this->centroAtualRetangulos[this->cor1][i].posicao;

			// convertendo para centimetros o valor das posicoes
			if(emCentimetros)
				posicaoObj[i] = posicaoObj[i] * GestorArq::proporcaoPixelCentimetro;

			Camera::converteCoordenadasParaOrigemNoInferiorEsquerdo(posicaoObj[i]);
		}
	}
	else{
		std::cerr << std::endl << "ERRO: " << "@Camera->getPosicaoAtualObjeto std::vector : " << "NAO FOI POSSIVEL ENCONTRAR NENHUM OBJETO DA COR INFORMADA. CONSIDERE CORRIGUIR OS FILTROS." << std::endl;
		return 1;
	}

	return 0;
}
