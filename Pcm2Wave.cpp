#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "wave.h"
#include "constant.h"

class Pcm2Wave
{
private: 
	WAVE_HEAD wave_head;
	FILE* src_pcm_file;
	FILE* dest_wave_file;
public:
    Pcm2Wave()
	{ 
		memcpy(&wave_head.riff_char, "RIFF", 4);
		memcpy(&wave_head.wave, "WAVE", 4);
		memcpy(&wave_head.fmt, "fmt ", 4);
		memcpy(&wave_head.fccID, "fact", 4);
		memcpy(&wave_head.data_field, "data", 4);
		wave_head.package_len = 0;
		wave_head.format_len = 16;
		wave_head.fixed =  1;
		wave_head.channel_number = 1;
		//  采样率 long int samplespersec
		wave_head.sample_rate = 8000 ;
	
    	// 量化数 int bitpersamples=8或16
		wave_head.bits_per_sample = 16;
		//  采样一次占字节数 int blockalig
		wave_head.byte_per_sample = wave_head.channel_number *  wave_head.bits_per_sample / 8; //NumChannels * BitsPerSample/8
       	//  每秒播放字节数 long int bytepersec
		wave_head.byte_rate = 	wave_head.sample_rate * wave_head.channel_number * wave_head.bits_per_sample / 8; //SampleRate * NumChannels * BitsPerSample /8
		
		
		wave_head.id = 4;
		wave_head.dwSize = 0;
		
		wave_head.data_len = 0;
	}
	
	Pcm2Wave(WAVE_HEAD* pwave_head)
	{
		if(pwave_head != NULL)
		{
			memcpy(&wave_head, pwave_head, sizeof(*pwave_head));
		}
	}
	

	~Pcm2Wave()
	{}


	void set_channel(short pchannel_number)
	{
		wave_head.channel_number = pchannel_number;
		wave_head.byte_per_sample = wave_head.channel_number *  wave_head.bits_per_sample / 8;
		wave_head.byte_rate = 	wave_head.sample_rate * wave_head.channel_number * wave_head.bits_per_sample / 8;
	}
	
    void set_sample_rate(int  psample_rate)
	{
		wave_head.sample_rate = psample_rate;
		wave_head.byte_rate = 	wave_head.sample_rate * wave_head.channel_number * wave_head.bits_per_sample / 8;
	}
	
	void set_bits_per_sample(short pbits_per_sample)
	{
		wave_head.bits_per_sample =   pbits_per_sample;
		wave_head.byte_per_sample = wave_head.channel_number *  wave_head.bits_per_sample / 8;
		wave_head.byte_rate = 	wave_head.sample_rate * wave_head.channel_number * wave_head.bits_per_sample / 8;
	}
	
	
    int change(const char *srcfile, const char *dsetfile)
	{
		int nFileLen = 0;
		int nSize = sizeof(wave_head);
		printf("wave的头的大小： %d\n", nSize);
		src_pcm_file = NULL;
		dest_wave_file = NULL;
		src_pcm_file = fopen(srcfile, "rb");
		if (src_pcm_file == NULL)
			return -1;
		
		dest_wave_file = fopen(dsetfile, "wb+");
		if (dest_wave_file == NULL)
			return -2;
		
		
		int nWrite = fwrite(&wave_head, 1, nSize, dest_wave_file);
		if (nWrite != nSize)
		{
			fclose(src_pcm_file);
			fclose(dest_wave_file);
			return -3;
		}
		
		while( !feof(src_pcm_file))
		{
			char readBuf[4096];
			int nRead = fread(readBuf, 1, 4096, src_pcm_file);
			if (nRead > 0)
			{
				fwrite(readBuf, 1, nRead, dest_wave_file); 
			}
			
			nFileLen += nRead;
		}
		printf("文件指针位置： %d\n", ftell(dest_wave_file));
		//将目的文件的游标指针指向文件的开头
		printf("nFileLen的大小： %d\n nSize的大小：%d\n", nFileLen, nSize);
		fseek(dest_wave_file, 0, SEEK_SET);
		
		wave_head.package_len = nFileLen - 8 + nSize;
		wave_head.data_len = nFileLen;
		nWrite = fwrite(&wave_head, 1, nSize, dest_wave_file);
		if (nWrite != nSize)
		{
			fclose(src_pcm_file);
			fclose(dest_wave_file);
			return -4;
		}
		fclose(src_pcm_file);
		fclose(dest_wave_file);
		
        return 0;		
	}
	
};


int main(char args [])
{
	Pcm2Wave pp;
	pp.set_sample_rate(11025);
	pp.change("jj.pcm", "jj.wav");
	return 0 ;
}


