/**
 *  @file   larpandoracontent/LArVertex/ND_GlobalAsymmetryFeatureTool.cc
 *
 *  @brief  Implementation of the global asymmetry feature tool class.
 *
 *  $Log: $
 */

#include "vertex/LArNDGlobalAsymmetryFeatureTool.h"
#include "Pandora/AlgorithmHeaders.h"
#include "larpandoracontent/LArHelpers/LArClusterHelper.h"
#include "larpandoracontent/LArHelpers/LArGeometryHelper.h"

using namespace pandora;

namespace lar_content
{

ND_GlobalAsymmetryFeatureTool::ND_GlobalAsymmetryFeatureTool() :
    ND_AsymmetryFeatureBaseTool()
{
}

//------------------------------------------------------------------------------------------------------------------------------------------

float ND_GlobalAsymmetryFeatureTool::GetAsymmetryForView(const CartesianVector &vertexPosition2D,
    const ND_VertexSelectionBaseAlgorithm::SlidingFitDataList &slidingFitDataList, const ND_VertexSelectionBaseAlgorithm::ShowerClusterList &) const
{
    bool useEnergy(true);
    CartesianVector energyWeightedDirectionSum(0.f, 0.f, 0.f), hitWeightedDirectionSum(0.f, 0.f, 0.f);
    ClusterVector asymmetryClusters;

    for (const ND_VertexSelectionBaseAlgorithm::SlidingFitData &slidingFitData : slidingFitDataList)
    {
        const Cluster *const pCluster(slidingFitData.GetCluster());

        asymmetryClusters.push_back(pCluster);

        if (pCluster->GetElectromagneticEnergy() < std::numeric_limits<float>::epsilon())
            useEnergy = false;

        const CartesianVector vertexToMinLayer(slidingFitData.GetMinLayerPosition() - vertexPosition2D);
        const CartesianVector vertexToMaxLayer(slidingFitData.GetMaxLayerPosition() - vertexPosition2D);

        const bool minLayerClosest(vertexToMinLayer.GetMagnitudeSquared() < vertexToMaxLayer.GetMagnitudeSquared());
        const CartesianVector &clusterDirection((minLayerClosest) ? slidingFitData.GetMinLayerDirection() : slidingFitData.GetMaxLayerDirection());

        if ((LArClusterHelper::GetClosestDistance(vertexPosition2D, pCluster) < m_maxAsymmetryDistance))
        {
            this->IncrementAsymmetryParameters(pCluster->GetElectromagneticEnergy(), clusterDirection, energyWeightedDirectionSum);
            this->IncrementAsymmetryParameters(static_cast<float>(pCluster->GetNCaloHits()), clusterDirection, hitWeightedDirectionSum);
        }
    }

    const CartesianVector &localWeightedDirectionSum(useEnergy ? energyWeightedDirectionSum : hitWeightedDirectionSum);

    if (localWeightedDirectionSum.GetMagnitudeSquared() < std::numeric_limits<float>::epsilon())
        return 0.f;

    return this->CalculateAsymmetry(useEnergy, vertexPosition2D, asymmetryClusters, localWeightedDirectionSum);
}

StatusCode ND_GlobalAsymmetryFeatureTool::ReadSettings(const TiXmlHandle xmlHandle)
{
    return ND_AsymmetryFeatureBaseTool::ReadSettings(xmlHandle);
}

} // namespace lar_content
