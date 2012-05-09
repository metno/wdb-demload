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

#ifndef DEMFILE_H_
#define DEMFILE_H_

#include "DemException.h"
#include <geometry/Polygon.h>
#include <PlaceSpecification.h>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/noncopyable.hpp>
#include <iterator>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

namespace dem
{

namespace internal
{
class SectionA;
}

class DemFile : boost::noncopyable
{
public:
	DemFile(const boost::filesystem::path & demFile);
	~DemFile();

	typedef std::vector<double> ValueContainer;

	const ValueContainer & data() const;

	std::string projDefinition() const { return projDefinition_; }

	typedef ValueContainer::size_type size_type;
	size_type xNumber() const { return ps_.xNumber_; }
	size_type yNumber() const { return ps_.yNumber_; }

	double xIncrement() const { return ps_.xIncrement_; }
	double yIncrement() const { return ps_.yIncrement_; }

	double startX() const  { return ps_.startX_; }
	double startY() const { return ps_.startY_; }

	geometry::Polygon area() const { return area_; }

	std::string rep() const;

	static const float NO_VALUE;

private:
	geometry::Polygon calculateArea_() const;
	std::string calculateProjDefinition_() const;

	static const float missingValue_;

	mutable boost::filesystem::ifstream file_;

	PlaceSpecification ps_;
	geometry::Polygon area_;
	std::string projDefinition_;
	internal::SectionA * sectionA_;

	mutable ValueContainer data_;
};


}

#endif /* DEMFILE_H_ */
