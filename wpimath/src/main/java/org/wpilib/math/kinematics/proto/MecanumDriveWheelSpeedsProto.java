// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package org.wpilib.math.kinematics.proto;

import org.wpilib.math.kinematics.MecanumDriveWheelVelocities;
import org.wpilib.math.proto.Kinematics.ProtobufMecanumDriveWheelSpeeds;
import org.wpilib.util.protobuf.Protobuf;
import us.hebi.quickbuf.Descriptors.Descriptor;

public class MecanumDriveWheelSpeedsProto
    implements Protobuf<MecanumDriveWheelVelocities, ProtobufMecanumDriveWheelSpeeds> {
  @Override
  public Class<MecanumDriveWheelVelocities> getTypeClass() {
    return MecanumDriveWheelVelocities.class;
  }

  @Override
  public Descriptor getDescriptor() {
    return ProtobufMecanumDriveWheelSpeeds.getDescriptor();
  }

  @Override
  public ProtobufMecanumDriveWheelSpeeds createMessage() {
    return ProtobufMecanumDriveWheelSpeeds.newInstance();
  }

  @Override
  public MecanumDriveWheelVelocities unpack(ProtobufMecanumDriveWheelSpeeds msg) {
    return new MecanumDriveWheelVelocities(
        msg.getFrontLeft(), msg.getFrontRight(), msg.getRearLeft(), msg.getRearRight());
  }

  @Override
  public void pack(ProtobufMecanumDriveWheelSpeeds msg, MecanumDriveWheelVelocities value) {
    msg.setFrontLeft(value.frontLeft);
    msg.setFrontRight(value.frontRight);
    msg.setRearLeft(value.rearLeft);
    msg.setRearRight(value.rearRight);
  }
}
