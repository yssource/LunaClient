#include "legacyudpplugin.h"

#include <luna.h>

#include "udplegacyconnectorplugin.h"

void LegacyUdpPlugin::initialize(luna::Luna * luna) {
    luna->addConnector(std::make_unique<UdpLegacyConnectorPlugin>());
}

void LegacyUdpPlugin::finalize(luna::Luna * luna) {

}