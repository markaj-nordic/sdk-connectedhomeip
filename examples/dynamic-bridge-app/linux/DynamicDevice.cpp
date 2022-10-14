/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    Copyright (c) 2019 Google LLC.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "DynamicDevice.h"

#define DEVICE_TYPE_BRIDGED_NODE 0x0013
// Device Version for dynamic endpoints:
#define DEVICE_VERSION_DEFAULT 1

DynamicDevice::DynamicDevice() {}

void DynamicDevice::AddDeviceType(EmberAfDeviceType type)
{
    mDeviceTypes.push_back(type);
}

Device DynamicDevice::CreateDevice()
{
    // All nodes are bridged devices.
    mDeviceTypes.push_back(EmberAfDeviceType{ DEVICE_TYPE_BRIDGED_NODE, DEVICE_VERSION_DEFAULT });
    mVersions.resize(mClusterRawPtrs.size());
    for (auto * c : mClusterRawPtrs)
        mClusterBaseRawPtrs.push_back(c);

    return Device(chip::Span<chip::DataVersion>(mVersions.data(), mVersions.size()),
                  chip::Span<EmberAfCluster>(mClusterDecls.data(), mClusterDecls.size()),
                  chip::Span<ClusterInterface *>(mClusterBaseRawPtrs.data(), mClusterBaseRawPtrs.size()),
                  chip::Span<EmberAfDeviceType>(mDeviceTypes.data(), mDeviceTypes.size()), mParentEndpointId);
}

DynamicDevice & DynamicDevice::AddCluster(std::unique_ptr<CommonCluster> cluster,
                                          const chip::Span<EmberAfAttributeMetadata> & attribs,
                                          const chip::CommandId * incomingCommands, const chip::CommandId * outgoingCommands)
{
    AddCluster(cluster.get(), attribs, incomingCommands, outgoingCommands);
    mClusters.emplace_back(std::move(cluster));
    return *this;
}

DynamicDevice & DynamicDevice::AddCluster(CommonCluster * cluster, const chip::Span<EmberAfAttributeMetadata> & attribs,
                                          const chip::CommandId * incomingCommands, const chip::CommandId * outgoingCommands)
{
    // Do what DECLARE_DYNAMIC_CLUSTER does.
    mClusterDecls.emplace_back(EmberAfCluster{ cluster->GetClusterId(), attribs.data(), (uint16_t) attribs.size(), 0,
                                               ZAP_CLUSTER_MASK(SERVER), nullptr, incomingCommands, outgoingCommands });
    mClusterRawPtrs.emplace_back(cluster);
    return *this;
}

DynamicDevice & DynamicDevice::AddCluster(std::unique_ptr<DynamicCluster> cluster)
{
    auto ptr = cluster.get();
    return AddCluster(std::move(cluster),
                      chip::Span<EmberAfAttributeMetadata>(ptr->mAttributeDecls.data(), ptr->mAttributeDecls.size()),
                      ptr->mIncomingCommands, ptr->mOutgoingCommands);
}
