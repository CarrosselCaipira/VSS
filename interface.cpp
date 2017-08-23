#include <gtk/gtk.h>
#include <vector>
#include <string>

#define NUM_MAX_ROBOS 9

using namespace std;

/*Vetor que Guarda as Variáveis que Identificam os Combo Box para Roteiros Individuais*/
int identRoteiro[NUM_MAX_ROBOS];
int comboBoxAtual=0;

/*Variáveis que Explicitam as Funções dos Robôs Baseando-se no Número de Robôs*/
vector<vector<string> > posicoesRobos;

vector<string> umRobo;
vector<string> doisRobos;
vector<string> tresRobos;
vector<string> quatroRobos;

/*Variáveis de Acesso aos Elementos de Principal*/
GtkWidget *layoutTabela;
GtkWidget *treeViewTabela;
GtkListStore *listStoreTabela;
bool gravando = false;

/*Variáveis de Acesso aos Elementos de Outros*/

/**
 * @brief      Função que Prepara Variáveis Globais Necessárias em Certas Partes do Programa
 */
void preparaGlobais () {

	umRobo.push_back("Jogador");

	doisRobos.push_back("Defensor");
	doisRobos.push_back("Atacante");

	tresRobos.push_back("Goleiro");
	tresRobos.push_back("Volante");
	tresRobos.push_back("Atacante");

	quatroRobos.push_back("Goleiro");
	quatroRobos.push_back("Meia Direita");
	quatroRobos.push_back("Meia Esquerda");
	quatroRobos.push_back("Atacante");

	posicoesRobos.push_back(umRobo);
	posicoesRobos.push_back(doisRobos);
	posicoesRobos.push_back(tresRobos);
	posicoesRobos.push_back(quatroRobos);

	for (int i=0;i <NUM_MAX_ROBOS; i++) {

		identRoteiro[i]=i;
	}
}

/*
 Enum Para Colunas da Tabela
 */
enum {
	COLUNA_STRING = 0,
	COLUNA_DOUBLE,
	NUM_COLUNAS
};

/**
 * @brief      Função que Joga uma String e um Valor na Tabela de Debug.
 *
 * @param[in]  descricao - String que Identifique o Valor Desejado na Tabela.
 * @param[in]  valor     - O Valor que Se Deseja Checar em Execução.
 */
void tabelaDebug(string descricao="", double valor=0) {

	GtkTreeIter treeIterTabela;

	gtk_list_store_append(listStoreTabela,&treeIterTabela);
	gtk_list_store_set(listStoreTabela,&treeIterTabela,COLUNA_STRING,descricao.c_str(),COLUNA_DOUBLE,valor,-1);

	gtk_widget_show_all(layoutTabela);
}

/**
 * @brief      Função Chamada Quando o CheckBox de Guardar em Arquivo é Ligado ou Desligado em Principal.
 *
 * @param      estado - Instância do CheckBox que Permite Saber se Foi Ativado ou Desativado.  
 */
void setaSalvamentoArquivo (GtkWidget *estado) {

	int index_ativo = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(estado));

	if (index_ativo==1) {

		g_print("Ligado");
	}

	else {

		g_print("Desligado");
	}
}

/**
 * @brief      Função Chamada Quando o Botão Voltar Frame é Apertado em Principal.
 */
void voltarFrame () {

	g_print(" Volta !");
}

/**
 * @brief      Função Chamada Quando o Botão Próximo Frame é Apertado em Principal.
 */
void proximoFrame () {

	g_print(" Próximo !");
}

/**
 * @brief      Função Chamada Quando o Botão de Gravação é Apertado em Principal.
 *
 * @param      apertado - Instância do Botão Apertado que Permite Trocar Seu Label.
 */
void iniciaParaGravacao (GtkWidget *apertado) {

	if (!gravando) {

		g_print(" Iniciando gravação ! ");
		gtk_button_set_label(GTK_BUTTON(apertado),"Parar Gravação");
	}

	else {

		g_print(" Parando gravação ! ");
		gtk_button_set_label(GTK_BUTTON(apertado),"Iniciar Gravação");
	}

	gravando = !gravando;
}

/**
 * @brief      Função Chamada Quando o Combo Box de Situação é Modificado em Principal.
 *
 * @param      ativo - Instância que Permite Descobrir o Item Ativo.
 */
void setaSituacao (GtkWidget *ativo) {

	string base = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ativo));

	g_print("%s ",base.c_str());
}

/**
 * @brief    Função Chamada Quando o Botão Começar é Apertado em Principal.  
 */
void comecarJogo () {

	g_print(" Jogo Começado ! ");
}

/**
 * @brief      Função Chamada Quando o Botão Pausar é Apertado em Principal.
 */
void pausarJogo () {

	g_print(" Jogo Pausado ! ");
}

/**
 * @brief      Função Chamada Quando o Botão Parar é Apertado em Principal.
 */
void pararJogo () {

	g_print(" Jogo Parado ! ");
}

/**
 * @brief      Função que Prepara a Instância dos Widgets da Seção Principal e Prepara Seus Sinais.
 *
 * @param      builder - O Construtor que Permite Acessar Objetos Criados no Glade.
 */
void preparaPrincipal(GtkBuilder *builder) {

	GtkWidget *checkArquivo;
	GtkWidget *botaoVoltaFrame;
	GtkWidget *botaoProxFrame;
	GtkWidget *botaoGravacao;
	GtkWidget *comboSituacao;
	GtkWidget *botaoComecar;
	GtkWidget *botaoPausar;
	GtkWidget *botaoParar;

	/*Configurações do Check Button de Salvamento em Arquivo*/
		checkArquivo = GTK_WIDGET(gtk_builder_get_object(builder, "checkbuttonArquivo"));
		g_signal_connect(checkArquivo, "toggled", G_CALLBACK(setaSalvamentoArquivo), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações da Tabela*/
		GtkCellRenderer *temp = gtk_cell_renderer_text_new();

		layoutTabela = GTK_WIDGET(gtk_builder_get_object(builder, "layoutTabela"));
		treeViewTabela = GTK_WIDGET(gtk_builder_get_object(builder, "treeviewTabela"));

		listStoreTabela = gtk_list_store_new(NUM_COLUNAS,G_TYPE_STRING, G_TYPE_DOUBLE);
		gtk_tree_view_set_model(GTK_TREE_VIEW(treeViewTabela),GTK_TREE_MODEL(listStoreTabela));

		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeViewTabela),-1, "Descrição", temp, "text", COLUNA_STRING, (char *)NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeViewTabela),-1, "Valor", temp, "text", COLUNA_DOUBLE, (char *)NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Painel de Gravação*/
		botaoVoltaFrame = GTK_WIDGET(gtk_builder_get_object(builder, "botaoVoltaFrame"));
		g_signal_connect(botaoVoltaFrame, "clicked", G_CALLBACK(voltarFrame), NULL);

		botaoProxFrame = GTK_WIDGET(gtk_builder_get_object(builder, "botaoProxFrame"));
		g_signal_connect(botaoProxFrame, "clicked", G_CALLBACK(proximoFrame), NULL);

		botaoGravacao = GTK_WIDGET(gtk_builder_get_object(builder, "botaoGravar"));
		g_signal_connect(botaoGravacao, "clicked", G_CALLBACK(iniciaParaGravacao), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Combo Box que Decide a Postura dos Robos ao Começar o Jogo*/
		comboSituacao = GTK_WIDGET(gtk_builder_get_object(builder, "comboSituacao"));
		g_signal_connect(comboSituacao, "changed", G_CALLBACK(setaSituacao), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Botão Começar*/
		botaoComecar = GTK_WIDGET(gtk_builder_get_object(builder, "botaoComecar"));
		g_signal_connect(botaoComecar, "clicked", G_CALLBACK(comecarJogo), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Botão Pausar*/
		botaoPausar = GTK_WIDGET(gtk_builder_get_object(builder, "botaoPausar"));
		g_signal_connect(botaoPausar, "clicked", G_CALLBACK(pausarJogo), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Botão Parar*/
		botaoParar = GTK_WIDGET(gtk_builder_get_object(builder, "botaoParar"));
		g_signal_connect(botaoParar, "clicked", G_CALLBACK(pararJogo), NULL);
	/*---------------------------------------------------------------------------------------*/

	tabelaDebug("Carrossel", 2);
	tabelaDebug("Caipira", 0);
	tabelaDebug("Rumo ao", 1);
	tabelaDebug("Título", 7);
}

/**
 * @brief      Função Chamada Quando o Número de Robôs é Modificado em Configurações.
 *
 * param       spinner - Instância do Spinner, Permitindo Assim Obter Seu Valor.
 */
void setNumRobos (GtkWidget *spinner) {

	g_print("oi");
}

/**
 * @brief      Função Chamada Quando o Botão Redefinir Limites é Apertado em Configurações.  
 */
void definirLimites () {

		g_print("oi 2");
}

/**
 * @brief        Função Chamada Quando o Botão Redefinir Cores é Apertado em Configurações.
 */
void definirCores () {

		g_print("oi 3");
}

/**
 * @brief      Função Chamada Quando o CheckBox do Gráfico é Ligado ou Desligado em Configurações.
 *
 * @param      estado - Instância do CheckBox que Permite Saber se Foi Ativado ou Desativado.
 */
void setaGrafico (GtkWidget *estado) {

	int index_ativo = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(estado));

	if (index_ativo==1) {

		g_print("Ligado");
		gtk_button_set_label(GTK_BUTTON(estado),"Gráfico Ativado");
	}

	else {

		g_print("Desligado");
		gtk_button_set_label(GTK_BUTTON(estado),"Gráfico Desativado");
	}
}

/**
 * @brief      Função Chamada Quando um dos RadioButtons da Orientação é Modificado em Configurações.
 *
 * @param      ativo - Instância que Permite Discernir Qual Lado Foi Escolhido
 */
void escolheLado (GtkWidget *ativo) {

	int index_ativo = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ativo));

	if (index_ativo==1) {

		g_print("Esquerda");
	}

	else {

		g_print("Direita");
	}
}

/**
 * @brief      Função Chamada Quando o Combo Box de Roteiro Base é Modificado em Configurações.
 *
 * @param      ativo - Instância que Permite Descobrir o Item Ativo.
 */
void setaRoteiroBase (GtkWidget *ativo) {

	string base = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ativo));

	g_print("%s ",base.c_str());
}

/**
 * @brief      Função Chamada Quando Algum Combo Box de Roteiro Individual é Modificado em Configurações. 
 *
 * @param      ativo  Instância do Combo Box Modificado
 * @param[in]  index  Indice do Combo Box Modificado
 */
void setaRoteiroIndividual (GtkWidget *ativo, gpointer index) {

	int *indice = (int*) index;

	string base = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(ativo));

	g_print("Combo box %d: %s\n",*indice,base.c_str());
}

/**
 * @brief      Função que Cria e Prepara os Combo Box Individuais do Roteiro.
 *
 * @return     Retorna Instância dos Novos Combo Box Configurados.
 */
GtkWidget* comboBoxPreenchido() {

	GtkWidget *comboBox = gtk_combo_box_text_new();

	for (int i=0;i<5;i++) {

		string temp = "teste";

		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(comboBox),temp.c_str());
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox),0);

	g_signal_connect(comboBox, "changed", G_CALLBACK(setaRoteiroIndividual),&identRoteiro[comboBoxAtual]);
	comboBoxAtual++;

	return GTK_WIDGET(comboBox);
}

/**
 * @brief      Função que Limpa o Paineis, Assim Como Aloca numCampos Novos Paineis.
 *
 * @param      painelPrincipal - Painel que Deve Ser Limpo.
 * @param[in]  numCampos       - Número de Novos Painéis a Ser Alocado.
 *
 * @return     Retorna Instância dos Novos Painéis Alocados.
 */
vector<GtkWidget*> limpaCriaPaineis(GtkWidget *painelPrincipal, int numCampos) {

	/*Limpa o Painel Com os Campos para que Eles Não se Acumulem*/
	GList *itensPainel, *iterador;

	itensPainel = gtk_container_get_children(GTK_CONTAINER(painelPrincipal));

	for(iterador = itensPainel; iterador != NULL; iterador = g_list_next(iterador))
  		gtk_widget_destroy(GTK_WIDGET(iterador->data));

	g_list_free(itensPainel);
	/*************************************************************************/

	/*Inicia os Layouts que Conterão os Campos, e os Inclui no Layout Principal*/

	vector<GtkWidget*> paineisAuxiliares;

	for (int i=0;i<numCampos + 1;i++) {

		GtkWidget *temp = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		gtk_box_set_homogeneous(GTK_BOX(temp),true);

		paineisAuxiliares.push_back(temp);
		gtk_box_pack_start(GTK_BOX(painelPrincipal),paineisAuxiliares[i],0,0,0);
	}
	/*************************************************************************/

	return paineisAuxiliares;
}

/**
 * @brief      Função que Preenche numCampos Paineis com Um Label e Um Combo Box.
 *
 * @param[in]  paineisPreenchidos - Painéis que Devem Ser Preenchidos.
 * @param[in]  numCampos          - Número de Painéis que Serão Preenchidos.
 *
 * @return     Retorna Instância dos Novos Combo Box Criados.
 */
vector<GtkWidget*> preenchePaineis(vector<GtkWidget*> paineisPreenchidos,int numCampos) {

	vector<GtkWidget*> camposInseridos;

	/*Preenche Os Layouts do Campo com Labels para Identificar os Campos e os Campos em Si, Dependedendo da Dimensão do Problema*/
	for (int i=0;i < numCampos+1;i++) {

		string label= (posicoesRobos[numCampos])[i] + ": ";
		
		GtkWidget *temp = gtk_label_new(&label[0]);

		gtk_widget_set_margin_start(temp, 10);
		gtk_box_pack_start(GTK_BOX(paineisPreenchidos[i]),temp,true,true,0);
		gtk_widget_set_halign(temp,GTK_ALIGN_START);

		camposInseridos.push_back(comboBoxPreenchido());

		gtk_box_pack_end(GTK_BOX(paineisPreenchidos[i]),camposInseridos[i],true,true,0);
	}
	/*************************************************************************/

	comboBoxAtual=0;

	return camposInseridos;

}

/**
 * @brief      Função Chamada Quando o Número de Robôs é Modificado em Configurações.
 *
 * @param      spinner - Instância do Spinner, Permitindo Assim Obter Seu Valor.
 * @param[in]  layout - O Layout Do Painel Principal que Conterá Todos Combo Box e Labels.
 */
void preparaRoteiroIndividual (GtkWidget *spinner, gpointer layout) {

	GtkWidget *layoutRoteiroIndividualGeral = (GtkWidget*) layout;
	vector<GtkWidget*> layoutRoteirosIndividuais;
	vector<GtkWidget*> comboRoteirosIndividuais;
	int numRobos = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner)) - 1;

	layoutRoteirosIndividuais = limpaCriaPaineis(layoutRoteiroIndividualGeral,numRobos);
	comboRoteirosIndividuais = preenchePaineis(layoutRoteirosIndividuais,numRobos);

	gtk_widget_set_visible(layoutRoteiroIndividualGeral,true);
	gtk_widget_show_all(layoutRoteiroIndividualGeral);
}

/**
 * @brief      Função que Prepara a Instância dos Widgets da Seção de Configuração e Prepara Seus Sinais.
 *
 * @param      builder - O Construtor que Permite Acessar Objetos Criados no Glade.
 */
void preparaConfiguracao (GtkBuilder *builder) {

	GtkWidget *spinNumRobos;
	GtkWidget *botaoDefinirLimites;
	GtkWidget *botaoDefinirCores;
	GtkWidget *checkGrafico;
	GtkWidget *botaoRadioEsq;
	GtkWidget *comboRoteiroConjunto;
	GtkWidget *layoutRoteiroIndividualGeral;

	/*Configurações do Spinner de Número de Robos*/
		spinNumRobos = GTK_WIDGET(gtk_builder_get_object(builder, "botaoSpinNumRobos"));
		g_signal_connect(spinNumRobos, "value-changed", G_CALLBACK(setNumRobos), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Botão de Redefinir Limites*/
		botaoDefinirLimites = GTK_WIDGET(gtk_builder_get_object(builder, "botaoDefinirLimites"));
		g_signal_connect(botaoDefinirLimites, "clicked", G_CALLBACK(definirLimites), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Botão de Redefinir Cores*/
		botaoDefinirCores = GTK_WIDGET(gtk_builder_get_object(builder, "botaoDefinirCores"));
		g_signal_connect(botaoDefinirCores, "clicked", G_CALLBACK(definirCores), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Check Button que Liga e Desliga o Gráfico*/
		checkGrafico = GTK_WIDGET(gtk_builder_get_object(builder, "checkBoxGrafico"));
		g_signal_connect(checkGrafico, "toggled", G_CALLBACK(setaGrafico), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações dos Botões de Rádio que Definem a Orientação*/
		botaoRadioEsq = GTK_WIDGET(gtk_builder_get_object(builder, "botaoRadioEsq"));
		g_signal_connect(botaoRadioEsq, "toggled", G_CALLBACK(escolheLado), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações dos Combo Box que Formam as Opções de Roteiro*/
		comboRoteiroConjunto = GTK_WIDGET(gtk_builder_get_object(builder, "comboRoteiroConjunto"));
		g_signal_connect(comboRoteiroConjunto, "changed", G_CALLBACK(setaRoteiroBase), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Spinner de Número de Robos 2*/
		layoutRoteiroIndividualGeral = GTK_WIDGET(gtk_builder_get_object(builder, "layoutRoteiroIndividual"));
		g_signal_connect(spinNumRobos, "value-changed", G_CALLBACK(preparaRoteiroIndividual), layoutRoteiroIndividualGeral);
	/*---------------------------------------------------------------------------------------*/

	preparaRoteiroIndividual(spinNumRobos,layoutRoteiroIndividualGeral);
}

/**
 * @brief      Função Chamada Quando o CheckBox de Gravação é Ligado ou Desligado em Outros.
 *
 * @param      estado - Instância do CheckBox que Permite Saber se Foi Ativado ou Desativado.
 * @param[in]  layout - O Layout que Será Revelado/Escondido.
 */
void setaGravacao (GtkWidget *estado, gpointer layout) {

	GtkWidget *layoutGravacao = (GtkWidget*) layout;
	int index_ativo = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(estado));

	if (index_ativo==1) {

		g_print("Ligado");
		gtk_button_set_label(GTK_BUTTON(estado),"Gravação Ativada");
		gtk_widget_set_visible(layoutGravacao,true);
	}

	else {

		g_print("Desligado");
		gtk_button_set_label(GTK_BUTTON(estado),"Gravação Desativada");
		gtk_widget_set_visible(layoutGravacao,false);
	}
}

/**
 * @brief      Função Chamada Quando o Botão Capturar é Apertado em Outros.  
 */
void fazerCaptura () {

	g_print("oi 4");
}

/**
 * @brief      Função Chamada Quando o Valor da Escala é Modificado.
 *
 * @param      valor - Instância da Escala que Permite Saber o Valor Atual da Mesma.
 */
void definirTaxa (GtkWidget *valor) {

	int valorSlider = (int) gtk_range_get_value(GTK_RANGE(valor));

	g_print(" %d ",valorSlider);
}

/**
 * @brief      Função que Prepara a Instância dos Widgets da Seção de Outros e Prepara Seus Sinais.
 *
 * @param      builder - O Construtor que Permite Acessar Objetos Criados no Glade.
 */
void preparaOutros (GtkBuilder *builder) {

	GtkWidget *checkGravacao;
	GtkWidget *layoutGravacao;
	GtkWidget *botaoCapturarCampoVazio;
	GtkWidget *escalaTaxaCampoVazio;

	/*Configurações do Check Button que Liga e Desliga a Gravação no Painel Principal*/
		checkGravacao = GTK_WIDGET(gtk_builder_get_object(builder, "checkBoxGravacao"));
		layoutGravacao = GTK_WIDGET(gtk_builder_get_object(builder, "layoutGravacao"));
		g_signal_connect(checkGravacao, "toggled", G_CALLBACK(setaGravacao), layoutGravacao);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Botão de Capturar o Campo Vazio*/
		botaoCapturarCampoVazio = GTK_WIDGET(gtk_builder_get_object(builder, "botaoCapturaCampoVazio"));
		g_signal_connect(botaoCapturarCampoVazio, "clicked", G_CALLBACK(fazerCaptura), NULL);
	/*---------------------------------------------------------------------------------------*/

	/*Configurações do Slider que Define a Taxa de Uso do Campo Vazio*/
		escalaTaxaCampoVazio = GTK_WIDGET(gtk_builder_get_object(builder, "escalaTaxaCampoVazio"));
		g_signal_connect(escalaTaxaCampoVazio, "value-changed", G_CALLBACK(definirTaxa), NULL);
	/*---------------------------------------------------------------------------------------*/
}

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);
 
	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "InterfaceCarrossel.glade", NULL);
 
	GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "janelaPrincipal"));
	gtk_builder_connect_signals(builder, NULL);

	preparaGlobais();
	preparaPrincipal(builder);
	preparaConfiguracao(builder);
	preparaOutros(builder);

	g_object_unref(builder);

	gtk_widget_show(window);
	gtk_main();

	return 0;
}