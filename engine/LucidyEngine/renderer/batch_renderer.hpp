#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "vertex.hpp"
#include "../settings.hpp"

#include <array>
#include <vector>
#include <unordered_map>

namespace ly{
    typedef struct BRTCD { virtual ~BRTCD(){}; } BRTChangeData;
    typedef struct BRTSD { int_t requiredVertices; int_t requiredIndices; } BRTSetupData;
    typedef struct BRTDL { uint_t vbBatchNum; uint_t ibBatchNum; range_t<uint_t> vbRange; range_t<uint_t> ibRange; } BRTDrawList;
    typedef struct BRTRD { string_t targetName; BRTSetupData setupData; BRTDrawList drawData; } BRTRankData;
    
    class BatchRenderer;
    class BatchRenderTarget;

    typedef struct BatchRenderBuffer{
        std::array< 
            std::array< Vertex, ( BATCH_VERTEX_BUFFER_SIZE / sizeof(Vertex) ) >, 
            BATCH_BUFFER_AMOUNT 
        > vertexBuffer;

        std::array< 
            std::array<float_t, ( BATCH_INDEX_BUFFER_SIZE / sizeof(uint_t) ) >, 
            BATCH_BUFFER_AMOUNT
        > indexBuffer;
    } BatchRenderBuffer;

    class BatchRenderTarget{
        public:
            virtual void setup(BatchRenderBuffer& t_buff, const BRTDrawList& t_bufferSetupData ) = 0;
            virtual void change(BatchRenderBuffer& t_buff, const BRTDrawList& t_bufferSetupData, const BRTChangeData& t_changeData){}
            virtual BRTSetupData getSetupData() = 0;
        protected:
            BRTSetupData m_setupData;
    };

    static bool BRTRankingMethod( const BRTRankData& lhs, const BRTRankData& rhs ){
        return ( lhs.setupData.requiredIndices + lhs.setupData.requiredVertices ) > ( rhs.setupData.requiredIndices + rhs.setupData.requiredVertices );
    }

    class BatchRenderer{
        public:
            BatchRenderer();
            ~BatchRenderer();

            void render();
            void addTarget(const string_t& t_name, BatchRenderTarget* t_target);
            bool_t modifyTarget( const string_t& t_targetName, const BRTChangeData& t_changeData );
            bool_t setDrawList( const std::vector<string_t>& t_targetNames );


        private:
            uint_t m_vbRenderId;
            uint_t m_vaRenderId;
            uint_t m_ibRenderId;
            const uint_t m_maxVertexBatchSize;
            const uint_t m_maxIndexBatchSize;
            bool_t allowRender;

            BatchRenderBuffer m_buffer;
            std::unordered_map<string_t, BatchRenderTarget*> m_renderTargets;
            std::vector<BRTRankData> m_renderRankingList;

            size_t getTargetDrawListIndex( const string_t& t_targetName );
            void initLayout();


    };
}

#endif // BATCH_RENDERER_HPP
