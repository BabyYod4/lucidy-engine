#include "batch_renderer.hpp"
#include "../generic/graphic_lib.hpp"
#include <algorithm>
#include <stddef.h>

ly::BatchRenderer::BatchRenderer():
    m_maxVertexBatchSize( ( BATCH_VERTEX_BUFFER_SIZE / sizeof(Vertex) ) ),
    m_maxIndexBatchSize( ( BATCH_INDEX_BUFFER_SIZE / sizeof(float_t) ) ),
    allowRender(false)
 { initLayout(); }

ly::BatchRenderer::~BatchRenderer() {}

void ly::BatchRenderer::render() {
    if (allowRender){
        if (BATCH_BUFFER_AMOUNT > 1){
            for( uint_t i=0; i<BATCH_BUFFER_AMOUNT; i++){
                GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderId));
                GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_buffer.vertexBuffer[i].size(), m_buffer.vertexBuffer[i].data() ));

                GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibRenderId));
                GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint_t) * m_buffer.indexBuffer[i].size(), m_buffer.indexBuffer[i].data() ));

                GLCALL(glBindVertexArray(m_vaRenderId));
                GLCALL( glDrawElements(GL_TRIANGLES, m_buffer.indexBuffer[i].size(), GL_UNSIGNED_INT, nullptr ) );
            }
        }else{
            GLCALL( glBindVertexArray(m_vaRenderId) );
            GLCALL( glDrawElements(GL_TRIANGLES, m_buffer.indexBuffer[0].size(), GL_UNSIGNED_INT, nullptr ) );
        }
    }

}

void ly::BatchRenderer::addTarget(const string_t& t_name, BatchRenderTarget* t_target) {
    m_renderTargets.insert( { t_name, t_target } );
}

ly::bool_t ly::BatchRenderer::setDrawList(const std::vector<string_t>& t_targetNames) {
    if( t_targetNames.size() == 0 ){ 
        std::cerr << "Unable to setup Draw List because no data is provided!" << std::endl;
        allowRender = false;
        return false; 
    }

    for( const string_t& e : t_targetNames ){ 
        if( m_renderTargets.find(e) == m_renderTargets.end() ){ 
            std::cerr << "Unable to setup Draw List because target [" << e << "] does not exist!" << std::endl;
            allowRender = false;
            return false; 
        } 
    }
    
    m_renderRankingList.clear();
    m_renderRankingList.reserve( t_targetNames.size() );
    
    for(uint_t i=0; i<t_targetNames.size(); i++){
        m_renderRankingList[i].targetName = t_targetNames[i];
        m_renderRankingList[i].setupData = m_renderTargets[ t_targetNames[i] ]->getSetupData();
    }

    std::sort( m_renderRankingList.begin(), m_renderRankingList.end(), BRTRankingMethod );

    uint_t currentBatchSizeVert = 0;
    uint_t currentBatchSizeIndex = 0;
    uint_t currentBatchNumVert = 0;
    uint_t currentBatchNumIndex = 0;

    for( auto& target: m_renderRankingList ){
        if( (currentBatchNumVert > BATCH_BUFFER_AMOUNT) || (currentBatchNumIndex > BATCH_BUFFER_AMOUNT) ){ 
            std::cerr << "Unable to setup Draw List because its requires more than the maximum of " << BATCH_BUFFER_AMOUNT << " batches." 
                << "\t- If you need more batches, change the value of 'BATCH_BUFFER_AMOUNT' in the 'settings.hpp file' "
                << std::endl;
            allowRender = false;
            return false; 
        }

        if (currentBatchSizeVert >= m_maxVertexBatchSize){ currentBatchSizeVert = 0; currentBatchNumVert++;  }
        if (currentBatchSizeIndex >= m_maxIndexBatchSize){ currentBatchSizeIndex = 0; currentBatchNumIndex++;  }

        target.drawData.vbBatchNum = currentBatchNumVert;
        target.drawData.ibBatchNum = currentBatchNumIndex;
        target.drawData.vbRange = range_t<uint_t>{ currentBatchSizeVert, currentBatchSizeVert + target.setupData.requiredVertices  };
        target.drawData.ibRange = range_t<uint_t>{ currentBatchSizeIndex, currentBatchSizeIndex + target.setupData.requiredIndices  };

        currentBatchSizeVert += target.setupData.requiredVertices;
        currentBatchSizeIndex += target.setupData.requiredIndices;
    }

    for( const auto& target: m_renderRankingList ){
        m_renderTargets[ target.targetName ]->setup( m_buffer, target.drawData );
    }

    if (BATCH_BUFFER_AMOUNT == 1){
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderId));
        GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_buffer.vertexBuffer[0].size(), m_buffer.vertexBuffer[0].data() ));

        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibRenderId));
        GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint_t) * m_buffer.indexBuffer[0].size(), m_buffer.indexBuffer[0].data() ));
    }

    allowRender = true;
    return true;
}

ly::bool_t ly::BatchRenderer::modifyTarget(const string_t& t_targetName, const BRTChangeData& t_changeData ){
    if( m_renderTargets.find(t_targetName) == m_renderTargets.end() ){ 
        std::cerr << "Unable to modify target [" << t_targetName << "] because it does not exist!" << std::endl;
        return false; 
    }
    
    const size_t i = getTargetDrawListIndex( t_targetName );
    if ( i == (size_t)(-1) ){ 
        std::cerr << "Unable to modify target [" << t_targetName << "] because it is not selected in the drawList!" << std::endl;
        return false; 
    }

    m_renderTargets[t_targetName]->change( m_buffer, m_renderRankingList[i].drawData, t_changeData );
    return true;
}

size_t ly::BatchRenderer::getTargetDrawListIndex(const string_t& t_targetName) {
    for( size_t i=0; i < m_renderRankingList.size(); i++ ){
        if ( m_renderRankingList[i].targetName == t_targetName ){ return i; }
    }
    return (size_t)(-1);
}

void ly::BatchRenderer::initLayout() {
    GLCALL(glCreateVertexArrays(1, &m_vaRenderId));
    GLCALL(glBindVertexArray(m_vaRenderId));

    GLCALL(glCreateBuffers(1, &m_vbRenderId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderId));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_maxVertexBatchSize, nullptr, GL_DYNAMIC_DRAW ));

    GLCALL(glEnableVertexArrayAttrib(m_vbRenderId, 0));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos) ));

    GLCALL(glEnableVertexArrayAttrib(m_vbRenderId, 1));
    GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color) ));

    GLCALL(glCreateBuffers(1, &m_ibRenderId));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibRenderId));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint_t) * m_maxIndexBatchSize, nullptr, GL_DYNAMIC_DRAW ));

}
