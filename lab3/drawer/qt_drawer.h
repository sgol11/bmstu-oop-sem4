#ifndef QT_DRAWER_H
#define QT_DRAWER_H

#include <QGraphicsScene>
#include "base_drawer.h"


class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
    explicit QtDrawer(std::shared_ptr<QGraphicsScene> &src_scene);
    QtDrawer(const QtDrawer &src_drawer);
    ~QtDrawer() override = default;

    void draw_line(const Point &point1, const Point &point2) override;
    void clear_scene() override;

private:
    std::shared_ptr<QGraphicsScene> scene;
};


#endif // QT_DRAWER_H
