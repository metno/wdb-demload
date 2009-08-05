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

#ifndef SECTIONB_H_
#define SECTIONB_H_

#include <geometry/Point.h>
#include <boost/noncopyable.hpp>
#include <deque>
#include <string>


namespace dem
{
class DemFile;

namespace internal
{

class SectionB : boost::noncopyable
{
public:
	SectionB(std::ifstream & s);
	~SectionB();


	int currentRow() const { return i(1,6); }
	int currentCol() const { return i(7,12); }
	int mElevations() const { return i(13,18); }
	int nElevations() const { return i(19,24); }
	geometry::Point firstCoordinate() const { return geometry::Point(v(25,48), v(49,72)); }
	float localDatumElevation() const { return v(73,96); }
	float lowestLevel() const { return v(97, 120); }
	float higetsLevel() const { return v(121, 144); }

	typedef std::deque<float> ElevationList;
	const ElevationList & elevations() const { return elevations_; }

	std::string rep() const;

private:
	typedef std::string::size_type pos;

	std::string r(pos from, pos to) const;
	float v(pos from, pos to) const;
	int i(pos from, pos to) const;


	char header_[144];
	ElevationList elevations_;

	friend class ::dem::DemFile;
};

}
}

#endif /* SECTIONB_H_ */
