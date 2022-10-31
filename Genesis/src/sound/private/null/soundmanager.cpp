// Copyright 2015 Pedro Nunes
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

#include "sound/private/null/soundmanager.h"

namespace Genesis::Sound::Private::Null
{

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::Update( float delta )
{

}

SoundInstanceSharedPtr SoundManager::CreateSoundInstance( ResourceSound* pResourceSound, SoundBusSharedPtr pBus )
{
    return nullptr;
}

void SoundManager::SetPlaylist( ResourcePlaylist* pResourcePlaylist, bool shuffle )
{

}

ResourcePlaylist* SoundManager::GetPlaylist() const
{
    return nullptr;
}

SoundInstanceSharedPtr SoundManager::GetCurrentTrack() const
{
    return nullptr;
}

const SoundInstanceList& SoundManager::GetSoundInstances() const
{
    static SoundInstanceList list;
    return list;
}

void SoundManager::SetListener( const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up )
{

}

glm::vec3 SoundManager::GetListenerPosition() const
{
    return glm::vec3( 0.0f );
}

unsigned int SoundManager::GetActiveSoundCount() const
{
    return 0u;
}

unsigned int SoundManager::GetMaximumSoundCount() const
{
    return 0u;
}

unsigned int SoundManager::GetVirtualSoundCount() const
{
    return 0u;
}

} // namespace Genesis::Sound::Private::Null
