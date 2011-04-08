/*!
* \file   MusicPlayer.h
* \author oln, StefanP.MUC
* \date   November 10 2010
* \brief  Header of class "MusicPlayer" containing everything to play
*         music tracks.
*/

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <vector>

#include <SFML/Audio.hpp>
#include <OgreSingleton.h>
#include <OgreSharedPtr.h>

/*! \brief Class to manage playing of music.
 *
 */
class MusicPlayer: public Ogre::Singleton<MusicPlayer>
{
    public:
        MusicPlayer(const Ogre::String& path);
        virtual ~MusicPlayer();
        void update();
        void start(const unsigned int& trackNumber);
        void next();

        inline const bool& isRandomized() const{return randomized;}
        inline void setRandomize(const bool& randomize){randomized = randomize;}

        static MusicPlayer& getSingleton();
        static MusicPlayer* getSingletonPtr();

    private:
        std::vector<Ogre::SharedPtr<sf::Music> > tracks;
        bool loaded;
        bool randomized;
        unsigned int currentTrack;
};

#endif /* MUSICPLAYER_H */
