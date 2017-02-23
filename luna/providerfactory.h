#ifndef LUNAPROVIDERFACTORY_H
#define LUNAPROVIDERFACTORY_H

#include <memory>

#include "provider.h"

namespace luna {
    enum class ProviderType : int {
        none,
        illumination,
        audio,
        screen,
        //fire,
        //plasma,
        COUNT,
    };

    class ProviderFactory
    {
    public:
        ProviderFactory();

        std::unique_ptr<Provider> make(ProviderType type, class QObject * parent);
    private:
        typedef std::unique_ptr<Provider>(* creator_t)(class QObject *);
        template<typename ElemT, typename IndexT, IndexT count>
        class EnumArray {
        public:
            ElemT & operator[](IndexT index){
                return mData[static_cast<size_t>(index)];
            }

        private:
            ElemT mData[static_cast<size_t>(count)];
        };

        EnumArray<creator_t, ProviderType, ProviderType::COUNT> mCreators;
    };
}

#endif // LUNAPROVIDERFACTORY_H
