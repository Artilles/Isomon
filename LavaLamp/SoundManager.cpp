#include "include\SoundManager.h"
#include <iostream>
#include <fstream>
#include <string>


SoundManager::SoundManager()
{
	device = alcOpenDevice(NULL);
	if (!device)
	{
		std::cout << "Failed to open sound card.\n";
		exit(2);
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
	{
		ALCenum error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Failed to open sound context.\n";
			exit(3);
		}			
	}
}

SoundManager::~SoundManager()
{
	/*for (int i = 0; i < _soundList.size(); i++)
	{
		alDeleteSources(1, _soundList[i].sourceId);
		if (_soundList[i].bufferId != -1)
		{
			alDeleteBuffers(1, _soundList[i].bufferId);
			delete[] _soundList[i].buffer;
		}
	}
	for (int i = 0; i < _songList.size(); i++)
	{
		alDeleteSources(1, _songList[i].sourceId);
		if (_songList[i].bufferId != -1)
		{
			alDeleteBuffers(1, _songList[i].bufferId);
			delete[] _songList[i].buffer;
		}
	}*/
	alcDestroyContext(context);
	alcCloseDevice(device);
}

unsigned int SoundManager::loadSound(const char* filename)
{
	unsigned int sourceId, bufferId;
	char* bufferData;
	bool duplicate = false;

	for (int i = 0; i < _soundList.size(); i++)
	{
		if (_soundList[i].name == filename && _soundList[i].bufferId != -1)
		{
			bufferId = _soundList[i].bufferId;
			duplicate = true;
			break;
		}
	}
	// Load the file
	if (!duplicate)
	{
		int channel, sampleRate, samplesPerSec, size;
		bufferData = loadWav(filename, channel, sampleRate, samplesPerSec, size);
		unsigned int format;

		alGenBuffers(1, &bufferId);

		if (channel == 1)
		{
			if (sampleRate == 8)
				format = AL_FORMAT_MONO8;
			else
				format = AL_FORMAT_MONO16;
		}
		else
		{
			if (sampleRate == 8)
				format = AL_FORMAT_STEREO8;
			else
				format = AL_FORMAT_STEREO16;
		}
		alBufferData(bufferId, format, bufferData, size, samplesPerSec);
	}
	alGenSources(1, &sourceId);
	alSourcei(sourceId, AL_BUFFER, bufferId);
	alSourcei(sourceId, AL_GAIN, 0.9f);
	_soundList.push_back(Sound(sourceId, (!duplicate ? bufferId : -1), bufferData, filename));
	return sourceId;
}

unsigned int SoundManager::loadSong(const char* filename)
{
	unsigned int sourceId, bufferId;
	char* bufferData;
	bool duplicate = false;

	// Search existing songs for duplicates, create the buffer
	for (int i = 0; i < _songList.size(); i++)
	{
		if (_songList[i].name == filename && _songList[i].bufferId != -1)
		{
			bufferId = _songList[i].bufferId;
			duplicate = true;
			break;
		}
	}
	// Load the file if it is not a duplicate
	if (!duplicate)
	{
		int channel, sampleRate, samplesPerSec, size;
		bufferData = loadWav(filename, channel, sampleRate, samplesPerSec, size);
		unsigned int format;

		alGenBuffers(1, &bufferId);

		if (channel == 1)
		{
			if (sampleRate == 8)
				format = AL_FORMAT_MONO8;
			else
				format = AL_FORMAT_MONO16;
		}
		else
		{
			if (sampleRate == 8)
				format = AL_FORMAT_STEREO8;
			else
				format = AL_FORMAT_STEREO16;
		}
		alBufferData(bufferId, format, bufferData, size, samplesPerSec);
	}
	alGenSources(1, &sourceId);
	alSourcei(sourceId, AL_BUFFER, bufferId);
	alSourcei(sourceId, AL_LOOPING, AL_TRUE);
	alSourcei(sourceId, AL_GAIN, 0.6f);
	_songList.push_back(Song(sourceId, (!duplicate ? bufferId : -1), bufferData, filename));
	return sourceId;
}

void SoundManager::deleteSound(unsigned int id)
{

}

void SoundManager::deleteSong(unsigned int id)
{

}

void SoundManager::playSound(const char* name)
{
	for (int i = 0; i < _soundList.size(); i++)
	{
		if (_soundList[i].name == name)
			play(_soundList[i].sourceId);
	}
}

void SoundManager::playSong(const char* name)
{
	for (int i = 0; i < _songList.size(); i++)
	{
		if (_songList[i].name == name)
			play(_songList[i].sourceId);
	}
}

void SoundManager::play(unsigned int id)
{
	/*ALint state;
	alGetSourcei(id, AL_SOURCE_STATE, &state);
	if (state != AL_PLAYING)
	{
		std::cout << state << std::endl;*/
		alSourcePlay(id);
	//}	
}

void SoundManager::stopSound(const char* name)
{
	for (int i = 0; i < _soundList.size(); i++)
	{
		if (_soundList[i].name == name)
			stop(_soundList[i].sourceId);
	}
}

void SoundManager::stopSong(const char* name)
{
	for (int i = 0; i < _songList.size(); i++)
	{
		if (_songList[i].name == name)
			stop(_songList[i].sourceId);
	}
}

void SoundManager::stop(unsigned int id)
{
	alSourceStop(id);
}

void SoundManager::stopAll()
{

}

char* SoundManager::loadWav(const char* filename, int& channel, int& samplerate, int& bps, int& size)
{
	std::string name = "resource\\music\\";
	name.append(filename);
	name.append(".wav");
	std::ifstream in(name, std::ios::binary);
	char tmpBuffer[4];
	in.read(tmpBuffer, 4);
	if (strncmp(tmpBuffer, "RIFF", 4) != 0)
	{
		std::cout << "This is not a valid WAV file (1) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << tmpBuffer[4] << '\n';
		return 0;
	}
	in.read(tmpBuffer, 4);
	int sizeInBytes = convertToInt(tmpBuffer, 4);
	in.read(tmpBuffer, 4);
	if (strncmp(tmpBuffer, "WAVE", 4) != 0)
	{
		std::cout << "This is not a valid WAV file (2) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << tmpBuffer[4] << '\n';
		return 0;
	}
	in.read(tmpBuffer, 4);
	if (strncmp(tmpBuffer, "fmt ", 4) != 0)
	{
		std::cout << "This is not a valid WAV file (3) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << tmpBuffer[4] << '\n';
		return 0;
	}
	in.read(tmpBuffer, 4);
	int fmtSize = convertToInt(tmpBuffer, 4);
	if (fmtSize != 16)
	{
		std::cout << "Sorry only PCM (not compressed WAV)" << fmtSize << '\n';
		return 0;
	}
	in.read(tmpBuffer, 2);
	int PCM = convertToInt(tmpBuffer, 2);
	if (PCM != 1)
	{
		std::cout << "Sorry only PCM (not compressed WAV)\n";
		return 0;
	}
	in.read(tmpBuffer, 2);
	int channels = convertToInt(tmpBuffer, 2);
	in.read(tmpBuffer, 4);
	int samples = convertToInt(tmpBuffer, 4);
	in.read(tmpBuffer, 4);
	int byteRate = convertToInt(tmpBuffer, 4);
	in.read(tmpBuffer, 2);
	int blockAlign = convertToInt(tmpBuffer, 2);
	in.read(tmpBuffer, 2);
	int bitsPerSample = convertToInt(tmpBuffer, 2);
	in.read(tmpBuffer, 4);
	if (strncmp(tmpBuffer, "data", 4) != 0)
	{
		std::cout << "This is not a valid WAV file (4) " << tmpBuffer[0] << tmpBuffer[1] << tmpBuffer[2] << tmpBuffer[3] << '\n';
		//	return 0;
	}
	in.read(tmpBuffer, 4);
	int dataSize = convertToInt(tmpBuffer, 4);
	if (dataSize <= 0)
	{
		std::cout << "This is not a valid WAV file (4) " << dataSize << '\n';
		return 0;
	}
	char* data = new char[dataSize];
	in.read(data, dataSize);
	std::cout << sizeInBytes << ' ' << fmtSize << ' ' << channels << ' ' << samples << ' ' << byteRate << ' ' << blockAlign << ' ' << bitsPerSample << ' ' << dataSize << std::endl;
	channel = channels;
	samplerate = bitsPerSample;
	bps = samples;
	size = dataSize;
	return data;
}

int SoundManager::convertToInt(char* buffer, int length)
{
	int a=0;
	if(!isBigEndian())
		for(int i=0;i<length;i++)
			((char*)&a)[i]= buffer[i];
	else
		for(int i=0;i<length;i++)
			((char*)&a)[sizeof(int)-i-1] = buffer[i];		
	return a;
}

bool SoundManager::isBigEndian()
{
	int a = 1;
	return (((unsigned char*)&a)[0] == 0);
}