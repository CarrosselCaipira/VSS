#include "posicionamento.hpp"

bool campoTime(const posXY posicao){
  return posicao.x < (TAM_X_CAMPO/2);
}

bool faixaSuperior(const posXY posicao){
  return posicao.y > (TAM_Y_CAMPO/2 + TAM_Y_GOL/2);
}

bool faixaInferior(const posXY posicao){
  return posicao.y < (TAM_Y_CAMPO/2 - TAM_Y_GOL/2);
}

bool faixaCentral(const posXY posicao){
  return (!faixaSuperior(posicao) && !faixaInferior(posicao));
}

bool faixaXDaAreaGolTime(const posXY posicao){
  return posicao.x < (TAM_X_GOL + TAM_X_AREA_GOL);
}

bool faixaXDaAreaGolAdv(const posXY posicao){
  return posicao.x > (TAM_X_CAMPO - TAM_X_GOL - TAM_X_AREA_GOL);
}

bool campoSemAreaGolTime(const posXY posicao){
  return (campoTime(posicao) && !faixaXDaAreaGolTime(posicao));
}

bool campoSemAreaGolAdv(const posXY posicao){
  return (!campoTime(posicao) && !faixaXDaAreaGolAdv(posicao));
}

bool areaEscanteioSuperiorTime(const posXY posicao){
  return (faixaSuperior(posicao) && faixaXDaAreaGolTime(posicao));
}

bool areaEscanteioInferiorTime(const posXY posicao){
  return (faixaInferior(posicao) && faixaXDaAreaGolTime(posicao));
}

bool areaEscanteioSuperiorAdv(const posXY posicao){
  return (faixaSuperior(posicao) && faixaXDaAreaGolAdv(posicao));
}

bool areaEscanteioInferiorAdv(const posXY posicao){
  return (faixaInferior(posicao) && faixaXDaAreaGolAdv(posicao));
}

bool areaAntesMetadeCampoTime(const posXY posicao){
  return (campoTime(posicao) && !faixaXDaAreaGolTime(posicao) && faixaCentral(posicao));
}

bool areaAntesMetadeCampoAdv(const posXY posicao){
  return (!campoTime(posicao) && !faixaXDaAreaGolAdv(posicao) && faixaCentral(posicao));
}

bool quinaSuperiorAreaGolTime(const posXY posicao){
  return ((posicao.y < (TAM_Y_CAMPO/2 + TAM_Y_GOL/2 + 10)) && faixaSuperior(posicao) && faixaXDaAreaGolTime(posicao));
}

inline bool quinaInferiorAreaGolTime(const posXY posicao){
  return ((posicao.y > (TAM_Y_CAMPO/2 - TAM_Y_GOL/2 - 10)) && faixaInferior(posicao) && faixaXDaAreaGolTime(posicao));
}

bool quinaSuperiorAreaGolAdv(const posXY posicao){
  return ((posicao.y < (TAM_Y_CAMPO/2 + TAM_Y_GOL/2 + 10)) && faixaSuperior(posicao) && faixaXDaAreaGolAdv(posicao));
}

bool quinaInferiorAreaGolAdv(const posXY posicao){
  return ((posicao.y > (TAM_Y_CAMPO/2 - TAM_Y_GOL/2 - 10)) && faixaInferior(posicao) && faixaXDaAreaGolAdv(posicao));
}

bool areaGolTime(const posXY posicao){
  return ((quinaSuperiorAreaGolTime(posicao) || faixaCentral(posicao) || quinaInferiorAreaGolTime(posicao)) && faixaXDaAreaGolTime(posicao));
}

bool areaGolAdv(const posXY posicao){
  return ((quinaSuperiorAreaGolAdv(posicao) || faixaCentral(posicao) || quinaInferiorAreaGolAdv(posicao)) && faixaXDaAreaGolAdv(posicao));
}

bool faixaSuperiorChuteGirando(const posXY posicao){
  return (posicao.y > (TAM_Y_CAMPO - ESPACO_CHUTE_GIRANDO));
}

bool faixaInferiorChuteGirando(const posXY posicao){
  return (posicao.y < ESPACO_CHUTE_GIRANDO);
}

bool faixaChuteGirandoTime(const posXY posicao){
  return (!faixaCentral(posicao) && posicao.x < (TAM_X_GOL + 6));
}

bool faixaChuteGirandoAdv(const posXY posicao){
  return (!faixaCentral(posicao) && posicao.x < (TAM_X_CAMPO - TAM_X_GOL - 6));
}

float yBolaPrevisto(const float numQuadrosGol, const float vetorSentidoEmYBola, const float posYBola){
  return numQuadrosGol * vetorSentidoEmYBola + posYBola
}
