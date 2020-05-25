#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "vertex.hpp"
#include "../settings.hpp"
#include <array>
#include <vector>

namespace ly{
    typedef struct BRTSD { } BRTSetupData;
    typedef struct BRTDL { } BRTDrawList;
    typedef struct BRTCD { virtual ~BRTCD(){}; } BRTChangeData;
    
    class BatchRenderer;
    class BatchRenderTarget;

    class BatchRenderTarget{
        public:
            virtual void setup(BatchRenderer* t_renderer) = 0;
            virtual void change(BatchRenderer* t_renderer, const BRTChangeData& t_changeData, const range_t<uint_t>& t_vbRange, const range_t<uint_t>& t_ibRange){}
            BRTSetupData getSetupData(){ return m_setupData; }
        protected:
            BRTSetupData m_setupData;
    };

    class BatchRenderer{
        public:
            std::array<Vertex, ( BATCH_VERTEX_BUFFER_SIZE / sizeof(Vertex) ) > m_vertexBuffer;
            std::array<float_t, ( BATCH_INDEX_BUFFER_SIZE / sizeof(float_t) ) > m_indexBuffer;

            BatchRenderer();
            ~BatchRenderer();

            void render();
            void addTarget(BatchRenderTarget* t_target);
            void setDrawList( std::vector<BRTDrawList>&& t_renderDrawList );
            void modifyRenderTarget( const uint_t t_renderTargetId, const BRTChangeData& t_changeData );

        private:
            std::vector<BatchRenderTarget*> m_renderTargets;
            std::vector<BRTDrawList> m_renderDrawList;
    };
}

#endif // BATCH_RENDERER_HPP
