/*
 demLoad

 Copyright (C) 2009 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: wdb@met.no

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301, USA
*/

#include <gtest/gtest.h>
#include <dem/DemFile.h>

TEST(DemStringConverterTest, simpleValue)
{
	dem::DemStringConverter<float> converter;
	ASSERT_FLOAT_EQ(1, converter("1"));
}

TEST(DemStringConverterTest, exponentValue)
{
	dem::DemStringConverter<float> converter;
	ASSERT_FLOAT_EQ(1e-08, converter("1D-08"));
}

TEST(DemStringConverterTest, exponentWithLongDecimalValue)
{
	dem::DemStringConverter<float> converter;
	ASSERT_FLOAT_EQ(1e-14, converter("0.000000000000001D+01"));
}

TEST(DemStringConverterTest, invalidValue)
{
	dem::DemStringConverter<float> converter;
	ASSERT_THROW(converter("hello?"), boost::bad_lexical_cast);
}

TEST(DemStringConverterTest, demMissingValue)
{
	dem::DemStringConverter<float> converter;
	ASSERT_FLOAT_EQ(-32767, converter("-32767"));
}

TEST(DemFileTest, nonexistingFile)
{
	ASSERT_THROW(dem::DemFile("/no/such/file.dem"), dem::FileDoesNotExist);
}
