#include"Audio.h"

namespace OpenGL_3_3Engine
{
	Sample::Sample()
	{
		sample = NULL;
		channel = NULL;
	}

	Sample::~Sample()
	{
		if(sample!=NULL)
		{
			FMOD_Sound_Release(sample);
			sample = NULL;
		}
	}

	Audio::Audio()
	{
		system = NULL;
	}

	Audio::~Audio()
	{
		for(SampleItr sI = samples.begin(); sI != samples.end(); sI++ )
		{
			(*sI) = NULL;
		}
		FMOD_System_Release(system);
	}

	bool Audio::Init()
	{
		if(FMOD_System_Create(&system) != FMOD_OK)
		{
			return false;
		}

		if(FMOD_System_Init(system,100,FMOD_INIT_NORMAL,NULL) != FMOD_OK)
		{
			return false;
		}

		return true;
	}

	void Audio::Update()
	{
		FMOD_System_Update(system);
	}

	Sample* Audio::Load(const std::string& fileName)
	{
		if(fileName.length() == 0) return NULL;

		Sample* sample = new Sample;
		FMOD_RESULT res;
		res = FMOD_System_CreateSound(
			system,
			fileName.c_str(),
			FMOD_DEFAULT,
			NULL,
			&sample->sample);

		if(res!=FMOD_OK) 
			return NULL;

		return sample;
	}

	bool Audio::Load(const std::string& fileName,const std::string& name)
	{
		if(fileName.length() == 0 || name.length() == 0) return false;

		Sample* sample = new Sample;
		sample->SetName(name);
		FMOD_RESULT res;

		res = FMOD_System_CreateSound(
			system,
			fileName.c_str(),
			FMOD_DEFAULT,
			NULL,
			&sample->sample);

		if(res != FMOD_OK) return false;

		samples.push_back(sample);
		return true;
	}

	bool Audio::SampleExists(const std::string& name)
	{
		for(SampleItr sI = samples.begin(); sI != samples.end(); sI++)
		{
			if(((*sI)->GetName().compare(name)) == 0)
			{
				return true;
			}
		}

		return false;
	}

	bool Audio::IsPlaying(const std::string& name)
	{
		Sample* samp = FindSample(name);
		if(samp == NULL) return false;

		int index;
		FMOD_Channel_GetIndex(samp->channel,&index);
		return(index > 0);
	}

	Sample* Audio::FindSample(const std::string& name)
	{
		Sample* sample = NULL;
		for(SampleItr sI = samples.begin(); sI != samples.end(); sI++)
		{
			if((*sI)->GetName().compare(name) == 0)
			{
				sample = (*sI);
				break;
			}
		}
		return sample;
	}

	bool Audio::Play(const std::string& name,float volume,bool looped,int numLoops)
	{
		FMOD_RESULT res;
		Sample* sample = FindSample(name);
		if(sample->sample != NULL)
		{
			
			
			res = FMOD_System_PlaySound(
				system,
				FMOD_CHANNEL_FREE,
				sample->sample,
				true,
				&sample->channel);

			if(res!=FMOD_OK)return false;

			if(!looped)
			{
				res = FMOD_Channel_SetLoopCount(sample->channel,-1);
			}
			else
			{
				res = FMOD_Channel_SetLoopCount(sample->channel,numLoops);
			}

			if(res!=FMOD_OK)return false;

			res = FMOD_Channel_SetVolume(sample->channel,volume);

			if(res!=FMOD_OK)return false;


			FMOD_Channel_SetPaused(sample->channel,false);
		}
		return true;
	}

	bool Audio::Play(Sample* sample,float volume,bool looped,int numLoops)
	{
		FMOD_RESULT res;
		if(sample == NULL) return false;
		if(sample->sample == NULL) return false;


		//set the volume
		FMOD_Channel_SetVolume(sample->channel,volume);

		//set the loops
		if(!looped)
		{
			FMOD_Channel_SetLoopCount(sample->channel,-1);
		}
		else
		{
			FMOD_Channel_SetLoopCount(sample->channel,numLoops);
		}

		res = FMOD_System_PlaySound(
			system,
			FMOD_CHANNEL_FREE,
			sample->sample,
			true,
			&sample->channel);

		if(res!=FMOD_OK)return false;

		

		FMOD_Channel_SetPaused(sample->channel,false);
		return true;
	}

	void Audio::Stop(const std::string& name)
	{
		if(!IsPlaying(name))return;
		Sample* sample = FindSample(name);
		if(sample==NULL)return;
		FMOD_Channel_Stop(sample->channel);
	}

	void Audio::StopAll()
	{
		for(SampleItr sI = samples.begin(); sI != samples.end(); sI++ )
		{
			FMOD_Channel_Stop((*sI)->channel);
		}
	}

	void Audio::StopAllExcept(const std::string& name)
	{
		for(SampleItr sI = samples.begin(); sI != samples.end(); sI++ )
		{
			if((*sI)->GetName().compare(name) != 0)
				FMOD_Channel_Stop((*sI)->channel);
		}
	}
};