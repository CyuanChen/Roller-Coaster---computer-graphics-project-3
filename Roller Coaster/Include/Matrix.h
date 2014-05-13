inline void mulMatrix444(float a[][4], float b[][4], float c[][4])
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			c[i][j] = 0;
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){		
			for(int k = 0; k < 4; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

inline void mulMatrix144(float a[][4], float b[][4], float c[][4])
{
	for(int i = 0; i < 1; i++)
		for(int j = 0; j < 4; j++)
			c[i][j] = 0;
	
	for(int i = 0; i < 1; i++){
		for(int j = 0; j < 4; j++){		
			for(int k = 0; k < 4; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

inline float mulMatrix141(float a[][4], float b[][1], float c[][1])
{
	for(int i = 0; i < 1; i++)
		for(int j = 0; j < 1; j++)
			c[i][j] = 0;
	
	for(int i = 0; i < 1; i++){
		for(int j = 0; j < 1; j++){		
			for(int k = 0; k < 4; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	return c[0][0];
}


inline float mulMatrix441(float a[][4], float b[][1], float c[][1])
{
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 1; j++)
			c[i][j] = 0;
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 1; j++){		
			for(int k = 0; k < 4; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	return c[0][0];
}