//
// Created by Andrej Redeky.
// Copyright © 2015-2023 Feldarian Softworks. All rights reserved.
// SPDX-License-Identifier: EUPL-1.2
//

#pragma once

#include <Feldarian/G1AL/Common.hpp>

namespace Feldarian::G1AL
{

namespace POD::Scenes
{

#include <Feldarian/G1AL/POD/Scenes/WHDWAV.hpp>

} // namespace POD::Scenes

namespace WHD::v1
{

using Header = POD::Scenes::WHD_Header_v1;
using DataFormat = POD::Scenes::WHD_DataFormat_v1;

struct Entry : POD::Scenes::WHD_Entry_v1
{
  Base::PCMS16::AudioDataInfo ToBaseDataInfo() const;
  bool FromBaseDataInfo(const Base::PCMS16::AudioDataInfo& baseDataInfo);
};

} // namespace WHD::v1

namespace WHD::v2
{

using Header = POD::Scenes::WHD_Header_v2;
using DataFormat = POD::Scenes::WHD_DataFormat_v2;
using EntryStreamsDistanceBasedMaster = POD::Scenes::WHD_EntryStreamsDistanceBasedMaster_v2;

struct EntryScenes : POD::Scenes::WHD_EntryScenes_v2
{
  Base::PCMS16::AudioDataInfo ToBaseDataInfo() const;
  bool FromBaseDataInfo(const Base::PCMS16::AudioDataInfo& baseDataInfo);
};

struct EntryStreams : POD::Scenes::WHD_EntryStreams_v2
{
  Base::PCMS16::AudioDataInfo ToBaseDataInfo() const;
  bool FromBaseDataInfo(const Base::PCMS16::AudioDataInfo& baseDataInfo);
};

struct EntryStreamsDistanceBased : POD::Scenes::WHD_EntryStreamsDistanceBased_v2
{
  Base::PCMS16::AudioDataInfo ToBaseDataInfo() const;
  bool FromBaseDataInfo(const Base::PCMS16::AudioDataInfo& baseDataInfo);
};

} // namespace WHD::v2

namespace WAV::v2
{

using Header = POD::Scenes::WAV_Header_v2;

} // namespace WAV::v2

} // namespace Feldarian::G1AL
