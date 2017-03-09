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

#include "DemFile.h"
#include "internal/SectionA.h"
#include "internal/SectionB.h"
#include <deque>
#include <iostream>
#include <cmath>

namespace dem
{


DemFile::DemFile(const boost::filesystem::path & demFile) :
	file_(demFile), sectionA_(0)
{
	file_.exceptions(std::istream::badbit | std::istream::failbit | std::istream::eofbit);

	if ( not boost::filesystem::exists(demFile))
		throw FileDoesNotExist();
	sectionA_ = new internal::SectionA(file_);

	projDefinition_ = calculateProjDefinition_();

	geometry::Polygon p = sectionA_->area();
	geometry::Point lowerLeft = p.corners().front(); // spec says lower left is first
	ps_.startX_ = lowerLeft.x();
	ps_.startY_ =  lowerLeft.y();
	ps_.xIncrement_ = sectionA_->xResolution();
	ps_.yIncrement_ = sectionA_->yResolution();
	ps_.xNumber_ = sectionA_->colsInProfile();
	ps_.yNumber_ = 1 + (p.corners().at(1).y() - ps_.startY_) / ps_.xIncrement_;
	ps_.projDefinition_ = const_cast<char*>(projDefinition_.c_str());

	area_ = calculateArea_();

	////std::cout << ps_.startX_ << ", " << ps_.startY_ << ", " << ps_.xIncrement_ << ", " << ps_.yIncrement_ << ", " << ps_.xNumber_ << ", " << ps_.yNumber_  << ", " << ps_.projDefinition_ << std::endl;

}

DemFile::~DemFile()
{
	delete sectionA_;
}

std::string DemFile::rep() const
{
	return sectionA_->rep();
}


const DemFile::ValueContainer & DemFile::data() const
{
	if ( data_.empty() )
	{
		const int rows = sectionA_->rowsInProfile();
		const int cols = sectionA_->colsInProfile();
		const int noOfEntries = rows * cols;

		typedef boost::shared_ptr<dem::internal::SectionB> SectionBPtr;
		typedef std::vector<SectionBPtr> SectionBList;
		SectionBList columns;
		for ( int i = 0; i < noOfEntries; ++ i )
			columns.push_back(SectionBPtr(new dem::internal::SectionB(file_)));


		// Find lowest point in grid
		double lowestY = std::numeric_limits<double>::max();
		geometry::Polygon originalGrid = sectionA_->area();
		for ( unsigned i = 0; i < originalGrid.noOfCorners(); ++ i )
		{
			double thisY = originalGrid.corners()[i].y();
			if ( thisY < lowestY )
				lowestY = thisY;
		}

		// Fill in data in front of columns
		int minMissing = std::numeric_limits<int>::max();
		int count = 0;
		for ( SectionBList::iterator it = columns.begin(); it != columns.end(); ++ it )
		{
			geometry::Point startPoint = (*it)->firstCoordinate();
			if ( startPoint.y() > lowestY )
			{
				int missingPointsInFront = (startPoint.y() - lowestY) / yIncrement();
				if ( missingPointsInFront < minMissing )
					minMissing = missingPointsInFront;
				++ count;
			}

			dem::internal::SectionB::ElevationList & elevations = (*it)->elevations_;

			size_t noOfPointsBeforeData = (startPoint.y() - startY()) / yIncrement();
			elevations.insert(elevations.begin(), noOfPointsBeforeData, NO_VALUE);
		}

		// Find longest column
		dem::internal::SectionB::ElevationList::size_type longestColumn = 0;
		for ( SectionBList::iterator it = columns.begin(); it != columns.end(); ++ it )
		{
			dem::internal::SectionB::ElevationList::size_type length = (*it)->elevations().size();
			if ( length > longestColumn )
				longestColumn = length;
		}

		// Append to end of each column, so they become of the same length
		for ( SectionBList::iterator it = columns.begin(); it != columns.end(); ++ it )
		{
			dem::internal::SectionB::ElevationList & elevations = (*it)->elevations_;
			size_t noOfPointsAfterData = longestColumn - elevations.size();
			if ( noOfPointsAfterData != 0)
				elevations.insert(elevations.end(), noOfPointsAfterData, NO_VALUE);
		}

		// Fill in data structure
		const dem::internal::SectionB & front = * columns.front();
		for ( unsigned i = 0; i < front.elevations().size(); ++ i )
			for ( SectionBList::iterator it = columns.begin(); it != columns.end(); ++ it )
				data_.push_back((*it)->elevations()[i]);

		// Change any explicitly missing values to NO_VAULE
		std::replace(data_.begin(), data_.end(), missingValue_, NO_VALUE);
	}
	return data_;
}

std::string DemFile::calculateProjDefinition_() const
{
	std::ostringstream projDef;

	int planimetricSystem = sectionA_->groundPlanimetricReferenceSystem();
	if ( planimetricSystem == 1 )
	{
		projDef << "+proj=utm ";
		projDef << "+zone=" << sectionA_->zone() << " ";
	}
	else
		throw InvalidProjection("Can only handle UTM projection");

	int horizontalDatum = sectionA_->horizontalDatum();
	switch ( horizontalDatum )
	{
	case 1:
		projDef << "+datum=NAD27 ";
		break;
	case 2:
		throw InvalidProjection("Cannot handle WGS72 Datum");
		//projDef << "+datum=WGS72 ";
		break;
	case 3:
		projDef << "+datum=WGS84 ";
		break;
	case 4:
		projDef << "+datum=NAD83 ";
		break;
	case 5:
		throw InvalidProjection("Cannot handle Old Hawaii Datum");
	case 6:
		throw InvalidProjection("Cannot handle Puerto Rico Datum");
	default:
		throw InvalidProjection("Unknown horizontal datum: " + boost::lexical_cast<std::string>(horizontalDatum));
	}

	int unit = sectionA_->planimetricUnit();
	if ( unit == 1 )
		projDef << "+units=ft ";
	else if ( unit == 2 )
		projDef << "+units=m ";
	else
		throw InvalidProjection("Cannot handle unit " + boost::lexical_cast<std::string>(unit));

	projDef << "+no_defs";

	return projDef.str();
}

geometry::Polygon DemFile::calculateArea_() const
{
	return sectionA_->area();
}

const float DemFile::NO_VALUE = std::numeric_limits<float>::quiet_NaN();

const float DemFile::missingValue_ = -32767;
}
