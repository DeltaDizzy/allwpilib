// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <gtest/gtest.h>
#include <hal/HAL.h>

#include "frc/geometry/Rotation3d.h"
#include "frc/simulation/ADIS16448_IMUSim.h"
#include "frc/ADIS16448_IMU.h"
#include "units/angle.h"

namespace frc::sim {
    TEST(ADIS16448_IMUSimTest, SetAttributes) {
        HAL_Initialize(500, 0);

        ADIS16448_IMU gyro;
        ADIS16448_IMUSim sim{gyro};

        EXPECT_EQ(0, gyro.GetAngle().value());
        EXPECT_EQ(0, gyro.GetGyroAngleX().value());
        EXPECT_EQ(0, gyro.GetGyroAngleY().value());
        EXPECT_EQ(0, gyro.GetGyroAngleZ().value());
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

        ADIS16448_IMU gyro{};
        ADIS16448_IMUSim sim{gyro};

        frc::Rotation3d OFFSET1{0_deg, 0_deg, 90_deg};
        gyro.Reset(OFFSET1);
        EXPECT_EQ(90_deg, gyro.GetAngle());
        EXPECT_EQ(0_deg, gyro.GetGyroAngleX());
        EXPECT_EQ(0_deg, gyro.GetGyroAngleY());
        EXPECT_EQ(90_deg, gyro.GetGyroAngleZ());

        sim.SetGyroAngleZ(10_deg);
        EXPECT_EQ(100_deg, gyro.GetAngle());

        sim.SetGyroAngleZ(90_deg);
        EXPECT_EQ(180_deg, gyro.GetAngle());

        gyro.Reset(frc::Rotation3d{0_deg,90_deg,90_deg});
        EXPECT_EQ(90_deg, gyro.GetGyroAngleY());
        EXPECT_EQ(90_deg, gyro.GetAngle());
    }
}  // namespace frc::sim