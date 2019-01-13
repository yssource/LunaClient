#pragma once

#include "LightProvider.hpp"
#include "ThemeColor.hpp"

#include <QObject>
#include <QColor>
#include <QSettings>

#include <memory>

enum Source {
    ColorPicker,
    Temperature,
    Theme,
};

class LightModel : public QObject {
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(qreal brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)
    Q_PROPERTY(int source READ source WRITE setSource NOTIFY sourceChanged)

public:
    explicit LightModel();
    ~LightModel() override;
    void provider(std::weak_ptr<LightProvider> ptr);

    QColor color() const;
    qreal temperature() const;
    qreal brightness() const;
    int source() const;

public slots:
    void setColor(const QColor & color);
    void setTemperature(qreal temperature);
    void setBrightness(qreal value);
    void setSource(int value);
    void cieXYZ(qreal x, qreal y, qreal z);

signals:
    void colorChanged(QColor color);
    void temperatureChanged(qreal temperature);
    void brightnessChanged(qreal brightness);
    void sourceChanged(int source);

private:
    void notifyProvider();

    prism::CieXYZ mColor;
    qreal mTemperature;
    qreal mBrightness;

    std::weak_ptr<LightProvider> mProvider;
    int mSource;
    ThemeColor mThemeColor;
};