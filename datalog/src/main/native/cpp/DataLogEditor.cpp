// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <wpi/datalog/DataLogEditor.h>
#include <cstdint>
#include <vector>
#include "wpi/datalog/DataLogReader.h"

using namespace wpi::log;

void DataLogEditor::Trim(int64_t start, int64_t end) {
  startTimestamp = start;
  endTimestamp = end;
  trim = true;
}

void DataLogEditor::ExtractEntry(std::string_view name) {
  extractedEntryName = name;
  extract = true;
}

void DataLogEditor::RenameEntry(std::string_view currentName, std::string_view newName) {
  currentEntryName = currentName;
  newEntryName = newName;
  rename = true;
}

std::vector<DataLogRecord> DataLogEditor::ApplyEdits() {
  for (const DataLogRecord& record : m_reader->GetReader()) {
    if (trim) {
      // we can't indiscriminately trim, as we have to retain start records for all entries that occur in the valid region (and any entires with no start record must have *all* records purged)
      // we can either skip *all* control records or check the trimmed period to see which entries we need and only skip those entries' control records
      // for the sake of simplicity, as of now we choose the former
      if (record.IsControl() || (record.GetTimestamp() > startTimestamp && record.GetTimestamp() < endTimestamp)) {
        validRecords.push_back(record);
      }
    }

    if (extract) {
      if (m_reader->GetEntry(record.GetEntry())->name.data() == extractedEntryName.data()) {
        validRecords.push_back(record);
      }
    }

    if (rename) {
      auto entry = m_reader->GetEntry(record.GetEntry());
      if (record.IsStart() && entry->name.data() == currentEntryName) {
        // TODO: Figure out how to rename an entry
        // we *should* just need to emit a start record with a different name...but not sure how to get the data span
        validRecords.push_back(DataLogRecord{record.GetEntry(), record.GetTimestamp(), StartRecordData{entry->entry, entry->name, entry->type, entry->metadata}});
      }
    }
  }
  return validRecords;
}