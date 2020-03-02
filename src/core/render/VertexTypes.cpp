#include "VertexTypes.hpp"

#include "Buffer.hpp"

namespace sadekpet {

VertexLayout Vec2D::s_layout ({
    VertexElement(VertexType::FLOAT32, VertexElementCount::_2)
});
const VertexLayout& Vec2D::GetLayout() {
    return s_layout;
}
VertexLayout Vec3D::s_layout ({
    VertexElement(VertexType::FLOAT32, VertexElementCount::_3)
});
const VertexLayout& Vec3D::GetLayout() {
    return s_layout;
}

}