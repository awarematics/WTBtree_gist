


#include "WTBtree_gist.h"



// wkey를 Leaf 노드 키(LKEY)로 변환
WTB_KEY_IN_LKey *
range_key_to_node_key(wkey *w)
{
	WTB_KEY_IN_LKey *LKEY;
	char temp[12];
	
	for (int i=0; i<sizeof(temp); i++)
	{
		temp[i] = w[i+1];
	}
	
	if (w[0]=='l') // Leaf Node
	{
		LKEY = (WTB_KEY_IN_LKey *)palloc(sizeof(WTB_KEY_IN_LKey));
		memcpy((char*)LKEY, (char*)temp, sizeof(WTB_KEY_IN_LKey));		
	}
	
	return LKEY;
}

// wkey를 중간 노드 키(IKEY)로 변환
WTB_KEY_IN_IKey
node_key_to_range_key(wkey *w)
{
	WTB_KEY_IN_IKey IKEY;
	
	if (w[0]=='i') // Intermediate Node
	{
		for (int i=0; i<12; i++)
		{
			IKEY->lkey[i] = w[i+1];
			IKEY->ukey[i] = w[i+13];
		}
	}
	
	return IKEY;
}


// MBR 값을 GeoHash 값으로 변환
char *
WTBtree_util_MBRtoGeohash(WTB_KEY_IN_IKey *IKEY)
{
	int precision = 12;		
	char minGeohash[12], maxGeohash[12];
	bool cmp = true;		
	
	do 
	{
		minGeohash = (char *) geohash_encode(xmin, ymin, precision);
		maxGeohash = (char *) geohash_encode(xmax, ymax, precision);
	
		if (minGeohash = maxGeohash) 
		{
			cmp = true;	
		} else 
		{
			cmp = false;
		}
		
		precision--;
	} while (cmp);
		
	return minGeohash;
}