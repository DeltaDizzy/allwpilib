// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <algorithm>
#include <array>
#include <cmath>

#include "wpi/units/math.hpp"
#include "wpi/units/velocity.hpp"
#include "wpi/util/SymbolExports.hpp"

namespace wpi::math {
/**
 * Represents the wheel speeds for a mecanum drive drivetrain.
 */
struct WPILIB_DLLEXPORT MecanumDriveWheelVelocities {
  /**
   * Speed of the front-left wheel.
   */
  wpi::units::meters_per_second_t frontLeft = 0_mps;

  /**
   * Speed of the front-right wheel.
   */
  wpi::units::meters_per_second_t frontRight = 0_mps;

  /**
   * Speed of the rear-left wheel.
   */
  wpi::units::meters_per_second_t rearLeft = 0_mps;

  /**
   * Speed of the rear-right wheel.
   */
  wpi::units::meters_per_second_t rearRight = 0_mps;

  /**
   * Renormalizes the wheel speeds if any individual speed is above the
   * specified maximum.
   *
   * Sometimes, after inverse kinematics, the requested speed from one or
   * more wheels may be above the max attainable speed for the driving motor on
   * that wheel. To fix this issue, one can reduce all the wheel speeds to make
   * sure that all requested module speeds are at-or-below the absolute
   * threshold, while maintaining the ratio of speeds between wheels.
   *
   * @param attainableMaxSpeed The absolute max speed that a wheel can reach.
   * @return Desaturated MecanumDriveWheelVelocities.
   */
  constexpr MecanumDriveWheelVelocities Desaturate(
      wpi::units::meters_per_second_t attainableMaxSpeed) const {
    std::array<wpi::units::meters_per_second_t, 4> wheelSpeeds{
        frontLeft, frontRight, rearLeft, rearRight};
    wpi::units::meters_per_second_t realMaxSpeed =
        wpi::units::math::abs(*std::max_element(
            wheelSpeeds.begin(), wheelSpeeds.end(),
            [](const auto& a, const auto& b) {
              return wpi::units::math::abs(a) < wpi::units::math::abs(b);
            }));

    if (realMaxSpeed > attainableMaxSpeed) {
      for (int i = 0; i < 4; ++i) {
        wheelSpeeds[i] = wheelSpeeds[i] / realMaxSpeed * attainableMaxSpeed;
      }
      return MecanumDriveWheelVelocities{wheelSpeeds[0], wheelSpeeds[1],
                                     wheelSpeeds[2], wheelSpeeds[3]};
    }

    return *this;
  }

  /**
   * Adds two MecanumDriveWheelVelocities and returns the sum.
   *
   * <p>For example, MecanumDriveWheelVelocities{1.0, 0.5, 2.0, 1.5} +
   * MecanumDriveWheelVelocities{2.0, 1.5, 0.5, 1.0} =
   * MecanumDriveWheelVelocities{3.0, 2.0, 2.5, 2.5}
   *
   * @param other The MecanumDriveWheelVelocities to add.
   * @return The sum of the MecanumDriveWheelVelocities.
   */
  constexpr MecanumDriveWheelVelocities operator+(
      const MecanumDriveWheelVelocities& other) const {
    return {frontLeft + other.frontLeft, frontRight + other.frontRight,
            rearLeft + other.rearLeft, rearRight + other.rearRight};
  }

  /**
   * Subtracts the other MecanumDriveWheelVelocities from the current
   * MecanumDriveWheelVelocities and returns the difference.
   *
   * <p>For example, MecanumDriveWheelVelocities{5.0, 4.0, 6.0, 2.5} -
   * MecanumDriveWheelVelocities{1.0, 2.0, 3.0, 0.5} =
   * MecanumDriveWheelVelocities{4.0, 2.0, 3.0, 2.0}
   *
   * @param other The MecanumDriveWheelVelocities to subtract.
   * @return The difference between the two MecanumDriveWheelVelocities.
   */
  constexpr MecanumDriveWheelVelocities operator-(
      const MecanumDriveWheelVelocities& other) const {
    return *this + -other;
  }

  /**
   * Returns the inverse of the current MecanumDriveWheelVelocities.
   * This is equivalent to negating all components of the
   * MecanumDriveWheelVelocities.
   *
   * @return The inverse of the current MecanumDriveWheelVelocities.
   */
  constexpr MecanumDriveWheelVelocities operator-() const {
    return {-frontLeft, -frontRight, -rearLeft, -rearRight};
  }

  /**
   * Multiplies the MecanumDriveWheelVelocities by a scalar and returns the new
   * MecanumDriveWheelVelocities.
   *
   * <p>For example, MecanumDriveWheelVelocities{2.0, 2.5, 3.0, 3.5} * 2 =
   * MecanumDriveWheelVelocities{4.0, 5.0, 6.0, 7.0}
   *
   * @param scalar The scalar to multiply by.
   * @return The scaled MecanumDriveWheelVelocities.
   */
  constexpr MecanumDriveWheelVelocities operator*(double scalar) const {
    return {scalar * frontLeft, scalar * frontRight, scalar * rearLeft,
            scalar * rearRight};
  }

  /**
   * Divides the MecanumDriveWheelVelocities by a scalar and returns the new
   * MecanumDriveWheelVelocities.
   *
   * <p>For example, MecanumDriveWheelVelocities{2.0, 2.5, 1.5, 1.0} / 2 =
   * MecanumDriveWheelVelocities{1.0, 1.25, 0.75, 0.5}
   *
   * @param scalar The scalar to divide by.
   * @return The scaled MecanumDriveWheelVelocities.
   */
  constexpr MecanumDriveWheelVelocities operator/(double scalar) const {
    return operator*(1.0 / scalar);
  }
};
}  // namespace wpi::math

#include "wpi/math/kinematics/proto/MecanumDriveWheelVelocitiesProto.hpp"
#include "wpi/math/kinematics/struct/MecanumDriveWheelVelocitiesStruct.hpp"
