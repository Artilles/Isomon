#pragma once
#include "AL\al.h"
#include "AL\alc.h"
#include <string>
#include <vector>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	
	unsigned int loadSound(const char* filename);
	unsigned int loadSong(const char* filename);
	void deleteSound(unsigned int id);
	void deleteSong(unsigned int id);

	void playSound(const char* name);
	void playSong(const char* name);
	void play(unsigned int id);

	void stopSound(const char* name);
	void stopSong(const char* name);
	void stop(unsigned int id);
	void stopAll();

private:
	struct Sound
	{
		int sourceId;
		int bufferId;
		char* buffer;
		std::string name;
		Sound(unsigned int pSourceId, unsigned int pBufferId, char* pBuffer, const char* pName)
			: sourceId(pSourceId), bufferId(pBufferId), buffer(pBuffer), name(pName) {}
	};
	struct Song
	{
		int sourceId;
		int bufferId;
		char* buffer;
		std::string name;
		Song(unsigned int pSourceId, unsigned int pBufferId, char* pBuffer, const char* pName)
			: sourceId(pSourceId), bufferId(pBufferId), buffer(pBuffer), name(pName) {}
	};

	std::vector<Sound> _soundList;
	std::vector<Song> _songList;

	ALCcontext* context;
	ALCdevice* device;

	char* loadWav(const char* filename, int& channel, int& samplerate, int& bps, int& size);
	int convertToInt(char* buffer, int length);
	bool isBigEndian();
};