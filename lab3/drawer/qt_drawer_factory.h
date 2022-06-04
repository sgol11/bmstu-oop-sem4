#ifndef QT_DRAWER_FACTORY_H
#define QT_DRAWER_FACTORY_H

#include "abstract_drawer_factory.h"
#include "qt_drawer.h"


class QtDrawerFactory : public AbstractDrawerFactory
{
public:
    QtDrawerFactory() = delete;
    explicit QtDrawerFactory(std::shared_ptr<QGraphicsScene> &src_scene);

    std::unique_ptr<BaseDrawer> create_graphics() override;

private:
    std::shared_ptr<QGraphicsScene> scene;
};


#endif // QT_DRAWER_FACTORY_H
