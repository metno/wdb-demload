/*
 * DemLoadConfiguration.h
 *
 *  Created on: Aug 17, 2009
 *      Author: vegardb
 */

#ifndef DEMLOADCONFIGURATION_H_
#define DEMLOADCONFIGURATION_H_

#include <wdb/LoaderConfiguration.h>

namespace wdb
{

class DemLoadConfiguration : public wdb::load::LoaderConfiguration
{
public:
	DemLoadConfiguration(const std::string & defaultDataProvider) :
		wdb::load::LoaderConfiguration(defaultDataProvider)
	{}
};

}

#endif /* DEMLOADCONFIGURATION_H_ */
