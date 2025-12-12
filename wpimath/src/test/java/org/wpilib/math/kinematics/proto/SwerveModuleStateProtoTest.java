// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package org.wpilib.math.kinematics.proto;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;
import org.wpilib.math.geometry.Rotation2d;
import org.wpilib.math.kinematics.SwerveModuleVelocity;
import org.wpilib.math.proto.Kinematics.ProtobufSwerveModuleState;

class SwerveModuleStateProtoTest {
  private static final SwerveModuleVelocity DATA = new SwerveModuleVelocity(22.9, new Rotation2d(3.3));

  @Test
  void testRoundtrip() {
    ProtobufSwerveModuleState proto = SwerveModuleVelocity.proto.createMessage();
    SwerveModuleVelocity.proto.pack(proto, DATA);

    SwerveModuleVelocity data = SwerveModuleVelocity.proto.unpack(proto);
    assertEquals(DATA.speed, data.speed);
    assertEquals(DATA.angle, data.angle);
  }
}
