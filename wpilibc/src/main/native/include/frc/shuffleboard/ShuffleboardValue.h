// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <memory>
#include <string>
#include <string_view>

#include <networktables/NetworkTable.h>

namespace frc {

class ShuffleboardValue {
 public:
  explicit ShuffleboardValue(std::string_view title) : m_title(title) {}

  virtual ~ShuffleboardValue() = default;

  ShuffleboardValue(const ShuffleboardValue&) = delete;
  ShuffleboardValue& operator=(const ShuffleboardValue&) = delete;

  /**
   * Gets the title of this Shuffleboard value.
   */
  const std::string& GetTitle() const { return m_title; }

  /**
   * Builds the entries for this value.
   *
   * @param parentTable The table containing all the data for the parent. Values
   *                    that require a complex entry or table structure should
   *                    call {@code parentTable.getSubtable(getTitle())} to get
   *                    the table to put data into. Values that only use a
   *                    single entry should call
   *                    {@code parentTable.getEntry(getTitle())} to get that
   *                    entry.
   * @param metaTable   The table containing all the metadata for this value and
   *                    its sub-values
   */
  virtual void BuildInto(std::shared_ptr<nt::NetworkTable> parentTable,
                         std::shared_ptr<nt::NetworkTable> metaTable) = 0;

  /**
   * Enables user control of this widget in the Shuffleboard application.
   *
   * This method is package-private to prevent users from enabling control
   * themselves. Has no effect if the sendable is not marked as an actuator with
   * SendableBuilder::SetActuator().
   */
  virtual void EnableIfActuator() {}

  /**
   * Disables user control of this widget in the Shuffleboard application.
   *
   * This method is package-private to prevent users from enabling control
   * themselves. Has no effect if the sendable is not marked as an actuator with
   * SendableBuilder::SetActuator().
   */
  virtual void DisableIfActuator() {}

 private:
  std::string m_title;
};

}  // namespace frc
