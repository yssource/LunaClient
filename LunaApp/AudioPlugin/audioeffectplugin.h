#ifndef AUDIOEFFECTPLUGIN_H
#define AUDIOEFFECTPLUGIN_H

#include <QObject>
#include <lunaplugin/effectplugin.h>

#include "audiomodel.h"

class AudioEffectPlugin : public lunacore::EffectPlugin
{
public:
    std::shared_ptr<lunacore::Provider> createProvider() override;
    QString displayName() const override;
    int displayOrder() const override;
    QUrl itemUrl() const override;
    QObject * model() override;
private:
    std::unique_ptr<AudioModel> mModel;
};

#endif // AUDIOEFFECTPLUGIN_H
