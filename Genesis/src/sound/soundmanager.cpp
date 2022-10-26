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

#include "sound/private/soundmanagerimpl.h"
#include "sound/private/null/soundmanager.h"
#include "sound/private/soloud/soundmanager.h"
#include "sound/private/soundinstanceimpl.h"
#include "sound/soundmanager.h"
#include "sound/window.h"

namespace Genesis::Sound
{

SoundManager::SoundManager()
{
#if defined SOUND_USE_SOLOUD
    m_pImpl = std::make_unique<Private::SoLoud::SoundManager>();
#else
    m_pImpl = std::make_unique<Private::Null::SoundManager>();
#endif

    m_pDebugWindow = std::make_unique<Window>(this);
}

SoundManager::~SoundManager()
{

}

TaskStatus SoundManager::Update( float delta )
{
    m_pImpl->Update( delta );
    m_pDebugWindow->Update(delta);
    return TaskStatus::Continue;
}

SoundInstanceSharedPtr SoundManager::CreateSoundInstance( ResourceSound* pResourceSound )
{
    return m_pImpl->CreateSoundInstance( pResourceSound );
}

void SoundManager::SetPlaylist( ResourcePlaylist* pResourcePlaylist, const std::string& startingTrack /* = "" */, bool shuffle /* = false */ )
{
    m_pImpl->SetPlaylist( pResourcePlaylist, startingTrack, shuffle );
}

ResourcePlaylist* SoundManager::GetPlaylist() const
{
    return m_pImpl->GetPlaylist();
}

SoundInstanceSharedPtr SoundManager::GetCurrentSong() const
{
    return m_pImpl->GetCurrentSong();
}

const SoundInstanceList& SoundManager::GetSoundInstances() const
{
    return m_pImpl->GetSoundInstances();
}

void SoundManager::SetListener( const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up )
{  
    m_pImpl->SetListener( position, velocity, forward, up );
}

glm::vec3 SoundManager::GetListenerPosition() const
{
    return m_pImpl->GetListenerPosition();
}

unsigned int SoundManager::GetActiveSoundCount() const
{
    return m_pImpl->GetActiveSoundCount();
}

unsigned int SoundManager::GetMaximumSoundCount() const
{
    return m_pImpl->GetMaximumSoundCount();
}

unsigned int SoundManager::GetVirtualSoundCount() const
{
    return m_pImpl->GetVirtualSoundCount();
}

} // namespace Genesis::Sound
