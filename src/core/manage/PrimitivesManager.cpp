#include "PrimitivesManager.hpp"


namespace sadekpet {

PrimitivesManager* PrimitivesManager::s_instance = nullptr;

PrimitivesManager* PrimitivesManager::Init()
{
    if(s_instance == nullptr) {
        s_instance = new PrimitivesManager();
    }
    return s_instance;
}
PrimitivesManager::~PrimitivesManager()
{
    s_instance = nullptr;
}

void PrimitivesManager::AddPrimitives(const String& name, Primitives* primitives)
{
    s_instance->m_primitives.insert({name, Shared<Primitives>(primitives)});
}

Shared<Primitives> PrimitivesManager::GetPrimitives(const String& name)
{
    UnordMap<String, Shared<Primitives>>::iterator it = s_instance->m_primitives.find(name);
    return it->second;
}

PrimitivesManager::PrimitivesManager()
{
}

}