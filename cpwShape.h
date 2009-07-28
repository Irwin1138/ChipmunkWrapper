#pragma once

#include <map>

#include <boost/smart_ptr.hpp>

#include "chipmunk.h"

#include "cpwBody.h"
#include "cpwBB.h"

class cpwShape;
typedef boost::shared_ptr<cpwShape>			PcpwShape;
typedef boost::weak_ptr<cpwShape>			WPcpwShape;

class cpwShape {
public:
	// convenient factory functions
	static PcpwShape	CreateShape(cpShape *shape) {
		std::map<cpShape *, WPcpwShape>::iterator it;
		it = m_shapes.find(shape);
		if(it != m_shapes.end()) {
			return it->second.lock();
		}
		else return PcpwShape();
	}
	static PcpwShape	CreateCircleShape(PcpwBody body, cpFloat radius, cpVect offset) {
		PcpwShape shape(new cpwShape(body, radius, offset));
		shape->SetSelf(shape);
		return shape;
	}
	static PcpwShape	CreateSegmentShape(PcpwBody body, cpVect a, cpVect b, cpFloat radius) {
		PcpwShape shape(new cpwShape(body, a, b, radius));		
		shape->SetSelf(shape);
		return shape;
	}
	static PcpwShape	CreatePolyShape(PcpwBody body, int numVerts, cpVect *verts, cpVect offset) {
		PcpwShape shape(new cpwShape(body, numVerts, verts, offset));
		shape->SetSelf(shape);
		return shape;
	}
	~cpwShape() {
		std::map<cpShape *, WPcpwShape>::iterator it;
		it = m_shapes.find(m_shape);
		if(it != m_shapes.end()) {
			m_shapes.erase(it);
		}
		cpShapeFree(m_shape);
	}

	inline cpwBB		CacheBB() {
		return cpwBB(cpShapeCacheBB(m_shape));
	}
	inline void			ResetShapeIdCounter() {
		cpResetShapeIdCounter();
	}

	inline cpShape	*	GetShape() {
		return m_shape;
	}

	// Kustom accessorz
	inline unsigned int	GetId() {
		return m_shape->id;
	}
	inline cpwBB		GetBB() {
		return cpwBB(m_shape->bb);
	}
	inline unsigned int	GetCollisionType() {
		return m_shape->collision_type;
	}
	inline unsigned int	GetCollisionGroup() {
		return m_shape->group;
	}
	inline unsigned int	GetCollisionLayers() {
		return m_shape->layers;
	}
	inline void		*	GetUserData() {
		return m_shape->data;
	}
	inline PcpwBody		GetBody() {
		return cpwBody::Create(m_shape->body);
	}
	inline cpFloat		GetElasticity() {
		return m_shape->e;
	}
	inline cpFloat		GetFriction() {
		return m_shape->u;
	}
	inline cpVect		GetSurfaceVelocity() {
		return m_shape->surface_v;
	}

	/*inline unsigned int	SetId() {
		return m_shape->id;
	}
	inline cpwBB		SetBB() {
		return cpwBB(m_shape->bb);
	}*/
	inline void			SetCollisionType(unsigned int col_type) {
		m_shape->collision_type = col_type;
	}
	inline void			SetCollisionGroup(unsigned int col_group) {
		m_shape->group = col_group;
	}
	inline void			SetCollisionLayers(unsigned int col_layers) {
		m_shape->layers = col_layers;
	}
	inline void			SetUserData(void *data) {
		m_shape->data = data;
	}
	/*inline PcpwBody		SetBody() {
		return PcpwBody(cpwBody::Create(m_shape->body), null_deleter());
	}*/
	inline void			SetElasticity(cpFloat e) {
		m_shape->e = e;
	}
	inline void			SetFriction(cpFloat u) {
		m_shape->u = u;
	}
	/*inline cpVect		SetSurfaceVelocity() {
		return m_shape->surface_v;
	}*/
protected:
	void				SetSelf(PcpwShape shape) {
		m_shapes[m_shape] = shape;
	}

	cpwShape(PcpwBody body, cpFloat radius, cpVect offset) {
		m_shape = cpCircleShapeNew(body->GetBody(), radius, offset);
	}
	cpwShape(PcpwBody body, cpVect a, cpVect b, cpFloat radius) {
		m_shape = cpSegmentShapeNew(body->GetBody(), a, b, radius);
	}
	cpwShape(PcpwBody body, int numVerts, cpVect *verts, cpVect offset) {
		m_shape = cpPolyShapeNew(body->GetBody(), numVerts, verts, offset);
	}

	cpShape			*	m_shape;

	static std::map<cpShape *, WPcpwShape>
						m_shapes;
};

// the famous static member in static lib issue workaround
__declspec(selectany) std::map<cpShape *, WPcpwShape> cpwShape::m_shapes;