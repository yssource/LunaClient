#ifndef LUNALEGACY_H
#define LUNALEGACY_H

#include <QUdpSocket>
#include <QTimer>
#include "connection.h"
#include "binarystream.h"

namespace luna {
    class ConnectionLegacy : public Connection
    {
    public:
        explicit ConnectionLegacy(QObject * parent = nullptr);
        virtual ~ConnectionLegacy();

        bool isConnected() override;

        void connect() override;
        void disconnect() override;
        void update(const std::vector<PixelStrand> & pixelStrands,
                    const std::vector<ColorScalar> & whiteStrands) override;
        void shutdown() override;
        void getConfig(struct Config * config) override;

    protected slots:
        void datagramReceived();
        void keepAliveTimeout();
    private:
        enum {
            pixelCount = 120,
            port = 1234,
            bufferSize = 6 + pixelCount * 6,
        };
        bool mIsConnected;
        QUdpSocket mSocket;
        QTimer mKeepAliveTimer;
        BinaryStream<bufferSize> mBuffer;

        static const char * helloMessage;

        void send();
    };
}
#endif // LUNALEGACY_H