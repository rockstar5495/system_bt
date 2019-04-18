/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <deque>
#include <map>
#include <optional>

#include "custom_field_def.h"
#include "enum_def.h"
#include "enum_gen.h"
#include "packet_def.h"

class Declarations {
 public:
  void AddEnumDef(std::string name, EnumDef def) {
    enum_defs_.insert(std::pair(name, def));
    enum_defs_queue_.push_back(std::pair(name, def));
  }

  EnumDef* GetEnumDef(const std::string& name) {
    auto it = enum_defs_.find(name);
    if (it == enum_defs_.end()) {
      return nullptr;
    }

    return &(it->second);
  }

  void AddPacketDef(std::string name, PacketDef def) {
    packet_defs_.insert(std::pair(name, def));
    packet_defs_queue_.push_back(std::pair(name, def));
  }

  PacketDef* GetPacketDef(const std::string& name) {
    auto it = packet_defs_.find(name);
    if (it == packet_defs_.end()) {
      return nullptr;
    }

    return &(it->second);
  }

  void AddGroupDef(std::string name, FieldList* group_def) {
    group_defs_.insert(std::pair(name, group_def));
  }

  FieldList* GetGroupDef(std::string name) {
    if (group_defs_.find(name) == group_defs_.end()) {
      return nullptr;
    }

    return group_defs_.at(name);
  }

  void AddCustomFieldDef(std::string name, CustomFieldDef def) {
    custom_field_defs_.insert(std::pair(name, def));
    custom_field_defs_queue_.push_back(std::pair(name, def));
  }

  CustomFieldDef* GetCustomFieldDef(std::string name) {
    auto it = custom_field_defs_.find(name);
    if (it == custom_field_defs_.end()) {
      return nullptr;
    }

    return &(it->second);
  }

  std::map<std::string, FieldList*> group_defs_;

  std::map<std::string, EnumDef> enum_defs_;
  std::deque<std::pair<std::string, EnumDef>> enum_defs_queue_;
  std::map<std::string, PacketDef> packet_defs_;
  std::deque<std::pair<std::string, PacketDef>> packet_defs_queue_;
  std::map<std::string, CustomFieldDef> custom_field_defs_;
  std::deque<std::pair<std::string, CustomFieldDef>> custom_field_defs_queue_;
  bool is_little_endian;
};
