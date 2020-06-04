/**
 * @file EventSystem.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_EVENT_SYSTEM_HPP
#define PGR_EVENT_SYSTEM_HPP

#include <core/types.hpp>

namespace sadekpet {

/**
 * @brief Reference do listu.
 */
class IListRef 
{
public:
    virtual void SetIterator(List<void*>::iterator it) = 0;
    virtual void RemoveIterator() = 0;
    virtual List<void*>::iterator GetIterator() = 0;
};

/**
 * @brief Rozhraní pro reakci na výskyt nějaké události.
 * @tparam Event typ události.
 */
template<typename Event>
class IEventHandler : public IListRef
{
public:
    virtual void OnEvent(const Event& event) = 0;
    virtual bool IsAttached() = 0;
};

/**
 * @brief Implementace IEventHandler pomocí ukazatele na metodu poslouchající třídy na příslušný typ události.
 * @tparam Event typ události.
 * @tparam Listener třída poslouchající na událost.
 */
template<typename Event, typename Listener>
class EventHandler : IEventHandler<Event>
{
    typedef void (Listener::*Handler) (const Event&);
private:
    List<void*>::iterator m_it;
    Handler m_handler;
    Listener* m_listener;
	bool m_attached;
public:
    EventHandler()
        : m_listener(nullptr), m_handler(nullptr), m_attached(false) {}
    EventHandler(Listener* listener, Handler handler)
        : m_listener(listener), m_handler(handler), m_attached(false) {}
    
    inline void OnEvent(const Event& event) override { 
        (m_listener->*m_handler)(event); 
    }
    inline bool IsAttached() override { 
        return m_attached;
    }
    inline void SetIterator(List<void*>::iterator it) override { 
        m_it = it; 
		m_attached = true;
    }
    inline void RemoveIterator() override{
		m_attached = false;
    }
    inline List<void*>::iterator GetIterator() override { 
        return m_it; 
    }
};

/**
 * @brief Interface pro systém obstarávající nějakou událost.
 */
template<typename Event>
class IEventSystem
{
public:
    virtual void Attach(IEventHandler<Event>* handler) = 0;

    virtual void Detach(IEventHandler<Event>* handler) = 0;
};

#define PGR_EVENT_ACTIONS(eventType, eventSystem) \
    inline void Attach(IEventHandler<eventType>* handler) override { \
        eventSystem.Attach(handler); \
    } \
    inline void Detach(IEventHandler<eventType>* handler) override { \
        eventSystem.Detach(handler); \
    }

/**
 * @brief EventHandler co se automaticky Attachne a Detachne, podle jeho existence.
 */
template<typename Event, typename Listener>
class ScopedEventHandler : public EventHandler<Event, Listener>
{
    typedef void (Listener::*Handler) (const Event&);
private:
    IEventSystem<Event>* m_system;
public:
    ScopedEventHandler(Listener* listener, Handler handler, IEventSystem<Event>* system)
        : EventHandler<Event, Listener>(listener, handler), m_system(system) 
    {
        m_system->Attach((IEventHandler<Event>*)this);
    }
    ~ScopedEventHandler() 
    {
        if(this->IsAttached()) {
            m_system->Detach((IEventHandler<Event>*)this);
        }
    }
};

/**
 * @brief Provádí automatické volání funkcí při vzniknutí nějaké události.
 */
class EventSystem
{
private:
    UnordMap<TypeIndex, List<void*>> m_handlersMap;
public:
    EventSystem() : m_handlersMap() {}
    ~EventSystem() {
        for(Pair<TypeIndex, List<void*>> pair: m_handlersMap){
            List<void*>& handlers = pair.second;
            for(void* handler: handlers) {
                static_cast<IListRef*>(handler)->RemoveIterator();
            }
        }
    }

    template<typename Event>
    inline void Attach(IEventHandler<Event>* handler)
    {
        List<void*>& handlers = m_handlersMap[TypeIndex(typeid(Event))];
        handlers.push_back(handler);
        handler->SetIterator(--handlers.end());
    }
    template<typename Event>
    inline void Detach(IEventHandler<Event>* handler)
    {
        List<void*>& handlers = m_handlersMap[TypeIndex(typeid(Event))];
        handlers.erase(handler->GetIterator());
        handler->RemoveIterator();
    }
    template<typename Event>
    inline void Execute(const Event& event)
    {
        List<void*>& handlers = m_handlersMap[TypeIndex(typeid(Event))];
        for(void* handler: handlers) {
            static_cast<IEventHandler<Event>*>(handler)->OnEvent(event);
        }
    }
};

}

#endif // PGR_EVENT_SYSTEM_HPP