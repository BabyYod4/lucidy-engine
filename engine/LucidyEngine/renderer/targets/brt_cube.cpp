#include "brt_cube.hpp"


ly::BRTSetupData ly::BRTCube::getSetupData() {
    return BRTSetupData{ 8, 36 };
}

ly::BRTCube::BRTCube(): 
    m_vb({
        // front
        Vertex{ { -0.3f, -0.3f,  0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        Vertex{ {  0.3f, -0.3f,  0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        Vertex{ {  0.3f,  0.3f,  0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        Vertex{ { -0.3f,  0.3f,  0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        // back
        Vertex{ { -0.3f, -0.3f, -0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        Vertex{ {  0.3f, -0.3f, -0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        Vertex{ {  0.3f,  0.3f, -0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
        Vertex{ { -0.3f,  0.3f, -0.3f }, { 0.3f, 0.3f, 0.3f, 0.3f } }, 
    }),
    
    m_ib({
        // front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
    })

{}

const ly::Vertex* ly::BRTCube::getVertexBuff() {
    return m_vb.data();
}

const ly::uint_t* ly::BRTCube::getIndexBuff() {
    return m_ib.data();
}
