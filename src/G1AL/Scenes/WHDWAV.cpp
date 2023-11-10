//
// Created by Andrej Redeky.
// Copyright © 2015-2023 Feldarian Softworks. All rights reserved.
// SPDX-License-Identifier: EUPL-1.2
//

#include <Feldarian/G1AL/Scenes/WHDWAV.hpp>

namespace Feldarian::G1AL
{

using namespace Base::PCMS16;

namespace WHD::v1
{

AudioDataInfo Entry::ToBaseDataInfo() const
{
  if (format == DataFormat::INVALID)
    return {};

  return {
    0,
    dataSizeUncompressed,
    dataSize,
    sampleRate,
    static_cast<AudioDataFormat>(format),
    static_cast<uint16_t>(bitsPerSample),
    static_cast<uint16_t>(channels),
    static_cast<uint16_t>(blockAlign),
    static_cast<uint16_t>(samplesPerBlock)
  };
}

bool Entry::FromBaseDataInfo(const AudioDataInfo &baseDataInfo)
{
  if (baseDataInfo.format == AudioDataFormat::INVALID || baseDataInfo.format == AudioDataFormat::UNKNOWN_SUPPORTED)
    return false;
  
  format = static_cast<DataFormat>(baseDataInfo.format);
  sampleRate = baseDataInfo.sampleRate;
  bitsPerSample = baseDataInfo.bitsPerSample;
  dataSizeUncompressed = baseDataInfo.dataSizeUncompressed;
  dataSize = baseDataInfo.dataSize;
  channels = baseDataInfo.channels;
  samplesCount = baseDataInfo.dataSizeUncompressed / sizeof(int16_t);
  blockAlign = baseDataInfo.blockAlign;
  samplesPerBlock = baseDataInfo.samplesPerBlock;

  return true;
}

} // namespace WHD::v1

namespace WHD::v2
{

AudioDataInfo EntryScenes::ToBaseDataInfo() const
{
  if (format == DataFormat::INVALID)
    return {};

  if (format == DataFormat::OGG_VORBIS)
    return {};
  
  return {
    0,
    dataSizeUncompressed,
    dataSize,
    sampleRate,
    static_cast<AudioDataFormat>(format),
    static_cast<uint16_t>(bitsPerSample == 0 ? sizeof(int16_t) * 8 : bitsPerSample),
    static_cast<uint16_t>(channels),
    static_cast<uint16_t>(blockAlign == 0 ? sizeof(int16_t) * channels : blockAlign),
    static_cast<uint16_t>(format == DataFormat::IMA_ADPCM ? samplesPerBlock : channels)
  };
}

bool EntryScenes::FromBaseDataInfo(const AudioDataInfo &baseDataInfo)
{
  if (baseDataInfo.format == AudioDataFormat::INVALID || baseDataInfo.format == AudioDataFormat::UNKNOWN_SUPPORTED)
    return false;

  if (baseDataInfo.format == AudioDataFormat::OGG_VORBIS)
    return {};
  
  format = static_cast<DataFormat>(baseDataInfo.format);
  sampleRate = baseDataInfo.sampleRate;
  bitsPerSample = baseDataInfo.bitsPerSample;
  dataSizeUncompressed = baseDataInfo.dataSizeUncompressed;
  dataSize = baseDataInfo.dataSize;
  channels = baseDataInfo.channels;
  samplesCount = static_cast<uint32_t>(baseDataInfo.dataSizeUncompressed / sizeof(int16_t));
  blockAlign = baseDataInfo.blockAlign;
  samplesPerBlock = baseDataInfo.format == AudioDataFormat::PCM_S16 ? 0xCDCDCDCDu : baseDataInfo.samplesPerBlock;

  return true;
}

AudioDataInfo EntryStreams::ToBaseDataInfo() const
{
  if (format == DataFormat::INVALID)
    return {};

  return {
    0,
    dataSizeUncompressed,
    dataSize,
    sampleRate,
    static_cast<AudioDataFormat>(format),
    static_cast<uint16_t>(format == DataFormat::OGG_VORBIS || bitsPerSample == 0 ? sizeof(int16_t) * 8 : bitsPerSample),
    static_cast<uint16_t>(channels),
    static_cast<uint16_t>(format == DataFormat::OGG_VORBIS || blockAlignOrUnknown == 0 ? sizeof(int16_t) * channels : blockAlignOrUnknown),
    static_cast<uint16_t>(format == DataFormat::IMA_ADPCM ? samplesPerBlock : channels)
  };
}

bool EntryStreams::FromBaseDataInfo(const AudioDataInfo &baseDataInfo)
{
  if (baseDataInfo.format == AudioDataFormat::INVALID || baseDataInfo.format == AudioDataFormat::UNKNOWN_SUPPORTED)
    return false;
  
  format = static_cast<DataFormat>(baseDataInfo.format);
  sampleRate = baseDataInfo.sampleRate;
  bitsPerSample = baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? 0u : baseDataInfo.bitsPerSample;
  dataSizeUncompressed = baseDataInfo.dataSizeUncompressed;
  dataSize = baseDataInfo.dataSize;
  channels = baseDataInfo.channels;
  samplesCount = static_cast<uint32_t>(baseDataInfo.dataSizeUncompressed / sizeof(int16_t));
  blockAlignOrUnknown = baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? 0u : baseDataInfo.blockAlign;
  samplesPerBlock = baseDataInfo.format == AudioDataFormat::OGG_VORBIS ? 0x004F3E93u : (baseDataInfo.format == AudioDataFormat::PCM_S16 ? 0xCDCDCDCDu : baseDataInfo.samplesPerBlock);

  return true;
}

AudioDataInfo EntryStreamsDistanceBased::ToBaseDataInfo() const
{
  if (format != DataFormat::PCM_S16)
    return {};
  
  return {
    0,
    dataSizeUncompressed,
    dataSize,
    sampleRate,
    static_cast<AudioDataFormat>(format),
    static_cast<uint16_t>(bitsPerSample == 0 ? sizeof(int16_t) * 8 : bitsPerSample),
    static_cast<uint16_t>(channels),
    static_cast<uint16_t>(blockAlign == 0 ? sizeof(int16_t) * channels : blockAlign),
    static_cast<uint16_t>(channels)
  };
}

bool EntryStreamsDistanceBased::FromBaseDataInfo(const AudioDataInfo &baseDataInfo)
{
  if (baseDataInfo.format == AudioDataFormat::INVALID || baseDataInfo.format == AudioDataFormat::UNKNOWN_SUPPORTED)
    return false;

  if (baseDataInfo.format != AudioDataFormat::PCM_S16)
    return false;

  format = static_cast<DataFormat>(baseDataInfo.format);
  sampleRate = baseDataInfo.sampleRate;
  bitsPerSample = baseDataInfo.bitsPerSample;
  dataSizeUncompressed = baseDataInfo.dataSizeUncompressed;
  dataSize = baseDataInfo.dataSize;
  channels = baseDataInfo.channels;
  samplesCount = static_cast<uint32_t>(baseDataInfo.dataSizeUncompressed / sizeof(int16_t));
  blockAlign = baseDataInfo.blockAlign;
  samplesPerBlock = baseDataInfo.format == AudioDataFormat::PCM_S16 ? 0xCDCDCDCDu : baseDataInfo.samplesPerBlock;

  return true;
}

} // namespace WHD::v2

} // namespace Feldarian::G1AL
