#pragma once

#include <map>

#include <boost/smart_ptr.hpp>

#include "chipmunk.h"

class cpwBody;
typedef boost::shared_ptr<cpwBody>		PcpwBody;
typedef boost::weak_ptr<cpwBody>		WPcpwBody;

class cpwBody {
public:
	// convenient factory functions
	static PcpwBody				Create() {
		PcpwBody body(new cpwBody);
		body->SetSelf(body);
		return body;
	}
	static PcpwBody				Create(cpFloat m, cpFloat i) {
		PcpwBody body(new cpwBody(m, i));
		body->SetSelf(body);
		return body;
	}
	// accessor for some chipmunk user accessible functions and structures
	// if the cpBody was created through use of one of the factory functions,
	// this function will return proper reference counted shared_ptr
	static PcpwBody				Create(cpBody *existing) {
		std::map<cpBody *, WPcpwBody>::iterator it;
		it = m_bodies.find(existing);
		if(it != m_bodies.end()) {
			return it->second.lock();
		}
		else return PcpwBody();
	}

	~cpwBody() {
		// erase self from the map
		std::map<cpBody *, WPcpwBody>::iterator it;
		it = m_bodies.find(m_body);
		if(it != m_bodies.end()) {
			m_bodies.erase(it);
		}
		cpBodyFree(m_body);
	}
	// Kustom Accessorz

	inline void					SetMass(cpFloat m) {
		cpBodySetMass(m_body, m);
	}
	inline void					SetMoment(cpFloat i) {
		cpBodySetMoment(m_body, i);
	}
	inline void					SetAngle(cpFloat a) {
		cpBodySetAngle(m_body, a);
	}
	inline void					SetPosition(cpVect p) {
		m_body->p = p;
	}
	inline void					SetVelocity(cpVect v) {
		m_body->v = v;
	}
	inline void					SetAngularVelocity(cpFloat w) {
		m_body->w = w;
	}
	inline void					SetTorque(cpFloat t) {
		m_body->t = t;
	}

	inline void					Slew(cpVect pos, cpFloat dt) {
		cpBodySlew(m_body, pos, dt);
	}

	inline void					UpdateVelocity(cpVect gravity, cpFloat damping, cpFloat dt) {
		cpBodyUpdateVelocity(m_body, gravity, damping, dt);
	}

	inline void					UpdatePosition(cpFloat dt) {
		cpBodyUpdatePosition(m_body, dt);
	}

	inline cpFloat				GetMass() {
		return m_body->m;
	}
	inline cpFloat				GetMoment() {
		return m_body->i;
	}
	inline cpVect				GetForce() {
		return m_body->f;
	}
	inline cpFloat				GetAngle() {
		return m_body->a;
	}
	inline cpVect				GetVecAngle() {
		return m_body->rot;
	}
	inline cpFloat				GetTorque() {
		return m_body->t;
	}
	inline cpVect				GetPosition() {
		return m_body->p;
	}
	inline cpVect				GetVelocity() {
		return m_body->v;
	}
	inline cpFloat				GetAngularVelocity() {
		return m_body->w;
	}

	inline cpVect				Local2World(cpVect v) {
		return cpBodyLocal2World(m_body, v);
	}

	inline cpVect				World2Local(cpVect v) {
		return cpBodyWorld2Local(m_body, v);
	}

	inline void					ResetForces() {
		cpBodyResetForces(m_body);
	}

	inline void					ApplyImpulse(cpVect j, cpVect r) {
		cpBodyApplyImpulse(m_body, j, r);
	}

	// not intended for external use, not wrapping...
	/*inline void					ApplyBiasImpulse(cpVect j, cpVect r) {
		cpBodyApplyBiasImpulse(m_body, j, r);
	}*/

	inline void					ApplyForce(cpVect f, cpVect r) {
		cpBodyApplyForce(m_body, f, r);
	}
	inline void					ApplyTorque(cpFloat t) {
		m_body->t += t;
	}

	inline cpBody			*	GetBody() {
		return m_body;
	}
protected:
	cpwBody() {
		m_body = cpBodyNew(1.0f, 1.0f);
	}
	cpwBody(cpFloat m, cpFloat i) {
		m_body = cpBodyNew(m, i);
	}

	inline void					SetSelf(PcpwBody self) {
		m_bodies[m_body] = self;
		//m_bodies.size();
		//m_bodies.insert(std::pair<cpBody *, WPcpwBody>(m_body, WPcpwBody(self)));
	}

	cpBody					*	m_body;
	//bool						m_null_delete;
	
	// maps every cpBody to corresponding shared_ptr
	static std::map<
		cpBody *, WPcpwBody>	m_bodies;
};

// the famous static member in static lib issue workaround
__declspec(selectany) std::map<cpBody *, WPcpwBody> cpwBody::m_bodies;

inline void DampedSpring(PcpwBody a, PcpwBody b, cpVect anchr1, cpVect anchr2, cpFloat rlen, cpFloat k, cpFloat dmp, cpFloat dt) {
	cpDampedSpring(a->GetBody(), b->GetBody(), anchr1, anchr2, rlen, k, dmp, dt);
}