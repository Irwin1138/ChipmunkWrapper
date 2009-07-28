#pragma once

#include "chipmunk.h"
#include "cpwBody.h"


class cpwJoint;

typedef boost::shared_ptr<cpwJoint>			PcpwJoint;

class cpwJoint {
public:
	static inline PcpwJoint	CreatePinJoint(PcpwBody a, PcpwBody b, cpVect anchr1, cpVect anchr2) {
		return PcpwJoint(new cpwJoint(a, b, anchr1, anchr2));
	}
	static inline PcpwJoint	CreateSlideJoint(PcpwBody a, PcpwBody b, cpVect anchr1, cpVect anchr2, cpFloat min, cpFloat max) {
		return PcpwJoint(new cpwJoint(a, b, anchr1, anchr2, min, max));
	}
	static inline PcpwJoint	CreatePivotJoint(PcpwBody a, PcpwBody b, cpVect pivot) {
		return PcpwJoint(new cpwJoint(a, b, pivot));
	}
	static inline PcpwJoint	CreateGrooveJoint(PcpwBody a, PcpwBody b, cpVect groove_a, cpVect groove_b, cpVect anchr2) {
		return PcpwJoint(new cpwJoint(a, b, groove_a, groove_b, anchr2));
	}


	cpwJoint(PcpwBody a, PcpwBody b, cpVect anchr1, cpVect anchr2) {
		m_joint = cpPinJointNew(a->GetBody(), b->GetBody(), anchr1, anchr2);
	}
	cpwJoint(PcpwBody a, PcpwBody b, cpVect anchr1, cpVect anchr2, cpFloat min, cpFloat max) {
		m_joint = cpSlideJointNew(a->GetBody(), b->GetBody(), anchr1, anchr2, min, max);
	}
	cpwJoint(PcpwBody a, PcpwBody b, cpVect pivot) {
		m_joint = cpPivotJointNew(a->GetBody(), b->GetBody(), pivot);
	}
	cpwJoint(PcpwBody a, PcpwBody b, cpVect groove_a, cpVect groove_b, cpVect anchr2) {
		m_joint = cpGrooveJointNew(a->GetBody(), b->GetBody(), groove_a, groove_b, anchr2);
	}

	~cpwJoint() {
		cpJointFree(m_joint);
	}

	inline cpJoint		*	GetJoint() {
		return m_joint;
	}
protected:
	cpJoint				*	m_joint;
};