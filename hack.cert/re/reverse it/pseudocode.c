scanf("%50s", in_string);
slen =  strlen(in_string);

int i = 0;

while(i < slen)
{
in_string[i] = (byte)(in_string[i] ^ in_string[i+1]);
i++;
}

if (strcmp(in_string, asc_404723) == 0)
	good_flag()
else
	bad_flag()