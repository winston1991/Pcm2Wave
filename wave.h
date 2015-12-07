typedef struct WAVE_HEAD
{
	char riff_char[4];   // "RIFF" char riff_id[4]="RIFF"
    int package_len ;    //�ļ��ܳ�-8 long int size0=���ܳ�-8
	char wave[4];
	char fmt[4];
    int format_len;   
    short fixed;      //  fmttag=0x01
	short channel_number;  //  channel=1 ��2
    int   sample_rate;   //  ������ long int samplespersec
	int   byte_rate;   //  ÿ�벥���ֽ��� long int bytepersec
	short byte_per_sample;   //  ����һ��ռ�ֽ��� int blockalign=������*������/8
	short bits_per_sample;   // ������ int bitpersamples=8��16
	char fccID[4]; // must be "fact"
    int  id; // must be 0x4
    int dwSize; // ��ʱû������ɶ��
    char  data_field[4];   //  data_id="data"
    int  data_len;  //  ���������ֽ��� long int size2=�ĳ�-44
	
} WAVE_HEAD;