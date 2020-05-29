#include "brt_square.hpp"


ly::BRTSetupData ly::BRTSquare::getSetupData() {
    return BRTSetupData{ 4, 6 };
}

ly::BRTSquare::BRTSquare(float_t t_scale): 

    m_vb({
        Vertex { { -0.5f*t_scale, -0.5f*t_scale, 0.0f } , { 1.0f, 0.0f, 0.0f, 1.0f } }, 
        Vertex { {  0.5f*t_scale, -0.5f*t_scale, 0.0f } , { 0.0f, 1.0f, 1.0f, 1.0f } }, 
        Vertex { {  0.5f*t_scale,  0.5f*t_scale, 0.0f } , { 0.0f, 0.0f, 1.0f, 1.0f } }, 
        Vertex { { -0.5f*t_scale,  0.5f*t_scale, 0.0f } , { 0.0f, 0.0f, 0.0f, 1.0f } }, 
    }),

    m_ib({
        8, 9, 10, // first triangle 8 9 10
		10, 11, 8  // second triangle 10 11 8
    })
{}

const ly::Vertex* ly::BRTSquare::getVertexBuff() {
    return m_vb.data();
}

const ly::uint_t* ly::BRTSquare::getIndexBuff() {
    return m_ib.data();
}
