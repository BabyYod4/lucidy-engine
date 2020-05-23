#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include "window.hpp"

namespace ly{

    class GuiWindow{
    public:
        GuiWindow();
        GuiWindow(Window& t_window);
        ~GuiWindow();

        void open();
        void close();
        void clear();
        void flush();

        void drawStart( cstring_t t_menuName );
        void drawEnd();

        void drawText( cstring_t t_text );
        bool drawButton( cstring_t t_name );
    private:
        Window& m_window;
    };

}
#endif /* GUI_WINDOW_HPP */
