#include <gtk/gtk.h>
#include <vector>
#include <string>

using namespace std;

//Avaliar se Todas essas Variáveis Precisam Ser Globais.

/*Variáveis que Explicitam as Funções dos Robôs Baseando-se no Número de Robôs*/
vector<vector<string> > posicoesRobos;

vector<string> umRobo;
vector<string> doisRobos;
vector<string> tresRobos;
vector<string> quatroRobos;

/*Variáveis de Acesso ao Arquivo*/
GtkBuilder *builder;

/*Variáveis de Acesso à Janela*/
GtkWidget *window;

/*Variáveis de Acesso aos Elementos de Configuração*/
GtkWidget *spinNumRobos;
GtkWidget *botaoDefinirLimites;
GtkWidget *botaoDefinirCores;
GtkWidget *checkGrafico;
GtkWidget *botaoRadioEsq;
GtkWidget *comboRoteiroConjunto;
GtkWidget *layoutRoteiroIndividualGeral;
vector<GtkWidget*> layoutRoteirosIndividuais;
vector<GtkWidget*> comboRoteirosIndividuais;

/**
 * @brief      Função que Prepara o que Será Escrito nas Labels para Representar os Robôs, de Acordo com o Número de Rôbos
 */
void preparaPosicoesRobos () {

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

		paineisAuxiliares.push_back(temp);
		gtk_box_pack_start(GTK_BOX(painelPrincipal),paineisAuxiliares[i],0,0,0);
	}
	/*************************************************************************/

	return paineisAuxiliares;
}

vector<GtkWidget*> preenchePaineis(vector<GtkWidget*> paineisPreenchidos,int numCampos) {

	vector<GtkWidget*> camposInseridos;

	/*Preenche Os Layouts do Campo com Labels para Identificar os Campos e os Campos em Si, Dependedendo da Dimensão do Problema*/
	for (int i=0;i < numCampos+1;i++) {

		string label= (posicoesRobos[numCampos])[i] + ": ";
		
		GtkWidget *temp = gtk_label_new(&label[0]);
		
		gtk_box_pack_start(GTK_BOX(paineisPreenchidos[i]),temp,false,false,0);

		camposInseridos.push_back(gtk_combo_box_text_new());

		gtk_box_pack_end(GTK_BOX(paineisPreenchidos[i]),camposInseridos[i],false,false,2);
	}
	/*************************************************************************/

	return camposInseridos;

}

void setaRoteiroIndividual (GtkWidget *spinner) {

	int numRobos = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinner)) - 1;

	layoutRoteirosIndividuais = limpaCriaPaineis(layoutRoteiroIndividualGeral,numRobos);
	comboRoteirosIndividuais = preenchePaineis(layoutRoteirosIndividuais,numRobos);

	gtk_widget_set_visible(layoutRoteiroIndividualGeral,true);
	gtk_widget_show_all(layoutRoteiroIndividualGeral);

	g_print("%lu ",layoutRoteirosIndividuais.size());
	g_print("%lu ",comboRoteirosIndividuais.size());
}

/**
 * @brief      Função que Prepara a Instância dos Widgets da Seção de Configuração e Prepara Seus Sinais.
 */
void preparaConfiguracao () {

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

	/*Configurações do Spinner de Número de Robos*/
		layoutRoteiroIndividualGeral = GTK_WIDGET(gtk_builder_get_object(builder, "layoutRoteiroIndividual"));
		g_signal_connect(spinNumRobos, "value-changed", G_CALLBACK(setaRoteiroIndividual), NULL);
	/*---------------------------------------------------------------------------------------*/

	setaRoteiroIndividual(spinNumRobos);
}

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);
 
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "InterfaceCarrossel.glade", NULL);
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "janelaPrincipal"));
	gtk_builder_connect_signals(builder, NULL);

	preparaPosicoesRobos();
	preparaConfiguracao();

	g_object_unref(builder);
 
	gtk_widget_show(window);
	gtk_main();

	return 0;
}