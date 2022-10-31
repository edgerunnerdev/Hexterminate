// Copyright 2022 Pedro Nunes
//
// This file is part of Genesis.
//
// Genesis is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Genesis is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Genesis. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <memory>

#include "coredefines.h"

namespace Genesis::Sound
{

namespace Private
{
    class SoundBusImpl;
    using SoundBusImplUniquePtr = std::unique_ptr<SoundBusImpl>;
}

GENESIS_DECLARE_SMART_PTR( SoundBus );
GENESIS_DECLARE_SMART_PTR( SoundInstance );

class SoundBus
{
public:
    friend class SoundInstance;

    enum class Type
    {
        SFX,
        Music,

        Count
    };

    SoundBus(Type type);
    virtual ~SoundBus();
    virtual void* GetNativeBus() const;
    
    Type GetType() const;

private:

    Private::SoundBusImplUniquePtr m_pImpl;
    Type m_Type;
};

inline SoundBus::Type SoundBus::GetType() const
{
    return m_Type;
}

} // namespace Genesis::Sound
