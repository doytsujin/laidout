//
// $Id$
//	
// Laidout, for laying out
// Copyright (C) 2004-2006 by Tom Lechner
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// For more details, consult the COPYING file in the top directory.
//
// Please consult http://www.laidout.org about where to send any
// correspondence about this software.
//
#ifndef SPREADEDITOR_H
#define SPREADEDITOR_H

#include <lax/interfaces/viewerwindow.h>
#include <lax/interfaces/pathinterface.h>
#include "document.h"
#include "drawdata.h"

//----------------------- LittleSpread --------------------------------------

class LittleSpread : public LaxInterfaces::SomeData
{
 public:
	int what;
	Spread *spread; // holds the outline, etc..
	LaxInterfaces::PathsData *connection;
	int lowestpage,highestpage;
	LittleSpread *prev,*next;
	LittleSpread(Spread *sprd, LittleSpread *prv);
	virtual ~LittleSpread();
	virtual int pointin(flatpoint pp,int pin=1);
	virtual void mapConnection();
	virtual void FindBBox();
};

//----------------------- PageLabel --------------------------------------

class PageLabel
{
 public:
	int labeltype; //plain label, circled, highlighted circle, etc..
	int pagenumber;
	char *labelbase,*label;
	PageLabel(int pnum,const char *nlabel="#",int ninfo=0);
	virtual ~PageLabel();
	virtual const char *Label() { return label; }
	virtual const char *Label(const char *nlabel,int ninfo=-1);
	virtual void UpdateLabel();
	virtual void Pagenum(int np);
};

//----------------------- SpreadInterface --------------------------------------
class SpreadEditor;

class SpreadInterface : public LaxInterfaces::InterfaceWithDp
{
 protected:
	int centerlabels;
	char drawthumbnails;
	int arrangetype;
	int mx,my,firsttime;
	int reversebuttons;
	int curpage, dragpage;
	LittleSpread *curspread;
	//SpreadView *view;
	//char dataislocal; 
	Laxkit::PtrStack<LittleSpread> spreads;
	Laxkit::PtrStack<PageLabel> pagelabels;
	int *temppagemap;
	//Laxkit::PtrStack<TextBlock> notes;
 public:
	Document *doc;
	Project *project;
	unsigned int style;
	unsigned long controlcolor;
	SpreadInterface(Laxkit::Displayer *ndp,Project *proj,Document *docum);
	virtual ~SpreadInterface();
	virtual int rLBDown(int x,int y,unsigned int state,int count);
	virtual int rLBUp(int x,int y,unsigned int state);
	virtual int rMBDown(int x,int y,unsigned int state,int count);
	virtual int rMBUp(int x,int y,unsigned int state);
	virtual int LBDown(int x,int y,unsigned int state,int count);
	virtual int LBUp(int x,int y,unsigned int state);
	virtual int MBDown(int x,int y,unsigned int state,int count);
	virtual int MBUp(int x,int y,unsigned int state);
//	//virtual int RBDown(int x,int y,unsigned int state,int count);
//	//virtual int RBUp(int x,int y,unsigned int state);
	virtual int MouseMove(int x,int y,unsigned int state);
	virtual int CharInput(unsigned int ch,unsigned int state);
	virtual int CharRelease(unsigned int ch,unsigned int state);
	virtual int Refresh();
//	//virtual int DrawData(Laxkit::anObject *ndata,int info=0);
//	//virtual int UseThis(Laxkit::anObject *newdata,unsigned int); // assumes not use local
//	//virtual void Clear();
//	//virtual void deletedata();
	virtual int InterfaceOn();
//	//virtual int InterfaceOff();
	virtual const char *whattype() { return "SpreadInterface"; }
	virtual const char *whatdatatype() { return "LittleSpread"; }

	virtual void GetSpreads();
	virtual void ArrangeSpreads(int how=-1);
	virtual int findPage(int x,int y);
	virtual int findSpread(int x,int y,int *page=NULL);
	virtual void Center(int w=1);
	virtual void drawLabel(int x,int y,PageLabel *plabel);

	virtual void Reset();
	virtual void ApplyChanges();
	virtual void SwapPages(int previouspos, int newpos);
	virtual void SlidePages(int previouspos, int newpos);

	friend class SpreadEditor;
};

//----------------------- SpreadEditor --------------------------------------

class SpreadEditor : public LaxInterfaces::ViewerWindow
{
 protected:
	Document *doc;
	Project *project;
 public:
	SpreadEditor(Laxkit::anXWindow *parnt,const char *ntitle,unsigned long nstyle,
						int xx, int yy, int ww, int hh, int brder,
						Project *project, Document *ndoc);
	virtual int init();
	virtual int CharInput(unsigned int ch,unsigned int state);
	virtual int ClientEvent(XClientMessageEvent *e,const char *mes);
	virtual int MoveResize(int nx,int ny,int nw,int nh);
	virtual int Resize(int nw,int nh);
};

#endif

