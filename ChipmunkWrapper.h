#pragma once

#include <chipmunk.h>

// yes, boost
#include <boost/smart_ptr.hpp>

// just in case
class cpwBody;
class cpwBB;
class cpwShape;
class cpwJoint;
class cpwSpace;

typedef boost::shared_ptr<cpwBody>			PcpwBody;
typedef boost::weak_ptr<cpwBody>			WPcpwBody;

typedef boost::shared_ptr<cpwBB>			PcpwBB;
typedef boost::weak_ptr<cpwBB>				WPcpwBB;

typedef boost::shared_ptr<cpwShape>			PcpwShape;
typedef boost::weak_ptr<cpwShape>			WPcpwShape;

typedef boost::shared_ptr<cpwJoint>			PcpwJoint;
typedef boost::weak_ptr<cpwJoint>			WPcpwJoint;

typedef boost::shared_ptr<cpwSpace>			PcpwSpace;
typedef boost::weak_ptr<cpwSpace>			WPcpwSpace;

#include "cpwBB.h"

#include "cpwJoint.h"
#include "cpwShape.h"
#include "cpwSpace.h"
#include "cpwBody.h"