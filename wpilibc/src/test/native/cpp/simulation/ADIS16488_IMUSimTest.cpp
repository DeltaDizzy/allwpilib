// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>
#include <hal/HAL.h>

#include "frc/simulation/ADIS16448_IMUSim.h"
#include "frc/ADIS16448_IMU.h"
#include "units/angle.h"

namespace frc::sim {
    TEST(ADIS16448_IMUSimTest, SetAttributes) {
        HAL_Initialize(500, 0);

        ADIS16448_IMU gyro;
        ADIS16448_IMUSim sim{gyro};

        EXPECT_EQ(0, gyro.GetAngle().value());
        EXPECT_EQ(0, gyro.GetRate().value());

        constexpr units::degree_t TEST_ANGLE{123.456};
        constexpr units::degrees_per_second_t TEST_RATE{229.3504};
        sim.SetGyroAngleZ(TEST_ANGLE);
        sim.SetGyroRateZ(TEST_RATE);
        EXPECT_EQ(TEST_ANGLE, gyro.GetAngle());
        EXPECT_EQ(TEST_RATE, gyro.GetGyroRateZ());
    }

    TEST(ADIS16448_IMUSimTest, Offset) {
        HAL_Initialize(500, 0);

        ADIS16448_IMU gyro;
        ADIS16448_IMUSim sim{gyro};

        EXPECT_EQ(0, gyro.GetAngle().value());
        EXPECT_EQ(0, gyro.GetGyroAngleX().value());
        EXPECT_EQ(0, gyro.GetGyroAngleY().value());
        EXPECT_EQ(0, gyro.GetGyroAngleZ().value());

        frc::Rotation3d OFFSET1{units::degree_t{0}, units::degree_t{0}, units::degree_t{90}};
        gyro.Reset(OFFSET1);
        EXPECT_EQ(units::degree_t{90}, gyro.GetAngle());
        EXPECT_EQ(units::degree_t{0}, gyro.GetGyroAngleX());
        EXPECT_EQ(units::degree_t{0}, gyro.GetGyroAngleY());
        EXPECT_EQ(units::degree_t{90}, gyro.GetGyroAngleZ());

        sim.SetGyroAngleZ(units::degree_t{10});
        EXPECT_EQ(units::degree_t{100}, gyro.GetAngle());

        sim.SetGyroAngleZ(units::degree_t{90});
        EXPECT_EQ(units::degree_t{180}, gyro.GetAngle());

        gyro.Reset(frc::Rotation3d{units::degree_t{0},units::degree_t{90},units::degree_t{90}});
        EXPECT_EQ(units::degree_t{90}, gyro.GetGyroAngleY());
        EXPECT_EQ(units::degree_t{90}, gyro.GetAngle());
    }
}  // namespace frc::sim