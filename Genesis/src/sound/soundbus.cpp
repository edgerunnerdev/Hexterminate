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

#include "sound/soundbus.h"

#include "sound/private/null/soundbus.h"
#include "sound/private/soloud/soundbus.h"

namespace Genesis::Sound
{

SoundBus::SoundBus( Type type )
    : m_Type( type )
{
#if defined SOUND_USE_SOLOUD
    m_pImpl = std::make_unique<Private::SoLoud::SoundBus>();
#else
    m_pImpl = std::make_unique<Private::Null::SoundManager>();
#endif
}

SoundBus::~SoundBus()
{
    // Don't move empty destructor to header, needed for m_pImpl to be deleted correctly.
}

void* SoundBus::GetNativeBus() const
{
    return m_pImpl->GetNativeBus();
}

} // namespace Genesis::Sound
