/**
 * @file MaterialManager.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-29
 */

#ifndef PGR_MATERIAL_MANAGER_HPP
#define PGR_MATERIAL_MANAGER_HPP

#include <core/types.hpp>
#include <core/render/Material.hpp>

namespace sadekpet {

class MaterialManager
{
private:
    static MaterialManager* s_instance;
    static String s_materialsPath;
    UnordMap<String, Material> m_materials;
public:
    static MaterialManager* Init();
    ~MaterialManager();
    static void AddMaterial(const String& name, const Material& material);
    static Material GetMaterial(const String& name);
    static void LoadMaterial(const String& name);

private:
    MaterialManager();
};

}

#endif // PGR_MATERIAL_MANAGER_HPP