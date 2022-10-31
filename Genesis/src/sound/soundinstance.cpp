// Copyright 2021 Pedro Nunes
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

#include <list>
#include <memory>

#if SOUND_USE_SOLOUD
#include "sound/private/soloud/soundinstance.h"
#else
#include "sound/private/null/soundinstance.h"
#endif

#include "sound/soundinstance.h"

namespace Genesis::Sound
{

SoundInstance::SoundInstance()
{
#if SOUND_USE_SOLOUD
    m_pImpl = std::make_unique<Private::SoLoud::SoundInstance>();
#else
    m_pImpl = std::make_unique<Private::Null::SoundInstance>();
#endif
}
    
SoundInstance::~SoundInstance()
{
    // Don't move empty destructor to header, needed for m_pImpl to be deleted correctly.
}

void SoundInstance::Initialise( ResourceSound* pResourceSound, SoundBusSharedPtr pSoundBus, void* pData )
{
    m_pImpl->Initialise( pResourceSound, pSoundBus, pData );
}

bool SoundInstance::IsPlaying() const
{
    return m_pImpl->IsPlaying();
}

bool SoundInstance::IsPaused() const
{
    return m_pImpl->IsPaused();
}

void SoundInstance::Stop()
{
    m_pImpl->Stop();
}

bool SoundInstance::IsValid() const
{
    return m_pImpl->IsValid();
}

unsigned int SoundInstance::GetLength() const
{
    return m_pImpl->GetLength();
}

unsigned int SoundInstance::GetPosition() const
{
    return m_pImpl->GetPosition();
}

float SoundInstance::GetAudability() const
{
    return m_pImpl->GetAudability();
}

ResourceSound* SoundInstance::GetResource() const
{
    return m_pImpl->GetResource();
}

void SoundInstance::SetMinimumDistance( float value )
{
    m_pImpl->SetMinimumDistance( value );
}

void SoundInstance::Set3DAttributes( const glm::vec3* pPosition /* = nullptr */, const glm::vec3* pVelocity /* = nullptr */ )
{
    m_pImpl->Set3DAttributes( pPosition, pVelocity );
}
    
void SoundInstance::Get3DAttributes( glm::vec3* pPosition /* = nullptr */, glm::vec3* pVelocity /* = nullptr */ )
{
    m_pImpl->Get3DAttributes( pPosition, pVelocity );
}
    
void SoundInstance::SetVolume( float value )
{
    m_pImpl->SetVolume( value );
}

float SoundInstance::GetVolume() const
{
    return m_pImpl->GetVolume();
}

} // namespace Genesis::Sound
