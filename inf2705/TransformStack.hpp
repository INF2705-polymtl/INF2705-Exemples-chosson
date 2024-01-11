#pragma once


#include <cstddef>
#include <cstdint>

#include <stack>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;


struct ProjectionBox
{
	float leftFace;
	float rightFace;
	float bottomFace;
	float topFace;
	float nearDist;
	float farDist;
};

struct TransformStack : public std::stack<mat4>
{
	using stack<mat4>::stack;

	TransformStack() {
		pushIdentity();
	}

	TransformStack(const mat4& m) {
		push(m);
	}

	void scale(const vec3& v) {
		top() = glm::scale(top(), v);
	}
	void translate(const vec3& v) {
		top() = glm::translate(top(), v);
	}
	void rotate(float angleDegrees, const vec3& v) {
		top() = glm::rotate(top(), radians(angleDegrees), v);
	}

	void lookAt(const vec3& eye, const vec3& center, const vec3& up) {
		top() = glm::lookAt(eye, center, up);
	}
	void frustum(const ProjectionBox& plane) {
		top() = glm::frustum(plane.leftFace, plane.rightFace, plane.bottomFace, plane.topFace, plane.nearDist, plane.farDist);
	}
	void perspective(float fovyDegrees, float aspect, float nearFace, float farFace) {
		top() = glm::perspective(radians(fovyDegrees), aspect, nearFace, farFace);
	}
	void ortho(const ProjectionBox& plane) {
		top() = glm::ortho(plane.leftFace, plane.rightFace, plane.bottomFace, plane.topFace, plane.nearDist, plane.farDist);
	}
	void ortho2D(const ProjectionBox& plane) {
		top() = glm::ortho(plane.leftFace, plane.rightFace, plane.bottomFace, plane.topFace);
	}

	TransformStack& operator*= (const mat4& matrix) {
		top() *= matrix;
		return *this;
	}

	TransformStack& operator*= (const TransformStack& other) {
		*this *= other.top();
		return *this;
	}

	using stack<mat4>::push;
	using stack<mat4>::pop;

	void push() {
		push(top());
	}

	void pushIdentity() {
		push(mat4(1.0f));
	}
};
