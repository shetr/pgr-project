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
#include <string>
#include <optional>

namespace sadekpet {

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

}

#endif // PGR_TYPES_HPP