/**
 *  @file   larpandoracontent/LArVertex/AsymmetryFeatureBaseTool.h
 *
 *  @brief  Header file for the global asymmetry feature tool class.
 *
 *  $Log: $
 */
#ifndef LAR_ND_ASYMMETRY_FEATURE_BASE_TOOL_H
#define LAR_ND_ASYMMETRY_FEATURE_BASE_TOOL_H 1

#include "vertex/LArNDVertexSelectionBaseAlgorithm.h"

namespace lar_content
{

/**
 *  @brief  AsymmetryFeatureBaseTool class
 */
class ND_AsymmetryFeatureBaseTool : public ND_VertexSelectionBaseAlgorithm::VertexFeatureTool
{
public:
    /**
     *  @brief  Default constructor
     */
    ND_AsymmetryFeatureBaseTool();

    /**
     *  @brief  Run the tool
     *
     *  @param  pAlgorithm address of the calling algorithm
     *  @param  pVertex address of the vertex
     *  @param  slidingFitDataListMap map of the sliding fit data lists
     *  @param  showerClusterListMap map of the shower cluster lists
     *
     *  @return the asymmetry feature
     */
    void Run(LArMvaHelper::MvaFeatureVector &featureVector, const ND_VertexSelectionBaseAlgorithm *const pAlgorithm,
        const pandora::Vertex *const pVertex, const ND_VertexSelectionBaseAlgorithm::SlidingFitDataListMap &slidingFitDataListMap,
        const ND_VertexSelectionBaseAlgorithm::ClusterListMap &, const ND_VertexSelectionBaseAlgorithm::KDTreeMap &,
        const ND_VertexSelectionBaseAlgorithm::ShowerClusterListMap &showerClusterListMap, const float, float &);

protected:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    /**
     *  @brief  Get the asymmetry feature for a given view
     *
     *  @param  vertexPosition2D the vertex position projected into this view
     *  @param  slidingFitDataList the list of sliding fit data objects for this view
     *  @param  showerClusterList the list of shower cluster objects for this view
     *
     *  @return the asymmetry feature
     */
    virtual float GetAsymmetryForView(const pandora::CartesianVector &vertexPosition2D,
        const ND_VertexSelectionBaseAlgorithm::SlidingFitDataList &slidingFitDataList,
        const ND_VertexSelectionBaseAlgorithm::ShowerClusterList &showerClusterList) const = 0;

    /**
     *  @brief  Increment the asymmetry parameters
     *
     *  @param  weight the weight to assign to this vector
     *  @param  clusterDirection the direction of the cluster
     *  @param  localWeightedDirectionSum the current energy-weighted local cluster direction vector
     */
    void IncrementAsymmetryParameters(
        const float weight, const pandora::CartesianVector &clusterDirection, pandora::CartesianVector &localWeightedDirectionSum) const;

    /**
     *  @brief  Calculate the asymmetry feature
     *
     *  @param  useEnergyMetrics whether to use energy-based metrics instead of hit-counting-based metrics
     *  @param  vertexPosition2D the vertex position in this view
     *  @param  asymmetryCluster the vector of cluster objects to be used in the asymmetry calculation
     *  @param  localWeightedDirectionSum the local event axis
     *
     *  @return the asymmetry feature
     */
    virtual float CalculateAsymmetry(const bool useEnergyMetrics, const pandora::CartesianVector &vertexPosition2D,
        const pandora::ClusterVector &asymmetryClusters, const pandora::CartesianVector &localWeightedDirectionSum) const;

    float m_maxAsymmetryDistance; ///< The max distance between cluster (any hit) and vertex to calculate asymmetry score
};

} // namespace lar_content

#endif // #ifndef LAR_ASYMMETRY_FEATURE_BASE_TOOL_H
