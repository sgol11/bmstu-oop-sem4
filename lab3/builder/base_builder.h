#ifndef BASE_BUILDER_H
#define BASE_BUILDER_H

#include "../objects/object.h"


class BaseBuilder
{
public:
    BaseBuilder() = default;
    virtual ~BaseBuilder() = default;

    virtual bool is_built() = 0;
    virtual void reset() = 0;
    virtual void build() = 0;
};


class BuilderCreator
{
public:
    BuilderCreator() = default;
    virtual ~BuilderCreator() = default;

    virtual std::shared_ptr<BaseBuilder> create_builder() = 0;
};


#endif // BASE_BUILDER_H
