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

#ifndef DEMEXCEPTION_H_
#define DEMEXCEPTION_H_

#include <exception>
#include <string>

namespace dem
{

class DemException : public std::exception
{
	std::string msg_;
public:
	DemException(const std::string & msg) : msg_(msg) {}
	virtual ~DemException() throw() {}
	virtual const char* what() const throw() { return msg_.c_str(); }
};

#define DEM_EXCEPTION(ExceptionName, message) \
	class ExceptionName : public DemException { \
	public: \
	ExceptionName() : DemException(message) {} \
	}
#define DEM_CUSTOM_MESSAGE_EXCEPTION(ExceptionName) \
class ExceptionName : public DemException { \
public: \
	ExceptionName(const std::string & msg) : DemException(msg) {} \
}

DEM_EXCEPTION(FileDoesNotExist, "File does not exist");
DEM_EXCEPTION(NotEnoughDataInFile, "File does not contain enough data");
DEM_EXCEPTION(UnableToReadFile, "Unable to read file");
DEM_EXCEPTION(InternalError, "Internal error");
DEM_CUSTOM_MESSAGE_EXCEPTION(InvalidProjection);

}

#endif /* DEMEXCEPTION_H_ */
