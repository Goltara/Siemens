#include <swilib.h>
#include "obs.h"

IMGHDR *CreateIMGHDRFromImgFile(const char *path)
{
	IMGHDR *img;
	HObj obj;
	short w, h;
	
	obj = CreateHObjFromImgFile(path);
	
	//для jpg обязательно нужны размеры, иначе пикает
	Obs_GetInputImageSize (obj, &w, &h);
	Obs_SetOutputImageSize (obj, w, h);
	
	Obs_Start(obj);
	
	
	img = HObj2IMGHDR(obj);
	Obs_DestroyObject(obj);
	
	return img;
}

void DrawIMGHDR(IMGHDR *img, int x, int y, int w, int h)
{
	RECT rc;
	DRWOBJ drwobj;
	StoreXYWHtoRECT(&rc, x, y, w, h);
	SetPropTo_Obj5(&drwobj, &rc, 0, img);
	SetColor(&drwobj, NULL, NULL);
	DrawObject(&drwobj);
}

void DrawIMGHDR_2(IMGHDR *img, int x, int y, int x2, int y2, int bleed_x, int bleed_y)
{
	RECT rc;
	DRWOBJ drwobj;
	StoreXYXYtoRECT(&rc, x, y, x2, y2);
	SetProp2ImageOrCanvas(&drwobj, &rc, 0, img, bleed_x, bleed_y);
	SetColor(&drwobj, NULL, NULL);
	DrawObject(&drwobj);
}

void FreeIMGHDR(IMGHDR *img)
{
	if (img)
	{
		if (img->bitmap)
			mfree(img->bitmap);
		mfree(img);
	}
}

unsigned int GetWidthWS(WSHDR *ws, const int font)
{
	return (Get_WS_width(ws, font) + 1);
}