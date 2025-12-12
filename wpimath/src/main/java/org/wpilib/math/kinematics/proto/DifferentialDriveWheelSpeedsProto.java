// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package org.wpilib.math.kinematics.proto;

import org.wpilib.math.kinematics.DifferentialDriveWheelVelocities;
import org.wpilib.math.proto.Kinematics.ProtobufDifferentialDriveWheelSpeeds;
import org.wpilib.util.protobuf.Protobuf;
import us.hebi.quickbuf.Descriptors.Descriptor;

public class DifferentialDriveWheelSpeedsProto
    implements Protobuf<DifferentialDriveWheelVelocities, ProtobufDifferentialDriveWheelSpeeds> {
  @Override
  public Class<DifferentialDriveWheelVelocities> getTypeClass() {
    return DifferentialDriveWheelVelocities.class;
  }

  @Override
  public Descriptor getDescriptor() {
    return ProtobufDifferentialDriveWheelSpeeds.getDescriptor();
  }

  @Override
  public ProtobufDifferentialDriveWheelSpeeds createMessage() {
    return ProtobufDifferentialDriveWheelSpeeds.newInstance();
  }

  @Override
  public DifferentialDriveWheelVelocities unpack(ProtobufDifferentialDriveWheelSpeeds msg) {
    return new DifferentialDriveWheelVelocities(msg.getLeft(), msg.getRight());
  }

  @Override
  public void pack(ProtobufDifferentialDriveWheelSpeeds msg, DifferentialDriveWheelVelocities value) {
    msg.setLeft(value.left);
    msg.setRight(value.right);
  }
}
