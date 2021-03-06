/*
 *
 * Copyright (C) 2011-2012 ArkCORE2 <http://www.arkania.net/>
 * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/> 
 *
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __UPDATEDATA_H
#define __UPDATEDATA_H

#include "ByteBuffer.h"
class WorldPacket;

enum OBJECT_UPDATE_TYPE
{
    UPDATETYPE_VALUES               = 0,
    UPDATETYPE_CREATE_OBJECT        = 1,
    UPDATETYPE_CREATE_OBJECT2       = 2,
    UPDATETYPE_OUT_OF_RANGE_OBJECTS = 3,
};

enum OBJECT_UPDATE_FLAGS
{
    UPDATEFLAG_NONE         = 0x0000,
    UPDATEFLAG_SELF         = 0x0001, //  0
    UPDATEFLAG_TRANSPORT    = 0x0002, //  1
    UPDATEFLAG_HAS_TARGET   = 0x0004, //  2
    UPDATEFLAG_UNK3         = 0x0008, //  3 old UPDATEFLAG_LOWGUID
    UPDATEFLAG_UNK4         = 0x0010, //  4 old UPDATEFLAG_HIGHGUID
    UPDATEFLAG_LIVING       = 0x0020, //  5
    UPDATEFLAG_HAS_POSITION = 0x0040, //  6
    UPDATEFLAG_VEHICLE      = 0x0080, //  7
    UPDATEFLAG_POSITION     = 0x0100, //  8
    UPDATEFLAG_ROTATION     = 0x0200, //  9
    UPDATEFLAG_UNK10        = 0x0400, // 10 4.0.3 not found
    UPDATEFLAG_UNK11        = 0x0800, // 11 4.0.3
    UPDATEFLAG_UNK12        = 0x1000, // 12 4.0.3
};

class UpdateData
{
    public:
        UpdateData(uint16 map);

        void AddOutOfRangeGUID(std::set<uint64>& guids);
        void AddOutOfRangeGUID(uint64 guid);
        void AddUpdateBlock(const ByteBuffer &block);
        bool BuildPacket(WorldPacket* packet);
        bool HasData() const { return m_blockCount > 0 || !m_outOfRangeGUIDs.empty(); }
        void Clear();

        std::set<uint64> const& GetOutOfRangeGUIDs() const { return m_outOfRangeGUIDs; }

    protected:
        uint16 m_map;
        uint32 m_blockCount;
        std::set<uint64> m_outOfRangeGUIDs;
        ByteBuffer m_data;

        void Compress(void* dst, uint32 *dst_size, void* src, int src_size);
};
#endif
