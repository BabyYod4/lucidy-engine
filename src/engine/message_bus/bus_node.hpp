#ifndef BUS_NODE_HPP
#define BUS_NODE_HPP

#include "message_bus.hpp"

#include <memory>

class BusNode
{
public:
    BusNode(std::shared_ptr<MessageBus> t_messageBus){
        m_messageBus = t_messageBus;
        m_messageBus->addReceiver( [this](Message t_message){ onMessageReceive(t_message); } );
    }

protected:
    std::shared_ptr<MessageBus> m_messageBus;

    void sendMessage(const Message& t_message) { 
        m_messageBus->sendMessage(t_message);
    }

    virtual void onMessageReceive(Message& t_message){};
};

#endif // BUS_NODE_HPP
