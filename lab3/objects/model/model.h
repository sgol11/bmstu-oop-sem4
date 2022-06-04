#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <utility>

#include "../object.h"


class Model : public VisibleObject
{
public:
    Model() = default;
    virtual ~Model() = default;
};


#endif // MODEL_H
