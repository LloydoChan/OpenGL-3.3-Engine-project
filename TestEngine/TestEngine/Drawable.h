//Drawable.h - abstract interface for a range of classes
#pragma once

#include <glm\glm.hpp>

class Drawable
{
public:
	Drawable(){};
	virtual ~Drawable(){};

	virtual void render() const = 0;

	void SetTransform(glm::mat4& mat) {transformation = mat;}
	const glm::mat4& GetTransform()const {return transformation;}
private:
	glm::mat4 transformation;
};