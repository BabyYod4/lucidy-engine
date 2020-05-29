#ifndef BRT_CUBE_HPP
#define BRT_CUBE_HPP

#include "../batch_render_target.hpp"

namespace ly{

    class BRTCube : public BatchRenderTarget{
        public:
            BRTCube();
            BRTSetupData getSetupData() override;
            const Vertex* getVertexBuff() override;
            const uint_t* getIndexBuff() override;
        private:
            std::array<Vertex, 8> m_vb;
            std::array<uint_t, 36> m_ib; 

    };

}

#endif //BRT_CUBE_HPP
