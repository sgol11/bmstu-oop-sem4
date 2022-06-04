#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include "../object.h"
#include "../../visitor/visitor.h"


class Composite : public Object
{
public:
    Composite() = default;
    explicit Composite(std::shared_ptr<Object> &object);
    explicit Composite(const std::vector<std::shared_ptr<Object>> &vector);
    ~Composite() = default;

    bool is_composite() override { return true; };

    bool add(const std::shared_ptr<Object> &element) override;
    bool remove(const Iterator &iter) override;

    virtual void update_center() override;
    virtual Point get_center() override;

    void transform(const Point &move_params, const Point &scale_params, const Point &rotate_params) override;
    void accept(std::shared_ptr<Visitor> visitor) override;

    Iterator begin() override;
    Iterator end()   override;

protected:
    Point center;
    std::vector<std::shared_ptr<Object>> objects;

private:
    void transform_objects(const Point &move_params, const Point &scale_params, const Point &rotate_params);
    void move_objects_to_origin();
    void move_objects_to_center();
};


#endif // COMPOSITE_H
