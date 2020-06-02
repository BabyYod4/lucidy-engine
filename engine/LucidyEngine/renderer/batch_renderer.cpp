#include "batch_renderer.hpp"
#include "../generic/graphic_lib.hpp"
#include <algorithm>
#include <stddef.h>

ly::BatchRenderer::BatchRenderer(const size_t& t_buffSizeBytes, const ratio_t& t_vbRatio, const ratio_t& t_ibRatio):
    m_maxVertices(( (t_buffSizeBytes * t_vbRatio.num) / t_vbRatio.denum ) / sizeof(Vertex)  ),
    m_maxIndices(( (t_buffSizeBytes * t_ibRatio.num) / t_ibRatio.denum ) / sizeof(uint_t) ),
    allowRender(true)
 { initLayout(); }

ly::BatchRenderer::~BatchRenderer() {
    m_drawList.clear();
    std::vector<BRTData>().swap(m_drawList);
    for( const auto& e: m_renderTargets ){ e.second->destroy(); }
    m_renderTargets.clear();
    std::unordered_map<string_t, BatchRenderTarget*>().swap(m_renderTargets);
}

void ly::BatchRenderer::draw() {
    if (allowRender){
        GLCALL( glBindVertexArray(m_vaRenderId) );
        GLCALL( glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr ) ); 
    }
}

void ly::BatchRenderer::addTarget(const string_t& t_name, BatchRenderTarget* t_target) {
    m_renderTargets.insert( { t_name, t_target } );
}

ly::bool_t ly::BatchRenderer::setDrawList(const std::vector<string_t>& t_targetNames) {
    if( t_targetNames.size() < 1 ){ 
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
    
    m_drawList.clear();
    m_drawList.reserve( t_targetNames.size() );

    for(size_t i=0; i<t_targetNames.size(); i++){
        m_drawList.push_back( 
            BRTData{ 
                t_targetNames[i], 
                BRTDrawData{ {0,0}, {0,0} }, 
                m_renderTargets[ t_targetNames[i] ]->getSetupData() 
            } 
        );
    }

    std::sort( m_drawList.begin(), m_drawList.end(), BRTRankingMethod );

    if ( checkBatchSetup() ){
        allowRender = true;
        for( const auto& target: m_drawList ){ m_renderTargets[ target.targetName ]->setup(); }
        applyBatch();
    }else{
        allowRender = false;
    }

    return allowRender;
}

ly::bool_t ly::BatchRenderer::modifyTarget(const string_t& t_targetName, cstring_t t_changeCommand ){
    if( m_renderTargets.find(t_targetName) == m_renderTargets.end() ){ 
        std::cerr << "Unable to modify target [" << t_targetName << "] because it does not exist!" << std::endl;
        return false; 
    }
    
    const size_t i = getTargetDrawListIndex( t_targetName );
    if ( i == (size_t)(-1) ){ 
        std::cerr << "Unable to modify target [" << t_targetName << "] because it is not selected in the drawList!" << std::endl;
        return false; 
    }

    m_renderTargets[t_targetName]->change( t_changeCommand );
    return true;
}

size_t ly::BatchRenderer::getTargetDrawListIndex(const string_t& t_targetName) {
    for( size_t i=0; i < m_drawList.size(); i++ ){
        if ( m_drawList[i].targetName == t_targetName ){ return i; }
    }
    return (size_t)(-1);
}

void ly::BatchRenderer::initLayout() {
    GLCALL(glCreateVertexArrays(1, &m_vaRenderId));
    GLCALL(glBindVertexArray(m_vaRenderId));

    GLCALL(glCreateBuffers(1, &m_vbRenderId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderId));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_maxVertices, nullptr, GL_DYNAMIC_DRAW ));

    GLCALL( glEnableVertexAttribArray(0) );
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, pos) ));

    GLCALL( glEnableVertexAttribArray(1) );
    GLCALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color) ));

    GLCALL(glCreateBuffers(1, &m_ibRenderId));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibRenderId));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint_t) * m_maxIndices, nullptr, GL_DYNAMIC_DRAW ));

}

bool ly::BatchRenderer::checkBatchSetup() {

    if ( m_drawList[0].setupData.requiredVertices > m_maxVertices ){
        if (m_drawList.back().setupData.requiredVertices > m_maxVertices){
            std::cerr << "Unable to setup Draw List because vertex requirment of smallest BRTTarget [" << m_drawList.back().targetName << "] is larger than the maximum buffer size per batch draw call! \r\n" 
            << "\t - MaxBatchBufferSize: " << m_maxVertices * sizeof(Vertex) << " bytes" << "\r\n"
            << "\t - BiggestRenderTargetSize: " << m_drawList.back().setupData.requiredVertices * sizeof(Vertex) << " bytes" << std::endl;
            return false;
        }
        std::cerr << "Unable to setup Draw List because vertex requirment of largest BRTTarget [" << m_drawList[0].targetName << "] is larger than the maximum buffer size per batch draw call! \r\n" 
            << "\t - MaxBatchBufferSize: " << m_maxVertices * sizeof(Vertex) << " bytes" << "\r\n"
            << "\t - BiggestRenderTargetSize: " << m_drawList[0].setupData.requiredVertices * sizeof(Vertex) << " bytes" << std::endl;
        return false;
    }

    if ( m_drawList[0].setupData.requiredIndices > m_maxIndices ){
        if (m_drawList.back().setupData.requiredIndices > m_maxIndices){
            std::cerr << "Unable to setup Draw List because index requirment of smallest BRTTarget [" << m_drawList.back().targetName << "] is larger than the maximum buffer size per batch draw call! \r\n" 
            << "\t - MaxBatchBufferSize: " << m_maxIndices * sizeof(uint_t) << " bytes" << "\r\n"
            << "\t - BiggestRenderTargetSize: " << m_drawList.back().setupData.requiredIndices * sizeof(Vertex) << " bytes" << std::endl;
            return false;
        }
        std::cerr << "Unable to setup Draw List because index requirement of largest BRTTarget [" << m_drawList[0].targetName << "] is larger than the maximum buffer size per batch draw call!" 
            << "\t - MaxBatchBufferSize: " << m_maxIndices * sizeof(uint_t) << " bytes" << "\r\n"
            << "\t - BiggestRenderTargetSize: " << m_drawList[0].setupData.requiredIndices * sizeof(uint_t) << " bytes" << std::endl;
        return false;
    }


    if ( !drawListFits() ){ std::cerr << "Unable to setup Draw List because index and or vertex requirments are too large" << std::endl; }

    return true;

}

void ly::BatchRenderer::applyBatch() {
 
    m_indexCount = 0;
    uint_t offset = 0;
    uint_t required = 0;
    
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderId));

    for( auto& target: m_drawList){
        required = target.setupData.requiredVertices;
        GLCALL(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex) * offset, sizeof(Vertex) * required, m_renderTargets[target.targetName]->getVertexBuff() ));
        target.drawData.offsetVb.start = offset;
        offset += required;
        target.drawData.offsetVb.end = offset;
    }

    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibRenderId));
    offset = 0; required = 0;

    for( auto& target: m_drawList){
        required = target.setupData.requiredIndices;
        GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint_t) * offset, sizeof(uint_t) * required, m_renderTargets[target.targetName]->getIndexBuff() ));
        target.drawData.offsetIb.start = offset;
        offset += required;
        target.drawData.offsetIb.end = offset;
        m_indexCount += required;
    }

}

ly::bool_t ly::BatchRenderer::drawListFits() {
    size_t vertSize = 0, indSize = 0;
    for( const auto& e: m_drawList){ 
        vertSize += e.setupData.requiredVertices; 
        indSize += e.setupData.requiredIndices;
    }
    return ( vertSize <= m_maxVertices ) && ( indSize <= m_maxIndices );
}

