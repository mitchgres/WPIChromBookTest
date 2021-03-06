// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <cmath>

#include <wpi/numbers>

#include "frc/geometry/Pose2d.h"
#include "gtest/gtest.h"

using namespace frc;

static constexpr double kEpsilon = 1E-9;

TEST(Twist2dTest, Straight) {
  const Twist2d straight{5.0_m, 0.0_m, 0.0_rad};
  const auto straightPose = Pose2d().Exp(straight);

  EXPECT_NEAR(straightPose.X().value(), 5.0, kEpsilon);
  EXPECT_NEAR(straightPose.Y().value(), 0.0, kEpsilon);
  EXPECT_NEAR(straightPose.Rotation().Radians().value(), 0.0, kEpsilon);
}

TEST(Twist2dTest, QuarterCircle) {
  const Twist2d quarterCircle{5.0_m / 2.0 * wpi::numbers::pi, 0_m,
                              units::radian_t(wpi::numbers::pi / 2.0)};
  const auto quarterCirclePose = Pose2d().Exp(quarterCircle);

  EXPECT_NEAR(quarterCirclePose.X().value(), 5.0, kEpsilon);
  EXPECT_NEAR(quarterCirclePose.Y().value(), 5.0, kEpsilon);
  EXPECT_NEAR(quarterCirclePose.Rotation().Degrees().value(), 90.0, kEpsilon);
}

TEST(Twist2dTest, DiagonalNoDtheta) {
  const Twist2d diagonal{2.0_m, 2.0_m, 0.0_deg};
  const auto diagonalPose = Pose2d().Exp(diagonal);

  EXPECT_NEAR(diagonalPose.X().value(), 2.0, kEpsilon);
  EXPECT_NEAR(diagonalPose.Y().value(), 2.0, kEpsilon);
  EXPECT_NEAR(diagonalPose.Rotation().Degrees().value(), 0.0, kEpsilon);
}

TEST(Twist2dTest, Equality) {
  const Twist2d one{5.0_m, 1.0_m, 3.0_rad};
  const Twist2d two{5.0_m, 1.0_m, 3.0_rad};
  EXPECT_TRUE(one == two);
}

TEST(Twist2dTest, Inequality) {
  const Twist2d one{5.0_m, 1.0_m, 3.0_rad};
  const Twist2d two{5.0_m, 1.2_m, 3.0_rad};
  EXPECT_TRUE(one != two);
}

TEST(Twist2dTest, Pose2dLog) {
  const Pose2d end{5_m, 5_m, Rotation2d(90_deg)};
  const Pose2d start{};

  const auto twist = start.Log(end);

  EXPECT_NEAR(twist.dx.value(), 5 / 2.0 * wpi::numbers::pi, kEpsilon);
  EXPECT_NEAR(twist.dy.value(), 0.0, kEpsilon);
  EXPECT_NEAR(twist.dtheta.value(), wpi::numbers::pi / 2.0, kEpsilon);
}
