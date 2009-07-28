#pragma once

#include <set>

//#include "ChipmunkWrapper.h"
#include "chipmunk.h"
#include "cpwShape.h"
#include "cpwBody.h"
#include "cpwJoint.h"

typedef std::set<PcpwBody> BodySet;
typedef std::set<PcpwShape> ShapeSet;
typedef std::set<PcpwJoint> JointSet;

class cpwSpace {
public:
	cpwSpace()
	:
	m_space(cpSpaceNew()) {

	}
	cpwSpace(int iterations)
	:
	m_space(cpSpaceNew()) {
		m_space->iterations = iterations;
	}

	//static PcpwSpace	Create();
	//static PcpwSpace	Create(int iterations);

	~cpwSpace() {
		cpSpaceFree(m_space);
		m_bodyList.clear();
		m_shapeList.clear();
		m_staticShapeList.clear();
		m_jointList.clear();
	}

	inline void			AddShape(PcpwShape shape) {
		cpSpaceAddShape(m_space, shape->GetShape());
		m_shapeList.insert(shape);
	}
	inline void			AddStaticShape(PcpwShape shape) {
		cpSpaceAddStaticShape(m_space, shape->GetShape());
		m_staticShapeList.insert(shape);
	}
	inline void			AddBody(PcpwBody body) {
		cpSpaceAddBody(m_space, body->GetBody());
		m_bodyList.insert(body);
	}
	inline void			AddJoint(PcpwJoint joint) {
		cpSpaceAddJoint(m_space, joint->GetJoint());
		m_jointList.insert(joint);
	}

	inline void			RemoveShape(PcpwShape shape) {
		cpSpaceRemoveShape(m_space, shape->GetShape());

		std::set<PcpwShape> ::iterator iter = m_shapeList.find(shape);
		if(iter != m_shapeList.end()) {
			m_shapeList.erase(iter);
		}
	}
	inline void			RemoveStaticShape(PcpwShape shape) {
		cpSpaceRemoveStaticShape(m_space, shape->GetShape());

		std::set<PcpwShape> ::iterator iter = m_staticShapeList.find(shape);
		if(iter != m_staticShapeList.end()) {
			m_staticShapeList.erase(iter);
		}
	}
	inline void			RemoveBody(PcpwBody body) {
		cpSpaceRemoveBody(m_space, body->GetBody());

		std::set<PcpwBody> ::iterator iter = m_bodyList.find(body);
		if(iter != m_bodyList.end()) {
			m_bodyList.erase(iter);
		}
	}
	inline void			RemoveJoint(PcpwJoint joint) {
		cpSpaceRemoveJoint(m_space, joint->GetJoint());

		std::set<PcpwJoint> ::iterator iter = m_jointList.find(joint);
		if(iter != m_jointList.end()) {
			m_jointList.erase(iter);
		}
	}
	// Kustom Accessorz
	inline int			GetIterations() {
		return m_space->iterations;
	}
	inline cpVect		GetGravity() {
		return m_space->gravity;
	}
	inline cpFloat		GetDamping() {
		return m_space->damping;
	}
	inline int			GetTimeStamp() {
		return m_space->stamp;
	}
	inline ShapeSet		GetShapes() {
		return m_shapeList;
	}
	inline ShapeSet		GetStaticShapes() {
		return m_staticShapeList;
	}
	inline BodySet		GetBodies() {
		return m_bodyList;
	}
	// get arbiters
	// get contacts
	inline JointSet		GetJoints() {
		return m_jointList;
	}


	inline void			SetIterations(int iterations) {
		m_space->iterations = iterations;
	}
	inline void			SetGravity(cpVect g) {
		m_space->gravity = g;
	}
	inline void			SetDamping(cpFloat damping) {
		m_space->damping = damping;
	}
	

	inline void			ResizeStaticHash(cpFloat dim, int count) {
		cpSpaceResizeStaticHash(m_space, dim, count);
	}
	inline void			ResizeActiveHash(cpFloat dim, int count) {
		cpSpaceResizeActiveHash(m_space, dim, count);
	}

	inline void			RehashStatic() {
		cpSpaceRehashStatic(m_space);
	}

	inline void			Step(cpFloat dt) {
		cpSpaceStep(m_space, dt);
	}

	inline cpSpace	*	GetSpace() {
		return m_space;
	}
protected:
	//void				SetSelf(PcpwSpace self);

	cpSpace			*	m_space;

	BodySet				m_bodyList;
	ShapeSet			m_shapeList;
	ShapeSet			m_staticShapeList;
	JointSet			m_jointList;
};