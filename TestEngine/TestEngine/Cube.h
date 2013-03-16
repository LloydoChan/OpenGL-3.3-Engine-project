#ifndef VBOCUBE_H
#define VBOCUBE_H

#include "Drawable.h"

class VBOCube : public Drawable
{

private:
    unsigned int vaoHandle;

public:
    VBOCube();

    void render()const;
};

#endif // VBOCUBE_H