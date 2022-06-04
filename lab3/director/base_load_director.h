#ifndef BASE_LOAD_DIRECTOR_H
#define BASE_LOAD_DIRECTOR_H

#include <string>

#include "../builder/base_builder.h"
#include "../loader/base_loader.h"


class BaseLoadDirector
{
public:
    BaseLoadDirector() = default;
    virtual ~BaseLoadDirector() = default;

    virtual std::shared_ptr<Object> create() = 0;
    virtual void set_loader(std::shared_ptr<BaseLoader> loader_arg) = 0;
    virtual void set_builder(std::shared_ptr<BaseBuilder> builder_arg) = 0;
};


#endif // BASE_LOAD_DIRECTOR_H
