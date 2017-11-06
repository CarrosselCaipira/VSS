#ifndef POSICIONAMENTO_H
#define POSICIONAMENTO_H

#include "tiposClasses.h"

#define TAM_X_GOL 10	// em cemtimetros
#define TAM_Y_GOL 40
#define RAIO_ATAQUE 6

#define TAM_X_CAMPO_SEM_GOL 150	// em cemtimetros
#define TAM_X_CAMPO TAM_X_CAMPO_SEM_GOL + TAM_X_GOL + TAM_X_GOL // 170
#define TAM_Y_CAMPO 130	// em cemtimetros

#define TAM_QUADRADO_INUTIL 7

#define TAM_X_AREA_GOL 15
#define TAM_Y_AREA_GOL 70
#define CENTRO_X_GOL_ADV (TAM_X_CAMPO-TAM_X_GOL)
#define CENTRO_Y_GOL TAM_Y_CAMPO / 2

/* SOB ANALISE DE NECESSIDADE */
// #define POS_X_NECESSARIA_PARA_GOLEIRO_TER_TEMPO_DEFENDER (TAM_X_GOL + TAM_ROBO/2 + 2)	// 2 cm a mais para o robo ter espaco para andar
// #define DIST_GIRO TAM_ROBO*2

#define INICIO_AREA_ATUACAO_GOLEIRO (TAM_X_GOL) // 10 cm
#define FIM_AREA_ATUACAO_GOLEIRO (TAM_X_CAMPO * 0.5500) // 93,5 cm

#define INICIO_AREA_ATUACAO_VOLANTE (TAM_X_GOL) // 10 cm
#define FIM_AREA_ATUACAO_VOLANTE (TAM_X_CAMPO - 10) // 160 cm

#define INICIO_AREA_ATUACAO_ATACANTE (TAM_X_GOL + TAM_X_AREA_GOL + TAM_ROBO / 2) // 93,5cm
#define FIM_AREA_ATUACAO_ATACANTE (TAM_X_CAMPO - 10) // 160 cm

#define ESPACO_CHUTE_GIRANDO 6

// Nossa metade do campo.
bool campoTime(const posXY posicao);

// Metade do campo do adversario.
bool campoAdv(const posXY posicao);

// Metade superior do campo.
bool campoMetadeSuperior(const posXY posicao);

// Metade inferior do campo.
bool campoMetadeInferior(const posXY posicao);

// faixa superior do campo.
bool faixaSuperior(const posXY posicao);

// faixa inferior do campo.
bool faixaInferior(const posXY posicao);

// Faixa Central do Campo como um todo
bool faixaCentral(const posXY posicao);

// faixa da linha da area do gol do nosso time para tras (ate a parede do campo).
bool faixaXDaAreaGolTime(const posXY posicao);

// faixa da linha da area do gol adversario time para tras (ate a parede do campo).
bool faixaXDaAreaGolAdv(const posXY posicao);

// Do final da area do goleiro ate o meio de Campo.
bool campoSemAreaGolTime(const posXY posicao);

// Do final da area do goleiro adversario ate o meio de Campo.
bool campoSemAreaGolAdv(const posXY posicao);

// Interseccao de faixaXDaAreaGolTime() com faixaSuperior()
bool areaEscanteioSuperiorTime(const posXY posicao);

// Interseccao de faixaXDaAreaGolTime() com faixaInferior()
bool areaEscanteioInferiorTime(const posXY posicao);

// Interseccao de faixaXDaAreaGolAdv() com faixaSuperior()
bool areaEscanteioSuperiorAdv(const posXY posicao);

// Interseccao de faixaXDaAreaGolAdv() com faixaInferior()
bool areaEscanteioInferiorAdv(const posXY posicao);

// "Miolo" central do nosso campo.
bool areaAntesMetadeCampoTime(const posXY posicao);

// "Miolo" central do campo adversario.
bool areaAntesMetadeCampoAdv(const posXY posicao);

// Tamanho adicional que completa a area superior do nosso gol.
bool quinaSuperiorAreaGolTime(const posXY posicao);

// Tamanho adicional que completa a area inferior do nosso gol.
bool quinaInferiorAreaGolTime(const posXY posicao);

// Tamanho adicional que completa a area superior do gol adversario.
bool quinaSuperiorAreaGolAdv(const posXY posicao);

// Tamanho adicional que completa a area inferior do gol adversario.
bool quinaInferiorAreaGolAdv(const posXY posicao);

// Area do gol do nosso time. (linhas do desenho do campo)
bool areaGolTime(const posXY posicao);

// Area do gol do time adversario. (linhas do desenho do campo)
bool areaGolAdv(const posXY posicao);

// Area definida para fazer o chute girando.
// Faixa pertencente a faixaSuperior() mas menor, onde o robo fara o chute girando.
bool faixaSuperiorChuteGirando(const posXY posicao);

// Area definida para fazer o chute girando.
// Faixa pertencente a faixaInferior() mas menor, onde o robo fara o chute girando.
bool faixaInferiorChuteGirando(const posXY posicao);

// Area definida para fazer o chute girando.
// Faixa pertencente a faixaXDaAreaGolTime() mas menor, onde o robo fara o chute girando.
bool faixaChuteGirandoTime(const posXY posicao);

// Area definida para fazer o chute girando.
// Faixa pertencente a faixaXDaAreaGolAdv() mas menor, onde o robo fara o chute girando.
bool faixaChuteGirandoAdv(const posXY posicao);

// Função que baseando-se em dados retorna o Y esperado da bola em NumQuadrosGol.
float yBolaPrevisto(const float numQuadrosGol, const float vetorSentidoEmYBola, const float posYBola);

// Area definida pelo quadrado inútil no canto superior esquerdo.
bool quadradoInutilCantoSuperiorEsquerdo(const posXY posicao);

// Area definida pelo quadrado inútil no canto inferior esquerdo.
bool quadradoInutilCantoInferiorEsquerdo(const posXY posicao);

// Area definida pelo quadrado inútil no canto superior direito.
bool quadradoInutilCantoSuperiorDireito(const posXY posicao);

// Area definida pelo quadrado inútil no canto inferior direito.
bool quadradoInutilCantoInferiorDireito(const posXY posicao);

// Area definida por qualquer dos quadrados inuteis.
bool quadradosInuteis(const posXY posicao);

// Checa se a bola está no raio de ataque dado, baseando-se na posição do robô.
bool raioAtaque(const posXY posicao, int raio);

// Checa se o robo está com a bola logo a frente.
bool roboComBola(const posXY posicao, int raio);

// Checa se a bola está no intervalo y do robô.
bool bolaNoIntervaloYRobo(cont posXY posicao);

/* POSICIONAMENTO_H */
#endif
