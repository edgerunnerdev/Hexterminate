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

#include "sound/private/soundmanagerimpl.h"

#include <memory>
#include <unordered_map>

namespace SoLoud
{
class Soloud;
class Wav;
class WavStream;
} // namespace SoLoud

namespace Genesis::Sound::Private::SoLoud
{

class SoundManager : public SoundManagerImpl
{
public:
    SoundManager();
    virtual ~SoundManager() override;

    virtual void Update( float delta ) override;
    virtual SoundInstanceSharedPtr CreateSoundInstance( ResourceSound* pResourceSound ) override;
    virtual void SetPlaylist( ResourcePlaylist* pResourcePlaylist, const std::string& startingSong, bool shuffle ) override;
    virtual ResourcePlaylist* GetPlaylist() const override;
    virtual SoundInstanceSharedPtr GetCurrentSong() const override;
    virtual const SoundInstanceList& GetSoundInstances() const override;
    virtual void SetListener( const glm::vec3& position, const glm::vec3& velocity, const glm::vec3& forward, const glm::vec3& up ) override;
    virtual glm::vec3 GetListenerPosition() const override;
    virtual unsigned int GetActiveSoundCount() const override;
    virtual unsigned int GetMaximumSoundCount() const override;
    virtual unsigned int GetVirtualSoundCount() const override;

private:
    SoundInstanceSharedPtr WavCreateSoundInstance( ResourceSound* pResourceSound );
    SoundInstanceSharedPtr WavStreamCreateSoundInstance( ResourceSound* pResourceSound );

    std::unique_ptr<::SoLoud::Soloud> m_pSoloud;
    bool m_Initialized;
    glm::vec3 m_ListenerPosition;
    SoundInstanceList m_SoundInstances;
    ResourcePlaylist* m_Playlist;
    SoundInstanceSharedPtr m_CurrentTrack;
    bool m_PlaylistShuffle;

    std::unordered_map<std::string, std::shared_ptr<::SoLoud::Wav>> m_AudioSources;
    std::unordered_map<std::string, std::shared_ptr<::SoLoud::WavStream>> m_StreamedAudioSources;
};

} // namespace Genesis::Sound::Private::SoLoud
