//
// $Id$
//	
// Laidout, for laying out
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
// Copyright (c) 2004-2007 Tom Lechner
//
#ifndef EPSUTILS_H
#define EPSUTILS_H

#include <lax/doublebbox.h>
#include <Imlib2.h>


int scaninEPS(FILE *f, Laxkit::DoubleBBox *bbox, char **title, char **date, 
		char **preview, int *depth, int *width, int *height);
Imlib_Image EpsPreviewToImlib(const char *preview, int width, int height, int depth);
int WriteEpsPreviewAsPng(const char *fullgspath,
						 const char *epsfile, int epsw, int epsh,
						 const char *previewfile, int maxw, int maxh,
						 char **error_ret);

#endif

