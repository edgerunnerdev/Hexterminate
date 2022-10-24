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

#include "sound/private/soloud/soundmanager.h"

#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>

#include <resources/resourcesound.h>
#include <sound/soundinstance.h>

#include "genesis.h"
#include "logger.h"

namespace Genesis::Sound::Private::SoLoud
{

::SoLoud::Soloud* g_pSoloud = nullptr;

SoundManager::SoundManager()
    : m_Initialized(false)
    , m_ListenerPosition(0.0f)
{
    m_pSoloud = std::make_unique<::SoLoud::Soloud>();
    int result = m_pSoloud->init();
    if (result == ::SoLoud::SO_NO_ERROR)
    {
        m_Initialized = true;
        g_pSoloud = m_pSoloud.get();
    }
    else
    {
        Genesis::FrameWork::GetLogger()->LogError( "Failed to initialize SoLoud audio library: %s", m_pSoloud->getErrorString( result ) );
    }
}

SoundManager::~SoundManager()
{
    if (m_Initialized)
    {
        m_pSoloud->deinit();
    }
}

void SoundManager::Update( float delta )
{
    if (m_Initialized)
    {
        m_pSoloud->update3dAudio();
    }
}

SoundInstanceSharedPtr SoundManager::CreateSoundInstance( ResourceSound* pResourceSound )
{
    return pResourceSound->IsStreamed() ? WavStreamCreateSoundInstance(pResourceSound) : WavCreateSoundInstance(pResourceSound);
}

SoundInstanceSharedPtr SoundManager::WavCreateSoundInstance( ResourceSound* pResourceSound )
{
    std::shared_ptr<::SoLoud::Wav> pAudioSource = nullptr;
    auto audioSourceIt = m_AudioSources.find( pResourceSound->GetFilename().GetFullPath() );
    if ( audioSourceIt == m_AudioSources.end() )
    {
        pAudioSource = std::make_shared<::SoLoud::Wav>();
        int result = pAudioSource->load( pResourceSound->GetFilename().GetFullPath().c_str() );
        if ( result == ::SoLoud::SO_NO_ERROR )
        {
            m_AudioSources[ pResourceSound->GetFilename().GetFullPath().c_str() ] = pAudioSource;
        }
        else
        {
            Genesis::FrameWork::GetLogger()->LogError( "SoundManager::WavCreateSoundInstance ('%s'): %s", pResourceSound->GetFilename().GetFullPath().c_str(), m_pSoloud->getErrorString( result ) );
            return nullptr;
        }
    }
    else
    {
        pAudioSource = audioSourceIt->second;
    }

    SoundInstanceSharedPtr pInstance = std::make_shared<SoundInstance>();
    pInstance->Initialise( pResourceSound, pAudioSource.get() );
    return pInstance;
}

SoundInstanceSharedPtr SoundManager::WavStreamCreateSoundInstance( ResourceSound* pResourceSound )
{
    std::shared_ptr<::SoLoud::WavStream> pAudioSource = nullptr;
    auto audioSourceIt = m_StreamedAudioSources.find( pResourceSound->GetFilename().GetFullPath() );
    if ( audioSourceIt == m_StreamedAudioSources.end() )
    {
        pAudioSource = std::make_shared<::SoLoud::WavStream>();
        int result = pAudioSource->load( pResourceSound->GetFilename().GetFullPath().c_str() );
        if ( result == ::SoLoud::SO_NO_ERROR )
        {
            m_StreamedAudioSources[ pResourceSound->GetFilename().GetFullPath().c_str() ] = pAudioSource;
        }
        else
        {
            Genesis::FrameWork::GetLogger()->LogError( "SoundManager::WavStreamCreateSoundInstance ('%s'): %s", pResourceSound->GetFilename().GetFullPath().c_str(), m_pSoloud->getErrorString( result ) );
            return nullptr;
        }
    }
    else
    {
        pAudioSource = audioSourceIt->second;
    }

    SoundInstanceSharedPtr pInstance = std::make_shared<SoundInstance>();
    pInstance->Initialise( pResourceSound, pAudioSource.get() );
    return pInstance;
}

void SoundManager::SetPlaylist( ResourceSound* pResourceSound, const std::string& startingSong, bool shuffle )
{

}

ResourceSound* SoundManager::GetPlaylistResource() const
{
    return nullptr;
}

SoundInstanceSharedPtr SoundManager::GetCurrentSong() const
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
    m_pSoloud->set3dListenerPosition( position.x, position.y, position.z );
    m_pSoloud->set3dListenerVelocity( velocity.x, velocity.y, velocity.z );
    m_pSoloud->set3dListenerAt( forward.x, forward.y, forward.z );
    m_pSoloud->set3dListenerUp( up.x, up.y, up.z );
    m_ListenerPosition = position;
}

glm::vec3 SoundManager::GetListenerPosition() const
{
    return m_ListenerPosition;
}

int SoundManager::GetActiveSoundCount() const
{
    return static_cast<int>( m_pSoloud->getActiveVoiceCount() );
}

} // namespace Genesis::Sound::Private::SoLoud
