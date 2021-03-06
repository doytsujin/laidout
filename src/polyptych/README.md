Polyptych
---------
Everything in this directory is released under the Gnu Public License, version 2.0

This directory is for an opengl based 3-d shape unwrapper, and related 
image to polyedron renderers. This comprises these things:

 1. Polyptych, a standalone opengl based polyhedron unwrapper
 2. spheretocube, a command line sphere image to cube faces renderer
 3. spheretopoly, a command line sphere image to random polyhedron renderer
 4. convertahedron, command line utility to convert between various things Polyhedron class understands.


At some point, the things here will most likely be separated from Laidout
into its own project, and Laidout will use libraries from that project.

Polyptych depends on Graphicsmagick++, Laxkit, Opengl, and FTGL.  
Spheretopoly depends on Graphicsmagick++, and the Laxkit.  
Spheretocube depends on Graphicsmagick++, and only vectors.o from the Laxkit.  
Convertahedron depends on only the Laxkit.  

For a recent debian system, these extra dependencies can be installed (as root) with the
following, for ubuntu, do "sudo apt-get" instead:

    apt-get install libgraphicsmagick++1-dev mesa-common-dev libglu1-mesa-dev libftgl-dev

To make the standalone versions (first "cd src"):

    make polyptych
    make spheretocube
    make spheretopoly
    make convertahedron

Alternately, you can create a deb style package from the top directory with this:

    dpkg-buildpackage -rfakeroot
