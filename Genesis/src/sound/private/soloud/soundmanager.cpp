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

#include <resources/resourceplaylist.h>
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
    , m_pPlaylist(nullptr)
    , m_PlaylistShuffle(false)
{
    m_pSoloud = std::make_unique<::SoLoud::Soloud>();
    int result = m_pSoloud->init();
    if (result == ::SoLoud::SO_NO_ERROR)
    {
        m_Initialized = true;
        g_pSoloud = m_pSoloud.get();
        m_pSoloud->setMaxActiveVoiceCount(64u);
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
        m_SoundInstances.remove_if([](const SoundInstanceSharedPtr& pInstance) { return !pInstance->IsValid(); });
        UpdatePlaylist();
    }
}

SoundInstanceSharedPtr SoundManager::CreateSoundInstance( ResourceSound* pResourceSound, SoundBusSharedPtr pBus )
{
    if ( pResourceSound->CanInstance() == false )
    {
        return nullptr;
    }
    else
    {
        ::SoLoud::AudioSource* pAudioSourceRaw = nullptr;
        auto audioSourceIt = m_AudioSources.find( pResourceSound->GetFilename().GetFullPath() );
        if ( audioSourceIt == m_AudioSources.end() )
        {
            int result = ::SoLoud::UNKNOWN_ERROR;
            std::shared_ptr<::SoLoud::AudioSource> pAudioSource;
            if ( pResourceSound->IsStreamed() )
            {
                pAudioSource = std::make_shared<::SoLoud::WavStream>();
                pAudioSourceRaw = pAudioSource.get();
                result = reinterpret_cast<::SoLoud::WavStream*>(pAudioSourceRaw)->load( pResourceSound->GetFilename().GetFullPath().c_str() );
            }
            else
            {
                pAudioSource = std::make_shared<::SoLoud::Wav>();
                pAudioSourceRaw = pAudioSource.get();
                result = reinterpret_cast<::SoLoud::Wav*>(pAudioSourceRaw)->load( pResourceSound->GetFilename().GetFullPath().c_str() );
            }
        
            if ( result == ::SoLoud::SO_NO_ERROR )
            {
                // The attenuation model has to be explicitly set, as the default is not to attenuate over distance.
                if (pResourceSound->Is3D())
                {
                    pAudioSource->set3dAttenuation(::SoLoud::AudioSource::INVERSE_DISTANCE, 1.0f);
                }

                m_AudioSources[ pResourceSound->GetFilename().GetFullPath().c_str() ] = pAudioSource;
            }
            else
            {
                Genesis::FrameWork::GetLogger()->LogError( "SoundManager::CreateSoundInstance ('%s'): %s", pResourceSound->GetFilename().GetFullPath().c_str(), m_pSoloud->getErrorString( result ) );
                return nullptr;
            }
        }
        else
        {
            pAudioSourceRaw = audioSourceIt->second.get();
        }

        SoundInstanceSharedPtr pInstance = std::make_shared<SoundInstance>();
        pInstance->Initialise( pResourceSound, pBus, pAudioSourceRaw );
        m_SoundInstances.push_back(pInstance);
        pResourceSound->SetInstancingTimePoint();
        return pInstance;
    }
}

void SoundManager::SetPlaylist( ResourcePlaylist* pResourcePlaylist, bool shuffle )
{
    if ( pResourcePlaylist == m_pPlaylist )
    {
        return;
    }

    // If we're changing playlists, stop the previous one.
    // There's no need to start playing the first track here, that will be handled in the next Update().
    m_pPlaylist = pResourcePlaylist;
    m_PlaylistShuffle = shuffle;

    if ( m_pCurrentTrack != nullptr && m_pCurrentTrack->IsValid() )
    {
        m_pCurrentTrack->Stop();
        m_pCurrentTrack = nullptr;
    }
}

ResourcePlaylist* SoundManager::GetPlaylist() const
{
    return m_pPlaylist;
}

SoundInstanceSharedPtr SoundManager::GetCurrentTrack() const
{
    return m_pCurrentTrack;
}

const SoundInstanceList& SoundManager::GetSoundInstances() const
{
    return m_SoundInstances;
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

unsigned int SoundManager::GetActiveSoundCount() const
{
    return m_pSoloud->getActiveVoiceCount();
}

unsigned int SoundManager::GetMaximumSoundCount() const
{
    return m_pSoloud->getMaxActiveVoiceCount();
}

unsigned int SoundManager::GetVirtualSoundCount() const
{
    return m_pSoloud->getVoiceCount();
}

void SoundManager::UpdatePlaylist()
{
    ResourcePlaylist* pPlaylist = GetPlaylist();
    if ( pPlaylist )
    {
        if ( m_pCurrentTrack == nullptr || m_pCurrentTrack->IsValid() == false )
        {
            ResourceSound* pNextTrackResource = pPlaylist->GetNextTrack( m_PlaylistShuffle );
            if ( pNextTrackResource )
            {
                m_pCurrentTrack = FrameWork::GetSoundManager()->CreateSoundInstance( pNextTrackResource, SoundBus::Type::Music );
            }
        }
    }
}

} // namespace Genesis::Sound::Private::SoLoud
