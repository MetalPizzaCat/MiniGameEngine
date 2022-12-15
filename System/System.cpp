#include "System.hpp"

void System::bindLua(lua_State *state)
{
    luabridge::getGlobalNamespace(state)
            .beginClass<System>("System")
            .addFunction("print", &System::print)
            .endClass();
}