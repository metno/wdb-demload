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

#include "dem/DemFile.h"
#include "configuration/DemLoadConfiguration.h"
#include <wdb/LoaderDatabaseConnection.h>
#include <wdbLogHandler.h>
#include <wdbException.h>
#include <boost/filesystem.hpp>
#include <iostream>


using namespace std;

void printInfo(const dem::DemFile & topography)
{
	cout << topography.rep() << endl;
	cout << "Dimensions: (" << topography.xNumber() << ", " << topography.yNumber() << ")" << endl;
	cout << "Increment:  (" << topography.xIncrement() << ", " << topography.yIncrement() << ")" << endl;
	cout << "start pos:  (" << topography.startX() << ", " << topography.startY() << ")" << endl;
	cout << "proj4text:   " << topography.projDefinition() << endl;
	cout << topography.area().wkt();
}

std::ostream & version(std::ostream & s)
{
    out << PACKAGE_STRING << endl;
}

std::ostream & help(std::ostream & s, const wdb::DemLoadConfiguration & conf)
{
	version(s);
	s << '\n';
    s << "Usage: demLoad [OPTIONS] DEM_FILES...\n\n";
//    s << "If you don't give any files on command line, stdin will be read instead.\n\n"; // doesn't work yet
    s << "Options:\n";
	s << conf.shownOptions();
	return s;
}

std::ostream & list(std::ostream & s, const dem::DemFile & f)
{
	s << "Topography data for area " << f.area() << "\n";
	s << "Increment distance " << f.xIncrement() << ", " << f.yIncrement() << "\n";
	s << "Proj definition " << f.projDefinition() << endl;
	return s << endl;
}

int main(int argc, char ** argv)
{
	wdb::DemLoadConfiguration conf("demload");
	conf.parse(argc, argv);

	if ( conf.general().help )
	{
		help(cout, conf);
		return 0;
	}
	if ( conf.general().version )
	{
		version(cout);
		return 0;
	}

	wdb::WdbLogHandler logHandler( conf.logging().loglevel, conf.logging().logfile );
    WDB_LOG & log = WDB_LOG::getInstance( "wdb.demLoad.main" );
    log.debug( "Starting demLoad" );

	wdb::load::LoaderDatabaseConnection db(conf);

    const std::vector<std::string> & file = conf.input().file;
	std::vector<boost::filesystem::path> files;
	copy(file.begin(), file.end(), back_inserter(files));

	bool listInsteadOfLoad = conf.output().list;

	for ( std::vector<boost::filesystem::path>::const_iterator it = files.begin(); it != files.end(); ++ it )
	{
		log.infoStream() << "loading file " << it->file_string();

		dem::DemFile f(* it);

		if ( listInsteadOfLoad )
		{
			list(cout , f);
		}
		else
		{
			std::string placeName;
			try
			{
				placeName = db.getPlaceName(f.xNumber(), f.yNumber(), f.xIncrement(), f.yIncrement(), f.startX(), f.startY(), f.projDefinition());
			}
			catch ( wdb::empty_result & )
			{
				if ( conf.loading().placeName.empty() )
					placeName = boost::filesystem::basename(* it);
				else
					placeName = conf.loading().placeName;
				placeName = db.addPlaceDefinition(placeName, f.xNumber(), f.yNumber(), f.xIncrement(), f.yIncrement(), f.startX(), f.startY(), f.projDefinition());
			}
			try
			{
				db.write(
						& f.data()[0],
						f.data().size(),
						"demload", // will be ignored and overridden by whatever is in config.
						placeName,
						"infinity",
						"-infinity",
						"infinity",
						"altitude",
						"height above reference ellipsoid",
						0, 0,
						0,
						0);
			}
			catch ( std::exception & e )
			{
				std::cout << "Error when loading file " << it->native_file_string() << ": " << e.what() << std::endl;
			}
		}
	}
}
