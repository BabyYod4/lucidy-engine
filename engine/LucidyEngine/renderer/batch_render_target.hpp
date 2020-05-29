#ifndef BATCH_RENDER_TARGET_HPP
#define BATCH_RENDER_TARGET_HPP


#include "../settings.hpp"
#include "vertex.hpp"

#include <array>

namespace ly{

    typedef struct BRTSD { uint_t requiredVertices; uint_t requiredIndices; } BRTSetupData;
    typedef struct BRTDD { uint_t batchNum; range_t offsetVb; range_t offsetIb; } BRTDrawData;
    typedef struct BRTRD { string_t targetName; BRTDrawData drawData; BRTSetupData setupData; } BRTData;
    
    class BatchRenderTarget{
        public:
            virtual void setup(){};
            virtual void change(cstring_t t_changeCommand){}

            virtual const Vertex* getVertexBuff() = 0;
            virtual const uint_t* getIndexBuff() = 0;
            virtual BRTSetupData getSetupData() = 0;
        protected:
            BRTSetupData m_setupData;
    };

}
#endif // BATCH_RENDER_TARGET_HPP
