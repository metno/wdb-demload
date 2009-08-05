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

#ifndef SECTION_H_
#define SECTION_H_

#include "ValueInterpreter.h"
#include <dem/DemException.h>
#include <vector>
#include <fstream>

namespace dem
{
namespace internal
{
class Section
{
public:

	std::istream::streampos startPos() const { return start_; }
	virtual std::istream::streampos endPos() const = 0;

protected:
	explicit Section(std::ifstream & data);
	~Section();

//	typedef std::string::size_type pos;
	typedef std::istream::streamoff pos;

	std::string r(pos from, pos to) const;
	float v(pos from, pos to) const;
	int i(pos from, pos to) const;

	std::string data_;

	std::ifstream & s_;
	std::istream::streampos start_;

	static const unsigned sectionSize_;

private:
	Section(); // undefined
};

}
}

#endif /* SECTION_H_ */
