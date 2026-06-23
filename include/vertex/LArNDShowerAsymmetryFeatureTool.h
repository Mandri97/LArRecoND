/**
 *  @file   larpandoracontent/LArVertex/ND_ShowerAsymmetryFeatureTool.h
 *
 *  @brief  Header file for the shower asymmetry feature tool class.
 *
 *  $Log: $
 */
#ifndef LAR_ND_SHOWER_ASYMMETRY_FEATURE_TOOL_H
#define LAR_ND_SHOWER_ASYMMETRY_FEATURE_TOOL_H 1

#include "vertex/LArNDAsymmetryFeatureBaseTool.h"

#include "larpandoracontent/LArObjects/LArTwoDSlidingFitResult.h"

namespace lar_content
{

/**
 *  @brief  ND_ShowerAsymmetryFeatureTool class
 */
class ND_ShowerAsymmetryFeatureTool : public ND_AsymmetryFeatureBaseTool
{
public:
    /**
     *  @brief  Default constructor
     */
    ND_ShowerAsymmetryFeatureTool();

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle) override;

    /**
     *  @brief  Get the shower asymmetry feature for a given view
     *
     *  @param  vertexPosition2D the projected vertex position
     *  @param  showerClusterList the list of shower clusters in this view
     *
     *  @return the shower asymmetry feature
     */
    float GetAsymmetryForView(const pandora::CartesianVector &vertexPosition2D, const ND_VertexSelectionBaseAlgorithm::SlidingFitDataList &,
        const ND_VertexSelectionBaseAlgorithm::ShowerClusterList &showerClusterList) const override;

    /**
     *  @brief  Get whether we should use a given shower cluster for asymmetry calculation
     *
     *  @param  vertexPosition the projected vertex position
     *  @param  showerCluster the shower cluster
     *
     *  @return whether the shower cluster should be considered
     */
    bool ShouldUseShowerCluster(const pandora::CartesianVector &vertexPosition, const ND_VertexSelectionBaseAlgorithm::ShowerCluster &showerCluster) const;

    float m_vertexClusterDistance; ///< The distance around the vertex to look for shower clusters
};

} // namespace lar_content

#endif // #ifndef LAR_SHOWER_ASYMMETRY_FEATURE_TOOL_H
