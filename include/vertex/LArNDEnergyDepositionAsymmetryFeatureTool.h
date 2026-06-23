/**
 *  @file   larpandoracontent/LArVertex/EnergyDepositionAsymmetryFeatureTool.h
 *
 *  @brief  Header file for the energy deposition asymmetry feature tool class.
 *
 *  $Log: $
 */
#ifndef LAR_ND_ENERGY_DEPOSITION_ASYMMETRY_FEATURE_TOOL_H
#define LAR_ND_ENERGY_DEPOSITION_ASYMMETRY_FEATURE_TOOL_H 1

#include "vertex/LArNDGlobalAsymmetryFeatureTool.h"

namespace lar_content
{

/**
 *  @brief  EnergyDepositionAsymmetryFeatureTool class
 */
class ND_EnergyDepositionAsymmetryFeatureTool : public ND_GlobalAsymmetryFeatureTool
{
public:
    /**
     *  @brief  Default constructor
     */
    ND_EnergyDepositionAsymmetryFeatureTool();

private:
    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle) override;

    /**
     *  @brief  Calculate the energy deposition asymmetry feature
     *
     *  @param  useEnergyMetrics whether to use energy-based metrics instead of hit-counting-based metrics
     *  @param  vertexPosition2D the vertex position in this view
     *  @param  slidingFitDataList the list of sliding fit data objects
     *  @param  localWeightedDirectionSum the local event axis
     *
     *  @return the energy deposition asymmetry feature
     */
    float CalculateAsymmetry(const bool useEnergyMetrics, const pandora::CartesianVector &vertexPosition2D,
        const pandora::ClusterVector &clusterVector, const pandora::CartesianVector &localWeightedDirectionSum) const override;
};

} // namespace lar_content

#endif // #ifndef LAR_ENERGY_DEPOSITION_ASYMMETRY_FEATURE_TOOL_H
