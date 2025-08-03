// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>
#include <vector>
#include "wpi/datalog/DataLogReader.h"
#include "wpi/datalog/DataLogReaderThread.h"

namespace wpi::log {
class DataLogEditor {
 public:
  explicit DataLogEditor(std::unique_ptr<DataLogReaderThread> reader)
      : m_reader{std::move(reader)} {}

  void Trim(int64_t start, int64_t end);
  void ExtractEntry(std::string_view name);
  void RenameEntry(std::string_view currentName, std::string_view newName);
  std::vector<DataLogRecord> ApplyEdits();

 private:
  std::unique_ptr<DataLogReaderThread> m_reader;
  std::vector<DataLogRecord> validRecords;

  int64_t startTimestamp;
  int64_t endTimestamp;
  std::string_view extractedEntryName;
  std::string_view currentEntryName;
  std::string_view newEntryName;

  bool trim = false;
  bool extract = false;
  bool rename = false;
};
}  // namespace wpi::log