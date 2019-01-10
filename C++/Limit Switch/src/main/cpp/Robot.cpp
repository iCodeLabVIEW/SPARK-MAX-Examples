/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/smartdashboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "rev/CANSparkMax.h"

class Robot : public frc::TimedRobot {
  // initialize SPARK MAX with CAN ID
  static const int deviceID = 1;
  rev::CANSparkMax m_motor{deviceID, rev::CANSparkMax::MotorType::kBrushless};

  /**
   * A CANDigitalInput object is constructed using the GetForwardLimitSwitch() or
   * GetReverseLimitSwitch() method on an existing CANSparkMax object, depending
   * on which direction you would like to limit
   * 
   * Limit switches can be configured to one of two polarities:
   *  rev::CANDigitalInput::LimitSwitchPolarity::kNormallyOpen
   *  rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed
   */
  rev::CANDigitalInput m_forwardLimit = m_motor.GetForwardLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);
  rev::CANDigitalInput m_reverseLimit = m_motor.GetReverseLimitSwitch(rev::CANDigitalInput::LimitSwitchPolarity::kNormallyClosed);

  frc::SendableChooser<std::string> m_enableChooserForward;
  frc::SendableChooser<std::string> m_enableChooserReverse;
  const std::string kEnable = "Enable";
  const std::string kDisable = "Disable";

  frc::Joystick m_stick{0};

 public:
  void RobotInit() {
    m_enableChooserForward.SetDefaultOption(kEnable, kEnable);
    m_enableChooserForward.AddOption(kDisable, kDisable);
    frc::SmartDashboard::PutData("Enable Forward Limit", &m_enableChooserForward);

    m_enableChooserReverse.SetDefaultOption(kEnable, kEnable);
    m_enableChooserReverse.AddOption(kDisable, kDisable);
    frc::SmartDashboard::PutData("Enable Reverse Limit", &m_enableChooserReverse);
  }
  void TeleopPeriodic() {
    m_motor.Set(m_stick.GetY());

    /**
     * Limit switches are enabled by default when the are intialized. They can be disabled
     * by calling EnableLimitSwitch(false) on a CANDigitalInput object
     * 
     * Limit switches can be reenabled by calling EnableLimitSwitch(true)
     */
    if(m_enableChooserForward.GetSelected() == kEnable) {
      m_forwardLimit.EnableLimitSwitch(true);
    } else {
      m_forwardLimit.EnableLimitSwitch(false);
    }

    if(m_enableChooserReverse.GetSelected() == kEnable) {
      m_reverseLimit.EnableLimitSwitch(true);
    } else {
      m_reverseLimit.EnableLimitSwitch(false);
    }
  }
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
