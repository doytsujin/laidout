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
/********* impositions.cc: ****************/

//----------------<< Builtin Imposition Instances >>--------------------
//
//This file's main purpose is to define GetBuiltinImpositionPool.
//
//To compile in your own imposition types, you must:
// 1. Write code, compile and put its object file in ???
// 2. Include its header here,
// 3. push an initial instance onto existingpool in function GetBuiltinImpositionPool
// 
//--- 



#include "../laidout.h"
#include "imposition.h"
#include "impositioninst.h"
#include "netimposition.h"

using namespace Laxkit;

//! Return a new Imposition instance that is type impos.
/*! \ingroup objects
 * Searches laidout->impositionpool, and returns a duplicate of
 * the imposition or NULL.
 */
Imposition *newImposition(const char *impos)
{
	if (!impos) return NULL;
	int c;
	for (c=0; c<laidout->impositionpool.n; c++) {
		if (!strcmp(impos,laidout->impositionpool.e[c]->Stylename())) {
			return (Imposition *)laidout->impositionpool.e[c]->duplicate();
		}
	}
	return NULL;
}

//**** new Impositions might want to install various novel Style/Styledefs,
//	***** or other initializations might have to occur... more thought required here!!
/*! \fn Laxkit::PtrStack<Imposition> *GetBuiltinImpositionPool(Laxkit::PtrStack<Imposition> *existingpool)
 * \ingroup pools
 */
//! Return a stack of defined impositions.
/*! blah
 *
 */
PtrStack<Imposition> *GetBuiltinImpositionPool(PtrStack<Imposition> *existingpool) //existingpool=NULL
{
	if (!existingpool) { // create new pool if you are not appending to an existing one.
		existingpool=new PtrStack<Imposition>;
	}

	existingpool->push(new Singles(),1);
	existingpool->push(new DoubleSidedSingles(),1);
	existingpool->push(new BookletImposition(),1);
	existingpool->push(new NetImposition(),1);
	//existingpool->push(new CompositeImposition(),1);
	//existingpool->push(new BasicBook(),1);
	//existingpool->push(new AnyOtherSpecificImpositionsYouWantBuiltIn,1);
	//...

	return existingpool;
}
