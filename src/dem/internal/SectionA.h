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

#ifndef SECTIONA_H_
#define SECTIONA_H_

#include <geometry/Polygon.h>
#include <boost/noncopyable.hpp>
#include <string>
#include <iosfwd>
#include <vector>

namespace dem
{

namespace internal
{

class SectionA : boost::noncopyable
{
public:
	SectionA(std::ifstream & s);
	~SectionA();

	std::string rep() const;

	std::string originCode() const { return r(141,144); }
	int demLevelCode() const { return i(145,150); }
	int elevationPattern() const { return i(151, 156); }
	int groundPlanimetricReferenceSystem() const { return i(157, 162); }
	int zone() const { return i(163,168); }
	int planimetricUnit() const { return i(529,534); }
	int elevationUnit() const { return i(535,540); }
	int sidesOfPolygon() const { return i(541, 546); }
	geometry::Polygon area() const;
	float lowestLevel() const { return v(739, 762); }
	float higetsLevel() const { return v(763, 786); }
	float angleFromPrimaryAxis() const { return v(787,810); }
	int elevationAccuracy() const { return i(811,816); }
	float xResolution() const { return v(817,828); }
	float yResolution() const { return v(829, 840); }
	float zResolution() const { return v(841, 852); }
	int rowsInProfile() const { return i(853,858); }
	int colsInProfile() const { return i(859,864); }
	int verticalDatum() const { return i(889,890); }
	int horizontalDatum() const { return i(891,892); }

private:
	typedef std::string::size_type pos;

	std::string r(pos from, pos to) const;
	float v(pos from, pos to) const;
	int i(pos from, pos to) const;

	char data_[1024];
};


}

}

#endif /* SECTIONA_H_ */
