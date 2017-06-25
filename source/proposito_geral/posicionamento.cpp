#include "posicionamento.hpp"

inline bool campoTime(const posXY posicao){
  return posicao.x < (TAM_X_CAMPO/2);
}

inline bool faixaSuperior(const posXY posicao){
  return posicao.y > (TAM_Y_CAMPO/2 + TAM_Y_GOL/2);
}

inline bool faixaInferior(const posXY posicao){
  return posicao.y < (TAM_Y_CAMPO/2 - TAM_Y_GOL/2);
}

inline bool faixaCentral(const posXY posicao){
  return (!faixaSuperior(posicao) && !faixaInferior(posicao));
}

inline bool faixaXDaAreaGolTime(const posXY posicao){
  return posicao.x < (TAM_X_GOL + TAM_X_AREA_GOL);
}

inline bool faixaXDaAreaGolAdv(const posXY posicao){
  return posicao.x > (TAM_X_CAMPO - TAM_X_GOL - TAM_X_AREA_GOL);
}

inline bool campoSemAreaGolTime(const posXY posicao){
  return (campoTime(posicao) && !faixaXDaAreaGolTime(posicao));
}

inline bool campoSemAreaGolAdv(const posXY posicao){
  return (!campoTime(posicao) && !faixaXDaAreaGolAdv(posicao));
}

inline bool areaEscanteioSuperiorTime(const posXY posicao){
  return (faixaSuperior(posicao) && faixaXDaAreaGolTime(posicao));
}

inline bool areaEscanteioInferiorTime(const posXY posicao){
  return (faixaInferior(posicao) && faixaXDaAreaGolTime(posicao));
}

inline bool areaEscanteioSuperiorAdv(const posXY posicao){
  return (faixaSuperior(posicao) && faixaXDaAreaGolAdv(posicao));
}

inline bool areaEscanteioInferiorAdv(const posXY posicao){
  return (faixaInferior(posicao) && faixaXDaAreaGolAdv(posicao));
}

inline bool areaAntesMetadeCampoTime(const posXY posicao){
  return (campoTime(posicao) && !faixaXDaAreaGolTime(posicao) && faixaCentral(posicao));
}

inline bool areaAntesMetadeCampoAdv(const posXY posicao){
  return (!campoTime(posicao) && !faixaXDaAreaGolAdv(posicao) && faixaCentral(posicao));
}

inline bool quinaSuperiorAreaGolTime(const posXY posicao){
  return ((posicao.y < (TAM_Y_CAMPO/2 + TAM_Y_GOL/2 + 10)) && faixaSuperior(posicao) && faixaXDaAreaGolTime(posicao));
}

inline bool quinaInferiorAreaGolTime(const posXY posicao){
  return ((posicao.y > (TAM_Y_CAMPO/2 - TAM_Y_GOL/2 - 10)) && faixaInferior(posicao) && faixaXDaAreaGolTime(posicao));
}

inline bool quinaSuperiorAreaGolAdv(const posXY posicao){
  return ((posicao.y < (TAM_Y_CAMPO/2 + TAM_Y_GOL/2 + 10)) && faixaSuperior(posicao) && faixaXDaAreaGolAdv(posicao));
}

inline bool quinaInferiorAreaGolAdv(const posXY posicao){
  return ((posicao.y > (TAM_Y_CAMPO/2 - TAM_Y_GOL/2 - 10)) && faixaInferior(posicao) && faixaXDaAreaGolAdv(posicao));
}

inline bool areaGolTime(const posXY posicao){
  return ((quinaSuperiorAreaGolTime(posicao) || faixaCentral(posicao) || quinaInferiorAreaGolTime(posicao)) && faixaXDaAreaGolTime(posicao));
}

inline bool areaGolAdv(const posXY posicao){
  return ((quinaSuperiorAreaGolAdv(posicao) || faixaCentral(posicao) || quinaInferiorAreaGolAdv(posicao)) && faixaXDaAreaGolAdv(posicao));
}

inline bool faixaSuperiorChuteGirando(const posXY posicao){
  return (posicao.y > (TAM_Y_CAMPO - ESPACO_CHUTE_GIRANDO));
}

inline bool faixaInferiorChuteGirando(const posXY posicao){
  return (posicao.y < ESPACO_CHUTE_GIRANDO);
}

inline  bool faixaChuteGirandoTime(const posXY posicao){
  return (!faixaCentral(posicao) && posicao.x < (TAM_X_GOL + 6));
}

inline  bool faixaChuteGirandoAdv(const posXY posicao){
  return (!faixaCentral(posicao) && posicao.x < (TAM_X_CAMPO - TAM_X_GOL - 6));
}

inline float yBolaPrevisto(const float numQuadrosGol, const float vetorSentidoEmYBola, const float posYBola){
  return numQuadrosGol * vetorSentidoEmYBola + posYBola
}

inline bool areaAtuacaoRobo(const int indiceRobo){
  switch(indiceRobo){
    case 0:
      return (xBola < FIM_AREA_ATUACAO_GOLEIRO && xBola > INICIO_AREA_ATUACAO_GOLEIRO);
    case 1:
      return xBola < FIM_AREA_ATUACAO_GOLEIRO && xBola > INICIO_AREA_ATUACAO_GOLEIRO
    case 2:
      return xBola < FIM_AREA_ATUACAO_GOLEIRO && xBola > INICIO_AREA_ATUACAO_GOLEIRO
  }
}

inline bool comportamentoDefensivo(int indiceRobo){
  switch(indiceRobo){
    case 0:
    case 1:
    case 2:
  }
}
