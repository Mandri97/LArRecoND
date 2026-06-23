/**
 *  @file   larpandoracontent/LArVertex/HitAngleVertexSelectionAlgorithm.h
 *
 *  @brief  Header file for the hit angle vertex selection algorithm class.
 *
 *  $Log: $
 */
#ifndef LAR_ND_HIT_ANGLE_VERTEX_SELECTION_ALGORITHM_H
#define LAR_ND_HIT_ANGLE_VERTEX_SELECTION_ALGORITHM_H 1

#include "vertex/LArNDVertexSelectionBaseAlgorithm.h"

namespace lar_content
{

/**
 *  @brief  HitAngleVertexSelectionAlgorithm class
 */
class ND_HitAngleVertexSelectionAlgorithm : public ND_VertexSelectionBaseAlgorithm
{
public:
    /**
     *  @brief  Default constructor
     */
    ND_HitAngleVertexSelectionAlgorithm();

private:
    void GetVertexScoreList(const pandora::VertexVector &vertexVector, const BeamConstants &beamConstants, HitKDTree2D &kdTreeU,
        HitKDTree2D &kdTreeV, HitKDTree2D &kdTreeW, VertexScoreList &vertexScoreList) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    VertexFeatureTool::FeatureToolVector m_featureToolVector; ///< The feature tool map
};

} // namespace lar_content

#endif // #ifndef LAR_HIT_ANGLE_VERTEX_SELECTION_ALGORITHM_H
