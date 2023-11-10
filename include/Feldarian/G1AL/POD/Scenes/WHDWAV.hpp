//
// Created by Andrej Redeky.
// SPDX-License-Identifier: Unlicense
//
// Extended format information: TBD
//

#pragma once

#include <cstdint>

//
// WHD section
//
// Quick notes until extended format information is present:
// - from V1 onward, header has exactly the same format and size, first entry always starts at offset 0x10
// - always has null-terminated filenames before WHD entries (apart from Freedom Fighters)
// - V1 filenames are aligned on 4-bytes for Hitman: Contracts (exclusive, so if size with null-terminator is 16 for example, total size for the filename is 20 in file)
// - V2 has minimal entry size of 0x40 (WHD_EntryScenes_v2 and WHD_EntryStreams_v2) and maximum of 0x70 (WHD_EntryStreamsDistanceBasedMaster_v2), entries are always padded with zeroes to fit these sizes
// - V2 has filenames of all entries aligned on 16-bytes (inclusive, so if size with null-terminator is 16 for example, total size for the filename is 16 in file)
// - V3 filename offsets seem to be 0, needs checking (TODO)
//
// V1 is for Hitman 2: Silent Assassin, Freedom Fighters and Hitman: Contracts
// V2 is for Hitman: Blood Money
// V3 is for Kane & Lynch: Dead Men and Mini Ninjas (TODO - missing information + headers!)
// V4 is for Kane & Lynch 2: Dog Days (TODO - missing information + headers!)
//

struct WHD_Header_v1
{
  uint32_t fileSizeMinus8 = 0; // total file size - 0x8 for some reason
  uint32_t fileSize = 0; // total file size
  uint8_t unk8[0x8]; // always seems to be a sequence 03 00 00 00 04 00 00 00
};

enum class WHD_DataFormat_v1 : uint16_t
{
  INVALID = 0x00,
  PCM_S16 = 0x01,
  IMA_ADPCM = 0x11,
  OGG_VORBIS = 0x1000
};

struct WHD_Entry_v1
{
  uint32_t magic = 6; // always 6
  uint32_t fileNameOffset = 0; // offset to null-terminated file name, filename offset may be 0 in which case it is not present in WHD file
  WHD_DataFormat_v1 format = WHD_DataFormat_v1::INVALID;
  uint16_t dataInStreams = 0; // either 0 when data is present in scene WAV file or 0x8000 when it is present in streams file
  uint32_t sampleRate = 0;
  uint32_t bitsPerSample = 0;
  uint32_t dataSizeUncompressed = 0; // uncompressed data size, equal dataSize when format == 1
  uint32_t dataSize = 0;
  uint32_t channels = 0;
  uint32_t dataOffset = 0; // offset of data, depending on dataInStreams value, is offset in streams file or scene WAV file
  uint32_t samplesCount = 0; // always half of dataSizeUncompressed
  uint32_t blockAlign = 0;
  uint32_t samplesPerBlock = 0;  // always 1 when format == 1
};

using WHD_Header_v2 = WHD_Header_v1;

using WHD_DataFormat_v2 = WHD_DataFormat_v1;

struct WHD_EntryScenes_v2
{
  uint32_t fileNameLength;
  uint32_t fileNameOffset;
  WHD_DataFormat_v2 format;
  uint16_t dataInStreams; // always 0
  uint32_t sampleRate;
  uint32_t bitsPerSample;
  uint32_t dataSizeUncompressed;
  uint32_t dataSize;
  uint32_t channels;
  uint32_t dataOffset;
  uint32_t samplesCount;
  uint32_t blockAlign;
  uint32_t samplesPerBlock;
  uint8_t pad30[0x10]; // in WHD, has additional padding bytes filled with zeroes without exceptions
};

struct WHD_EntryStreamsDistanceBased_v2
{
  uint32_t id; // always 0
  uint32_t fileNameOffset;
  WHD_DataFormat_v2 format; // always 0x01 PCM
  uint16_t dataInStreams; // always has 0x80 set, 0xFF00 mask differs, either 0x8200 or 0x0100, other values not found, exact purpose yet unknown, but 0x8200 comes first (padding not zeroed), 0x0100 second (padding zeroed)
  uint32_t sampleRate;
  uint32_t bitsPerSample;
  uint32_t dataSizeUncompressed;
  uint32_t dataSize;
  uint32_t channels;
  uint32_t dataOffset; // may start with "LIP " (0x2050494C) chunk, read like described under STR format (LIP data is ONLY in STR files)
  uint32_t samplesCount;
  uint32_t blockAlign; // always 0
  uint32_t samplesPerBlock; // always 0
  uint32_t unk30; // not always 0, purpose unknown
};

struct WHD_EntryStreamsDistanceBasedMaster_v2
{
  WHD_EntryStreamsDistanceBased_v2 subEntries;
  uint8_t pad68[0x8];  // in WHD, has additional padding bytes filled with zeroes without exceptions
};

struct WHD_EntryStreams_v2
{
  uint32_t id; // always "PHO\0" (0x004F4850)
  uint32_t filePathOffset;
  WHD_DataFormat_v2 format; // 0x01 - PCM 16-bit, 0x11 - IMA ADPCM, 0x1000 - OGG
  uint16_t dataInStreams; // always 0x80, 0xFF00 mask is always 0
  uint32_t sampleRate;
  uint32_t bitsPerSample; // 0 for OGG
  uint32_t dataSizeUncompressed;
  uint32_t dataSize;
  uint32_t channels;
  uint32_t dataOffset; // may start with "LIP " (0x2050494C) chunk, read like described under STR format (LIP data is ONLY in STR files)
  uint32_t samplesCount;
  uint32_t blockAlignOrUnknown; // unknown value for OGG, block align for PCM adn ADPCM
  uint32_t samplesPerBlock; // 0xCDCDCDCD for PCMs, 0x07f9 for ADPCM, 0x004F3E93 for OGG...
  uint16_t hasLIP; // this is either 0x00 or 0x04, if it is 0x04 then LIP data is present
  uint16_t unk32; // this always has some value when LIP data is present, 0x0000 otherwise
  uint8_t pad34[0xC]; // in WHD, has additional padding bytes filled with zeroes without exceptions
};

//
// WAV section
//
// Quick notes until extended format information is present:
// - V1 has two different scene formats, Pack.WAV which has all the data, no Repeat.WAV used, and PackRepeat.WAV which references data in Repeat.WAV)
// - from V2, all of the Glacier 1 games had same header for scenes WAV and all started their data at 0x10 offset
//
// V1 is for Hitman: Codename 47 (TODO - missing information + headers!)
// V2 is for Hitman 2: Silent Assassin, Freedom Fighters, Hitman: Contracts, Hitman: Blood Money, Kane & Lynch: Dead Men, Mini Ninjas and Kane & Lynch 2: Dog Days
//

struct WAV_Header_v2
{
  uint32_t unk0; // always 0
  uint32_t fileSize; // total file size
  uint32_t unk8; // always 3
  uint32_t unkC; // always 4
};
