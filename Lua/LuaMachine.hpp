#pragma once

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>
#include "../Log.hpp"

/// @brief Wrapper around lua_State that handles lua state and function calls
class LuaMachine
{
public:
    /// @brief Creates a new lua state with table,math and string loaded
    LuaMachine()
    {
        m_lua = luaL_newstate();
        luaL_openlibs(m_lua);
        // enable tables
        /*lua_pushcfunction(m_lua, luaopen_table);
        lua_pushliteral(m_lua, LUA_TABLIBNAME);
        lua_call(m_lua, 1, 0);
        // enable lua
        lua_pushcfunction(m_lua, luaopen_base);
        lua_pushliteral(m_lua, "");
        lua_call(m_lua, 1, 0);
        // enable string
        lua_pushcfunction(m_lua, luaopen_string);
        lua_pushliteral(m_lua, LUA_STRLIBNAME);
        lua_call(m_lua, 1, 0);
        // enable math
        lua_pushcfunction(m_lua, luaopen_math);
        lua_pushliteral(m_lua, LUA_MATHLIBNAME);
        lua_call(m_lua, 1, 0);
        // enable io
        lua_pushcfunction(m_lua, luaopen_io);
        lua_pushliteral(m_lua, LUA_IOLIBNAME);
        lua_call(m_lua, 1, 0);*/
    }
    /// @brief Get raw lua state
    /// @return
    lua_State *getState() { return m_lua; }

    /// @brief Call a lua function, ignoring the return result
    /// @param name name of the function
    /// @return true if execution was successful
    template <typename... Args>
    bool call(const char *name, Args... args)
    {
        luabridge::LuaRef fn = luabridge::getGlobal(m_lua, name);
        if (fn.isNil())
        {
            Log::error(fmt::format("Unable to find function with name: {}", name));
            return false;
        }
        if (!fn.isFunction())
        {
            Log::error(fmt::format("Object {} is not a function", name));
            return false;
        }
        fn(args...);
        return true;
    }

    /// @brief Check if a function is present in loaded lua code
    /// @param name
    /// @return
    bool isFunctionPresent(const char *name);

    /// @brief Load chunk of lua code and execute it immediately
    /// @param code Text for the code
    /// @return True is code was successfully loaded and executed
    bool loadCode(const char *code);

    ~LuaMachine()
    {
        lua_close(m_lua);
    }

private:
    lua_State *m_lua;
};