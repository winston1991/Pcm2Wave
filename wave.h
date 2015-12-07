typedef struct WAVE_HEAD
{
	char riff_char[4];   // "RIFF" char riff_id[4]="RIFF"
    int package_len ;    //文件总长-8 long int size0=文总长-8
	char wave[4];
	char fmt[4];
    int format_len;   
    short fixed;      //  fmttag=0x01
	short channel_number;  //  channel=1 或2
    int   sample_rate;   //  采样率 long int samplespersec
	int   byte_rate;   //  每秒播放字节数 long int bytepersec
	short byte_per_sample;   //  采样一次占字节数 int blockalign=声道数*量化数/8
	short bits_per_sample;   // 量化数 int bitpersamples=8或16
	char fccID[4]; // must be "fact"
    int  id; // must be 0x4
    int dwSize; // 暂时没发现有啥用
    char  data_field[4];   //  data_id="data"
    int  data_len;  //  采样数据字节数 long int size2=文长-44
	
} WAVE_HEAD;