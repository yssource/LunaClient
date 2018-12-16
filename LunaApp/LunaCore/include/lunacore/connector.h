#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <vector>
#include <memory>
#include <string>

#include "lunacore_global.h"

namespace lunacore {
    class LUNACORESHARED_EXPORT Host {
    public:
        virtual ~Host();
        virtual std::string displayName() const = 0;
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual bool isConnected() const = 0;
        virtual void getStrands(std::vector<class Strand *> & strands) = 0;
    };

    class LUNACORESHARED_EXPORT Connector {
    public:
        virtual ~Connector();
        virtual void update() = 0;
        virtual void getHosts(std::vector<Host *> & hosts) = 0;
    };
}

#endif // CONNECTOR_H