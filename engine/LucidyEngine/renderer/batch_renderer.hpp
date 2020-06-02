#ifndef BATCH_RENDERER_HPP
#define BATCH_RENDERER_HPP

#include "batch_render_target.hpp"

#include <vector>
#include <unordered_map>

namespace ly{

    static bool BRTRankingMethod( const BRTData& lhs, const BRTData& rhs ){
        return ( lhs.setupData.requiredIndices + lhs.setupData.requiredVertices ) > ( rhs.setupData.requiredIndices + rhs.setupData.requiredVertices );
    }

    class BatchRenderer{
        public:
            BatchRenderer( const size_t& t_buffSizeBytes, const ratio_t& t_vbRatio, const ratio_t& t_ibRatio );
            ~BatchRenderer();

            void draw();
            void addTarget( const string_t& t_name, BatchRenderTarget* t_target);
            bool_t modifyTarget( const string_t& t_targetName, cstring_t t_changeCommand );
            bool_t setDrawList( const std::vector<string_t>& t_targetNames );


        private:
            uint_t m_vbRenderId, m_vaRenderId, m_ibRenderId;
            const uint_t m_maxVertices, m_maxIndices;

            bool_t allowRender;
            uint_t m_indexCount;

            std::unordered_map<string_t, BatchRenderTarget*> m_renderTargets;
            std::vector<BRTData> m_drawList;

            size_t getTargetDrawListIndex( const string_t& t_targetName );
            void initLayout();

            bool checkBatchSetup();
            bool_t drawListFits();
            void applyBatch();

    };
}

#endif // BATCH_RENDERER_HPP
