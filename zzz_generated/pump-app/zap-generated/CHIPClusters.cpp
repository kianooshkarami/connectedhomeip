/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
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

// THIS FILE IS GENERATED BY ZAP

#include "CHIPClusters.h"

#include <cstdint>

#include <support/BufferWriter.h>
#include <support/SafeInt.h>
#include <support/logging/CHIPLogging.h>
#include <system/SystemPacketBuffer.h>

#include <app/chip-zcl-zpro-codec.h>
#include <app/common/gen/ids/Attributes.h>
#include <app/util/basic-types.h>

#include <app/InteractionModelEngine.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/SafeInt.h>
#include <zap-generated/CHIPClientCallbacks.h>

#define COMMAND_HEADER(name, clusterId)                                                                                            \
    const char * kName = name;                                                                                                     \
    uint8_t seqNum     = mDevice->GetNextSequenceNumber();                                                                         \
                                                                                                                                   \
    PacketBufferWriter buf(System::PacketBufferHandle::New(kMaxBufferSize));                                                       \
    if (buf.IsNull())                                                                                                              \
    {                                                                                                                              \
        ChipLogError(Zcl, "Could not allocate packet buffer while trying to encode %s command", kName);                            \
        return CHIP_ERROR_INTERNAL;                                                                                                \
    }                                                                                                                              \
                                                                                                                                   \
    if (doEncodeApsFrame(buf, clusterId, kSourceEndpoint, mEndpoint, 0, 0, 0, 0, false))                                           \
    {

#define COMMAND_FOOTER()                                                                                                           \
    }                                                                                                                              \
    if (!buf.Fit())                                                                                                                \
    {                                                                                                                              \
        ChipLogError(Zcl, "Command %s can't fit in the allocated buffer", kName);                                                  \
    }                                                                                                                              \
    return SendCommand(seqNum, buf.Finalize(), onSuccessCallback, onFailureCallback);

namespace chip {
namespace {
// TODO: Find a way to calculate maximum message length for clusters
//       https://github.com/project-chip/connectedhomeip/issues/965
constexpr uint16_t kMaxBufferSize = 1024;

// This is a global command, so the low bits are 0b00.  The command is
// standard, so does not need a manufacturer code, and we're sending client
// to server, so all the remaining bits are 0.
constexpr uint8_t kFrameControlGlobalCommand = 0x00;

// Pick source endpoint as 1 for now
constexpr EndpointId kSourceEndpoint = 1;

const uint8_t kReportingDirectionReported = 0x00;
} // namespace

using namespace app::Clusters;
using namespace System;
using namespace Encoding::LittleEndian;

namespace Controller {

// TODO(#4502): onCompletion is not used by IM for now.
// TODO(#4503): length should be passed to commands when byte string is in argument list.
// TODO(#4503): Commands should take group id as an argument.

// FlowMeasurement Cluster Commands
// FlowMeasurement Cluster Attributes
CHIP_ERROR FlowMeasurementCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                      Callback::Cancelable * onFailureCallback)
{
    COMMAND_HEADER("DiscoverFlowMeasurementAttributes", FlowMeasurement::Id);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(Globals::Commands::Ids::DiscoverAttributes).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

CHIP_ERROR FlowMeasurementCluster::ReadAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                              Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000000;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR FlowMeasurementCluster::ConfigureAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                   Callback::Cancelable * onFailureCallback, uint16_t minInterval,
                                                                   uint16_t maxInterval, int16_t change)
{
    COMMAND_HEADER("ReportFlowMeasurementMeasuredValue", FlowMeasurement::Id);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(Globals::Commands::Ids::ConfigureReporting)
        .Put8(kReportingDirectionReported)
        .Put32(FlowMeasurement::Attributes::Ids::MeasuredValue)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

CHIP_ERROR FlowMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(0x0000, onReportCallback);
}

CHIP_ERROR FlowMeasurementCluster::ReadAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                 Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000001;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR FlowMeasurementCluster::ReadAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                 Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000002;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR FlowMeasurementCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x0000FFFD;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16uAttributeCallback>);
}

// PressureMeasurement Cluster Commands
// PressureMeasurement Cluster Attributes
CHIP_ERROR PressureMeasurementCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                          Callback::Cancelable * onFailureCallback)
{
    COMMAND_HEADER("DiscoverPressureMeasurementAttributes", PressureMeasurement::Id);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(Globals::Commands::Ids::DiscoverAttributes).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

CHIP_ERROR PressureMeasurementCluster::ReadAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                  Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000000;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR PressureMeasurementCluster::ConfigureAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                       Callback::Cancelable * onFailureCallback,
                                                                       uint16_t minInterval, uint16_t maxInterval, int16_t change)
{
    COMMAND_HEADER("ReportPressureMeasurementMeasuredValue", PressureMeasurement::Id);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(Globals::Commands::Ids::ConfigureReporting)
        .Put8(kReportingDirectionReported)
        .Put32(PressureMeasurement::Attributes::Ids::MeasuredValue)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

CHIP_ERROR PressureMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(0x0000, onReportCallback);
}

CHIP_ERROR PressureMeasurementCluster::ReadAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                     Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000001;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR PressureMeasurementCluster::ReadAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                     Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000002;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR PressureMeasurementCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                    Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x0000FFFD;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16uAttributeCallback>);
}

// TemperatureMeasurement Cluster Commands
// TemperatureMeasurement Cluster Attributes
CHIP_ERROR TemperatureMeasurementCluster::DiscoverAttributes(Callback::Cancelable * onSuccessCallback,
                                                             Callback::Cancelable * onFailureCallback)
{
    COMMAND_HEADER("DiscoverTemperatureMeasurementAttributes", TemperatureMeasurement::Id);
    buf.Put8(kFrameControlGlobalCommand).Put8(seqNum).Put32(Globals::Commands::Ids::DiscoverAttributes).Put32(0x0000).Put8(0xFF);
    COMMAND_FOOTER();
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                     Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000000;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR TemperatureMeasurementCluster::ConfigureAttributeMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                          Callback::Cancelable * onFailureCallback,
                                                                          uint16_t minInterval, uint16_t maxInterval,
                                                                          int16_t change)
{
    COMMAND_HEADER("ReportTemperatureMeasurementMeasuredValue", TemperatureMeasurement::Id);
    buf.Put8(kFrameControlGlobalCommand)
        .Put8(seqNum)
        .Put32(Globals::Commands::Ids::ConfigureReporting)
        .Put8(kReportingDirectionReported)
        .Put32(TemperatureMeasurement::Attributes::Ids::MeasuredValue)
        .Put8(41)
        .Put16(minInterval)
        .Put16(maxInterval);
    buf.Put16(static_cast<uint16_t>(change));
    COMMAND_FOOTER();
}

CHIP_ERROR TemperatureMeasurementCluster::ReportAttributeMeasuredValue(Callback::Cancelable * onReportCallback)
{
    return RequestAttributeReporting(0x0000, onReportCallback);
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMinMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                        Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000001;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeMaxMeasuredValue(Callback::Cancelable * onSuccessCallback,
                                                                        Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x00000002;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16sAttributeCallback>);
}

CHIP_ERROR TemperatureMeasurementCluster::ReadAttributeClusterRevision(Callback::Cancelable * onSuccessCallback,
                                                                       Callback::Cancelable * onFailureCallback)
{
    app::AttributePathParams attributePath;
    attributePath.mEndpointId = mEndpoint;
    attributePath.mClusterId  = mClusterId;
    attributePath.mFieldId    = 0x0000FFFD;
    attributePath.mFlags.Set(app::AttributePathParams::Flags::kFieldIdValid);
    return mDevice->SendReadAttributeRequest(attributePath, onSuccessCallback, onFailureCallback,
                                             BasicAttributeFilter<Int16uAttributeCallback>);
}

} // namespace Controller
} // namespace chip