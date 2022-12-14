#pragma once

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <LuaBridge/LuaBridge.h>

static const luaL_Reg luaLibs[] = {
    {"", luaopen_base},
    {nullptr, nullptr}};

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

    /// @brief Call a lua function with no arguments or results
    /// @param name
    /// @return true if execution was successful
    bool call(const char *name);

    /// @brief Loads and executes lua code
    /// @param code
    bool loadCode(const char *code);

    ~LuaMachine()
    {
        std::cout << "Closing machine" << std::endl;
        lua_close(m_lua);
    }

private:
    lua_State *m_lua;
};