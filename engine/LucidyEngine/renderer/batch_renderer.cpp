#include "batch_renderer.hpp"
#include "../generic/graphic_lib.hpp"
#include <algorithm>
#include <stddef.h>

ly::BatchRenderer::BatchRenderer():
    m_maxVertices(( (BATCH_RENDERER_BUFF_SIZE * BATCH_RENDERER_VB_RATIO.num) / BATCH_RENDERER_VB_RATIO.denum ) / sizeof(Vertex)  ),
    m_maxIndices(( (BATCH_RENDERER_BUFF_SIZE * BATCH_RENDERER_IB_RATIO.num) / BATCH_RENDERER_IB_RATIO.denum ) / sizeof(uint_t) ),
    allowRender(true), ibLoop(false), m_indexCount(0), m_batchCount(0)
 { initLayout(); }

ly::BatchRenderer::~BatchRenderer() {}

void ly::BatchRenderer::draw() {
    if (allowRender){

        if( m_batchCount == 1) { 
            applyBatch(1);
            GLCALL( glBindVertexArray(m_vaRenderId) );
            GLCALL( glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr ) ); 
        }else{
            for(uint_t i=1; i<=m_batchCount; i++){
                applyBatch(i);
                GLCALL( glBindVertexArray(m_vaRenderId) );
                GLCALL( glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr ) ); 
            }
        }

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
                BRTDrawData{0, {0,0}, {0,0} }, 
                m_renderTargets[ t_targetNames[i] ]->getSetupData() 
            } 
        );
    }

    std::sort( m_drawList.begin(), m_drawList.end(), BRTRankingMethod );

    for( const auto& target: m_drawList ){
        m_renderTargets[ target.targetName ]->setup();
    }
        
    if ( checkBatchSetup() ){
        allowRender = true;
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
    // std::cout << "Required: " << m_drawList[0].targetName << std::endl;

    if ( m_drawList[0].setupData.requiredVertices > m_maxVertices ){
        std::cerr << "Unable to setup Draw List because vertex requirment of largest BRTTarget [" << m_drawList[0].targetName << "] is larger than the maximum buffer size per batch draw call! \r\n" 
            << "\t - MaxBatchBufferSize: " << m_maxVertices * sizeof(Vertex) << " bytes" << "\r\n"
            << "\t - BiggestRenderTargetSize: " << m_drawList[0].setupData.requiredVertices * sizeof(Vertex) << " bytes" << std::endl;
        return false;
    }

    if ( m_drawList[0].setupData.requiredIndices > m_maxIndices ){
        std::cerr << "Unable to setup Draw List because index requirement of largest BRTTarget [" << m_drawList[0].targetName << "] is larger than the maximum buffer size per batch draw call!" 
            << "\t - MaxBatchBufferSize: " << m_maxIndices * sizeof(uint_t) << " bytes" << "\r\n"
            << "\t - BiggestRenderTargetSize: " << m_drawList[0].setupData.requiredIndices * sizeof(uint_t) << " bytes" << std::endl;
        return false;
    }

    uint_t neededVB = 0, neededIB = 0;
    uint_t batchNumVB = 1, batchNumIB = 1;    
    for( const auto& target: m_drawList ){
        if (neededVB >= m_maxVertices) { batchNumVB++; neededVB=0; }
        if (neededIB >= m_maxIndices) { batchNumIB++; neededIB=0; }
        neededVB += target.setupData.requiredVertices;
        neededIB += target.setupData.requiredIndices;
    }
    
    if (batchNumVB == batchNumIB){ 
        ibLoop = false;
        m_batchCount = batchNumVB; 
    } else if (batchNumVB > batchNumIB){ 
        ibLoop = false; 
        m_batchCount = batchNumVB; 
    } else if (batchNumVB < batchNumIB){
        ibLoop = true;
        m_batchCount = batchNumIB; 
    }

    uint_t batchNum = 1, needed=0;
    for( auto& target: m_drawList ){
        target.drawData.batchNum = batchNum;
        
        if ( ibLoop ){ 
            needed += target.setupData.requiredIndices;
            if (needed >= m_maxIndices ) { batchNum++; needed = 0; }
        } else { 
            needed += target.setupData.requiredVertices; 
            if (needed >= m_maxVertices ) { batchNum++; needed = 0; }
        }
    }


    return true;

}

void ly::BatchRenderer::applyBatch(const uint_t t_batchNum) {

    if (t_batchNum == 0){ return; }
    
    uint_t offset = 0;
    uint_t required = 0;
    
    std::vector<BRTData>::iterator start;
    std::vector<BRTData>::iterator end;
    if (m_batchCount == 1){
        start = m_drawList.begin();
        end = m_drawList.end();
        m_indexCount = 0;
    }else{
        start = std::find_if (m_drawList.begin(), m_drawList.end(), [&t_batchNum](const BRTData& i)->bool_t{ return t_batchNum == i.drawData.batchNum; }  );
        end = std::find_if (m_drawList.begin(), m_drawList.end(), [&t_batchNum](const BRTData& i)->bool_t{ return (t_batchNum + 1) == i.drawData.batchNum; }  );
    }

    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbRenderId));

    std::for_each(start, end, [this, &offset, &required](BRTData& target){
        required = target.setupData.requiredVertices;
        GLCALL(glBufferSubData(GL_ARRAY_BUFFER, sizeof(Vertex) * offset, sizeof(Vertex) * required, m_renderTargets[target.targetName]->getVertexBuff() ));
        target.drawData.offsetVb.start = offset;
        offset += required;
        target.drawData.offsetVb.end = offset;
    } );

    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibRenderId));
    offset = 0; required = 0;

    std::for_each(start, end, [this, &offset, &required](BRTData& target){
        required = target.setupData.requiredIndices;
        GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint_t) * offset, sizeof(uint_t) * required, m_renderTargets[target.targetName]->getIndexBuff() ));
        target.drawData.offsetIb.start = offset;
        offset += required;
        target.drawData.offsetIb.end = offset;
        m_indexCount += required;
    } );

}
