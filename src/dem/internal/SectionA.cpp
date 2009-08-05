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

#include "SectionA.h"
#include "ValueInterpreter.h"
#include <dem/DemException.h>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <sstream>

namespace dem
{

namespace internal
{

SectionA::SectionA(std::ifstream & s)
{
	s.read(data_, 1024);
}

SectionA::~SectionA()
{
}

std::string SectionA::rep() const
{
	std::ostringstream s;

	s << "A RECORD:\n";
	s << '\n';
	s << "originCode:\t\t\t" << originCode() << '\n';
	s << "demLevelCode:\t\t\t" << demLevelCode() << '\n';
	s << "elevationPattern:\t\t" << elevationPattern() << '\n';
	s << "groundPlanimetricReferenceSystem:\t" << groundPlanimetricReferenceSystem() << '\n';
	s << "zone:\t\t\t\t" << zone() << '\n';
	s << "planimetricUnit:\t\t" << planimetricUnit() << '\n';
	s << "elevationUnit:\t\t\t" << elevationUnit() << '\n';
	s << "sidesOfPolygon:\t\t\t" << sidesOfPolygon() << '\n';
	s << "area:\t\t\t\t" << area() << '\n';
	s << "lowestLevel:\t\t\t" << lowestLevel() << '\n';
	s << "higetsLevel:\t\t\t" << higetsLevel() << '\n';
	s << "angleFromPrimaryAxis:\t\t" << angleFromPrimaryAxis() << '\n';
	s << "elevationAccuracy:\t\t" << elevationAccuracy() << '\n';
	s << "xResolution:\t\t\t" << xResolution() << '\n';
	s << "yResolution:\t\t\t" << yResolution() << '\n';
	s << "zResolution:\t\t\t" << zResolution() << '\n';
	s << "rowsInProfile:\t\t\t" << rowsInProfile() << '\n';
	s << "colsInProfile:\t\t\t" << colsInProfile() << '\n';
	s << "verticalDatum:\t\t\t" << verticalDatum() << '\n';
	s << "horizontalDatum:\t\t" << horizontalDatum() << '\n';
	s << "========================================\n";
	return s.str();
}

geometry::Polygon SectionA::area() const
{
	std::vector<geometry::Point> points;
	for ( int pos = 547; pos <= 738; pos += 48 )
	{
		geometry::Point p(v(pos,pos+24), v(pos+24,pos+48));
		points.push_back(p);
	}
	geometry::Polygon ret(points.begin(), points.end());
	return ret;
}

std::string SectionA::r(pos from, pos to) const
{
	--from; // the standard counts from 1 instead of 0

	std::string raw(data_ + from, data_ + to);
	boost::algorithm::trim(raw);
	return raw;
}


float SectionA::v(pos from, pos to) const
{
	std::string s = r(from,to);
	return ValueInterpreter<float>()(s);
}
int SectionA::i(pos from, pos to) const
{
	std::string s = r(from,to);
	return ValueInterpreter<int>()(s);
}

}

}
