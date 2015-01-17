
//字符串拆分后的数量
int getSplitLen(LPCTSTR s1, char c1)
{
	int len=0;
	int i=0;
	int j=strlen(s1);
	int k=0;			//char index
	for (i=0;i<j;i++)
	{
		if(s1[i] == c1)
		{
			len++;
			k=i;
		}
	}
	if(k+1<j) len++;
	return len;
}

//获取拆分后的制定字符串 s1原始字符串 c1分割字符 s2返回字符串
void getSplit(LPCTSTR s1, char c1, int i_index, char* s2)
{
	int len=0;
	int i=0;
	int j=strlen(s1);
	int k=0;			//char index
	
	for (i=0;i<j;i++)
	{
		if(s1[i] == c1)
		{
			len++;
			continue;
		}
		
		if (len == i_index)
		{
			s2[k] = s1[i];
			k++;
		}
		if (len > i_index)
			break;
	}
	s2[k] = 0;
}
