#ifndef ABSTRACT_DRAWER_FACTORY_H
#define ABSTRACT_DRAWER_FACTORY_H

#include <memory>
#include "base_drawer.h"


class AbstractDrawerFactory
{
public:
    AbstractDrawerFactory() = default;
    virtual ~AbstractDrawerFactory() = default;

    virtual std::unique_ptr<BaseDrawer> create_graphics() = 0;
};


#endif // ABSTRACT_DRAWER_FACTORY_H
