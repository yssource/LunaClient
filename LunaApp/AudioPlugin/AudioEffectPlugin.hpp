#pragma once

#include "AudioModel.hpp"

#include <luna/interface/EffectPlugin.hpp>

#include <QObject>

class AudioEffectPlugin : public luna::interface::EffectPlugin
{
public:
    std::shared_ptr<luna::interface::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<AudioModel> mModel;
};
