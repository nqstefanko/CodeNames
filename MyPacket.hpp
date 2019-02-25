#include <SFML/Network.hpp>

class MyPacket : public sf::Packet
{
    virtual const void* onSend(std::size_t& size);
    virtual void onReceive(const void* data, std::size_t size);
};