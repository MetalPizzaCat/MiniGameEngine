#include "LuaMachine.hpp"

bool LuaMachine::loadCode(const char *code)
{
    if (luaL_dostring(m_lua, code) != LUA_OK)
    {
        std::cout << " Error loading code" << std::endl;
        const char *result = lua_tostring(m_lua, -1);
        std::cout << result << std::endl;
        return false;
    }
    return true;
}

bool LuaMachine::isFunctionPresent(const char *name)
{
    luabridge::LuaRef fn = luabridge::getGlobal(m_lua, name);
    return !fn.isNil() && fn.isFunction();
}