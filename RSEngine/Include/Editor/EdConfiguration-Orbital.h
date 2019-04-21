/*

Orbital-ng
placeholder copyright stuff (c) 2019

*/

#ifndef _EdConfiguration_Orbital_h_
#define _EdConfiguration_Orbital_h_

namespace rs {
    namespace Editor {
        class EOrbitalConfig : public EditorComponent {
        public:
            bool Initialize();
            void Draw(bool* p_open);
        };
    }
}

#endif // _EdConfiguration_Orbital_h_
