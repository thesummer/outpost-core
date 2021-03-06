/*
 * Copyright (c) 2015-2017, German Aerospace Center (DLR)
 *
 * This file is part of the development version of OUTPOST.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Authors:
 * - 2015-2017, Fabian Greif (DLR RY-AVS)
 */
// ----------------------------------------------------------------------------

#include <unittest/harness.h>
#include <outpost/time/date.h>

using namespace outpost::time;

TEST(DateUtilsTest, shouldHaveAStartingEpoch)
{
    Date date = DateUtils::getDate(0);

    EXPECT_EQ(0, date.year);
    EXPECT_EQ(3, date.month);
    EXPECT_EQ(1, date.day);
}

TEST(DateUtilsTest, shouldCalculateOffsetsBetweenEpochs)
{
	const Date taiEpochStart  = { 1958, 1, 1, 0, 0, 0 };
	const Date unixEpochStart = { 1970, 1, 1, 0, 0, 0 };
	const Date gpsEpochStart  = { 1980, 1, 6, 0, 0, 0 };

    EXPECT_EQ(719468, DateUtils::getDay(unixEpochStart));

    EXPECT_EQ(8040, DateUtils::getDay(gpsEpochStart) - DateUtils::getDay(taiEpochStart));
	EXPECT_EQ(4383, DateUtils::getDay(unixEpochStart) - DateUtils::getDay(taiEpochStart));
}

TEST(DateUtilsTest, shouldCalculateTaiOffsetsForLeapSeconds)
{
	int64_t taiDayOffset = DateUtils::getDay(Date { 1958, 1, 1, 0, 0, 0 });

	EXPECT_EQ(741484800, (DateUtils::getDay(Date { 1981,  6, 30, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1981-06-30T23:59:60Z
	EXPECT_EQ(694224000, (DateUtils::getDay(Date { 1979, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1979-12-31T23:59:60Z
	EXPECT_EQ(662688000, (DateUtils::getDay(Date { 1978, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1978-12-31T23:59:60Z
	EXPECT_EQ(631152000, (DateUtils::getDay(Date { 1977, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1977-12-31T23:59:60Z
	EXPECT_EQ(599616000, (DateUtils::getDay(Date { 1976, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1976-12-31T23:59:60Z
	EXPECT_EQ(567993600, (DateUtils::getDay(Date { 1975, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1975-12-31T23:59:60Z
	EXPECT_EQ(536457600, (DateUtils::getDay(Date { 1974, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1974-12-31T23:59:60Z
	EXPECT_EQ(504921600, (DateUtils::getDay(Date { 1973, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1973-12-31T23:59:60Z
	EXPECT_EQ(473385600, (DateUtils::getDay(Date { 1972, 12, 31, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1972-12-31T23:59:60Z
	EXPECT_EQ(457488000, (DateUtils::getDay(Date { 1972,  6, 30, 0, 0, 0 }) - taiDayOffset + 1) * 86400);	// 1972-06-30T23:59:60Z
}
