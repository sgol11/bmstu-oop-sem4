#ifndef EDGE_H
#define EDGE_H

#include <memory>


class Edge
{
public:
    Edge() = default;
    Edge(const std::size_t &start_index, const std::size_t &end_index);

    Edge(const Edge &) = default;

    ~Edge() = default;

    std::size_t get_start_index() const;
    std::size_t get_end_index() const;

    void set_start_index(const std::size_t &src_start_index);
    void set_end_index(const std::size_t &src_end_index);

private:
    std::size_t start_index;
    std::size_t end_index;
};


#endif // EDGE_H
