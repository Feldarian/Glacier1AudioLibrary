//
// Created by Andrej Redeky.
// Copyright © 2015-2023 Feldarian Softworks. All rights reserved.
// SPDX-License-Identifier: EUPL-1.2
//

#include <Feldarian/G1AL/Streams/STR.hpp>

namespace Feldarian::G1AL
{

using namespace Base::PCMS16;

namespace STR::v1
{

AudioDataInfo DataHeader::ToBaseDataInfo() const
{
  if (format == DataFormat::INVALID || format == DataFormat::DISTANCE_BASED_MASTER)
    return {};

  return {
    0,
    static_cast<uint32_t>(samplesCount * sizeof(int16_t)),
    0, // must be filled externally, cannot deduce from this header alone...
    sampleRate,
    format == DataFormat::IMA_ADPCM ? AudioDataFormat::IMA_ADPCM : (format == DataFormat::OGG_VORBIS ? AudioDataFormat::OGG_VORBIS : AudioDataFormat::PCM_S16),
    static_cast<uint16_t>(bitsPerSample ? bitsPerSample : 16),
    static_cast<uint16_t>(channels),
    static_cast<uint16_t>(format == DataFormat::IMA_ADPCM && blockAlign ? blockAlign : channels * ((bitsPerSample ? bitsPerSample : 16) / 8)),
    static_cast<uint16_t>(samplesPerBlock ? samplesPerBlock : channels)
  };
}

bool DataHeader::FromBaseDataInfo(const AudioDataInfo &baseDataInfo)
{
  if (baseDataInfo.format == AudioDataFormat::INVALID || baseDataInfo.format == AudioDataFormat::UNKNOWN_SUPPORTED)
    return false;

  if (format == DataFormat::DISTANCE_BASED_MASTER && baseDataInfo.format != AudioDataFormat::PCM_S16)
    return false;
  
  format = baseDataInfo.format == AudioDataFormat::IMA_ADPCM ? DataFormat::IMA_ADPCM : (baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? DataFormat::OGG_VORBIS : DataFormat::PCM_S16);
  samplesCount = static_cast<uint32_t>(baseDataInfo.dataSizeUncompressed / sizeof(int16_t));
  channels = baseDataInfo.channels;
  sampleRate = baseDataInfo.sampleRate;
  bitsPerSample = baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? 0u : baseDataInfo.bitsPerSample;
  blockAlign = baseDataInfo.format == AudioDataFormat::PCM_S16 || baseDataInfo.format == AudioDataFormat::IMA_ADPCM ? baseDataInfo.blockAlign : 0u;
  samplesPerBlock = baseDataInfo.format == AudioDataFormat::IMA_ADPCM ? baseDataInfo.samplesPerBlock : 0u;

  return true;
}

} // namespace STR::v1

namespace STR::v2
{

AudioDataInfo DataHeader::ToBaseDataInfo() const
{
  if (format == DataFormat::INVALID || format == DataFormat::UNKNOWN_MASTER)
    return {};

  return {
    0,
    static_cast<uint32_t>(samplesCount * sizeof(int16_t)),
    0, // must be filled externally, cannot deduce from this header alone...
    sampleRate,
    format == DataFormat::IMA_ADPCM ? AudioDataFormat::IMA_ADPCM : (format == DataFormat::OGG_VORBIS ? AudioDataFormat::OGG_VORBIS : AudioDataFormat::PCM_S16),
    static_cast<uint16_t>(bitsPerSample ? bitsPerSample : 16),
    static_cast<uint16_t>(channels),
    static_cast<uint16_t>(format == DataFormat::IMA_ADPCM && blockAlign ? blockAlign : channels * ((bitsPerSample ? bitsPerSample : 16) / 8)),
    static_cast<uint16_t>(samplesPerBlock ? samplesPerBlock : channels)
  };
}

bool DataHeader::FromBaseDataInfo(const AudioDataInfo &baseDataInfo)
{
  if (baseDataInfo.format == AudioDataFormat::INVALID || baseDataInfo.format == AudioDataFormat::UNKNOWN_SUPPORTED)
    return false;

  if (format == DataFormat::UNKNOWN_MASTER)
    return false;
  
  format = baseDataInfo.format == AudioDataFormat::IMA_ADPCM ? DataFormat::IMA_ADPCM : (baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? DataFormat::OGG_VORBIS : DataFormat::PCM_S16);
  samplesCount = static_cast<uint32_t>(baseDataInfo.dataSizeUncompressed / sizeof(int16_t));
  channels = baseDataInfo.channels;
  sampleRate = baseDataInfo.sampleRate;
  bitsPerSample = baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? 0u : baseDataInfo.bitsPerSample;
  blockAlign = baseDataInfo.format == AudioDataFormat::PCM_S16 || baseDataInfo.format == AudioDataFormat::IMA_ADPCM ? baseDataInfo.blockAlign : 0u;
  samplesPerBlock = baseDataInfo.format == AudioDataFormat::IMA_ADPCM ? baseDataInfo.samplesPerBlock : 0u;

  return true;
}

} // namespace STR::v2

} // namespace Feldarian::G1AL
