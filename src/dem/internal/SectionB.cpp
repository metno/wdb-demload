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

#include "SectionB.h"
#include "ValueInterpreter.h"
#include <boost/algorithm/string/trim.hpp>
#include <sstream>
#include <cmath>
#include <fstream>
#include <iostream>

namespace dem
{
namespace internal
{

SectionB::SectionB(std::ifstream & s)
{
	s.read(header_, 144);

	int positions = mElevations() * nElevations();

	for ( int i = 0; i < positions; ++ i)
	{
		float f;
		s >> f;
		elevations_.push_back(f);
	}

	//reallign stream here
	std::istream::streampos pos = s.tellg();
	static int i = 0;
	s.seekg(1024 - (pos % 1024), std::istream::cur);
}

SectionB::~SectionB()
{
}

std::string SectionB::rep() const
{
	std::ostringstream s;
	s << "B RECORD:\n";
	s << '\n';
	s << "currentRow:\t\t" << currentRow() << '\n';
	s << "currentCol:\t\t" << currentCol() << '\n';
	s << "mElevations:\t\t" << mElevations() << '\n';
	s << "nElevations:\t\t" << nElevations() << '\n';
	s << "firstCoordinate:\t" << firstCoordinate() << '\n';
	s << "localDatumElevation:\t" << localDatumElevation() << '\n';
	s << "lowestLevel:\t\t" << lowestLevel() << '\n';
	s << "higetsLevel:\t\t" << higetsLevel() << '\n';
	s << "========================================\n";

	return s.str();
}

std::string SectionB::r(pos from, pos to) const
{
	--from; // the standard counts from 1 instead of 0

	std::string raw(header_ + from, header_ + to);
	boost::algorithm::trim(raw);
	return raw;
}


float SectionB::v(pos from, pos to) const
{
	std::string s = r(from,to);
	return ValueInterpreter<float>()(s);
}
int SectionB::i(pos from, pos to) const
{
	std::string s = r(from,to);
	return ValueInterpreter<int>()(s);
}


}
}
