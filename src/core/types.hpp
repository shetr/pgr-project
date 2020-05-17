/**
 * @file types.hpp
 * @author sadekpet 
 * @brief Shorter names of some types.
 * 
 */

#ifndef PGR_TYPES_HPP
#define PGR_TYPES_HPP

#include <stdint.h>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <list>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <optional>

#include <glm/glm.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtc/matrix_transform.hpp> 

namespace sadekpet {

using uint = unsigned int;

template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;

template<typename T>
using Vector = std::vector<T>;

template<typename T>
using List = std::list<T>;

template<typename K, typename V>
using UnordMap = std::unordered_map<K, V>;

template<typename K>
using Set = std::set<K>;

template<typename T>
using Opt = std::optional<T>;

template<typename T, typename U>
using Pair = std::pair<T, U>;

using TypeIndex = std::type_index;

using String = std::string;

template<typename ClassType, typename MemberType> size_t memberOffset(MemberType ClassType::*member)
{
    return (char*)&((ClassType*)nullptr->*member) - (char*)nullptr;
}

#ifndef M_PI
#define M_PI 3.14159f
#endif
#ifndef M_PI_2
#define M_PI_2 (3.14159f/2)
#endif

}

#endif // PGR_TYPES_HPP