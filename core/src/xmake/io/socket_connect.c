/*!A cross-platform build utility based on Lua
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (C) 2015 - 2019, TBOOX Open Source Group.
 *
 * @author      ruki
 * @file        socket_connect.c
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME    "socket_connect"
#define TB_TRACE_MODULE_DEBUG   (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

// io.socket_connect(sock, addr, port, family)
tb_int_t xm_io_socket_connect(lua_State* lua)
{
    // check
    tb_assert_and_check_return_val(lua, 0);

    // is user data?
    if (!lua_isuserdata(lua, 1)) 
        return 0;

    // get socket
    tb_socket_ref_t sock = (tb_socket_ref_t)lua_touserdata(lua, 1);
    tb_check_return_val(sock, 0);

    // get address
    tb_char_t const* address = lua_tostring(lua, 2);
    tb_assert_and_check_return_val(address, 0);

    // get port
    tb_size_t port = (tb_size_t)luaL_checknumber(lua, 3);

    // get family
    tb_char_t const* family = lua_tostring(lua, 4);

    // init address
    tb_ipaddr_t addr;
    tb_ipaddr_set(&addr, address, port, (family && !tb_strcmp(family, "ipv6"))? TB_IPADDR_FAMILY_IPV6 : TB_IPADDR_FAMILY_IPV4);

    // connect socket
    lua_pushnumber(lua, (tb_int_t)tb_socket_connect(sock, &addr));
    return 1;
}

