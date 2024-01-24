package edu.wpi.first.wpilibj.simulation;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

import edu.wpi.first.hal.HAL;
import edu.wpi.first.math.geometry.Rotation3d;
import edu.wpi.first.wpilibj.ADIS16448_IMU;

class ADIS16448_IMUSimTest {
    @Test
    void testCallbacks() {
        HAL.initialize(500, 0);

        try(ADIS16448_IMU gyro = new ADIS16448_IMU()) {
            ADIS16448_IMUSim sim = new ADIS16448_IMUSim(gyro);

            assertEquals(0, gyro.getAngle());
            assertEquals(0, gyro.getRate());

            sim.setGyroAngleZ(123.456);
            sim.setGyroRateZ(229.3504);

            assertEquals(123.456, gyro.getAngle());
            assertEquals(229.3504, gyro.getRate());

            gyro.reset();
            sim.setGyroRateZ(0);
            assertEquals(0, gyro.getAngle());

            gyro.reset(new Rotation3d(0, 0, Math.PI));
            assertEquals(gyro.getAngle(), 180);
        }
    }
}
