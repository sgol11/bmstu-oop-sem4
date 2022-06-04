#include "edge.h"


Edge::Edge(const std::size_t &start_index, const std::size_t &end_index)
{
    set_start_index(start_index);
    set_end_index(end_index);
}

std::size_t Edge::get_start_index() const
{
    return start_index;
}

std::size_t Edge::get_end_index() const
{
    return end_index;
}

void Edge::set_start_index(const size_t &src_start_index)
{
    start_index = src_start_index;
}

void Edge::set_end_index(const size_t &src_end_index)
{
    end_index = src_end_index;
}
