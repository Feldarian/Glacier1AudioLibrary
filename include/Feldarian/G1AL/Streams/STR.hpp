//
// Created by Andrej Redeky.
// Copyright © 2015-2023 Feldarian Softworks. All rights reserved.
// SPDX-License-Identifier: EUPL-1.2
//

#pragma once

#include <Feldarian/G1AL/Common.hpp>

namespace Feldarian::G1AL
{

namespace POD::Streams
{

#include <Feldarian/G1AL/POD/Streams/STR.hpp>

} // namespace POD::Streams

namespace STR::v1
{

using LanguageID = POD::Streams::STR_LanguageID_v1;
using Header = POD::Streams::STR_Header_v1;
using DataFormat = POD::Streams::STR_DataFormat_v1;
using Entry = POD::Streams::STR_Entry_v1;

struct DataHeader : POD::Streams::STR_DataHeader_v1
{
  Base::PCMS16::AudioDataInfo ToBaseDataInfo() const;
  bool FromBaseDataInfo(const Base::PCMS16::AudioDataInfo& soundRecord);
};

} // namespace STR::v1

namespace STR::v2
{

using LanguageID = POD::Streams::STR_LanguageID_v2;
using Header = POD::Streams::STR_Header_v2;
using DataFormat = POD::Streams::STR_DataFormat_v2;
using Entry = POD::Streams::STR_Entry_v2;

struct DataHeader : POD::Streams::STR_DataHeader_v2
{
  Base::PCMS16::AudioDataInfo ToBaseDataInfo() const;
  bool FromBaseDataInfo(const Base::PCMS16::AudioDataInfo& soundRecord);
};

} // namespace STR::v2

} // namespace Feldarian::G1AL
