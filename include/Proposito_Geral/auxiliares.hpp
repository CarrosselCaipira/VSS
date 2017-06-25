/*
 * ESTE software foi fornecido como exemplo de controlador de futebol de robôs na Segunda Oficina Brasileira de Futebol de Robôs realizada junto ao 5o Workshop em Automação e Robótica Aplicada (Robocontrol) 2010.

 * Você que está de posse dESTE software, está livre para utilizá-lo, alterá-lo, copiá-lo e incluí-lo parcial ou integralmente em outros software desde que acompanhado da seguinte indicação:
 * "Este software tem seções de código desenvolvidas por Rene Pegoraro no Laboratório de Integração de Sistemas e Dispositivos Inteligentes (LISDI) do Departamento de Computação da Faculdade de Ciências da Universidade Estadual Paulista (UNESP) - Campos de Bauru - SP - Brasil"

 * Se qualquer publicação for gerada pela utilização de software utilizando parcial ou integralmente ESTE software, esta publicação deve conter os devidos créditos para o "Grupo de Integração de Sistemas e Dispositivos Inteligentes (GISDI) do Departamento de Computação da Faculdade de Ciências da Universidade Estadual Paulista (UNESP) - Campos de Bauru - SP - Brasil"
 */



#ifndef FUNCOESAUXILIARES_H_
#define FUNCOESAUXILIARES_H_

#include "TiposClasses.h"

/** satura o valor de 0 a 255 */
inline guint8 satura(int x) {
	if (x < 0)
		return 0;
	else if (x > 255)
		return 255;
	else
		return x;
}

/** tangete exata (correta) do angulo aproximado obtido de atan2x */
inline float tgx(int ax) {
	if (ax > 128)
		return 128.0 / (255 - ax);
	else
		return ax / 128.0;
}

/** angulo aproximado dado os catetos,
 * somente para o 1o quadrante resultando em valores de 0 a 255 */
inline int atan2x(int y, int x) {
	if (x > y)
		return y * 128 / x;
	else {
		if (y == 0)
			return 255;
		return 255 - x * 128 / y;
	}
}

inline void SCT_RGB(int ax, int bx, int lum, guint8 &r, guint8 &g, guint8 &b) {
	float alfa = atan(tgx(ax));
	float beta = atan(tgx(bx));
	lum *= 1.73;// 1.73 (ajuste para lum ser 442, soma vetorial de r, g e b = 255);
	int bAux = lum * sin(beta);
	int irg = lum * cos(beta);
	int rAux = irg * cos(alfa);
	int gAux = irg * sin(alfa);
	int maxi = max(rAux, max(gAux, bAux));
	if (maxi > 255) {
		r = rAux * 255 / maxi;
		g = gAux * 255 / maxi;
		b = bAux * 255 / maxi;
	} else {
		r = rAux;
		g = gAux;
		b = bAux;
	}
}

inline void RGB_SCT(int r, int g, int b, int &ax, int &bx, int &lum) {
	ax = atan2x(g, r);
	int irg = r * r + g * g;
	bx = atan2x(b, sqrt(irg));
	lum = sqrt(irg + b * b) / 1.73;
}

/** Inicia o vetor que conver RGB (4 bits de r, 4 de g e 4 de b) para a paleta de cores calibradas */
void iniciaVetoresRGBPaleta(guint8 rgb_paleta[], int aInicio[], int bInicio[],
		int lumInicio[], int aFinal[], int bFinal[], int lumFinal[]);

/** ang1 - ang2 */
float difAngulos(float ang1, float ang2);

/** ang1 - ang2 */
float difAngulosAbs(float ang1, float ang2);

inline float atang2(float y, float x) {
	float ang = (x == 0 && y == 0) ? 0 : atan2(y, x) * 180 / M_PI;
	return ang >= 0 ? ang : ang + 360;
}

inline float seno(float x) {
	return sin(x * M_PI / 180);
}

inline float coss(float x) {
	return cos(x * M_PI / 180);
}

inline int difAngMenos180a180(float A1, float A2) {
	int dif = A1 - A2;
	if (abs(dif) > 180) {
		if (A1 < A2) {
			dif = 360 + dif;
		} else {
			dif = dif - 360;
		}
	}
	return dif;
}

void geraMatrizComb(guint8 comb[MAX_CONT_COMB][NUM_ROBOS_TIME]);

void erro(string msg);

void erro(string msg, int errno);

void gravaLog(char *s);

/** classe que repreesenta uma camera com todas as variaveis necessárias para obter as informacoes de uma imagem da camera.
 esta classe foi criada para simplificar a utilizacao de duas cameras  */
class FutebolCamera {
public:
	FutebolCamera(int indCamera);

	int indCamera;

	// indicacao de qual lado a camera
	Lado nossoLado;

	// Valores ideais para o tamanho dos blobs. Estes valores mudam dependendo do tamanho da imagem capturada pela camera
	int tamIdealXBlob; // ideal
	int tamIdealYBlob;
	int minLimiteXBlob; // 50% do ideal
	int minLimiteYBlob;
	int maxLimiteXBlob; // 50% mais que o ideal
	int maxLimiteYBlob;
	int numIdealPixelsBlob;
	int numMinPixelsBlob;
	int numMaxPixelsBlob;
	int distIdealEtiquetas;
	// considerando que apenas as partes mais internas dos circulos (etiquetas) sao visiveis
	int minDistEtiquetas;
	// considerando que apenas as partes mais externas dos circulos (etiquetas) sao visiveis
	int maxDistEtiquetas;
	int maxPixelsPorSegundo;

	Glib::RefPtr<Gdk::Pixbuf> imgOrig, imgCap, imgDigi;
	Cor *pImgCap;
	guint8 pImgDigi[640 * 480]; //indice da cor;
	guint8 pImgAux[640 * 480]; //salvamento temporario de pImgDigi
	Cor imgs[10][640 * 480]; // imagens para salvar quadros para analise e usado para calcular o campo vazio

	/** inicio das faixas do canal A, do B e do I(lum) */
	int aInicio[MAX_IND_CORES], bInicio[MAX_IND_CORES],
			lumInicio[MAX_IND_CORES];
	/** fim das faixas do canal A, do B e do I(lum) */
	int aFinal[MAX_IND_CORES], bFinal[MAX_IND_CORES], lumFinal[MAX_IND_CORES];

	guint8 rgb_paleta[32768];

	// variaveis para obter o campo vazio
	int contImgsCampoVazio;
	Cor pCampoVazio[640 * 480];
	int contImgsIntervalo;
	int nivelCampoVazio;

	LimitesCampo limitesCampo;

	/** Propriedades armazenadas no arquivo futebol.parametros */
	Props *props;

	void recalculaPixelsPosCentimetros();

	void converteRGB24Paleta(guint8 *pImgDigi, Cor *pImgCap, Cor *pCampoVazio);

	void processa();

	virtual void nucleoFutebol(guint8 *pImgDigi, guint8 rgb_paleta[]) {
	}

	void preparaCampoVazio();

	void iniciaVetoresRGBPaleta();

	void leParametros();

	void leImgCampoVazio();

	void leParametros(int inicio[], int final[], string canal);

	void salvaParametros();

	void salvaImgCampoVazio();

	void salvaParametros(int inicio[], int final[], string canal);

	~FutebolCamera();
};
#endif /* FUNCOESAUXILIARES_H_ */
