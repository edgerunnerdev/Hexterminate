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

#include "sound/private/soloud/soundinstance.h"

#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>

#include <resources/resourcesound.h>

namespace Genesis::Sound::Private::SoLoud
{

extern ::SoLoud::Soloud* g_pSoloud;

SoundInstance::SoundInstance()
    : m_pResourceSound(nullptr)
    , m_Handle(0)
    , m_Position(0.0f)
    , m_Velocity(0.0f)
{

}

SoundInstance::~SoundInstance()
{
    
}

void SoundInstance::Initialise( ResourceSound* pResourceSound, void* pData )
{
    m_pResourceSound = pResourceSound;
    ::SoLoud::AudioSource* pAudioSource = reinterpret_cast<::SoLoud::AudioSource*>( pData );
    if (pResourceSound->Is3D())
    {
        // For 3D sounds, delay playing them until Set3DAttributes() has been called.
        m_Handle = g_pSoloud->play3d( *pAudioSource, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, true );
    }
    else
    {
        m_Handle = g_pSoloud->play( *pAudioSource );
    }

    if (pResourceSound->IsLooping())
    {
        g_pSoloud->setLooping( m_Handle, true );
    }
}

bool SoundInstance::IsPlaying() const
{
    return false;
}

void SoundInstance::Stop()
{
    g_pSoloud->stop( m_Handle );
}

unsigned int SoundInstance::GetLength() const
{
    return 0u;
}

unsigned int SoundInstance::GetPosition() const
{
    return 0u;
}

float SoundInstance::GetAudability() const
{
    return 0.0f;
}

ResourceSound* SoundInstance::GetResource() const
{
    return m_pResourceSound;
}

void SoundInstance::SetMinimumDistance( float value )
{

}
    
void SoundInstance::Set3DAttributes( const glm::vec3* pPosition, const glm::vec3* pVelocity )
{
    if (pPosition != nullptr)
    {
        g_pSoloud->set3dSourcePosition( m_Handle, pPosition->x, pPosition->y, pPosition->z );
    }

    if (pVelocity != nullptr)
    {
        g_pSoloud->set3dSourceVelocity( m_Handle, pVelocity->x, pVelocity->y, pVelocity->z );
    }

    g_pSoloud->setPause( m_Handle, false );
}

void SoundInstance::Get3DAttributes( glm::vec3* pPosition, glm::vec3* pVelocity )
{
    if ( pPosition != nullptr )
    {
        *pPosition = m_Position;
    }

    if ( pVelocity != nullptr )
    {
        *pVelocity = m_Velocity;
    } 
}

void SoundInstance::SetVolume( float value )
{
    g_pSoloud->setVolume( m_Handle, value );
}

float SoundInstance::GetVolume() const
{
    return g_pSoloud->getVolume( m_Handle );
}

} // namespace Genesis::Sound::SoLoud
