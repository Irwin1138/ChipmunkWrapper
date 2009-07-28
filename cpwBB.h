#pragma once

//#include "ChipmunkWrapper.h"
#include "chipmunk.h"

// wrapped merely for convenience
class cpwBB {
public:
	cpwBB() {
		m_bb.l = 0.0f;
		m_bb.b = 0.0f;
		m_bb.r = 0.0f;
		m_bb.t = 0.0f;
	}
	cpwBB(cpBB bb)
	:
	m_bb(bb) {

	}
	cpwBB(const cpFloat l, const cpFloat b,	const cpFloat r, const cpFloat t) {
		m_bb.l = l;
		m_bb.b = b;
		m_bb.r = r;
		m_bb.t = t;
	}

	~cpwBB() {

	}

	inline int			Intersects(const cpwBB b) {
		return cpBBintersects(m_bb, b.GetBB());
	}
	inline int			ContainsBB(const cpwBB other) {
		return cpBBcontainsBB(m_bb, other.GetBB());
	}
	inline int			ContainsVect(const cpVect v) {
		return cpBBcontainsVect(m_bb, v);
	}

	inline cpVect		ClampVect(const cpVect v) {
		return cpBBClampVect(m_bb, v);
	}
	inline cpVect		WrapVect(const cpVect v) {
		return cpBBWrapVect(m_bb, v);
	}

	inline cpBB			GetBB() const {
		return m_bb;
	}
protected:
	cpBB				m_bb;
};