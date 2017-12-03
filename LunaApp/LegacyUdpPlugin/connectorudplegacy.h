#ifndef CONNECTORUDPLEGACY_H
#define CONNECTORUDPLEGACY_H

#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

#include <connector.h>
#include <colorutils.h>
#include <strand.h>

#include "binarystream.h"
#include "socket.h"


class HostUDPLegacy : public luna::Host {
public:
    HostUDPLegacy(net::Address address);
    virtual ~HostUDPLegacy();
    std::string displayName() const override;
    void connect() override;
    void disconnect() override;
    bool isConnected() const override;
    void getStrands(std::vector<luna::Strand *> &strands) override;
    void send();
    const net::Address & address() const { return mAddress; }
private:
    bool mIsConnected;
    std::vector<std::unique_ptr<luna::Strand>> mStrands;
    enum {
        PIXEL_COUNT = 120,
        BUFFER_SIZE  = 6 + PIXEL_COUNT * 6,
    };
    net::Address mAddress;
    net::SocketUdp mSocket;
    BinaryStream mBuffer;
};

class ConnectorUDPLegacy : public luna::Connector
{
public:
    ConnectorUDPLegacy(uint16_t port);
    ConnectorUDPLegacy(const ConnectorUDPLegacy &) = delete;
    virtual ~ConnectorUDPLegacy();
    ConnectorUDPLegacy & operator=(const ConnectorUDPLegacy &) = delete;
    void update() override;
    void getHosts(std::vector<luna::Host *> & hosts) override;
private:
    void sendDiscovery();
    void receiveFromHosts();
    void updateHosts();
    void onHostConnected();
    std::chrono::steady_clock::duration mDiscoveryInterval;
    net::SocketUdp mSocket;
    std::vector<std::unique_ptr<HostUDPLegacy>> mHosts;
    std::chrono::steady_clock::time_point mNextDiscovery;
    uint16_t mPort;
};

#endif // CONNECTORUDPLEGACY_H