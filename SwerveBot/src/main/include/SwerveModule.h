/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Encoder.h>
#include <frc/PWMVictorSPX.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/ProfiledPIDController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/SwerveModuleState.h>
#include <wpi/math>
#include <rev/CANSparkMax.h>
#define brushless rev::CANSparkMax::MotorType::kBrushless

class SwerveModule {
 public:
  SwerveModule(int driveMotorChannel, int turningMotorChannel);
  frc::SwerveModuleState GetState() const;
  void SetDesiredState(const frc::SwerveModuleState& state);

 private:
  static constexpr double kWheelRadius = 0.0508;
  static constexpr int kEncoderResolution = 4096;

  static constexpr auto kModuleMaxAngularVelocity =
      wpi::math::pi * 1_rad_per_s;  // radians per second
  static constexpr auto kModuleMaxAngularAcceleration =
      wpi::math::pi * 2_rad_per_s / 1_s;  // radians per second^2

  //frc::PWMVictorSPX m_driveMotor;   //this is the drive motor for the module
  //frc::PWMVictorSPX m_turningMotor; //this is the turning motor for the module

  rev::CANSparkMax m_driveMotor;
  rev::CANSparkMax m_turningMotor;

  //frc::Encoder m_driveEncoder{0, 1};
  //frc::Encoder m_turningEncoder{2, 3};
  rev::CANEncoder m_driveEncoder = m_driveMotor.GetEncoder();
  rev::CANEncoder m_turningEncoder = m_turningMotor.GetEncoder();

  //frc2::PIDController m_drivePIDController{1.0, 0, 0};
  rev::CANPIDController m_drivePIDController = m_driveMotor.GetPIDController();
  frc::ProfiledPIDController<units::radians> m_turningPIDController{1.0,0.0,0.0,{kModuleMaxAngularVelocity, kModuleMaxAngularAcceleration}};
  
  frc::SimpleMotorFeedforward<units::meter> m_driveFeedforward{1_V, 3_V / 1_mps};
  frc::SimpleMotorFeedforward<units::radians> m_turnFeedforward{ 1_V, 0.5_V / 1_rad_per_s};
};
