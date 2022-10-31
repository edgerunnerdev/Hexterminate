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

#include "sound/private/soloud/soundbus.h"

// clang-format off
#include "beginexternalheaders.h"
#include <soloud.h>
#include <soloud_bus.h>
#include "endexternalheaders.h"
// clang-format on

namespace Genesis::Sound::Private::SoLoud
{

extern ::SoLoud::Soloud* g_pSoloud;

SoundBus::SoundBus()
{
	m_pBus = std::make_unique<::SoLoud::Bus>();
	m_Handle = g_pSoloud->play( *m_pBus );
}

SoundBus::~SoundBus()
{

}

void* SoundBus::GetNativeBus() const
{
	return m_pBus.get();
}

} // namespace Genesis::Sound::Private::SoLoud
