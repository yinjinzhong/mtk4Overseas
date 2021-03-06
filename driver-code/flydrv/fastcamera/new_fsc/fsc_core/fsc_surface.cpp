#include <windows.h>
#include <ddraw.h>
#include "tvd_drv_if.h"
#include "platform.h"
#include "fsc_surface.h"
#include "fsc_tvd.h"

BOOL  UpdateBackCarOverlay(PVDO_BUF_INFO_T pVdoBufInfo);

#define MTK1_INFO_T VDO_BUF_INFO_T 
static DDPIXELFORMAT ddpfOverlayFormats[] = {
	{sizeof(DDPIXELFORMAT), DDPF_RGB, 0, 16,  0xF800, 0x07e0, 0x001F, 0},         // 16-bit RGB 5:6:5
    {sizeof(DDPIXELFORMAT), DDPF_FOURCC, MAKEFOURCC('M','T','K','1'),0,0,0,0,0},  // YUYV
};

static LPDIRECTDRAW                g_pDD = NULL;        // DirectDraw object
static LPDIRECTDRAWSURFACE         g_pDDSPrimary = NULL;// DirectDraw primary surface
LPDIRECTDRAWSURFACE                g_pDDSVideo = NULL; // The overlay primary.
static LPDIRECTDRAWSURFACE         g_pDDSGraphic = NULL; // The overlay primary.

#define BACKCAR_START_MASK          (1 << 0)
#define AV_START_MASK               (1 << 1)

extern DWORD *g_pfgBackcarAVStart; 
extern HANDLE g_hBackcarAvEvent;


static void ReleaseAllObjects(void)
{

/*
	if(g_pDDSGraphic != NULL)
	{
	    g_pDDSGraphic->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);
		g_pDDSGraphic->Release();
		g_pDDSGraphic = NULL;
		RETAILMSG(TRUE,(TEXT("Release Graphic Surface Success!")));
	}
*/
	if (g_pDDSVideo != NULL)
	{
		g_pDDSVideo->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);
		g_pDDSVideo->Release();
		g_pDDSVideo = NULL;
		RETAILMSG(TRUE,(TEXT("[%s]Release Video Surface Success!\r\n"),__FUNCTION__));
	}
	if (g_pDDSPrimary != NULL)
	{
		g_pDDSPrimary->Release();
		g_pDDSPrimary = NULL;
	}
	if (g_pDD != NULL)
	{
		g_pDD->Release();
		g_pDD = NULL;
	}
}



BOOL  InitDDraw(HWND hWnd)
{
	DDSURFACEDESC			   ddsd;
	HRESULT 				   hRet;
	DDCAPS					   ddcaps;
	LPBYTE	pDDVideoBuffer = NULL;

    if (g_pDD)
		return TRUE;
  hRet = DirectDrawCreate(NULL, &g_pDD, NULL);
 if (hRet != DD_OK)
 {
	 RETAILMSG(TRUE, (TEXT("DirectDrawCreate FAILED")));
	 goto EXIT;
 }
 
 // Get exclusive mode
 hRet = g_pDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL/*DDSCL_FULLSCREEN */);
 if (hRet != DD_OK)
 {
	 RETAILMSG(TRUE,(TEXT("SetCooperativeLevel FAILED")));
	 goto EXIT;
 }
 
 
 memset(&ddsd, 0, sizeof(ddsd));
 ddsd.dwSize = sizeof(ddsd);
 
 ddsd.dwFlags = DDSD_CAPS  ;
 ddsd.ddsCaps.dwCaps =	DDSCAPS_PRIMARYSURFACE ;
 //ddsd.dwBackBufferCount = 1;
 hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSPrimary, NULL);
 if (hRet != DD_OK)
 {
	 if (hRet == DDERR_NOFLIPHW)
	 {
		 RETAILMSG(TRUE,(TEXT("******** Display driver doesn't support flipping surfaces. ********")));
	 }
	 RETAILMSG(TRUE,(TEXT("CreateSurface FAILED")));
	 goto EXIT;
 }
 
 RETAILMSG(TRUE,(TEXT("Create pramary surface success\r\n")));
 // See if we can support overlays.
 
 memset(&ddcaps, 0, sizeof(ddcaps));
 ddcaps.dwSize = sizeof(ddcaps);
 hRet = g_pDD->GetCaps(&ddcaps, NULL);
 if (hRet != DD_OK)
 {
	 RETAILMSG(TRUE,(TEXT("GetCaps FAILED")));
	 goto EXIT;
	 
 }
 if (ddcaps.dwOverlayCaps == 0)
 {
	 RETAILMSG(TRUE,(TEXT("Overlays are not supported in hardware!")));
	 goto EXIT;
 }
 
 if (ddcaps.dwOverlayCaps & DDOVERLAYCAPS_OVERLAYSUPPORT)
	 RETAILMSG(TRUE,(TEXT(" Supports overlay surfaces.\r\n")));
 
 EXIT:

	return (TRUE);
}

BOOL   CreateBackCarUISurface(HWND hWnd)
{

 DDSURFACEDESC				ddsd;
 HRESULT					hRet;
 RECT	 rc;

 LPBYTE  pDDVideoBuffer = NULL;

 ///////////////////////////////////////////////////////////////////////////
 // Create the main DirectDraw object
 ///////////////////////////////////////////////////////////////////////////
 InitDDraw(hWnd);

  rc.left = 0;
  rc.top = 0;
 
  rc.right = 800 - rc.left;
  rc.bottom = 480 -rc.top;
 
 
  // Create the overlay Graphic surface. We will attempt the pixel formats
  // in our table one at a time until we find one that jives.
 
  memset(&ddsd, 0, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
 
  ddsd.ddsCaps.dwCaps = DDSCAPS_OVERLAY ;
  ddsd.dwFlags =   DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH  | DDSD_PIXELFORMAT   ;
  ddsd.dwWidth = 800;
  ddsd.dwHeight = 480;
 // ddsd.dwBackBufferCount = 1;
 
 
  ddsd.ddpfPixelFormat = ddpfOverlayFormats[0];
  hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSGraphic, NULL);
 
 
  hRet = g_pDDSGraphic->Lock(&rc,&ddsd,DDLOCK_WRITEONLY,NULL);
 
  if (hRet != DD_OK)
  {
	  RETAILMSG(TRUE,(TEXT("Lock primary surface FAILED")));
	  goto EXIT;
  }
  FSTC_GUIInit((UINT16 *)ddsd.lpSurface);
  BC_SetBkColor(RGB_565(0,0,31));
 
  g_pDDSGraphic->Unlock(&rc);
 #if  0
  memset(&ovfx, 0, sizeof(ovfx));
  ovfx.dwSize = sizeof(ovfx);
  ovfx.dckSrcColorkey.dwColorSpaceLowValue= ((UINT32)(0<<11 | 0<<5 | 31)); // BLUE as the color key
  ovfx.dckSrcColorkey.dwColorSpaceHighValue=((UINT32)(0<<11 | 0<<5 | 31));
 
  
  hRet = g_pDDSGraphic->UpdateOverlay(&rc, g_pDDSPrimary, &rc, DDOVER_HIDE | DDOVER_KEYSRCOVERRIDE, &ovfx);
  if (hRet != DD_OK)
  {
	  RETAILMSG(1, (TEXT("UPDATE OVERLAY Failed %x DD_OK[%d]\r\n"),hRet,DD_OK));  
	  goto EXIT;
  }
  #endif

EXIT:
 
	 if (hRet != DD_OK)
	 {
		ReleaseAllObjects();
		return FALSE;
	 }
	 return TRUE;

 return TRUE;
}

BOOL  DetectVideoSurfaceAvailable(HWND hWnd)
{

	DDSURFACEDESC			   ddsd;
	HRESULT 				   hRet;
	RECT	rc;
	LPBYTE	pDDVideoBuffer = NULL;

	InitDDraw(hWnd);

	g_dwVdoFrameWidth = 720;
	g_dwVdoFrameHeight = 480;

	// Create the overlay Video surface. We will attempt the pixel formats
	// in our table one at a time until we find one that jives.
   
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.ddsCaps.dwCaps = DDSCAPS_OVERLAY | DDSCAPS_FLIP;
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH  | DDSD_PIXELFORMAT | DDSD_BACKBUFFERCOUNT;

	ddsd.dwWidth = g_dwVdoFrameWidth;
	ddsd.dwHeight = g_dwVdoFrameHeight;

	//Temp solution for stable image display.
	ddsd.dwBackBufferCount = 1;

	rc.left = 0;
	rc.top = 0;

	rc.right = g_dwVdoFrameWidth - rc.left;
	rc.bottom = g_dwVdoFrameHeight - rc.top;


	ddsd.ddpfPixelFormat = ddpfOverlayFormats[1];
	hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSVideo, NULL);
	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable to create overlay surface!\r\n")));
		goto EXIT;
	}
	
    
	
	//If destination rectangle is null, the overlay surface output window seems will be full screen.[mtk40136]
	hRet = g_pDDSVideo->UpdateOverlay(&rc, g_pDDSPrimary, NULL, DDOVER_SHOW, NULL);
	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable  Update Video Overlay!")));
		goto EXIT;
	}
	
EXIT:

	if (hRet != DD_OK)
	{
	   DestroyBackCarVideoSurfaces();
	   return FALSE;
	}
	DestroyBackCarVideoSurfaces();
	return TRUE;     
    
}
BOOL   CreateBackCarSurfaces(HWND hWnd, PVDO_BUF_INFO_T pVdoBufInfo, UINT32 u4BufCnt)
{

	DDSURFACEDESC			   ddsd;
	HRESULT 				   hRet;
	RECT	rc;
	UINT32 i;
	LPBYTE	pDDVideoBuffer = NULL;

	InitDDraw(hWnd);
#if 0
	g_dwVdoFrameWidth = 720;
	g_dwVdoFrameHeight = 480;
#endif
	// Create the overlay Video surface. We will attempt the pixel formats
	// in our table one at a time until we find one that jives.
    if (g_pDDSVideo)
		return TRUE;
	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.ddsCaps.dwCaps = DDSCAPS_OVERLAY | DDSCAPS_FLIP;
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH  | DDSD_PIXELFORMAT | DDSD_BACKBUFFERCOUNT;

	ddsd.dwWidth = g_dwVdoFrameWidth;
	ddsd.dwHeight = g_dwVdoFrameHeight;

	//Temp solution for stable image display.
	ddsd.dwBackBufferCount = u4BufCnt;

	rc.left = 0;
	rc.top = 0;

	rc.right = g_dwVdoFrameWidth - rc.left;
	rc.bottom = g_dwVdoFrameHeight - rc.top;


	ddsd.ddpfPixelFormat = ddpfOverlayFormats[1];
	hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSVideo, NULL);
	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable to create overlay surface!\r\n")));
		goto EXIT;
	}
	
    // Assign vdo buffer address to vdp flip before updateoverlay.
    for (i = 0; i < TVD_VDO_BUF_CNT; i++ )
    {
	    UpdateBackCarOverlay(&pVdoBufInfo[i]);
    }
	
	UpdateBackCarOverlay(&pVdoBufInfo[0]);
	
	//If destination rectangle is null, the overlay surface output window seems will be full screen.[mtk40136]
	hRet = g_pDDSVideo->UpdateOverlay(&rc, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);
	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable  Update Video Overlay!")));
		goto EXIT;
	}
	
EXIT:

	if (hRet != DD_OK)
	{
	   DestroyBackCarVideoSurfaces();
	   return FALSE;
	}
	return TRUE;
}


BOOL DestroyBackCarVideoSurfaces()
{
    RETAILMSG(1,(TEXT("[fastcamera] DestroyVideoSurfaces\r\n")));

	if (g_pDDSVideo != NULL)
	{
		g_pDDSVideo->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);
		g_pDDSVideo->Release();
		g_pDDSVideo = NULL;
		RETAILMSG(TRUE,(TEXT("Release Video Surface Success!")));
	}

	return TRUE;
}


BOOL DestroyBackCarUISurfaces()
{
	if(g_pDDSGraphic != NULL)
	{
	    g_pDDSGraphic->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);
		g_pDDSGraphic->Release();
		g_pDDSGraphic = NULL;
		RETAILMSG(TRUE,(TEXT("Release Graphic Surface Success!")));
	}
	
	RETAILMSG(TRUE, (TEXT("[fastcamera]DestroyBackCarWindow finished[%d]\r\n")));

	return TRUE;
}

BOOL DestroyBackCarSurfaces()
{
	ReleaseAllObjects();
	RETAILMSG(TRUE, (TEXT("[fastcamera]DestroyBackCarWindow finished[%d]\r\n")));

	return TRUE;
}

extern "C" BOOL   ShowBackCarUIOverlay()
{
	 RECT	 rc; 
	 DDOVERLAYFX	 ovfx;
	 HRESULT					hRet;
	
	 rc.left = 0;
	 rc.top = 0;
	
	 rc.right = 800 - rc.left;
	 rc.bottom = 480 -rc.top;
	
	
	 memset(&ovfx, 0, sizeof(ovfx));
	 ovfx.dwSize = sizeof(ovfx);
	 ovfx.dckSrcColorkey.dwColorSpaceLowValue= ((UINT32)(0<<11 | 0<<5 | 31)); // BLUE as the color key
	 ovfx.dckSrcColorkey.dwColorSpaceHighValue=((UINT32)(0<<11 | 0<<5 | 31));
	 ovfx.dwAlphaConst = 0x0;//0x89 modify by jdp 20120821
	 ovfx.dwAlphaConstBitDepth = 16;
	if(g_pDDSGraphic != NULL)
	{
		hRet = g_pDDSGraphic->UpdateOverlay(&rc, g_pDDSPrimary, &rc, DDOVER_SHOW | DDOVER_KEYSRCOVERRIDE | DDOVER_ALPHACONSTOVERRIDE, &ovfx);
	   
		RETAILMSG(TRUE,(TEXT("Show Graphic Surface Success!\r\n")));
	}


	return TRUE;


      
}
BOOL   ShowBackCarOverlay()
{
	
	RECT    rc;	
	HRESULT hRet = DD_OK;

	rc.left = 0;
	rc.top = 0;

	rc.right = 800 - rc.left;
	rc.bottom = 480 -rc.top;
	
    if (g_pfgBackcarAVStart != NULL)
    {
        RETAILMSG(1, (TEXT("[BCLIB]set backcar start for avswitch\r\n")));
         *g_pfgBackcarAVStart  |= (BACKCAR_START_MASK);
    }

    if (g_pfgBackcarAVStart != NULL && (*g_pfgBackcarAVStart & AV_START_MASK))
    {
        WaitForSingleObject(g_hBackcarAvEvent, 1000);
        ResetEvent(g_hBackcarAvEvent);
    }

   if (g_pDDSVideo != NULL)
   {
	   hRet = g_pDDSVideo->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_SHOW, NULL);
	   
   }
   if(hRet == DD_OK)	
   	{
       RETAILMSG(TRUE,(TEXT("Show Video Surface Success!\r\n")));
	   return TRUE;
   	}
   
   else
   	{
       RETAILMSG(TRUE,(TEXT("Show Video Surface Failed!\r\n")));
	   return FALSE;
   	}
   
}


BOOL  HideBackCarVideoOverlay(VOID)
{
	HRESULT hRet ;

	if(NULL == g_pDDSVideo)
		return FALSE;	

	
	RETAILMSG(TRUE,(TEXT("[FSC_Surface] Hide Video Overlay!")));
	hRet = g_pDDSVideo->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);

	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable  Update Video Overlay!")));
		return (FALSE);
	}

  if (g_pfgBackcarAVStart != NULL)
  {
      RETAILMSG(1, (TEXT("[BCLIB]set backcar stop for avswitch\r\n")));
      *g_pfgBackcarAVStart  &= ~(BACKCAR_START_MASK);
  }

	return (TRUE);
}


BOOL  HideBackCarOverlay(VOID)
{
	HRESULT hRet = g_pDDSVideo->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);

	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable  Update Video Overlay!")));
		return (FALSE);
	}
	
	if(g_pDDSGraphic != NULL)
	{
		g_pDDSGraphic->UpdateOverlay(NULL, g_pDDSPrimary, NULL, DDOVER_HIDE, NULL);
	   
		RETAILMSG(TRUE,(TEXT("Hide Graphic Surface Success!")));
	}
	return (TRUE);
}



BOOL  UpdateBackCarOverlay(PVDO_BUF_INFO_T pVdoBufInfo)
{    
	RECT            rc;
	DDSURFACEDESC   ddsdSrc;    
	HRESULT hRet;
	BOOL    bRet = FALSE;
    LPBYTE  pDDVideoBuffer = NULL;

    if(NULL == g_pDDSVideo)
		return FALSE;
	
	memset(&ddsdSrc, 0, sizeof(ddsdSrc));
	ddsdSrc.dwSize = sizeof(ddsdSrc);

	
	rc.left = 0;
	rc.top = 0;

    rc.right = g_dwVdoFrameWidth - rc.left;
	rc.bottom = g_dwVdoFrameHeight - rc.top;




	hRet = g_pDDSVideo->Lock(&rc,&ddsdSrc,DDLOCK_WAITNOTBUSY,NULL);
	if (hRet != DD_OK)
	{
		RETAILMSG(TRUE,(TEXT("Unable to Lock Video Surface buffer!")));
		goto EXIT;
	}

	pDDVideoBuffer =(LPBYTE)ddsdSrc.lpSurface;

	memcpy(pDDVideoBuffer,pVdoBufInfo,sizeof(VDO_BUF_INFO_T));
	
	g_pDDSVideo->Unlock(&rc);
	g_pDDSVideo->Flip(NULL,0);
	bRet = TRUE;

EXIT:;
	return bRet;

}


