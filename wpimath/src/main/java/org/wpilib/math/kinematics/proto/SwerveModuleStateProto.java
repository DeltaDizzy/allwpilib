// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package org.wpilib.math.kinematics.proto;

import org.wpilib.math.geometry.Rotation2d;
import org.wpilib.math.kinematics.SwerveModuleVelocities;
import org.wpilib.math.proto.Kinematics.ProtobufSwerveModuleState;
import org.wpilib.util.protobuf.Protobuf;
import us.hebi.quickbuf.Descriptors.Descriptor;

public class SwerveModuleStateProto
    implements Protobuf<SwerveModuleVelocities, ProtobufSwerveModuleState> {
  @Override
  public Class<SwerveModuleVelocities> getTypeClass() {
    return SwerveModuleVelocities.class;
  }

  @Override
  public Descriptor getDescriptor() {
    return ProtobufSwerveModuleState.getDescriptor();
  }

  @Override
  public ProtobufSwerveModuleState createMessage() {
    return ProtobufSwerveModuleState.newInstance();
  }

  @Override
  public SwerveModuleVelocities unpack(ProtobufSwerveModuleState msg) {
    return new SwerveModuleVelocities(msg.getSpeed(), Rotation2d.proto.unpack(msg.getAngle()));
  }

  @Override
  public void pack(ProtobufSwerveModuleState msg, SwerveModuleVelocities value) {
    msg.setSpeed(value.speed);
    Rotation2d.proto.pack(msg.getMutableAngle(), value.angle);
  }
}
