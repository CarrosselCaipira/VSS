#include "gestorArq.hpp"

GestorArq::GestorArq() {
	// inicializando o vector de configuracao das cores
	this->paramHSVCores.resize(NUM_TOTAL_CORES);

	// Associando as chaves (indices (int)) com o conteudo a ser armazenado (strings)
	this->identificacaoCores[AMARELO] = "AMARELO";
	this->identificacaoCores[AZUL] = "AZUL";
	this->identificacaoCores[ALARANJADO] = "ALARANJADO";
	this->identificacaoCores[ROSA] = "ROSA";
	this->identificacaoCores[ROXO] = "ROXO";
	this->identificacaoCores[VERDE] = "VERDE";

	// informando que o numero de cores da enumeracao eh diferente do numero de cores do mapa
	if(this->identificacaoCores.size() != NUM_TOTAL_CORES) {
		std::cerr << "ERRO: " << "@GestorArq->GestorArq(): " << "Numero de cores configuradas no mapa [" << this->identificacaoCores.size() << "]" << " eh diferente do numero de cores da enumeracao \'Cores\' [" << NUM_TOTAL_CORES << "]." << std::endl;
		exit(1);
	}
}

void GestorArq::getConfigCorDoArquivo() {
	// abrindo o arquivo de configuracoes para leitura
	this->arq.open(this->nomeArqConfig, cv::FileStorage::READ);

	// testando se o arquivo foi realmente aberto
	if(this->arq.isOpened() == false) {
		std::cerr << "ERRO: " << "@Camera->getConfigDoArquivo_1: " << "Nao foi possivel abrir o arquivo " << this->nomeArqConfig << std::endl;
		exit(1);
	}

	cv::FileNode itensLista; // nodo usado para caminhar pelo arquivo e acessar os elementos da lista da secao 'cores' do arquivo de configuracao

	itensLista =  this->arq["AreaCampo"]; // posicionando o FileNode para pegar as configuracoes de AreaCampo
	this->retanguloCampo.x = (int)itensLista["X"];
	this->retanguloCampo.y = (int)itensLista["Y"];
	this->retanguloCampo.width = (int)itensLista["Largura"];
	this->retanguloCampo.height = (int)itensLista["Altura"];
	this->isLadoEsquerdo = (int)itensLista["isLadoEsquerdo"];

	itensLista =  this->arq["EscalaConversao"]; // posicionando o FileNode para pegar as configuracoes de EscalaConversao
	this->TamanhoEmPixelsObjeto = (int)itensLista["TamanhoEmPixelsObjeto"];
	this->TamanhoEmCentimetrosObjeto = (int)itensLista["TamanhoEmCentimetrosObjeto"];
	this->proporcaoPixelCentimetro = TamanhoEmCentimetrosObjeto / TamanhoEmPixelsObjeto;

	itensLista =  this->arq["BuscaROIFrameAnterior"]; // posicionando o FileNode para pegar as configuracoes referente a busca de objetos com relacao ao frame anterior que usa a area onde se encotrava o objeto
	this->areaROIFrameAnterior = (int)itensLista["Area"];
	this->numeroTentativasBuscaROI = (int)itensLista["numeroTentativasBuscaROI"];
	this->proporcaoAumentoAmplitudeROI = (int)itensLista["proporcaoAumentoAmplitudeROI"];

	itensLista =  this->arq["BuscaCampoTodo"]; // posicionando o FileNode para pegar as configuracoes do referente a busca de objetos com relacao ao campo todo
	this->numeroTentativasBuscaCampoTodo = (int)itensLista["numeroTentativasBuscaCampoTodo"];
	this->proporcaoAumentoAmplitudeCampoTodo = (int)itensLista["proporcaoAumentoAmplitudeCampoTodo"];

	itensLista = this->arq["Cores"]; // posicionando o FileNode para pegar as configuracoes de Cores. (Cores eh uma sequencia, entao o FileNode itensLista contem outros FileNode's)
	// verificando se o que retornou da busca por 'Cores' eh mesmo uma sequencia/lista
	if(itensLista.type() != cv::FileNode::SEQ) {
	  std::cerr << "ERRO: " << "@Camera->getConfigDoArquivo_2: " << "\'Cores\' nao eh uma sequencia. Verifique o arquivo .yml " << std::endl;
	  exit(1);
  }

	int i = 0;
	/* cores eh uma lista (ou sequencia). Cada nome de cor no arquivo .yml (ex.: AMARELO) eh um mapa e cada nome de elemento de configuracao (ex.:H_MIN) eh um dos elementos do mapa. (duvidas: https://www.youtube.com/watch?v=W3tQPk8DNbk e https://www.youtube.com/watch?v=U9_gfT0n_5Q&t=)
	 * fni : iterator do nodo do arquivo yml. Ele itera por mapas para acessarmos as sequencias dentro de cada mapa.
	 */
	 // para cada uma das cores presentes na lista (ou sequencia)...
	for(cv::FileNodeIterator fni = itensLista.begin(); fni != itensLista.end(); fni++) {

		cv::FileNode itensMapa = (*fni)[this->identificacaoCores[i]]; /**< nodo usado para acessar as 'variaveis' de configuracao H_MIN, S_MIN, etc. dentro de cada elemento da lista, por exemplo AMARELO. this->identificacaoCores[i] retorna a srting correspondente ao indice i. */
		this->paramHSVCores[i].H_MIN = (int)(itensMapa["H_MIN"]);
		this->paramHSVCores[i].H_MAX = (int)(itensMapa["H_MAX"]);
		this->paramHSVCores[i].S_MIN = (int)(itensMapa["S_MIN"]);
		this->paramHSVCores[i].S_MAX = (int)(itensMapa["S_MAX"]);
		this->paramHSVCores[i].V_MIN = (int)(itensMapa["V_MIN"]);
		this->paramHSVCores[i].V_MAX = (int)(itensMapa["V_MAX"]);
		this->paramHSVCores[i].AreaMinima = (int)(itensMapa["AreaMinima"]);
		this->paramHSVCores[i].AreaMaxima = (int)(itensMapa["AreaMaxima"]);
		this->paramHSVCores[i].NumObjetosCor = (int)(itensMapa["NumObjetosCor"]);
		this->paramHSVCores[i].VezesErode = (int)(itensMapa["VezesErode"]);
		this->paramHSVCores[i].LarguraRetanguloErode = (int)(itensMapa["LarguraRetanguloErode"]);
		this->paramHSVCores[i].AlturaRetanguloErode = (int)(itensMapa["AlturaRetanguloErode"]);
		this->paramHSVCores[i].VezesDilatate = (int)(itensMapa["VezesDilatate"]);
		this->paramHSVCores[i].LarguraRetanguloDilatate = (int)(itensMapa["LarguraRetanguloDilatate"]);
		this->paramHSVCores[i].AlturaRetanguloDilatate = (int)(itensMapa["AlturaRetanguloDilatate"]);
		i++;
	}

	// se a contagem de itens no mapa eh diferente da do tamanho de elementos do mapa...
	if(i != this->identificacaoCores.size()) {
		std::cerr << "ERRO: " << "@Camera->getConfigDoArquivo_2: " << "O numero de elementos encontrados no arquivo de configuracao [" << i << "]"<< this->nomeArqConfig  << " nao confere com as configuracoes do mapa \'identificacaoCores\' de gestorArq.hpp ["<< this->identificacaoCores.size() << "]." << std::endl;
		exit(1);
	}

	// liberando o arquivo de configuracao
	this->arq.release();
}

void GestorArq::setNomeArqConfig(const std::string nome) {
	this->nomeArqConfig = nome;
}
