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

#include "Section.h"
#include <boost/algorithm/string/trim.hpp>
#include <istream>
#include <iostream>
#include <stdexcept>

namespace dem
{
namespace internal
{

const unsigned Section::sectionSize_ = 1024;


Section::Section(std::ifstream & s) :
	s_(s), start_(s.tellg())
{
	char buffer[sectionSize_];
	s.read(buffer, sectionSize_);
	if ( s.eof() )
		throw NotEnoughDataInFile();
	if ( ! s )
		throw UnableToReadFile();

	data_ = std::string(buffer, buffer + sectionSize_);
}

Section::~Section()
{
}


std::string Section::r(pos from, pos to) const
{
	--from; // the standard counts from 1 instead of 0

	std::string raw = data_.substr(from, to - from);
	boost::algorithm::trim(raw);
	return raw;
}
/*
std::string Section::r(pos from, pos to) const
{
	--from; // the standard counts from 1 instead of 0

	std::istream::streampos startRead = start_ + from;
	s_.seekg(startRead, std::ios_base::beg);

	//std::cout << startRead << std::endl;


//	if ( s_.fail() )
//	{
//		s_.clear();
//		s_.seekg(startRead, std::ios_base::beg);
//		if ( s_.fail() )
//			throw std::runtime_error("Error in stream");
//	}

	std::streamsize size = to - from;
	std::vector<char> buf(size);
	s_.read(&buf[0], size);
	std::string raw(buf.begin(), buf.end());
	boost::algorithm::trim(raw);
	return raw;
}
*/
float Section::v(pos from, pos to) const
{
	std::string s = r(from,to);
	return ValueInterpreter<float>()(s);
}
int Section::i(pos from, pos to) const
{
	std::string s = r(from,to);
	return ValueInterpreter<int>()(s);
}

}
}
