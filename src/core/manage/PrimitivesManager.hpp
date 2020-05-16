
#ifndef PGR_PRIMITIVES_MANAGER_HPP
#define PGR_PRIMITIVES_MANAGER_HPP

#include <core/render/Primitives.hpp>

namespace sadekpet {

class PrimitivesManager
{
private:
    static PrimitivesManager* s_instance;
    UnordMap<String, Shared<Primitives>> m_primitives;
public:
    static PrimitivesManager* Init();
    ~PrimitivesManager();
    static void AddPrimitives(const String& name, Primitives* primitives);
    static Shared<Primitives> GetPrimitives(const String& name);

private:
    PrimitivesManager();
};

}

#endif // PGR_PRIMITIVES_MANAGER_HPP