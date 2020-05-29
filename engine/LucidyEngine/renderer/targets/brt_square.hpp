#ifndef BRT_SQUARE_HPP
#define BRT_SQUARE_HPP

#include "../batch_render_target.hpp"

namespace ly{

    class BRTSquare : public BatchRenderTarget{
        public:
            BRTSquare(float_t t_scale);
            BRTSetupData getSetupData() override;
            const Vertex* getVertexBuff() override;
            const uint_t* getIndexBuff() override;
        private:
            std::array<Vertex, 4 > m_vb;
            std::array<uint_t, 6> m_ib; 

    };

}

#endif //BRT_SQUARE_HPP
